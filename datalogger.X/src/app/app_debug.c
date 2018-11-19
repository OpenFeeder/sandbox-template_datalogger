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

//void displayBootMessage( void )
//{
////    printf( "\n\n================ OpenFeeder ================\n\t" );
////    displayFirmwareVersion( );
////    printf( "\t" );
////    displayBuildDateTime( );
////    printf( "\tFor board v3.0\n" );
////    printf( "============================================\n\t" );
////    displayUniqueDeviceId( );
////    printf( "============================================\n" );
////    printf( "\tWeb page: https://github.com/OpenFeeder\n" );
////    printf( "\tMail: contact.openfeeder@gmail.com\n" );
////    printf( "============================================\n" );
////    printf( "\tType [?] key to display debug options.\n" );
////    printf( "============================================\n\n" );
//}



void APP_SerialDebugTasks( void )
{
//    uint16_t dc_pwm;
//    int i;
//    bool flag;
//    FILEIO_DRIVE_PROPERTIES drive_properties;
//
    if ( UART1_TRANSFER_STATUS_RX_DATA_PRESENT & UART1_TransferStatusGet( ) )
    {
        /* If there is at least one byte of data has been received. */
        uint8_t data_from_uart1 = UART1_Read( );

        switch ( data_from_uart1 )
        {
//            case ',':
//            case '?':
//                /* Interface firmware terminal (Debug) */
//                printf( "Key mapping:\n" );
//
//                printf( " f or F: flush data on USB device\n" );
//                //                printf( "> g or G: NOT USED\n" );
//                printf( " h or H: firmware & hardware information\n" );
//                printf( " j or J: files I/O on USB device\n" );
//                printf( "   - c or C: display CSV files\n" );
//                printf( "   - e or E: display errors file\n" );
//                printf( "   - i or I: display CONFIG.INI\n" );
//                printf( "   - l or L: list files\n" );
//                printf( "   - x or X: export files\n" );
//                printf( " k or K: USB device properties\n" );
//                printf( " q or Q: check status LEDs\n" );
//                break;
//
//            case 'f':
//            case 'F':
//
//                /* Flush data on USB device */
//
//                flushDataOnUsbDevice( );
//
//                break;
//                /* -------------------------------------------------------------- */
//
//            case 'h':
//            case 'H':
//
//                /* Hardware information */
//
//                /* Display external interrupt and timers states */
//                printf( "\tExternal interrupt states\n" );
//                printf( "\t\tINT0: %d\n", IEC0bits.INT0IE );
//                printf( "\t\tINT1: %d\n", IEC1bits.INT1IE );
//                printf( "\t\tINT2: %d\n", IEC1bits.INT2IE );
//                printf( "\t\tINT3: %d\n", IEC3bits.INT3IE );
//                printf( "\t\tINT4: %d\n", IEC3bits.INT4IE );
//
//                printf( "\n\tTimers\n" );
//                printf( "\t\tTimer2: %d\n", T2CONbits.TON );
//                printf( "\t\tTimer3: %d\n", T3CONbits.TON );
//                printf( "\t\tTimer4: %d\n", T4CONbits.TON );
//
//                /* Display all commands values */
//                printf( "\n\tPower commands\n" );
//                if ( CMD_VDD_ACC_PIR_SERVO_GetValue( ) == 1 )
//                {
//                    printf( "\t\tCMD_VDD_ACC_PIR: on\n" );
//                }
//                else
//                {
//                    printf( "\t\tCMD_VDD_ACC_PIR: off\n" );
//                }
//
//                if ( _TRISF1 )
//                {
//                    printf( "\t\tCMD_VCC_SERVO: off\n" );
//                }
//                else
//                {
//                    printf( "\t\tCMD_VCC_SERVO: on\n\n" );
//                }
//
//                if ( CMD_VDD_APP_V_USB_GetValue( ) == 0 )
//                {
//                    printf( "\t\tCMD_VDD_APP: off\n" );
//                }
//                else
//                {
//                    printf( "\t\tCMD_VDD_APP: on\n" );
//                }
//
//                if ( CMD_VDD_USB_GetValue( ) == 1 )
//                {
//                    printf( "\t\tCMD_VDD_USB: off\n" );
//                }
//                else
//                {
//                    printf( "\t\tCMD_VDD_USB: on\n\n" );
//                }
//                if ( CMD_VCC_IR_GetValue( ) == 1 )
//                {
//                    printf( "\t\tCMD_VCC_IR: off\n" );
//                }
//                else
//                {
//                    printf( "\t\tCMD_VCC_IR: on\n\n" );
//                }
//                if ( CMD_3V3_RF_GetValue( ) == 1 )
//                {
//                    printf( "\t\tCMD_3V3_RF: on\n" );
//                }
//                else
//                {
//                    printf( "\t\tCMD_3V3_RF: off\n" );
//                }
//
//                printf( "\n\tOutput compare\n" );
//                printf( "\t\tOC4: %d\n", OC4CON1bits.OCM );
//                printf( "\t\tOC4R: %d\n", OC4R );
//                printf( "\t\tOC4RS: %d\n\n", OC4RS );
//                printf( "\t\tOC5: %d\n", OC5CON1bits.OCM );
//                printf( "\t\tOC5R: %d\n", OC5R );
//                printf( "\t\tOC5RS: %d\n", OC5RS );
//
//                /* Display USB device status */
//                printf( "\n\tUSB device status: " );
//                printUSBHostDeviceStatus( );
//                putchar( '\n' );
//                break;
//                /* -------------------------------------------------------------- */
//
//            case 'j':
//            case 'J':
//            {
//                /* Files I/O on USB device */
//
//                uint8_t user_choice;
//
//                while ( false == ( UART1_TRANSFER_STATUS_RX_DATA_PRESENT & UART1_TransferStatusGet( ) ) );
//                user_choice = UART1_Read( );
//
//                switch ( user_choice )
//                {
//
//                    case 'C':
//                    case 'c':
//
//                        displayCsvFiles( );
//                        break;
//
//                    case 'e':
//                    case 'E':
//
//                        displayErrorsFile( );
//                        break;
//
//                    case 'i':
//                    case 'I':
//
//                        displayIniFile( );
//                        break;
//
//                    case 'L':
//                    case 'l':
//
//                        listFilesOnUsbDevice( );
//                        break;
//
//                    case 'x':
//                    case 'X':
//
//                        exportAllFiles( );
//                        break;
//
//                    default:
//                        break;
//
//                }
//
//                break;
//            }
//                /* -------------------------------------------------------------- */
//
//            case 'k':
//            case 'K':
//
//                /* Get USB device properties */
//                printf( "\tPlease wait, process is slow\n\t(approx. 7s per GB of drive space)\n" );
//
//                setLedsStatusColor( LED_USB_ACCESS );
//
//                usbMountDrive( );
//
//                drive_properties.new_request = true;
//                do
//                {
//                    FILEIO_DrivePropertiesGet( &drive_properties, 'A' );
//                }
//                while ( drive_properties.properties_status == FILEIO_GET_PROPERTIES_STILL_WORKING );
//
//                if ( FILEIO_GET_PROPERTIES_NO_ERRORS == drive_properties.properties_status )
//                {
//                    printf( "\tUSB device properties\n" );
//                    if ( 1 == drive_properties.results.disk_format )
//                    {
//                        printf( "\t\tDrive format: FAT12\n" );
//                    }
//                    else if ( 2 == drive_properties.results.disk_format )
//                    {
//                        printf( "\t\tDrive format: FAT16\n" );
//                    }
//                    else if ( 3 == drive_properties.results.disk_format )
//                    {
//                        printf( "\t\tDrive format: FAT32\n" );
//                    }
//                    else
//                    {
//                        printf( "\t\tDrive format: unknown (%d)\n", drive_properties.results.disk_format );
//                    }
//                    printf( "\t\tSector size: %u\n", drive_properties.results.sector_size );
//                    printf( "\t\tSector per cluster: %u\n", drive_properties.results.sectors_per_cluster );
//                    printf( "\t\tTotal clusters: %lu\n", drive_properties.results.total_clusters );
//                    printf( "\t\tFree clusters: %lu\n", drive_properties.results.free_clusters );
//                    printf( "\t\tTotal space: %lu MB\n", drive_properties.results.total_clusters * drive_properties.results.sectors_per_cluster * drive_properties.results.sector_size / 1024 / 1024 );
//                    printf( "\t\tFree space: %lu MB\n\n", drive_properties.results.free_clusters * drive_properties.results.sectors_per_cluster * drive_properties.results.sector_size / 1024 / 1024 );
//                }
//                else
//                {
//                    printf( "\tUSB device properties\n\t\tGet properties failed (%d)\n\n", drive_properties.properties_status );
//                }
//
//                usbUnmountDrive( );
//                break;
//                /* -------------------------------------------------------------- */
//
            case 'q':
            case 'Q':
                /* Check status LEDs */
                checkLedsStatus( );

                break;
                /* -------------------------------------------------------------- */

            case 't':
            case 'T':
            {
                
                struct tm current_time;
                
                RTCC_TimeGet(&current_time);
    
                printf( "%02u/%02u/20%02u %02u:%02u:%02u\n",
                        current_time.tm_mday,
                        current_time.tm_mon,
                        current_time.tm_year,
                        current_time.tm_hour,
                        current_time.tm_min,
                        current_time.tm_sec );
    
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


/*******************************************************************************
 End of File
 */
