/* 
 * File: app_usb.c
 * Author: OpenFeeder Team <https://github.com/orgs/OpenFeeder/people> 
 * Comments:
 * Revision history: 1
 */

#include "app_usb.h"

/* Interrupt handler for USB host. */
void __attribute__( ( interrupt, auto_psv ) ) _USB1Interrupt( )
{
    USB_HostInterruptHandler( );
}

bool usbMountDrive( void )
{
//    uint8_t success;
//    FILEIO_ERROR_TYPE errF;
             
//    /* Drive is already mounted. */
//    if ( USB_DRIVE_MOUNTED == appDataUsb.usb_drive_status )
//    {
//#if defined (USE_UART1_SERIAL_INTERFACE) && defined (DISPLAY_USB_INFO)
//        printf( "\tUSB drive already mounted\n" );
//#endif
//        /* Log event if required */
//        if ( true == appDataLog.log_events )
//        {
//           store_event(OF_ALREADY_MOUNTED_USB_DRIVE); 
//        }
//        
//        return USB_DRIVE_MOUNTED;
//    }
//
//    if ( USB_DEVICE_SUSPENDED == USBHostDeviceStatus( appDataUsb.device_address ) )
//    {
//        /* Log event if required */
//        if ( true == appDataLog.log_events )
//        {
//           store_event(OF_RESUME_USB_DRIVE); 
//        }  
//        // http://www.microchip.com/forums/m582058.aspx
//        // help_mla_usb.pdf => 1.4.2.1.1.14 USBHostResumeDevice Function            
//        success = USBHostResumeDevice( appDataUsb.device_address );
//        if ( USB_SUCCESS != success )
//        {
//            if ( USB_UNKNOWN_DEVICE == success )
//            {
//                sprintf( appError.message, "Device not found" );
//            }
//            else // USB_ILLEGAL_REQUEST
//            {
//                sprintf( appError.message, "Device cannot RESUME unless it is suspended" );
//            }
//            appError.current_line_number = __LINE__;
//            sprintf( appError.current_file_name, "%s", __FILE__ );
//            appError.number = ERROR_USB_MOUNT_DRIVE;
//
//            appDataUsb.usb_drive_status = ERROR_USB_RESUME_DEVICE;            
//            return appDataUsb.usb_drive_status;
//        }
//        else
//        {
//#if defined (USE_UART1_SERIAL_INTERFACE) && defined (DISPLAY_USB_INFO)
//            printf( "\tUSB device resumed\n" );
//#endif 
//        }
//    }
//    
//    /* Log event if required */
//    if ( true == appDataLog.log_events )
//    {
//       store_event(OF_MOUNT_USB_DRIVE); 
//    }
//    /* Attempt to mount the drive described by gUSBDrive as drive 'A'
//     * The deviceAddress parameter describes the USB address of the device;
//     * it is initialized by the application in the USB_ApplicationEventHandler
//     * function when a new device is detected.
//     */
//    errF = FILEIO_DriveMount( 'A', &gUSBDrive, &appDataUsb.device_address );
//    Nop( );
//    Nop( );
//    Nop( );
//    if ( FILEIO_ERROR_NONE != errF )
//    {
//        sprintf( appError.message, "Unable to mount drive (%u)", errF );
//        appError.current_line_number = __LINE__;
//        sprintf( appError.current_file_name, "%s", __FILE__ );
//        appError.number = ERROR_USB_MOUNT_DRIVE;
//        
//        appDataUsb.usb_drive_status = USB_DRIVE_NOT_MOUNTED;        
//        return appDataUsb.usb_drive_status;
//    }
//    
//    appDataUsb.usb_drive_status = USB_DRIVE_MOUNTED;
//    
//#if defined (USE_UART1_SERIAL_INTERFACE) && defined (DISPLAY_USB_INFO)
//    printf( "\tUSB drive mounted\n" );        
//#endif
//        
//    return appDataUsb.usb_drive_status;
    
    return false;
}

bool usbUnmountDrive( void )
{
//    uint8_t success;
    
//    /* Drive is already not mounted. */
//    if ( USB_DRIVE_NOT_MOUNTED == appDataUsb.usb_drive_status )
//    {
//#if defined (USE_UART1_SERIAL_INTERFACE) && defined (DISPLAY_USB_INFO)
//        printf( "\tUSB drive already unmounted\n" );
//#endif
//        /* Log event if required */
//        if ( true == appDataLog.log_events )
//        {
//           store_event(OF_ALREADY_UNMOUNTED_USB_DRIVE); 
//        }
//        
//        return appDataUsb.usb_drive_status;
//    }
//
//    /* Log event if required */
//    if ( true == appDataLog.log_events )
//    {
//       store_event(OF_UNMOUNT_USB_DRIVE); 
//    }
//    /* Unmount the drive since it is no longer in use. */
//    if ( FILEIO_RESULT_FAILURE == FILEIO_DriveUnmount( 'A' ) )
//    {
//        strcpy( appError.message, "Unable to unmount drive" );
//        appError.current_line_number = __LINE__;
//        sprintf( appError.current_file_name, "%s", __FILE__ );
//        appError.number = ERROR_USB_UNMOUNT_DRIVE;
//        
//        appDataUsb.usb_drive_status = USB_DRIVE_MOUNTED;
//        return appDataUsb.usb_drive_status;
//    }
//
//#if defined (USE_UART1_SERIAL_INTERFACE) && defined (DISPLAY_USB_INFO)
//    printf( "\tUSB drive unmounted\n" );
//#endif    
//    appDataUsb.usb_drive_status = USB_DRIVE_NOT_MOUNTED;
//
//    /* Log event if required */
//    if ( true == appDataLog.log_events )
//    {
//       store_event(OF_SUSPEND_USB_DRIVE); 
//    } 
//    // http://www.microchip.com/forums/m582058.aspx
//    // help_mla_usb.pdf => 1.4.2.1.1.18 USBHostSuspendDevice Function            
//    success = USBHostSuspendDevice( appDataUsb.device_address ); /* now no interrupt occur */
//    if ( USB_SUCCESS != success )
//    {
//        if ( USB_UNKNOWN_DEVICE == success )
//        {
//            strcpy( appError.message, "Unable to suspend drive: USB unknown device" );
//        }
//        else /* USB_ILLEGAL_REQUEST */
//        {
//            strcpy( appError.message, "Cannot suspend unless device is in normal run mode" );
//        }
//        appError.current_line_number = __LINE__;
//        sprintf( appError.current_file_name, "%s", __FILE__ );
//        appError.number = ERROR_USB_SUSPEND_DEVICE;
//        appDataUsb.usb_drive_status = USB_DRIVE_MOUNTED;
//    }
//    else
//    {
//#if defined (USE_UART1_SERIAL_INTERFACE) && defined (DISPLAY_USB_INFO)
//        printf( "\tUSB device suspended\n" );
//#endif 
//    }
//
//    return appDataUsb.usb_drive_status;
    
    return false;
}

bool USB_ApplicationEventHandler( uint8_t address, USB_EVENT event, void *data, uint32_t size )
{
    
//    uint8_t success;
    
    switch ( ( int ) event )
    {

        case EVENT_DETACH:

            printf( "\tUSB: EVENT_DETACH\n" );

            return true;
            break;
            /* -------------------------------------------------------------- */

        case EVENT_RESUME:

            printf( "\tUSB: EVENT_RESUME\n" );

            return true;
            break;
            /* -------------------------------------------------------------- */
        case EVENT_SUSPEND:

            printf( "\tUSB: EVENT_SUSPEND\n" );

            return true;
            break;
            /* -------------------------------------------------------------- */
            
        case EVENT_HUB_ATTACH:

            printf( "\tUSB: EVENT_HUB_ATTACH\n" );

            return true;
            break;
            /* -------------------------------------------------------------- */

        case EVENT_STALL:

            printf( "\tUSB: EVENT_STALL\n" );

            return true;
            break;
            /* -------------------------------------------------------------- */

        case EVENT_VBUS_SES_REQUEST:
            /* This means that the device was removed. */

            printf( "\tUSB: EVENT_VBUS_SES_REQUEST\n" );

            return true;
            break;
            /* -------------------------------------------------------------- */

        case EVENT_VBUS_OVERCURRENT:
            /* This means that the device was removed. */

            printf( "\tUSB: EVENT_VBUS_OVERCURRENT\n" );

            return true;
            break;
            /* -------------------------------------------------------------- */

        case EVENT_VBUS_REQUEST_POWER:
            /* The data pointer points to a byte that represents the amount of power
             * requested in mA, divided by two.  If the device wants too much power,
             * we reject it.
             */

            printf( "\tUSB: EVENT_VBUS_REQUEST_POWER - Port: %u - Current: %u (x2mA)\n", ( ( USB_VBUS_POWER_EVENT_DATA* ) data )->port, ( ( USB_VBUS_POWER_EVENT_DATA* ) data )->current );

            return true;
            break;
            /* -------------------------------------------------------------- */

        case EVENT_VBUS_RELEASE_POWER:
            /* This means that the device was removed. */

            printf( "\tUSB: EVENT_VBUS_RELEASE_POWER - Port: %u\n", ( ( USB_VBUS_POWER_EVENT_DATA* ) data )->port );

            return true;
            break;
            /* -------------------------------------------------------------- */

        case EVENT_VBUS_POWER_AVAILABLE:
            /* This means that the device was removed. */

            printf( "\tUSB: EVENT_VBUS_POWER_AVAILABLE\n" );

            return true;
            break;
            /* -------------------------------------------------------------- */

        case EVENT_UNSUPPORTED_DEVICE:
            /* Here are various other events that a user might want to handle
             * or be aware of.  In this demo we are not handling them so we
             * will just return true to allow the stack to move on from the error.
             */

            printf( "\tUSB: EVENT_UNSUPPORTED_DEVICE\n" );

            return true;
            break;
            /* -------------------------------------------------------------- */

        case EVENT_CANNOT_ENUMERATE:

            printf( "\tUSB: EVENT_CANNOT_ENUMERATE\n" );

            return true;
            break;
            /* -------------------------------------------------------------- */

        case EVENT_CLIENT_INIT_ERROR:

            printf( "\tUSB: EVENT_CLIENT_INIT_ERROR\n" );

            return true;
            break;
            /* -------------------------------------------------------------- */

        case EVENT_OUT_OF_MEMORY:

            printf( "\tUSB: EVENT_OUT_OF_MEMORY\n" );

            return true;
            break;
            /* -------------------------------------------------------------- */

        case EVENT_UNSPECIFIED_ERROR:
            /* This should never be generated. */

            printf( "\tUSB: EVENT_UNSPECIFIED_ERROR\n" );

            return true;
            break;
            /* -------------------------------------------------------------- */

        case EVENT_OVERRIDE_CLIENT_DRIVER_SELECTION:
            /* This should never be generated. */

            printf( "\tUSB: EVENT_OVERRIDE_CLIENT_DRIVER_SELECTION\n" );

            return false;
            break;
            /* -------------------------------------------------------------- */

        case EVENT_1MS:
            /* This should never be generated. */

            printf( "\tUSB: EVENT_1MS\n" );

            return true;
            break;
            /* -------------------------------------------------------------- */

        case EVENT_ALT_INTERFACE:
            /* This should never be generated. */

            printf( "\tUSB: EVENT_ALT_INTERFACE\n" );

            return true;
            break;
            /* -------------------------------------------------------------- */

        case EVENT_HOLD_BEFORE_CONFIGURATION:
            /* This should never be generated. */

            printf( "\tUSB: EVENT_HOLD_BEFORE_CONFIGURATION\n" );

            break;
            /* -------------------------------------------------------------- */

        case EVENT_MSD_ATTACH:

            printf( "\tUSB: EVENT_MSD_ATTACH\n" );

            APP_MountDrive (address);
            
            break;
            /* -------------------------------------------------------------- */

        default:
#if defined (USE_UART1_SERIAL_INTERFACE) && defined (DISPLAY_USB_INFO)
            printf( "\tUSB: ??????? (%d)\n", ( int ) event );
#endif
            break;
    }

    return false;
}


/*******************************************************************************
 End of File
 */
