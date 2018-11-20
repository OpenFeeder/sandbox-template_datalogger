/**
 * @file app_debug.h
 * @author OpenFeeder Team <https://github.com/orgs/OpenFeeder/people>
 * @version 1.0
 * @date 06/07/2016
 */

#ifndef _APP_DEBUG_HEADER_H
#define _APP_DEBUG_HEADER_H

#include <stdint.h>
#include "../framework/fileio/fileio.h"
#include "../framework/usb/usb.h"
#include "../framework/usb/usb_host_msd_scsi.h"

/**
 * Section: Global Variable Definitions
 */
#define UART1_BUFFER_SIZE  4

void displayBootMessage( void );
//void displayResetRegisters( void );
void APP_SerialDebugTasks( void );
//void printUSBHostDeviceStatus( void );
uint16_t readIntFromUart1( void );
void daves_putU1( const char * , unsigned int );
    
#endif /* _APP_DEBUG_HEADER_H */


/*******************************************************************************
 End of File
 */
