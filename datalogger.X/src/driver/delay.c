/**
 * @file delay.c
 * @author OpenFeeder Team <https://github.com/orgs/OpenFeeder/people>
 * @version 1.0
 * @date
 * @revision history 1
 * @dependency tmr3 --> ISR every 20 ms
 */

#include "delay.h"
#include "../app/app_timers_callback.h"

/* Not blocking delay function, can be used with this project. */

void setDelayMs( uint16_t timeout_ms )
{
    if ( timeout_ms < 100 )
    {
        g_timeout_x100ms = 1;
    }
    else
    {
        g_timeout_x100ms = timeout_ms / 100;
    }
}

bool isDelayMsEnding( void )
{
    if ( g_timeout_x100ms == 0 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

void setDelayMsLEDsStatus( uint16_t timeout_ms )
{
    if ( timeout_ms < 100 )
    {
        g_timeout_leds_status_x20ms = 1;
    }
    else
    {
        g_timeout_leds_status_x20ms = timeout_ms / 100;
    }
}

bool isDelayMsEndingLEDsStatus( void )
{
    if ( g_timeout_leds_status_x20ms == 0 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*******************************************************************************
 End of File
 */
