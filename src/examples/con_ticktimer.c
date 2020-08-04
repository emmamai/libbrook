#include <stdio.h>
#include <appevent.h>

void tick_handler( struct tm *tick_time, TimeUnits units_changed ) {
	printf( "Tick: %i:%i:%i\n", tick_time->tm_hour, tick_time->tm_min, tick_time->tm_sec );
}

static void init( void ) {
	tick_timer_service_subscribe( SECOND_UNIT, tick_handler );
}

static void deinit( void ) {
	tick_timer_service_unsubscribe();
}

int main( int argc, char** argv ) {
	init();
	app_event_loop();
	deinit();
}
