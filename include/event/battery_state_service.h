/* Battery State Service definitions */

#ifndef _BATTERY_SERVICE_H_

typedef struct BatteryChargeState {
	uint8_t charge_percent;
	bool is_charging;
	bool is_unplugged;
} BatteryChargeState;

typedef void(*BatteryStateHandler)( BatteryChargeState charge );

void battery_state_service_subscribe( BatteryStateHandler handler );
void battery_state_service_unsubscribe( void );
BatteryChargeState battery_state_service_peek( void );

#define _BATTERY_SERVICE_H_
#endif