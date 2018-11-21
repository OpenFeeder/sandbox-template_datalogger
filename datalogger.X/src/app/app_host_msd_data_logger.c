/*******************************************************************************
Copyright 2016 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

To request to license the code under the MLA license (www.microchip.com/mla_license), 
please contact mla_licensing@microchip.com
*******************************************************************************/

/** INCLUDES *******************************************************/

#include "app_host_msd_data_logger.h"
#include "../../mcc_generated_files/rtcc.h"

static FILEIO_OBJECT myFile;

typedef enum
{
    WAITING_FOR_ATTACH,
    MOUNTING_DRIVE,
    OPENING_FILE,
    WAITING_TO_WRITE,
    WRITING_TO_FILE,
    CLOSING_FILE,
    UNMOUNT_DRIVE,
    WAITING_FOR_DETACH,
    ERROR
} USB_HOST_MSD_DATA_LOGGER_DEMO_STATE;

typedef enum
{
    ERROR_NONE,
    ERROR_DRIVE_MOUNT_FAILED,
    ERROR_DRIVE_UNMOUNT_FAILED,        
    ERROR_FILE_OPEN_FAILED,
    ERROR_FILE_CLOSE_FAILED,    
    ERROR_FILE_WRITE_FAILED
} USB_ERROR;

static USB_HOST_MSD_DATA_LOGGER_DEMO_STATE demoState;
static USB_HOST_MSD_DATA_LOGGER_DEMO_STATE previous_demoState;
static volatile bool sampleRequested = false;
//static char printBuffer[10];
//static uint8_t blinkCount;

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

/*********************************************************************
* Function: void APP_HostMSDDataLoggerInitialize(void);
*
* Overview: Initializes the demo code
*
* PreCondition: None
*
* Input: None
*
* Output: None
*
********************************************************************/
void APP_HostMSDDataLoggerInitialize()
{
    demoState = WAITING_FOR_ATTACH;
    previous_demoState = WAITING_FOR_DETACH;
}

void APP_MountDrive(uint8_t address)
{
    if (demoState == WAITING_FOR_ATTACH)
    {
        g_deviceAddress = address;
        demoState = MOUNTING_DRIVE;
    }
}

/*********************************************************************
* Function: void APP_HostMSDDataLoggerTasks(void);
*
* Overview: Keeps the demo running.
*
* PreCondition: The demo should have been initialized via
*   the APP_HostMSDDataLoggerInitialize()  
*
* Input: None
*
* Output: None
*
********************************************************************/
bool APP_HostMSDDataLoggerTasks( int16_t measure )
{
    bool task_complete = false;
    char buffer[100];
    struct tm current_time;
    USB_ERROR error = ERROR_NONE;
    size_t num_data_written = 0;
    
    if(FILEIO_MediaDetect(&gUSBDrive, &g_deviceAddress) == false)
    {
        //The device has been removed.  Now we should wait for a new
        //  device to be attached.
        demoState = WAITING_FOR_ATTACH;
    }
    
    switch( demoState)
    {
        case WAITING_FOR_ATTACH:
            
            if (previous_demoState != demoState)
            {
                previous_demoState = demoState;
                printf("\t\tWAITING_FOR_ATTACH\n");
            }
            break;

        case MOUNTING_DRIVE:
        {      
            
            if (previous_demoState != demoState)
            {
                previous_demoState = demoState;
                printf("\t\tMOUNTING_DRIVE\n");
            }

            if( FILEIO_DriveMount ('A', &gUSBDrive, &g_deviceAddress) == FILEIO_ERROR_NONE)
            {
                LED_STATUS_B_SetHigh( );                
                demoState = OPENING_FILE;
            }
            else
            {
                error = ERROR_DRIVE_MOUNT_FAILED;
                demoState = ERROR;
            }
  
            break;
        }

        case OPENING_FILE:
            
            if (previous_demoState != demoState)
            {
                previous_demoState = demoState;
                printf("\t\tOPENING_FILE\n");
            }         
                
            if(FILEIO_Open(&myFile, "LOG.CSV", FILEIO_OPEN_WRITE | FILEIO_OPEN_CREATE | FILEIO_OPEN_APPEND) == FILEIO_RESULT_SUCCESS)
            {
                demoState = WRITING_TO_FILE;
            }
            else
            {
                error = ERROR_FILE_OPEN_FAILED;
                demoState = ERROR;
            }
            
            break;

        case WRITING_TO_FILE:
            
            if (previous_demoState != demoState)
            {
                previous_demoState = demoState;
                printf("\t\tWRITING_TO_FILE\n");
            }

            /* Get current date and time */
            while ( false == RTCC_TimeGet( &current_time ) );

            memset(buffer, '\0', sizeof(buffer));

            sprintf( buffer, "%02d/%02d/20%02d,%02d:%02d:%02d,%d\n",
                current_time.tm_mday,
                current_time.tm_mon,
                current_time.tm_year,
                current_time.tm_hour,
                current_time.tm_min,
                current_time.tm_sec,
                measure);

            num_data_written = FILEIO_Write( buffer, 1, strlen(buffer), &myFile );
            
            if ( num_data_written == strlen(buffer) )
            {            
                demoState = CLOSING_FILE;
            }
            else
            {
                error = ERROR_FILE_WRITE_FAILED;
                demoState = ERROR;
            }

            break;

        case CLOSING_FILE:
            
            if (previous_demoState != demoState)
            {
                previous_demoState = demoState;
                printf("\t\tCLOSING_FILE\n");
            }
            //Always make sure to close the file so that the data gets
            //  written to the drive.
            if ( FILEIO_Close(&myFile) == FILEIO_RESULT_SUCCESS)
            {
                demoState = UNMOUNT_DRIVE;                
            }
            else
            {
                error = ERROR_FILE_CLOSE_FAILED;
                demoState = ERROR;
            }
            
            break;

        case UNMOUNT_DRIVE:
            
            if (previous_demoState != demoState)
            {
                previous_demoState = demoState;
                printf("\t\tUNMOUNT_DRIVE\n");
            }
            // Unmount the drive since it is no longer in use.
            if (FILEIO_DriveUnmount ('A')  == FILEIO_ERROR_NONE )
            {

                LED_STATUS_B_SetLow( );
                //Now that we are done writing, we can do nothing until the
                //  drive is removed.

                task_complete = true;
            }
            else
            {
                error = ERROR_DRIVE_UNMOUNT_FAILED;
                demoState = ERROR;
            }
            break;
            
        case ERROR:
            
            switch (error)
            {                
                case ERROR_DRIVE_MOUNT_FAILED:
                    printf("\t\tERROR_DRIVE_MOUNT_FAILED\n");
                    break;
                case ERROR_DRIVE_UNMOUNT_FAILED:
                    printf("\t\tERROR_DRIVE_UNMOUNT_FAILED\n");
                    break;      
                case ERROR_FILE_OPEN_FAILED:
                    printf("\t\tERROR_FILE_OPEN_FAILED\n");
                    break;
                case ERROR_FILE_CLOSE_FAILED:
                    printf("\t\tERROR_FILE_CLOSE_FAILED\n");
                    break;   
                case ERROR_FILE_WRITE_FAILED:
                    printf("\t\tERROR_FILE_WRITE_FAILED\n");
                    break;
                default:
                    printf("\t\tERROR: %d\n", error);
                    break;
            }
            
            task_complete = true;
            break;

        default:
            break;
    }
    
    return task_complete;
}

void GetTimestamp( FILEIO_TIMESTAMP * timestamp )
{
    /* help_mla_fileio.pdf 
     * 1.7.1.3.32 FILEIO_TimestampGet Type */

    struct tm current_time;
    
    /* Get current date and time */
    RTCC_TimeGet(&current_time);

    timestamp->date.bitfield.day = current_time.tm_mday;
    timestamp->date.bitfield.month = current_time.tm_mon;
    timestamp->date.bitfield.year = current_time.tm_year + 20; // 2000-1980 = 20
    timestamp->time.bitfield.hours = current_time.tm_hour;
    timestamp->time.bitfield.secondsDiv2 = current_time.tm_sec / 2;
    timestamp->time.bitfield.minutes = current_time.tm_min;
    timestamp->timeMs = 0;
}
