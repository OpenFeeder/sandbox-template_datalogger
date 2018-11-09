/**
 * @file dht_sensor.h
 * @author OpenFeeder Team <https://github.com/orgs/OpenFeeder/people>
 * @version 1.0
 * @date 08/11/2018
 */

#ifndef __DHT_SENSOR_H
#define __DHT_SENSOR_H

// RE04 will be DHT22_DATA_WIRE on OpenFeeder board v3, name DHT22_SENSOR in this code

bool DHT22_Detect( void );

void DHT22_readbit( void );


#endif /* __DHT_SENSOR_H */


/*******************************************************************************
 End of File
 */
