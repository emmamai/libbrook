#ifndef _TICK_TIMER_SERVICE_H_

enum TimeUnits {
	SECOND_UNIT = 1,
	MINUTE_UNIT = 2,
	HOUR_UNIT = 4,
	DAY_UNIT = 8,
	MONTH_UNIT = 16,
	YEAR_UNIT = 32
}

typedef void(* TickHandler)( struct tm *tick_time, TimeUnits units_changed );
void tick_timer_service_subscribe( TimeUnits tick_units, TickHandler handler );
void tick_timer_service_unsubscribe( void );

#define _TICK_TIMER_SERVICE_H_
#endif 