/* This one's a bit big. Missing convenience macros, those will need put in sometime. */
#ifndef _HEALTH_SERVICE_H_

enum HealthMetric {
	HealthMetricStepCount,
	HealthMetricActiveSeconds,
	HealthMetricWalkedDistanceMeters,
	HealthMetricSleepSeconds,
	HealthMetricSleepRestfulSeconds,
	HealthMetricRestingKCalories,
	HealthMetricActiveKCalories,
	HealthMetricHeartRateBPM,
	HealthMetricHeartRateRawBPM
}
enum HealthServiceTimeScope {
	HealthServiceTimeScopeOnce,
	HealthServiceTimeScopeWeekly,
	HealthServiceTimeScopeDailyWeekdayOrWeeekend,
	HealthServiceTimeScopeDaily
}
enum HealthAggregation {
	HealthAggregationSum,
	HealthAggregationAvg,
	HealthAggregationMin,
	HealthAggregationMax
}
enum HealthActivity {
	HealthActivityNone,
	HealthActivitySleep,
	HealthActivityRestfulSleep,
	HealthActivityWalk,
	HealthActivityRun,
	HealthActivityOpenWorkout
}
enum HealthIterationDirection {
	HealthIterationDirectionPast,
	HealthIterationDirectionFuture
}
enum HealthServiceAccessibilityMask {
	HealthServiceAccessibilityMaskAvailable,
	HealthServiceAccessibilityMaskNoPermission,
	HealthServiceAccessibilityMaskNotSupported,
	HealthServiceAccessibilityMaskNotAvailable
}
enum HealthEventType {
	HealthEventSignificantUpdate,
	HealthEventMovementUpdate,
	HealthEventSleepUpdate,
	HealthEventMetricAlert,
	HealthEventHeartRateUpdate
}
enum AmbientLightLevel {
	AmbientLightLevelUnknown,
	AmbientLightLevelVeryDark,
	AmbientLightLevelDark,
	AmbientLightLevelLight,
	AmbientLightLevelVeryLight
}
enum MeasurementSystem {
	MeasurementSystemUnknown,
	MeasurementSystemMetric,
	MeasurementSystemImperial
}

struct HealthMinuteData {
	uint8_t steps;
	uint8_t orientation;
	uint16_t vmc;
	bool is_invalid;
	AmbientLightLevel light;
	uint8_t padding;
	uint8_t heart_rate_bpm;
	uint8_t reserved;
}
typedef struct HealthMetricAlert { /* The contents of this struct aren't explicitly defined in the spec */
	uint32_t handle;
} HealthMetricAlert;

typedef int32_t HealthValue;
typedef uint32_t HealthActivityMask;

typedef bool(* HealthActivityIteratorCB)( HealthActivity activity, time_t time_start, time_t time_end, void *context );
typedef void(* HealthEventHandler)( HealthEventType event, void *context );
HealthValue health_service_sum( HealthMetric metric, time_t time_start, time_t time_end );
HealthValue health_service_sum_today( HealthMetric metric );
HealthValue health_service_sum_averaged( HealthMetric metric, time_t time_start, time_t time_end, HealthServiceTimeScope scope );
HealthActivityMask health_service_peek_current_activities( void );
void health_service_activities_iterate( HealthActivityMask activity_mask, time_t time_start, time_t time_end, HealthIterationDirection direction, HealthActivityIteratorCB callback, void *context );
HealthServiceAccessibilityMask health_service_metric_accessible( HealthMetric metric, time_t time_start, time_t time_end );
HealthServiceAccessibilityMask health_service_metric_averaged_accessible( HealthMetric metric, time_t time_start, time_t time_end, HealthServiceTimeScope scope );
HealthServiceAccessibilityMask health_service_any_activity_accessible( HealthActivityMask activity_mask, time_t time_start, time_t time_end );
bool health_service_events_subscribe( HealthEventHandler handler, void *context );
bool health_service_events_unsubscribe( void );
uint32_t health_service_get_minute_history( HealthMinuteData *minute_data, uint32_t max_records, time_t *time_start, time_t *time_end );
MeasurementSystem health_service_get_measurement_system_for_display( HealthMetric metric );

#define _HEALTH_SERVICE_H_
#endif