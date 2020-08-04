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

#define MAX_CLIENTS 256

unsigned int s, s2;

typedef struct client {
	bool connected;
	TimeUnits timeunits;
	int socket;
	unsigned int len;
	struct sockaddr_un remote;
} client;

client clients[MAX_CLIENTS];

int get_open_client( void ) {
	int i;

	for ( i = 0; i < MAX_CLIENTS; i++ ) {
		if ( clients[i].connected == false )
			return i;
	}
	return -1;
}

int get_biggest_fd( void ) {
	int i, fd = -1;
	for( i = 0; i < MAX_CLIENTS; i++ ) {
		if ( clients[i].connected && clients[i].socket > fd )
			fd = clients[i].socket;
	}
	return fd;
} 

int main( int argc, char** argv ) {
	int cl;
	fd_set readfds;
	struct timeval timeout;
	TimeUnits timeunits;
	time_t rawtime;
	struct tm *current_time;
	struct tm old_time;

	signal( SIGPIPE, SIG_IGN );
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;

	if ( ( s = generic_service_create_socket( SERVICE_MGMT_PATH TICK_TIMER_SERVICE_MGMT_NAME ) ) < 0 )
		return errno;

	memset( clients, 0, sizeof( client ) * MAX_CLIENTS );


	time( &rawtime );
	current_time = localtime( &rawtime );
	memcpy( &old_time, current_time, sizeof( struct tm ) );

	while( true ) {
		/* alert subscribed clients */
		time( &rawtime );
		current_time = localtime( &rawtime );
		timeunits = 0;
		timeunits |= current_time->tm_sec == old_time.tm_sec ? 0 : SECOND_UNIT;
		timeunits |= current_time->tm_min == old_time.tm_min ? 0 : MINUTE_UNIT;
		timeunits |= current_time->tm_hour == old_time.tm_hour ? 0 : HOUR_UNIT;
		timeunits |= current_time->tm_yday == old_time.tm_yday ? 0 : DAY_UNIT;
		timeunits |= current_time->tm_mon == old_time.tm_mon ? 0 : MONTH_UNIT;
		timeunits |= current_time->tm_year == old_time.tm_year ? 0 : YEAR_UNIT;
		memcpy( &old_time, current_time, sizeof( struct tm ) );

		for ( cl = 0; cl < MAX_CLIENTS; cl++ ) {
			if ( clients[cl].connected && ( ( timeunits & clients[cl].timeunits ) != 0) ) {
				if ( send( clients[cl].socket, &timeunits, sizeof( timeunits ), 0 ) < 0 ) {
					clients[cl].connected = false;
					FD_CLR( clients[cl].socket, &readfds );
					close( clients[cl].socket );
				}
			}
		}

		/* check for new or changed subscriptions */
		FD_ZERO( &readfds );
		for ( cl = 0; cl < MAX_CLIENTS; cl++ ) {
			if ( clients[cl].connected )
				FD_SET( clients[cl].socket, &readfds );
		}
		if ( select( get_biggest_fd() + 1, &readfds, NULL, NULL, &timeout ) > 0 ) {
			for ( cl = 0; cl < MAX_CLIENTS; cl++ ) {
				if ( clients[cl].connected && FD_ISSET( clients[cl].socket, &readfds ) ) {
					if ( recv( clients[cl].socket, &timeunits, sizeof( TimeUnits ), 0 ) < 0 ) {
						clients[cl].connected = false;
						FD_CLR( clients[cl].socket, &readfds );
						close( clients[cl].socket );
					} else {
						clients[cl].timeunits = timeunits;
					}					
				}
			}
		}

		/* check for newly connected clients */
		cl = get_open_client();
		if ( cl >= 0 ) {
			clients[cl].socket = accept( s, (struct sockaddr*)&clients[cl].remote, &clients[cl].len );
			if ( clients[cl].socket > -1 ) {
				clients[cl].connected = true;
				FD_SET( clients[cl].socket, &readfds );
			}
		}
		usleep( 16666 );
	}
}