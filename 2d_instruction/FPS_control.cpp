#include "FPS_control.h"
//#include "common.h"
#include "DxLib.h"

constexpr int fps = 60;

long long FPS_control::loop_start_time = 0, FPS_control::loop_end_time = 0, FPS_control::sleep_time = 0, FPS_control::one_flame_time = 1000.00 / fps * 1000, FPS_control::fps_first_time = 0;
double FPS_control::fps_avelage = 0;
int FPS_control::all_fps_count = 0, FPS_control::fps_count = fps, FPS_control::cutted = 0;
std::queue<long long> FPS_control::time_queue;

short FPS_control::set_start_time()
{
	if (fps_count >= 60) {
		long long now = (GetNowHiPerformanceCount() / 1000.00);

		fps_avelage = (1000.00 / (((now)-fps_first_time / 1000.00) / 60.0));
		fps_count = 0;
		fps_first_time = GetNowHiPerformanceCount();

	}
	time_queue.push(GetNowHiPerformanceCount());
	fps_avelage = (1000.00 / (((time_queue.back() / 1000.00) - time_queue.front() / 1000.00) / 60.0));
	if (time_queue.size() > 60) {
		time_queue.pop();
	}
	fps_count++;

	DrawFormatStringF(0, 0, GetColor(255, 250, 250), "%.3f", fps_avelage);
	return 0;
}

short FPS_control::flame_update()
{
	loop_end_time = GetNowHiPerformanceCount();

	sleep_time = fps_count * 1000000 / fps - (loop_end_time - fps_first_time);

	if (sleep_time > 0) {
		cutted += sleep_time % 1000;
		if (cutted > 1000) {
			sleep_time += 1000;
			cutted -= 1000;
		}

		Sleep(sleep_time / 1000.0);
	}
	ScreenFlip();
	return 0;
}

void FPS_control::flame_avelage() {
	if (all_fps_count % 60 == 0) {
	}

}

FPS_control::FPS_control()
{

}

FPS_control::~FPS_control()
{

}

