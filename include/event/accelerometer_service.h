/* Accelerometer Service definitions */

#ifndef _ACCEL_SERVICE_H_

struct AccelData {
	int16_t x;
	int16_t y;
	int16_t z;
	bool did_vibrate;
	uint64_t timestamp;
}
struct AccelRawData {
	int16_t x;
	int16_t y;
	int16_t z;
}
enum AccelAxisType {
	ACCEL_AXIS_X,
	ACCEL_AXIS_Y,
	ACCEL_AXIS_Z
}
enum AccelSamplingRate {
	ACCEL_SAMPLING_10HZ = 10,
	ACCEL_SAMPLING_25HZ = 25,
	ACCEL_SAMPLING_50HZ = 50,
	ACCEL_SAMPLING_100HZ = 100
}

typedef void(* AccelDataHandler)( AccelData *data, uint32_t num_samples );
typedef void(* AccelRawDataHandler)( AccelRawData *data, uint32_t num_samples, uint64_t timestamp );
typedef void(* AccelTapHandler)( AccelAxisType axis, int32_t direction );

int accel_service_peek( AccelData * data ); /* in Pebble implementation, this cannot be used if subscribed to accel events*/
int accel_service_set_sampling_rate( AccelSamplingRate rate );
int accel_service_set_samples_per_update( uint32_t num_samples );
void accel_data_service_subscribe( uint32_t samples_per_update, AccelDataHandler handler );
void accel_data_service_unsubscribe( void );
int accel_tap_service_subscribe( AccelTapHandler handler );
void accel_tap_service_unsubscribe( void );
void accel_raw_data_service_subscribe( uint32_t samples_per_update, AccelRawDataHandler handler );
void accel_raw_data_service_unsubscribe( void );

#define _ACCEL_SERVICE_H_
#endif