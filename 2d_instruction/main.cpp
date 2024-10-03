#include "DxLib.h"
#include "Common.h"
#include "stage_load.h"
#include "FPS_control.h"
#include "game_control.h"
#include <time.h>
// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{


	ChangeWindowMode(TRUE);
	SetGraphMode(game_screen_right, game_screen_down, 32);
	SetWindowSize(960, 540);
	//SetWindowSize(1920, 1080);

	SetAlwaysRunFlag(TRUE);
	//SetWaitVSyncFlag(TRUE);
	SetWaitVSyncFlag(0);
	SetMainWindowClassName("テトリス");
	SetWindowStyleMode(0);
	SetMainWindowText("テトリス");
	SetUseASyncLoadFlag(TRUE);

	SetDrawMode(DX_DRAWMODE_ANISOTROPIC);

	SetDrawScreen(DX_SCREEN_BACK);

	srand(time(NULL));

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	FPS_control FPS_CONTROL;
	game_control GAME_CONTROL;

	while (ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		FPS_CONTROL.set_start_time();
		if (GAME_CONTROL.game_process() == game_end) {
			break;
		}
		FPS_CONTROL.flame_update();
	}
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
