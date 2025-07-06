#pragma once

#include <ogc/lwp_watchdog.h>
#include <ogc/lwp.h>
#include <ogc/lwp_mutex.h>

#define STEPS_DT (1.0f / 240.0f) // 1/240 seconds per physics step

#define ticks_to_secs_float(ticks) (((float)(ticks)/(float)(TB_TIMER_CLOCK*1000)))

extern bool enable_info;

int game_loop();