 /* Generic service handling functions */
#ifndef _GENERIC_SERVICE_H_


#define SERVICE_MGMT_PATH "/tmp/brook/"

/* app-side functions */
int generic_service_connect( char* name );

/* service-side functions */
int generic_service_create_socket( char* if_name );

#define _GENERIC_SERVICE_H_
#endif