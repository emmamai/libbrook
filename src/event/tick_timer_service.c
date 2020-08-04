#include <appevent.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

void tick_timer_service_subscribe( TimeUnits tick_units, TickHandler handler ) {
	if ( _tick_timer_socket > 0 ) {
		close( _tick_timer_socket );
		_tick_timer_socket = -1;
	}
	if ( ( _tick_timer_socket = generic_service_connect( SERVICE_MGMT_PATH TICK_TIMER_SERVICE_MGMT_NAME ) ) < 0 )
		exit( errno );
	if ( send( _tick_timer_socket, &tick_units, sizeof( TimeUnits ), 0 ) < 0 ) {
		perror( "send() failure while subscribing to tick timer service" );
		close( _tick_timer_socket );
		exit( errno );
	}
	_tick_timer_handler = handler;
}

void tick_timer_service_unsubscribe( void ) {
	close( _tick_timer_socket );
	_tick_timer_handler = NULL;
}