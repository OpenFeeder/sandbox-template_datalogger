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

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "../../mcc_generated_files/mcc.h"
#include "../framework/usb/usb.h"
#include "../framework/fileio/fileio.h"
#include "../framework/usb/usb_host_msd_scsi.h"
#include "../driver/led_status.h"

extern uint8_t g_deviceAddress;

//#define DISPLAY_USB_INFO
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
void APP_HostMSDDataLoggerInitialize();

/*********************************************************************
* Function: void APP_MountDrive (uint8_t address);
*
* Overview: Initializes the demo code
*
* PreCondition: None
*
* Input: address - Address of the USB device to mount
*
* Output: None
*
********************************************************************/
void APP_MountDrive(uint8_t address);

/*********************************************************************
* Function: void APP_HostMSDDataLoggerTasks(void);
*
* Overview: Keeps the demo running.
*
* PreCondition: The demo should have been initialized and started via
*   the APP_HostMSDDataLoggerInitialize() and APP_HostMSDDataLoggerStart() demos
*   respectively.
*
* Input: None
*
* Output: None
*
********************************************************************/
bool APP_HostMSDDataLoggerTasks( int16_t );

void GetTimestamp( FILEIO_TIMESTAMP * );

