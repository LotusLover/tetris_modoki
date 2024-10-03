#include "game_control.h"
#include "Common.h"
#include "Input.h"
#include "Load.h"
#include "menu.h"
int game_control::game_process()
{
	Input::get_keyboard();
	switch (Common::get_scene_number()) {
	case game_launch:
		//LOAD->img_load();
		if (Load::load_first()) {
			Common::scene_change(game_launch_loading);
		}
		break;
	case game_launch_loading:
		if (Load::load_second()) {
			Common::scene_change(game_menu_preload);
		}

		break;
	case game_menu_preload:
		//OBJECT_CONTROL.~unique_ptr();

		MENU_PTR = std::make_unique<menu>();

		Common::scene_change(game_menu);
		break;
	case game_menu:
		Common::scene_change(MENU_PTR->menu_draw());
		
		break;
	case game_play_preload:
		//MENU.~unique_ptr();
		STAGE_PTR = std::make_unique<stage>();
		STAGE_PTR->stage_init();
		Common::scene_change(game_play);
		//break;
	case game_play:
		if (STAGE_PTR->stage_all()>=1) {
			Common::scene_change(game_end);
		}
		break;
	case game_end:

		STAGE_PTR.release();
		Common::scene_change(game_menu);
		break;
	default:
		return true;
	}

	//FPS_CONTROL->flame_avelage();

	/*FPS_CONTROL->flame_update();*/

	return false;
}

game_control::game_control()
{
	Common::scene_change(game_launch);
}

game_control::~game_control()
{

}

void game_control::delete_ptr()
{
	if (MENU_PTR != nullptr) {
		MENU_PTR.reset();
	}
	if (STAGE_PTR != nullptr) {
		STAGE_PTR.reset();
	}
}
