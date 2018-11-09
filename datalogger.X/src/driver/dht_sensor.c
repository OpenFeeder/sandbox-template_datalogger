/**
 * @file dht_sensor.c
 * @author OpenFeeder Team <https://github.com/orgs/OpenFeeder/people>
 * @version 1.0
 * @date 08/11/2018
 */

#include <stdbool.h>

#define FCY 8000000UL/2 // instruction cycle freq for XC16 - FIXME : Test and measure blink with __delay_ms( 10 ) to find right FCY value 
#include <libpic30.h>

#include "../../mcc_generated_files/pin_manager.h"
#include "dht_sensor.h"

bool DHT22_Detect( void )
{
    bool acknowledge_sensor;

    DHT22_SENSOR_SetLow( );
    DHT22_SENSOR_SetDigitalOutput( );
    __delay_ms( 1 );
    DHT22_SENSOR_SetDigitalInput( );
    __delay_us( 80 );

    LED_STATUS_R_SetHigh( );
    acknowledge_sensor = DHT22_SENSOR_GetValue( );
    LED_STATUS_R_SetLow( );

    __delay_us( 50 ); // waiting for end sensor response process

    if ( 0 == acknowledge_sensor )
    {
        return true;
    }

    return false;
}

void DHT22_readbit( void )
{
    while ( 1 == DHT22_SENSOR_GetValue( ) );
    while ( 0 == DHT22_SENSOR_GetValue( ) );

    __delay_us( 50 );

    //LED_STATUS_R_SetHigh( );
    if ( 0 == DHT22_SENSOR_GetValue( ) )
    {
        //        EUSART_Write( '0' );
        Nop( );
    }
    else
    {
        //        EUSART_Write( '1' );
        Nop( );
    }
    //LED_STATUS_R_SetLow( );
}


/*******************************************************************************
 End of File
 */
