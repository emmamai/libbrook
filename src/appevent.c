#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <appevent.h>

void app_event_loop( void ) {
	int fd_max = 0;
	fd_set set;
	time_t rawtime;
	struct tm *current_time;
	TimeUnits time_units;

	while( true ) {

		if ( _tick_timer_socket > fd_max )
			fd_max = _tick_timer_socket;

		FD_ZERO( &set );
		if ( _tick_timer_socket > 0 )
			FD_SET( _tick_timer_socket, &set );
		
		if ( select( fd_max + 1, &set, NULL, NULL, NULL ) > 0 ) {
			if ( FD_ISSET( _tick_timer_socket , &set ) ) {
				if ( recv( _tick_timer_socket, &time_units, sizeof( time_units ), 0 ) < sizeof( time_units ) ) {
					perror( "read() failure handling tick timer\n" );
					exit( -1 );
				} else if ( _tick_timer_handler != NULL ){
					time( &rawtime );
					current_time = localtime( &rawtime );
					_tick_timer_handler( current_time, time_units );
				}
			}
		}
	}
}