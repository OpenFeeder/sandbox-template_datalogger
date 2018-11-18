/**
 * @file app_timers_callback.h
 * @author OpenFeeder Team <https://github.com/orgs/OpenFeeder/people>
 * @version 1.0
 * @date
 */

#ifndef _APP_TIMERS_CALLBACK_HEADER_H
#define _APP_TIMERS_CALLBACK_HEADER_H

#include "../../mcc_generated_files/mcc.h"

// *****************************************************************************
// *****************************************************************************
// Section: Constants
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: extern declarations
// *****************************************************************************
// *****************************************************************************

extern volatile uint16_t g_timeout_x100ms;
extern volatile uint16_t g_timeout_standby_x20ms;
extern volatile uint16_t g_timeout_em4095_x20ms;
extern volatile uint16_t g_timeout_leds_status_x20ms;
extern volatile uint8_t g_timeout_taking_reward;
extern volatile uint8_t g_timeout_punishment_x20ms;


// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************
/* These routines are called by drivers when certain events occur.
 */
void TMR1_CallBack( void );

#endif /* _APP_TIMERS_CALLBACK_HEADER_H */


/*******************************************************************************
 End of File
 */
