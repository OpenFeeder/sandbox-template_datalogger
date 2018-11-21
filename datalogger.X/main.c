/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system intialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.75.1
        Device            :  PIC24FJ256GB406
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.35
        MPLAB 	          :  MPLAB X v5.10
 */

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
 */

/**
  Section: Included Files
 */
#include "mcc_generated_files/mcc.h"

//#define _XTAL_FREQ 8000000  // for XC8...
//#define FCY 8000000UL/2 // instruction cycle freq for XC16 - FIXME : Test and measure blink with __delay_ms( 10 ) to find right FCY value 
//#include <libpic30.h>

#include "mcc_generated_files/system.h"
#include "mcc_generated_files/tmr1.h"
#include "mcc_generated_files/uart1.h"
#include "src/driver/led_status.h"
#include "src/driver/dht_sensor.h"
#include "src/app/app_debug.h"
#include "src/driver/../framework/usb/usb.h"
#include "src/driver/../framework/usb/usb_host_msd.h"
#include "src/app/app_host_msd_data_logger.h"
#include "src/app/app_alarm.h" 
#include "src/app/app_measure.h" 
#include "src/driver/buttons.h"
#include "src/driver/power.h"

#define INFINITE_LOOP_MODE 0
#define SERIAL_COMMUNICATION_MODE 1

uint8_t mode = INFINITE_LOOP_MODE;
uint8_t previous_mode = SERIAL_COMMUNICATION_MODE;
    
//int main( void )
//{
//    TRISEbits.TRISE4 = 0; // RE04
//    while ( 1 )
//    {
//        LATEbits.LATE4 = 1;
//        __delay_ms( 250 );
//        LATEbits.LATE4 = 0;
//        __delay_ms( 250 );
//    }
//    return 0;
//}

/*
                         Main application
 */
int main( void )
{
    bool go_to_deep_sleep = true;
    bool is_measure_get = false;
    bool is_usb_powered = false;
    bool task_complete = false;
    int16_t measure = 0;   
    
    /* Initialize the device */
    SYSTEM_Initialize( );

    /* Initialize the file i/o process */
    FILEIO_Initialize();
    FILEIO_RegisterTimestampGet( GetTimestamp );

    /* Display boot message */
    displayBootMessage();

    /* Status LED blinks */
    checkLedsStatus();           
    
    /* Read DHT22 sensor */
    //INTERRUPT_GlobalInterruptDisable( ); // Disable the Global Interrupts
//    if ( true == DHT22_Detect( ) )
//    {
//        int i;
//
//        for ( i = 0; i < 40; ++i )
//        {
//            DHT22_readbit( );
//        }
//
//        printf( "Sensor data ready\n" );
//    }
//    else
//    {
//        printf( "Sensor default\n" );
//    }
    //INTERRUPT_GlobalInterruptEnable( );

        /* Initialize the USB Host API. */
    if ( !USBHostInit( 0 ) )
    {
        printf( "\nFailure to initialize USB Host API!\n" );
        printf( "HOST: Cannot allocate space for endpoint 0.\n" );
    }

    /* Stop timer 1 to avoid wake up during deep sleep */
    TMR1_Stop();
    
    /* Set alarm mask*/
    rtcc_set_alarm( EVERY_10_SECONDS );
    
    while ( 1 )
    {
        /* Go to deep sleep if required */     
        if ( true == go_to_deep_sleep )
        {
            printf("Deep sleep\n");
            while ( !( UART1_StatusGet( ) & UART1_TX_COMPLETE ) )
            {
            // Wait for the tranmission to complete
            }   

            setLedsStatusColor( LEDS_OFF );
            
            /* Enter deep sleep */
            DSCONbits.DSEN = 1;
            DSCONbits.DSEN = 1;

            Sleep( ); 
            
            /* Wake up*/
            printf("Wake up\n");
            while ( !( UART1_StatusGet( ) & UART1_TX_COMPLETE ) )
            {
            // Wait for the tranmission to complete
            } 
            
            if ( BUTTON_PRESSED == USER_BUTTON_GetValue( ) )
            {
                go_to_deep_sleep = false;
                is_usb_powered = false;
                mode = SERIAL_COMMUNICATION_MODE;
            }
            else
            {
                /* Initialize data logger stack*/
                APP_HostMSDDataLoggerInitialize();

                go_to_deep_sleep = false;
                is_measure_get = false;
                task_complete = false;
                is_usb_powered = false;
                mode = INFINITE_LOOP_MODE;                
            }
  
        }

        if (previous_mode != mode)
        {
            previous_mode = mode;
            if ( SERIAL_COMMUNICATION_MODE == mode)
            {
                printf("Enter serial mode\nTo quit, enter x or X, or press the reset button\n"); 
            }
            else
            {
                printf("Enter infinite loop mode\n"); 
            }
            while ( !( UART1_StatusGet( ) & UART1_TX_COMPLETE ) )
            {
            // Wait for the tranmission to complete
            } 
        }
        
        if ( INFINITE_LOOP_MODE == mode )
        {
            /* If no measure => get data from the sensor */
            if ( false == is_measure_get )
            {
                /* Get measure from sensor */
                is_measure_get = getMeasure(&measure); 
            }

            /* If measure available and USB power off => power on USB */
            if ( true == is_measure_get && false == is_usb_powered)
            {
                /* Power on USB device */
                is_usb_powered = powerOnUsbDevice();
            }

            /* If measure available and USB power on => run the datalogger */
            if ( true == is_measure_get && true == is_usb_powered)
            {
                /* Host data logger task*/
                task_complete = APP_HostMSDDataLoggerTasks( measure );            
            }

            /* If the data logger compete its task => go to deep sleep mode */
            if (true == task_complete )
            {
                /* Power off USB device */
                powerOffUsbDevice();   

                is_usb_powered = false;
                go_to_deep_sleep = true;
                
            }   
        }
        else
        {
            if ( false == is_usb_powered)
            {
                /* Power on USB device */
                is_usb_powered = powerOnUsbDevice();
            }
            else
            {
                APP_SerialDebugTasks( );            
            }
        }      
        
        /* Maintain Device Drivers. */
        USBTasks( );
    }

    return 1;
}

/**
 End of File
 */

