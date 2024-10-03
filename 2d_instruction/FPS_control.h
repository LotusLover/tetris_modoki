#pragma once
#include<queue>
class FPS_control
{
private:
	static long long loop_start_time, loop_end_time, sleep_time, one_flame_time, fps_first_time;
	static double  fps_avelage;
	static int all_fps_count, fps_count, cutted;
	static std::queue<long long> time_queue;
public:
	static short set_start_time();
	static short flame_update();
	static void flame_avelage();

	FPS_control();
	~FPS_control();
};

