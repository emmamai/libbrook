/* Functions related to application startup, the event loop, and cleanup/exit. */
#ifndef _APPEVENT_H_

#include <stdint.h>
#include <stdbool.h>
#include <time.h>

#include <event/generic_service.h>
#include <event/accelerometer_service.h>
#include <event/app_focus_service.h>
#include <event/battery_state_service.h>
#include <event/compass_service.h>
#include <event/connection_service.h>
#include <event/health_service.h>
#include <event/tick_timer_service.h>

enum AppLaunchReason {
	APP_LAUNCH_SYSTEM,
	APP_LAUNCH_USER,
	APP_LAUNCH_PHONE,
	APP_LAUNCH_WAKEUP,
	APP_LAUNCH_WORKER,
	APP_LAUNCH_QUICK_LAUNCH,
	APP_LAUNCH_TIMELINE_ACTION,
	APP_LAUNCH_SMARTSTRAP		/* Consider: Change to APP_LAUNCH_PERIPHERAL and add a compat header */
};

enum AppExitReason {
	APP_EXIT_ACTION_PERFORMED_SUCCESSFULLY,
	APP_EXIT_NOT_SPECIFIED,
	NUM_EXIT_REASONS
};

void launch_reason( void );
uint32_t launch_get_args( void );
void app_event_loop( void );

#define _APPEVENT_H_
#endif