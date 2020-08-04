/* connection service definitions */
#ifndef _CONNECTION_SERVICE_H_

typedef void(* ConnectionHandler)( bool connected );

typedef struct ConnectionHandlers {
	ConnectionHandler app_connection_handler;
	ConnectionHandler kit_connection_handler;
} ConnectionHandlers;

bool connection_service_peek_app_connection( void );
bool connection_service_peek_kit_connection( void );
void connection_service_subscribe( ConnectionHandlers conn_handlers );
void connection_service_unsubscribe( void );

#define _CONNECTION_SERVICE_H_
#endif