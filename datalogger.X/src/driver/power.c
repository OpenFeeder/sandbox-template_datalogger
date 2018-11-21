/**
 * @file 
 * @author 
 * @version
 * @date
 * @revision
 * @dependency 
 */

#include "power.h"

bool powerOnUsbDevice() 
{
    // Power on the voltage regulator U5 (MIC39101 - 5.0YM)
    _LATB13 = 1;
    _LATF0 = 0; // powered the USB connector
    _TRISF0 = 0;
    
    LED_STATUS_R_SetHigh( );
    
    printf("\tPower on USB\n");
    while ( !( UART1_StatusGet( ) & UART1_TX_COMPLETE ) )
    {
    // Wait for the tranmission to complete
    }
    
    return true;
}

bool powerOffUsbDevice() 
{
    _TRISF0 = 1;
    // Power off the voltage regulator U5 (MIC39101 - 5.0YM)
    _LATB13 = 0;
    
    LED_STATUS_R_SetLow( );
    
    printf("\tPower off USB\n");
    while ( !( UART1_StatusGet( ) & UART1_TX_COMPLETE ) )
    {
    // Wait for the tranmission to complete
    }
    
    return true;
}

/*******************************************************************************
 End of File
 */
