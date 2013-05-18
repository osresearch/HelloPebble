/** \file
 * Hello, Pebble!
 *
 * Sample for the NYC Resistor Pebble programming class
 */
#include "pebble_os.h"
#include "pebble_app.h"

//! Generate your own UUID using `uuidgen` and replace it:
#define MY_UUID { \
	0x69, 0x5C, 0xE6, 0xFE, \
	0x5D, 0xC1, 0x43, 0x81, \
	0x85, 0x29, 0x9A, 0x82, \
	0xDB, 0x09, 0xA0, 0x69, \
	}

PBL_APP_INFO(
	MY_UUID,
	"Digital Watch",
	"hudson",
	1, 0,
	INVALID_RESOURCE,
	APP_INFO_WATCH_FACE
);


static Window window;
static TextLayer text;
static char time_str_buffer[32];


static void
handle_tick(
	AppContextRef ctx,
	PebbleTickEvent *event
)
{
	string_format_time(
		time_str_buffer,
		sizeof(time_str_buffer),
		"%I:%M:%S %p",
		event->tick_time
	);

	text_layer_set_text(&text, time_str_buffer);
}


static void
handle_init(
	AppContextRef ctx
)
{
	(void)ctx;

	window_init(&window, "Hello, Pebble");
	window_stack_push(&window, true /* Animated */);

	text_layer_init(&text, window.layer.frame);
	text_layer_set_text(&text, "");
	layer_add_child(&window.layer, &text.layer);
}


static void
handle_deinit(
	AppContextRef ctx
)
{
	(void)ctx;
}


void
pbl_main(
	void *params
)
{
	PebbleAppHandlers handlers = {
		.init_handler = handle_init,
		.deinit_handler = handle_deinit,
		.tick_info = {
			.tick_handler = handle_tick,
			.tick_units = SECOND_UNIT,
		},
	};

	app_event_loop(params, &handlers);
}