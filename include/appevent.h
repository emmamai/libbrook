/* Functions related to application startup, the event loop, and cleanup/exit. */
#ifndef _APPEVENT_H_

#include "event/accelerometer_service.h"
#include "event/app_focus_service.h"
#include "event/battery_state_service.h"
#include "event/compass_service.h"
#include "event/connection_service.h"
#include "event/health_service.h"
#include "event/tick_timer_service.h"

enum AppExitReason {
	APP_EXIT_ACTION_PERFORMED_SUCCESSFULLY,
	APP_EXIT_NOT_SPECIFIED,
	NUM_EXIT_REASONS
}

/* Blocks and waits for incoming events */
void app_event_loop( void );

#define _APPEVENT_H_
#endif