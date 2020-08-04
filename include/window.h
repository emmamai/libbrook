#ifndef _WINDOW_H_

#define WINDOW_SERVICE_MGMT_NAME "WindowService"

typedef enum WindowServiceCommand { 
	CMD_WINDOW_CREATE,
	CMD_WINDOW_DESTROY,

} WindowServiceCommand;

typedef enum WindowServiceData {
	DATA_WINDOW_SHM_NAME,
	DATA_WINDOW_CLICK,
	DATA_WINDOW_
} WindowServiceData;

typedef struct Window {
	char id[16];
	void* buffer;
	void* window_handlers;
	void* click_config_provider;
} Window;

typedef void(* WindowHandler)(struct Window *window);

typedef enum ButtonId {
	BUTTON_ID_BACK,
	BUTTON_ID_UP,
	BUTTON_ID_SELECT,
	BUTTON_ID_DOWN,
	NUM_BUTTONS
} ButtonId;

typedef void * ClickRecognizerRef;
typedef void(* ClickHandler)( ClickRecognizerRef recognizer, void* context );
typedef void(* ClickConfigProvider)( void* context );

typedef struct WindowHandlers {
	WindowHandler load;
	WindowHandler appear;
	WindowHandler disappear;
	WindowHandler unload;
} WindowHandlers;

Window* window_create( void );
void window_destroy( Window* window );

void window_set_click_config_provider( Window* window, ClickConfigProvider click_config_provider );
void window_set_click_config_provider_with_context( Window* window, ClickConfigProvider click_config_provider, void* context );
ClickConfigProvider window_get_click_config_provider( const Window* window );
void* window_get_click_config_context( Window* window );

void window_set_window_handlers( Window* window, WindowHandlers handlers );
struct Layer* window_get_root_layer( const Window* window );
void window_set_background_color( Window* window, GColor background_color );
bool window_is_loaded( Window* window );
void window_set_user_data( Window* window, void* data );
void* window_get_user_data( const Window* window );

void window_single_click_subscribe( ButtonId button_id, ClickHandler handler );
void window_single_repeating_click_subscribe( ButtonId button_id, uint16_t repeat_interval_ms, ClickHandler handler );
void window_multi_click_subscribe( ButtonId button_id, uint8_t min_clicks, uint8_t max_clicks, uint16_t timeout, bool last_click_only, ClickHandler handler );
void window_long_click_subscribe( ButtonId button_id, uint16_t delay_ms, ClickHandler down_handler, ClickHandler up_handler );
void window_raw_click_subscribe( ButtonId button_id, ClickHandler down_handler, ClickHandler up_handler, void* context );
void window_set_click_context( ButtonId button_id, void* context );

void window_stack_push( Window* window, bool animated );
Window* window_stack_pop( bool animated );
void window_stack_pop_all( const bool animated );
bool window_stack_remove( Window* window, bool animated );
Window* window_stack_get_top_window( void );
bool window_stack_contains_window( Window* window );

uint8_t click_number_of_clicks_counted( ClickRecognizerRef recognizer );
ButtonId click_recognizer_get_button_id( ClickRecognizerRef recognizer );
bool click_recognizer_is_repeating( ClickRecognizerRef recognizer );


#define _WINDOW_H_
#endif