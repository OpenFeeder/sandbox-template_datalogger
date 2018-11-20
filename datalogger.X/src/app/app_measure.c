/**
 * @file
 * @author
 * @version
 * @date 
 */

#include <stdio.h>
#include "app_measure.h"
#include "../../mcc_generated_files/tmr1.h"
#include "../../mcc_generated_files/uart1.h"

bool getMeasure( int16_t * measure)
{
    
    TMR1_Start();
    
    if ( 255 > *measure )
    {
        ++(*measure);
    }
    else
    {
        *measure = 0;
    }
    
    printf("\tMeasure: %d\n", *measure);
    while ( !( UART1_StatusGet( ) & UART1_TX_COMPLETE ) )
    {
    // Wait for the tranmission to complete
    } 
              
    TMR1_Stop();
    
    return true;
}
    

/*******************************************************************************
 End of File
 */
