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
#define FCY 8000000UL/2 // instruction cycle freq for XC16 - FIXME : Test and measure blink with __delay_ms( 10 ) to find right FCY value 
#include <libpic30.h>

#include "mcc_generated_files/system.h"
#include "mcc_generated_files/tmr1.h"
#include "mcc_generated_files/uart1.h"

#include "src/driver/led_status.h"
#include "src/driver/dht_sensor.h"

#include "src/app/app_debug.h"

#include "src/driver/../framework/usb/usb.h"
#include "src/driver/../framework/usb/usb_host_msd.h"

#include "src/app/app_host_msd_data_logger.h"

void powerUsbDevice(void);

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
    struct tm current_time;
    
    // initialize the device
    SYSTEM_Initialize( );

    FILEIO_Initialize();
    
    __delay_ms( 1 );
    printf( "Demo template datalogger\nread DHT22 sensor.\n\r" );
    while ( !( UART1_StatusGet( ) & UART1_TX_COMPLETE ) )
    {
        // Wait for the tranmission to complete
    }

    /* Status LED blinks */
    checkLedsStatus();

    /* Get current date and time */
    RTCC_TimeGet(&current_time);
    
    printf( "%02u/%02u/20%02u %02u:%02u:%02u\n",
            current_time.tm_mday,
            current_time.tm_mon,
            current_time.tm_year,
            current_time.tm_hour,
            current_time.tm_min,
            current_time.tm_sec );
    
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
    }
    
    printf( "Done\n" );

    powerUsbDevice();
    
    APP_HostMSDDataLoggerInitialize();
        
    while ( 1 )
    {
        // Add your application code
        
        /* Maintain Device Drivers. */
        USBTasks( );
        
//        APP_HostMSDDataLoggerTasks();
        
        APP_SerialDebugTasks( );
        
    }

    return 1;
}

void powerUsbDevice() 
{
    // Power on the voltage regulator U5 (MIC39101 - 5.0YM)
    _LATB13 = 1;
    _LATF0 = 0; // powered the USB connector
    _TRISF0 = 0;
}

/**
 End of File
 */

