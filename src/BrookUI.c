/* BrookUI
Windowing system for libbrook

BrookUI manages the window stack and window display for libbrook-based applications.

BrookUI provides a management interface through which information about the display,
the window stack, and individual windows can be queried. Through the management
interface, applications can request a buffer to be used as a graphics context.
These buffers are in ARGB8888 format. 

BrookUI also provides the AppFocusService to registered applications.
*/
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
#include <gcolor.h>
#include <window.h>

int s;

int main( int argc, char** argv ) {
	printf( "## BrookUI windowing system\n" );
	printf( "Built at %s on %s\n", __TIME__, __DATE__ );
	printf( "--------------------------------\n\n" );

	if ( ( s = generic_service_create_socket( SERVICE_MGMT_PATH WINDOW_SERVICE_MGMT_NAME ) ) < 0 )
		exit( errno );
}