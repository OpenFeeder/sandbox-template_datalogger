/**
 * @file app_debug.c
 * @author OpenFeeder Team <https://github.com/orgs/OpenFeeder/people>
 * @version 1.0
 * @date 06/07/2016
 * @revision history 3
 */

#include <ctype.h>
#include "app_debug.h"
#include "../framework/usb/usb.h"
#include "../../mcc_generated_files/uart1.h"
#include "../driver/led_status.h"
#include "../app/app_host_msd_data_logger.h"
#include "../app/app_alarm.h"
#include "../driver/power.h"

uint8_t g_deviceAddress;

void displayBootMessage( void )
{
    printf( "\n\n================= OpenFeeder =================\n\t" );
    printf("\t Datalogger demo\n");
//    displayFirmwareVersion( );
//    printf( "\t" );
//    displayBuildDateTime( );
//    printf( "\tFor board v3.0\n" );
//    printf( "============================================\n\t" );
//    displayUniqueDeviceId( );
    printf( "==============================================\n" );
    printf( "    Web page: https://github.com/OpenFeeder\n" );
    printf( "    Mail: contact.openfeeder@gmail.com\n" );
    printf( "==============================================\n" );
    printf( "    Type [?] key to display debug options.\n" );
    printf( "==============================================\n\n" );
}



void APP_SerialDebugTasks( void )
{

    if ( UART1_TRANSFER_STATUS_RX_DATA_PRESENT & UART1_TransferStatusGet( ) )
    {
        /* If there is at least one byte of data has been received. */
        uint8_t data_from_uart1 = UART1_Read( );

        switch ( data_from_uart1 )
        {
            case ',':
            case '?':
                /* Interface firmware terminal (Debug) */
                printf( "Key mapping:\n" );
                
                printf( " a or A: display alarm interval\n" ); 
                printf( " f or F: display files list\n" );
                printf( " l or L: display LOG.CSV content\n" );
//                printf( " p or P: pause the datalogger\n" );
//                printf( " r or R: run the datalogger\n" );
                printf( " q or Q: check status LEDs\n" );
                printf( " t or T: get current time\n" );
//                printf( " t or T: get current time\n" );
                printf( " x or X: reset system\n" );

                break;

            case 'a':
            case 'A':
            {
                
                switch ( RTCCON1Hbits.AMASK )
                {
                    case ONCE_A_YEAR:
                        printf("Once a year\n");
                        break;
                    case ONCE_A_MONTH:
                        printf("Once a month\n");
                        break;
                    case ONCE_A_WEEK:
                        printf("Once a week\n");
                        break;
                    case EVERY_DAY:
                        printf("Once a day\n");
                        break;
                    case EVERY_HOUR:
                        printf("Every hour\n");
                        break;
                    case EVERY_10_MINUTES:
                        printf("Every 10 minutes\n");
                        break;
                    case EVERY_MINUTE:
                        printf("Every minute\n");
                        break;
                    case EVERY_10_SECONDS:
                        printf("Every 10 seconds\n");
                        break;
                    case EVERY_SECOND:
                        printf("Every second\n");
                        break;
                    case EVERY_HALF_SECOND:
                        printf("Every half second\n");
                        break;
                }
                        
                break;
            }                   

            case 'F':
            case 'f':
            {
                FILEIO_SEARCH_RECORD searchRecord;
                int8_t result;
                static char ch[FILEIO_EXPORT_BUFFER_SIZE];
                
                // Declare a FILEIO_DRIVE_CONFIG structure to describe which functions the File I/O library will use to communicate with the media
                const FILEIO_DRIVE_CONFIG gUSBDrive =
                {
                    (FILEIO_DRIVER_IOInitialize)NULL,                     // Function to initialize the I/O pins used by the driver.
                    (FILEIO_DRIVER_MediaDetect)USBHostMSDSCSIMediaDetect,                   // Function to detect that the media is inserted.
                    (FILEIO_DRIVER_MediaInitialize)USBHostMSDSCSIMediaInitialize,           // Function to initialize the media.
                    (FILEIO_DRIVER_MediaDeinitialize)USBHostMSDSCSIMediaDeinitialize,              // Function to de-initialize the media.
                    (FILEIO_DRIVER_SectorRead)USBHostMSDSCSISectorRead,                     // Function to read a sector from the media.
                    (FILEIO_DRIVER_SectorWrite)USBHostMSDSCSISectorWrite,                   // Function to write a sector to the media.
                    (FILEIO_DRIVER_WriteProtectStateGet)USBHostMSDSCSIWriteProtectState,    // Function to determine if the media is write-protected.
                };

                if ( FILEIO_ERROR_NONE != FILEIO_DriveMount ('A', &gUSBDrive, &g_deviceAddress) )
                {
                    printf("Unable to mount drive");
                    return;                    
                }
                
                LED_STATUS_B_SetHigh( ); 
                
                result = FILEIO_Find( "*.*", FILEIO_ATTRIBUTE_ARCHIVE, &searchRecord, true );

                
                if ( FILEIO_RESULT_SUCCESS == result )
                {

                    sprintf( ch, "\t%s", searchRecord.shortFileName );
                    daves_putU1( ch, strlen( ch ) );
                    sprintf( ch, " (%ld bytes)\r\n", searchRecord.fileSize );
                    daves_putU1( ch, strlen( ch ) );

                    while ( FILEIO_RESULT_SUCCESS == FILEIO_Find( "*.*", FILEIO_ATTRIBUTE_ARCHIVE, &searchRecord, false ) )
                    {

                        sprintf( ch, "\t%s", searchRecord.shortFileName );
                        daves_putU1( ch, strlen( ch ) );
                        sprintf( ch, " (%ld bytes)\r\n", searchRecord.fileSize );
                        daves_putU1( ch, strlen( ch ) );

                    }

                }
                else
                {

//                    displayFileErr( ( char * ) searchRecord.shortFileName, false );

                }

                if ( FILEIO_ERROR_NONE != FILEIO_DriveUnmount ('A') )
                {
                    printf("Unable to unmount drive");
                    return;
                }

                LED_STATUS_B_SetLow( ); 
    
                break;
            }
                
            case 'L':
            case 'l':
            {
                FILEIO_SEARCH_RECORD searchRecord;
                int8_t result;
                FILEIO_OBJECT file;
                static char ch[FILEIO_EXPORT_BUFFER_SIZE];

                memset( ch, '\0', sizeof (ch ) );

                // Declare a FILEIO_DRIVE_CONFIG structure to describe which functions the File I/O library will use to communicate with the media
                const FILEIO_DRIVE_CONFIG gUSBDrive =
                {
                    (FILEIO_DRIVER_IOInitialize)NULL,                     // Function to initialize the I/O pins used by the driver.
                    (FILEIO_DRIVER_MediaDetect)USBHostMSDSCSIMediaDetect,                   // Function to detect that the media is inserted.
                    (FILEIO_DRIVER_MediaInitialize)USBHostMSDSCSIMediaInitialize,           // Function to initialize the media.
                    (FILEIO_DRIVER_MediaDeinitialize)USBHostMSDSCSIMediaDeinitialize,              // Function to de-initialize the media.
                    (FILEIO_DRIVER_SectorRead)USBHostMSDSCSISectorRead,                     // Function to read a sector from the media.
                    (FILEIO_DRIVER_SectorWrite)USBHostMSDSCSISectorWrite,                   // Function to write a sector to the media.
                    (FILEIO_DRIVER_WriteProtectStateGet)USBHostMSDSCSIWriteProtectState,    // Function to determine if the media is write-protected.
                };

                if ( FILEIO_ERROR_NONE != FILEIO_DriveMount ('A', &gUSBDrive, &g_deviceAddress) )
                {
                    printf("Unable to mount drive");
                    return;                    
                }
                
                LED_STATUS_B_SetHigh( );

                result = FILEIO_Find( "LOG.CSV", FILEIO_ATTRIBUTE_ARCHIVE, &searchRecord, true );

                if ( FILEIO_RESULT_SUCCESS == result )
                {

                    sprintf( ch, "\r\n" );
                    daves_putU1( ch, strlen( ch ) );
                    sprintf( ch, "\r\nContent of %s\r\n", searchRecord.shortFileName );
                    daves_putU1( ch, strlen( ch ) );

                    result = FILEIO_Open( &file, ( char * ) searchRecord.shortFileName, FILEIO_OPEN_READ );

                    if ( FILEIO_RESULT_SUCCESS == result )
                    {

                        while ( false == FILEIO_Eof( &file ) )
                        {

                            memset( ch, '\0', sizeof (ch ) );
                            FILEIO_Read( ch, 1, FILEIO_EXPORT_BUFFER_SIZE - 1, &file );
                            daves_putU1( ch, strlen( ch ) );

                        }
                        FILEIO_Close( &file );
                        sprintf( ch, "\r\n" );
                        daves_putU1( ch, strlen( ch ) );
                    }
                    else
                    {

//                        displayFileErr( ( char * ) searchRecord.shortFileName, false );

                    }  

                }
                else
                {

//                    displayFileErr( "20??????.CSV", false );

                }

                if ( FILEIO_ERROR_NONE != FILEIO_DriveUnmount ('A') )
                {
                    printf("Unable to unmount drive");
                    return;
                }
                
                LED_STATUS_B_SetLow( );
                
                break;
            }
                
            case 'q':
            case 'Q':
                /* Check status LEDs */
                TMR1_Start();
                checkLedsStatus( );
                TMR1_Stop();

                break;
                /* -------------------------------------------------------------- */
                
            case 's':
            case 'S':
            {
                /* Set RTCC module date and time value. */
                struct tm date_time;

                date_time.tm_mday = (int)readIntFromUart1( );
                if ( ( date_time.tm_mday > 31 ) || ( date_time.tm_mday == 0 ) )
                {
                    date_time.tm_mday = 1;
                }                

                date_time.tm_mon = (int)readIntFromUart1( );
                if ( ( date_time.tm_mon > 12 ) || ( date_time.tm_mon == 0 ) )
                {
                    date_time.tm_mon = 1;
                }      

                date_time.tm_year = (int)readIntFromUart1( );
                if ( date_time.tm_year > 99 )
                {
                    date_time.tm_year = 0;
                }     

                date_time.tm_hour = (int)readIntFromUart1( );
                if ( date_time.tm_hour > 23 )
                {
                    date_time.tm_hour = 0;
                }

                date_time.tm_min = (int)readIntFromUart1( );
                if ( date_time.tm_min > 59 )
                {
                    date_time.tm_min = 0;
                }

                date_time.tm_sec = (int)readIntFromUart1( );
                if ( date_time.tm_sec > 59 )
                {
                    date_time.tm_sec = 0;
                }
                
                printf( "%d\n", date_time.tm_mday );
                printf( "%d\n", date_time.tm_mon );
                printf( "%d\n", date_time.tm_year );
                printf( "%d\n", date_time.tm_hour );
                printf( "%d\n", date_time.tm_min );
                printf( "%d\n", date_time.tm_sec );

                RTCC_TimeSet( &date_time );
    
                printf( "\nTime set.\n" );
                break;
            }
            /* -------------------------------------------------------------- */
                
            case 't':
            case 'T':
            {
                
                struct tm current_time;
                
                while ( false == RTCC_TimeGet( &current_time ) );
    
                printf( "%02u/%02u/20%02u %02u:%02u:%02u\n",
                        current_time.tm_mday,
                        current_time.tm_mon,
                        current_time.tm_year,
                        current_time.tm_hour,
                        current_time.tm_min,
                        current_time.tm_sec );
    
                break;
            }
            
            case 'x':
            case 'X':
            {
                uint8_t user_choice;

                printf( "Do you really want to reset the system? (y/n)\r\n" );

                while ( false == ( UART1_TRANSFER_STATUS_RX_DATA_PRESENT & UART1_TransferStatusGet( ) ) );
                user_choice = UART1_Read( );

                switch ( user_choice )
                {
                    case 'y':
                    case 'Y':
                    {
                        /* Power off USB device */
                        powerOffUsbDevice();  
                
                        /* Reset */
                        __asm__ volatile ( "reset" );
                        break;
                    }

                    default:
                        break;
                }

                break;
            }
                /* -------------------------------------------------------------- */
    
            default:
                putchar( data_from_uart1 ); /* echo RX data if doesn't match */
                break;
        }
    } /* end of if ( UART1_TRANSFER_STATUS_RX_DATA_PRESENT & UART1_TransferStatusGet( ) ) */
}

uint16_t readIntFromUart1( void )
{
    char rx_data_buffer[UART1_BUFFER_SIZE];
    uint8_t numBytes;

    numBytes = 0; /* initialized numBytes */
    do
    {
        if ( UART1_TRANSFER_STATUS_RX_DATA_PRESENT & UART1_TransferStatusGet( ) )
        {
            rx_data_buffer[numBytes] = UART1_Read( );

            /* if received <CR> the stop received */
            if ( '\r' == rx_data_buffer[numBytes] )
            {
                break;
            }

            /* if received data is not a numerical value then return 0 */
            if ( isdigit( rx_data_buffer[numBytes] ) == false )
            {
                return 0;
            }

            ++numBytes;
        }
    }
    while ( numBytes < UART1_BUFFER_SIZE );

    rx_data_buffer[numBytes + 1] = '\0'; /* add end of string */

    return ( int ) strtol( rx_data_buffer, NULL, 10 );
} /* End of readIntFromUart1( ) */


/**
 * Print the status of USBHostDeviceStatus()
 *  USB_DEVICE_ATTACHED                 - Device is attached and running
 *  USB_DEVICE_DETACHED                 - No device is attached
 *  USB_DEVICE_ENUMERATING              - Device is enumerating
 *  USB_HOLDING_OUT_OF_MEMORY           - Not enough heap space available
 *  USB_HOLDING_UNSUPPORTED_DEVICE      - Invalid configuration or unsupported class
 *  USB_HOLDING_UNSUPPORTED_HUB         - Hubs are not supported
 *  USB_HOLDING_INVALID_CONFIGURATION   - Invalid configuration requested
 *  USB_HOLDING_PROCESSING_CAPACITY     - Processing requirement excessive
 *  USB_HOLDING_POWER_REQUIREMENT       - Power requirement excessive
 *  USB_HOLDING_CLIENT_INIT_ERROR       - Client driver failed to initialize
 *  USB_DEVICE_SUSPENDED                - Device is suspended
 *  Other                               - Device is holding in an error state.
 *                                        The return value indicates the error.
 */
void printUSBHostDeviceStatus( void )
{
//    uint8_t status = USBHostDeviceStatus( appDataUsb.device_address );
//
//    switch ( status )
//    {
//        case USB_DEVICE_ATTACHED:
//            printf( "USB_DEVICE_ATTACHED" );
//            break;
//
//        case USB_DEVICE_DETACHED:
//            printf( "USB_DEVICE_DETACHED" );
//            break;
//
//        case USB_DEVICE_ENUMERATING:
//            printf( "USB_DEVICE_ENUMERATING" );
//            break;
//
//        case USB_HOLDING_OUT_OF_MEMORY:
//            printf( "USB_HOLDING_OUT_OF_MEMORY" );
//            break;
//
//        case USB_HOLDING_UNSUPPORTED_DEVICE:
//            printf( "USB_HOLDING_UNSUPPORTED_DEVICE" );
//            break;
//
//        case USB_HOLDING_UNSUPPORTED_HUB:
//            printf( "USB_HOLDING_UNSUPPORTED_HUB" );
//            break;
//
//        case USB_HOLDING_INVALID_CONFIGURATION:
//            printf( "USB_HOLDING_INVALID_CONFIGURATION" );
//            break;
//
//        case USB_HOLDING_PROCESSING_CAPACITY:
//            printf( "USB_HOLDING_PROCESSING_CAPACITY" );
//            break;
//
//        case USB_HOLDING_POWER_REQUIREMENT:
//            printf( "USB_HOLDING_POWER_REQUIREMENT" );
//            break;
//
//        case USB_HOLDING_CLIENT_INIT_ERROR:
//            printf( "USB_HOLDING_CLIENT_INIT_ERROR" );
//            break;
//
//        case USB_DEVICE_SUSPENDED:
//            printf( "USB_DEVICE_SUSPENDED" );
//            break;
//
//        default:
//            /* If nothing else matches, do the default. */
//            printf( "Device is holding in an error state! (%d)", status );
//            break;
//    }
} /* End of printUSBHostDeviceStatus( ) */

void daves_putU1( const char *buf, unsigned int num_to_transmit )
{
    /* https://www.microchip.com/forums/m1063767.aspx */
    /* https://www.microchip.com/forums/FindPost/1063897 */
    UART1_TRANSFER_STATUS status;
    unsigned int numBytes = 0;

    while ( numBytes < num_to_transmit )
    {
        status = UART1_TransferStatusGet( );
        if ( status & UART1_TRANSFER_STATUS_TX_EMPTY )
        {
            numBytes += UART1_WriteBuffer( ( uint8_t * ) ( buf + numBytes ), num_to_transmit - numBytes );
            if ( numBytes < num_to_transmit )
            {
                continue;
            }
            else
            {
                break;
            }
        }
        else
        {
            continue;
        }
    }

} // End of daves_putU1

/*******************************************************************************
 End of File
 */
