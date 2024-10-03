#include "menu.h"
#include "Common.h"
#include "Input.h"
#include "DxLib.h"
#include "music.h"


menu::menu()
{
	menu_scene = menu_start;
	for (short s = 0; s < menu_num-1; s++) {
		Buttons.push_back(Button());	
	}
	Buttons.push_back(Button());
	menu_init();
	
}

menu::~menu()
{

}

void menu::menu_move()
{

}

int menu::menu_draw()
{
	switch (menu_scene) {
	case menu_start:
		menu_scene = menu_menu;
		break;

	case menu_menu:
		


		if (Input::get_key_paramater(KEY_INPUT_DOWN) != 0) {
			if (select_cool >= 10) {
				if (menu_num-1 > selected_pointer) {
					PlaySoundMem(Common::sound[0], DX_PLAYTYPE_BACK, 1);
					selected_pointer++;
					select_cool=0;
					
				}
			}
		}
		else if (Input::get_key_paramater(KEY_INPUT_UP) != 0) {
			if (select_cool >= 10) {
				if (0 < selected_pointer) {
					PlaySoundMem(Common::sound[0], DX_PLAYTYPE_BACK, 1);
					selected_pointer--;
					select_cool = 0;
				}
			}
		}
		

		music::play_music(3);

		DrawRotaGraph(game_screen_right / 2, game_screen_down / 2, 1, 0, Common::menu_img[5], TRUE);
		DrawRotaGraph(game_screen_right / 2, game_screen_down / 2 + 80, 1, 0, Common::menu_img[4], TRUE);

		DrawRotaGraph(1400, 150, 0.5, 0, Common::logo, TRUE);

		for (short s = 0; s < menu_num;s++) {
			short pushed = (Input::get_key_paramater(KEY_INPUT_Z));
			menu_scene = Buttons[s].button_all(selected_pointer,pushed,menu_scene);
			
		}

		if (select_cool <= 10) {
			select_cool++;
		}
		return game_menu;
		break;
	case menu_game_ready:
		menu_init();
		return game_play_preload;
		break;
	case menu_end:
		return game_end;
		break;
	}
	return 0;
}

void menu::menu_init()
{
	menu_scene = menu_start;
	select_cool = 0;
	now_pointer = 0;
	selected_pointer = 0;
	for (short s = 0; s < menu_num - 1; s++) {
		selected_counter[s] = 0;
		Buttons[s].button_init(menu_game_ready, Common::menu_img[s], 1550, 400 + 150 * s, 0.5, s);

	}
	selected_counter[3] = 0;
	Buttons[3].button_init(menu_game_ready, Common::menu_img[3], 1550, 400 + 150 * 3, 0.5, 3);

}
