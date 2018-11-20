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

bool USB_ApplicationEventHandler( uint8_t address, USB_EVENT event, void *data, uint32_t size )
{
    
//    uint8_t success;
    
    switch ( ( int ) event )
    {

        case EVENT_DETACH:
#if defined (DISPLAY_USB_INFO)
            printf( "\tUSB: EVENT_DETACH\n" );
#endif
            return true;
            break;
            /* -------------------------------------------------------------- */

        case EVENT_RESUME:
#if defined (DISPLAY_USB_INFO)
            printf( "\tUSB: EVENT_RESUME\n" );
#endif
            return true;
            break;
            /* -------------------------------------------------------------- */
        case EVENT_SUSPEND:
#if defined (DISPLAY_USB_INFO)
            printf( "\tUSB: EVENT_SUSPEND\n" );
#endif
            return true;
            break;
            /* -------------------------------------------------------------- */
            
        case EVENT_HUB_ATTACH:
#if defined (DISPLAY_USB_INFO)
            printf( "\tUSB: EVENT_HUB_ATTACH\n" );
#endif
            return true;
            break;
            /* -------------------------------------------------------------- */

        case EVENT_STALL:
#if defined (DISPLAY_USB_INFO)
            printf( "\tUSB: EVENT_STALL\n" );
#endif
            return true;
            break;
            /* -------------------------------------------------------------- */

        case EVENT_VBUS_SES_REQUEST:
            /* This means that the device was removed. */
#if defined (DISPLAY_USB_INFO)
            printf( "\tUSB: EVENT_VBUS_SES_REQUEST\n" );
#endif
            return true;
            break;
            /* -------------------------------------------------------------- */

        case EVENT_VBUS_OVERCURRENT:
            /* This means that the device was removed. */
#if defined (DISPLAY_USB_INFO)
            printf( "\tUSB: EVENT_VBUS_OVERCURRENT\n" );
#endif
            return true;
            break;
            /* -------------------------------------------------------------- */

        case EVENT_VBUS_REQUEST_POWER:
            /* The data pointer points to a byte that represents the amount of power
             * requested in mA, divided by two.  If the device wants too much power,
             * we reject it.
             */
#if defined (DISPLAY_USB_INFO)
            printf( "\tUSB: EVENT_VBUS_REQUEST_POWER - Port: %u - Current: %u (x2mA)\n", ( ( USB_VBUS_POWER_EVENT_DATA* ) data )->port, ( ( USB_VBUS_POWER_EVENT_DATA* ) data )->current );
#endif
            return true;
            break;
            /* -------------------------------------------------------------- */

        case EVENT_VBUS_RELEASE_POWER:
            /* This means that the device was removed. */
#if defined (DISPLAY_USB_INFO)
            printf( "\tUSB: EVENT_VBUS_RELEASE_POWER - Port: %u\n", ( ( USB_VBUS_POWER_EVENT_DATA* ) data )->port );
#endif
            return true;
            break;
            /* -------------------------------------------------------------- */

        case EVENT_VBUS_POWER_AVAILABLE:
            /* This means that the device was removed. */
#if defined (DISPLAY_USB_INFO)
            printf( "\tUSB: EVENT_VBUS_POWER_AVAILABLE\n" );
#endif
            return true;
            break;
            /* -------------------------------------------------------------- */

        case EVENT_UNSUPPORTED_DEVICE:
            /* Here are various other events that a user might want to handle
             * or be aware of.  In this demo we are not handling them so we
             * will just return true to allow the stack to move on from the error.
             */
#if defined (DISPLAY_USB_INFO)
            printf( "\tUSB: EVENT_UNSUPPORTED_DEVICE\n" );
#endif
            return true;
            break;
            /* -------------------------------------------------------------- */

        case EVENT_CANNOT_ENUMERATE:
#if defined (DISPLAY_USB_INFO)
            printf( "\tUSB: EVENT_CANNOT_ENUMERATE\n" );
#endif
            return true;
            break;
            /* -------------------------------------------------------------- */

        case EVENT_CLIENT_INIT_ERROR:
#if defined (DISPLAY_USB_INFO)
            printf( "\tUSB: EVENT_CLIENT_INIT_ERROR\n" );
#endif
            return true;
            break;
            /* -------------------------------------------------------------- */

        case EVENT_OUT_OF_MEMORY:
#if defined (DISPLAY_USB_INFO)
            printf( "\tUSB: EVENT_OUT_OF_MEMORY\n" );
#endif
            return true;
            break;
            /* -------------------------------------------------------------- */

        case EVENT_UNSPECIFIED_ERROR:
            /* This should never be generated. */
#if defined (DISPLAY_USB_INFO)
            printf( "\tUSB: EVENT_UNSPECIFIED_ERROR\n" );
#endif
            return true;
            break;
            /* -------------------------------------------------------------- */

        case EVENT_OVERRIDE_CLIENT_DRIVER_SELECTION:
            /* This should never be generated. */
#if defined (DISPLAY_USB_INFO)
            printf( "\tUSB: EVENT_OVERRIDE_CLIENT_DRIVER_SELECTION\n" );
#endif
            return false;
            break;
            /* -------------------------------------------------------------- */

        case EVENT_1MS:
            /* This should never be generated. */
#if defined (DISPLAY_USB_INFO)
            printf( "\tUSB: EVENT_1MS\n" );
#endif
            return true;
            break;
            /* -------------------------------------------------------------- */

        case EVENT_ALT_INTERFACE:
            /* This should never be generated. */
#if defined (DISPLAY_USB_INFO)
            printf( "\tUSB: EVENT_ALT_INTERFACE\n" );
#endif
            return true;
            break;
            /* -------------------------------------------------------------- */

        case EVENT_HOLD_BEFORE_CONFIGURATION:
            /* This should never be generated. */
#if defined (DISPLAY_USB_INFO)
            printf( "\tUSB: EVENT_HOLD_BEFORE_CONFIGURATION\n" );
#endif
            break;
            /* -------------------------------------------------------------- */

        case EVENT_MSD_ATTACH:
#if defined (DISPLAY_USB_INFO)
            printf( "\tUSB: EVENT_MSD_ATTACH\n" );
#endif
            APP_MountDrive (address);
            
            break;
            /* -------------------------------------------------------------- */

        default:
#if defined (DISPLAY_USB_INFO)
            printf( "\tUSB: ??????? (%d)\n", ( int ) event );
#endif
            break;
    }

    return false;
}


/*******************************************************************************
 End of File
 */
