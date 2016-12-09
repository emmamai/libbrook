/* Compass Service definitions */

#ifndef _COMPASS_SERVICE_H_

typedef int32_t CompassHeading;

enum CompassStatus {
	CompassStatusUnavailable,
	CompassStatusDataInvalid,
	CompassStatusCalibrating,
	CompassStatusCalibrated
}
struct CompassHeadingData {
	CompassHeading magnetic_heading;
	CompassHeading true_heading;
	CompassStatus compass_status;
	bool is_declination_valid;
}

typedef void(* CompassHeadingHandler)( CompassHeadingData heading );

int compass_service_set_heading_filter( CompassHeading filter );
void compass_service_subscribe( CompassHeadingHandler handler );
void compass_service_unsubscribe( void );
int compass_service_peek( CompassHeadingData *data );

#define _COMPASS_SERVICE_H_
#endif