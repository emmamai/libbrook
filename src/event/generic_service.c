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
#include <sys/stat.h>

#include <appevent.h>

int generic_service_connect( char* if_name ) {
	int s, len;
	struct sockaddr_un remote;

	if ( ( s = socket( AF_UNIX, SOCK_STREAM, 0) ) < 0 ) {
		perror( "socket() failure while connecting to service" );
		return -1;
	}
	remote.sun_family = AF_UNIX;
	strcpy( remote.sun_path, SERVICE_MGMT_PATH TICK_TIMER_SERVICE_MGMT_NAME );
	len = strlen( remote.sun_path ) + sizeof( remote.sun_family );
	if ( connect( s, (struct sockaddr *)&remote, len ) < 0 ) {
		perror( "connect() failure while connecting to service" );
		return -1;
	}
	return s;
}

int generic_service_create_socket( char* if_name ) {
	unsigned int len, s;
	struct sockaddr_un local;

	mkdir( SERVICE_MGMT_PATH, 0777 );

	s = socket(AF_UNIX, SOCK_STREAM, 0);
	local.sun_family = AF_UNIX;
	strcpy( local.sun_path, SERVICE_MGMT_PATH TICK_TIMER_SERVICE_MGMT_NAME );
	unlink( local.sun_path );
	len = strlen( local.sun_path ) + sizeof( local.sun_family );
	if ( bind( s, (struct sockaddr *)&local, len ) < 0 ) {
		perror( "bind() failure setting up socket\n" );
		return -1;
	}
	if ( listen( s, 16 ) < 0 ) {
		perror( "listen() failure setting up socket\n" );
		return -1;
	}
	fcntl( s, F_SETFL, O_NONBLOCK );
	return s;
}