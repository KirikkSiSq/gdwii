#pragma once

#include <ogc/lwp_watchdog.h>
#include <ogc/lwp.h>
#include <ogc/lwp_mutex.h>

#define STEPS_HZ 240
#define STEPS_DT (1.0f / STEPS_HZ) // 1/240 seconds per physics step

#define INPUT_BUFFER_SIZE 4
#define INPUT_BUFFER_MASK (INPUT_BUFFER_SIZE-1)

#define ticks_to_secs_float(ticks) (((float)(ticks)/(float)(TB_TIMER_CLOCK*1000)))

extern bool enable_info;
extern float amplitude;
extern float dt;
extern float death_timer;

extern u64 start_frame;

int game_loop();