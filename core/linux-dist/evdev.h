#include "types.h"
#include "linux-dist/evdev_mappings.h"
#include <linux/input.h>

#pragma once

struct AxisData
{
	s32 range; // smaller size than 32 bit might cause integer overflows
	s32 min;
	void init(int fd, int code, bool inverted);
	s8 convert(int value);
};

struct Controller
{
	int fd;
	ControllerMapping* mapping;
	AxisData data_x;
	AxisData data_y;
	AxisData data_trigger_left;
	AxisData data_trigger_right;
	void init();
};

#define EVDEV_DEVICE_CONFIG_KEY "evdev_device_id_%d"
#define EVDEV_MAPPING_CONFIG_KEY "evdev_mapping_%d"
#define EVDEV_DEVICE_STRING "/dev/input/event%d"
#define EVDEV_MAPPING_PATH "/mappings/%s"

#ifdef TARGET_PANDORA
	#define EVDEV_DEFAULT_DEVICE_ID_1 4
#else
	#define EVDEV_DEFAULT_DEVICE_ID_1 0
#endif

#define EVDEV_DEFAULT_DEVICE_ID(port) (port == 1 ? EVDEV_DEFAULT_DEVICE_ID_1 : -1)

extern int input_evdev_init(Controller* controller, const char* device, const char* mapping_fname);
extern bool input_evdev_handle(Controller* controller, u32 port);





