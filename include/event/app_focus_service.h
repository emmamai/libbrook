/* App Focus Service definitions */

#ifndef _APP_FOCUS_SERVICE_H_

typedef void(* AppFocusHandler)( bool in_focus );

typedef struct AppFocusHandlers {
	AppFocusHandler will_focus;
	AppFocusHandler did_focus;
} AppFocusHandlers;

void app_focus_service_subscribe_handlers( AppFocusHandlers handlers );
void app_focus_service_subscribe( AppFocusHandler handler );

#define _APP_FOCUS_SERVICE_H_
#endif