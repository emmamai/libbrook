/* BrookInit
Starts basic Brook services. Can also act as a very minimal init process if
started as PID 1, to boot a system running nothing but Brook.
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int parent_pid;
sigset_t set;

void fork_run( char* name ) {
	if ( fork() )
		return;

	execvp( name, (char *[]){ name, 0 } );	
}

int main( int argc, char** argv ) {
	int status;
	printf( "BrookInit\n" );

	if ( ( parent_pid = getpid() ) == 1 ) {
		printf( "Running as PID 1\n" );
		setenv( "PATH", "/usr/bin:/usr/sbin:/bin:/sbin", 0 );
	}

	sigfillset( &set );
	sigprocmask( SIG_BLOCK, &set, 0 );

	if ( fork() ) {
		while( true ) {
			wait( &status );
		}
	}

	sigprocmask( SIG_UNBLOCK, &set, 0 );
	setsid();
	setpgid( 0, 0 );

	fork_run( "TickTimerService" );
	return execvp( "BrookUI", (char *[]){ "BrookUI", 0 } );
}