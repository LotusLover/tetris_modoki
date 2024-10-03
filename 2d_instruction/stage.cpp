#include "stage.h"
#include "Common.h"
#include "DxLib.h"
#include "Input.h"
#include "music.h"

constexpr int make_x = 5, make_y = 0;

unsigned char block_color_red[7] =   { 255 ,0  ,255,255,255,0  ,127 };
unsigned char block_color_green[7] = { 0 ,255,0  ,137,127  ,0  ,127 };
unsigned char block_color_blue[7] =  { 255,0  ,0  ,0  ,127 ,255,255 };

stage::stage()
{
	stage_init();
	nect_block_num = 0;
}

stage::~stage()
{

}

void stage::stage_init()
{
	nect_block_num = 0;
	
	music::play_music(5);

	for (short t = 0; t < stage_y; t++) {
		for (short s = 0; s < stage_x; s++) {
			field[s][t].block_init(stage_pos_x, stage_pos_y, 255, 255, 255, s, t,1);
		}
	}

	for (char c = 0; c < block_kind_max; c++) {
		block_order[c] = -1;
	}

	for (char c = 0; c < block_kind_max; c++) {
		char buf = rand()%block_kind_max;
		if (block_order[buf] == -1) {
			block_order[buf] = c;
		}
		else {
			c--;
			continue;
		}
	}

	for (char c = 0; c < block_kind_max*2; c++) {
		next_block[c] = block_order[c % block_kind_max];
		nect_block_num++;
	}
	make_block();

	next_block_charge();

	block_fall_count = 0;
	block_fall_flag = 1;
	block_cooldown = 30;
	button_down_flag = 0;
	button_up_flag = 0;
	button_left_flag = 0;
	button_right_flag = 0;
	button_rotate_flag = 0;
	game_over_flag = 0;
	erazed_counter = 0;
	game_over_count = game_over_draw_time;
	game_over_scene_change_flag = 0;
}

void stage::stage_draw()
{
	DrawRotaGraph(game_screen_right / 2, game_screen_down / 2, 2, 0, Common::menu_img[6], TRUE);
	for (short t = 0; t < stage_y; t++) {
		for (short s = 0; s < stage_x; s++) {

			DrawRotaGraph(stage_pos_x+ s * block_x,stage_pos_y+ t * block_y, 0.1, 0, Common::block_img, TRUE);
			field[s][t].block_draw();

		}
	}
	next_block_draw();
}

void stage::stage_process()
{
	if (game_over_flag == 0) {
		move_block();
		stage_draw();
		block_draw();
		score_draw();
	}
	else {
		stage_draw();
		block_draw();
		game_over_judge();
	}


}

void stage::stage_judge()
{
	int judge_count = 0;
	for (short t = 0; t < stage_y; t++) {
		judge_count = 0;
		for (short s = 0; s < stage_x; s++) {
			if (field[s][t].get_flag() == 2) {
				judge_count++;
			}
		}
		if (judge_count >= stage_x) {
			erazed_counter++;
			for (short s = 0; s < stage_x; s++) {
				//stage_array[s][t] = stage_array[s][t - 1];
				for (short u = t; u > 0; u--) {
					field[s][u].block_make(field[s][u].get_x_num(), field[s][u].get_y_num(), field[s][u - 1].get_red(), field[s][u - 1].get_green(), field[s][u - 1].get_blue(), field[s][u - 1].get_flag());
				}
			}
			t--;
			PlaySoundMem(Common::sound[1], DX_PLAYTYPE_BACK, 1);
		}
	}

	next_block_charge();
}

void stage::make_block()
{
	falling_block_type = next_block_used();
	falling_block_x = make_x;
	falling_block_y = make_y;
	falling_block_angle = 0;
	

	for (short t = 0; t < 4; t++) {
		for (short s = 0; s < 4; s++) {
			/*if (block_shape_1[falling_block_type][t][s] > 0) {*/
				falling_block[t][s].block_init(stage_pos_x, stage_pos_y,block_color_red[falling_block_type], block_color_green[falling_block_type], block_color_blue[falling_block_type], falling_block_x + s, falling_block_y + t, block_shape_1[falling_block_type][t][s]);
			//}
				if (block_shape_1[falling_block_type][t][s] > 0) {
					if (field[falling_block_x + s][falling_block_y + t].get_flag() >= 2&&game_over_flag!=1) {
						game_over_flag = 1;
					}
				}
		}
	}

}

void stage::rotate_block()
{

	char cant_rotate = 0,rotate_assist_x=0,rotate_assist_y=0,rotate_flag=0;
	char falling_block_angle_temp = falling_block_angle+1;
	if (falling_block_angle_temp ==4) {
		falling_block_angle_temp = 0;
	}
	

	switch (falling_block_angle_temp) {
	case 0:
		for (short t = 0; t < 4; t++) {
			for (short s = 0; s < 4; s++) {
				if (cant_rotate != 1) {
				if (block_shape_1[falling_block_type][t][s] > 0) {
					if (falling_block_x + s>= stage_x || falling_block_x + s  < 0 || field[falling_block_x + s ][falling_block_y + t].get_flag() == 2) {
						
						cant_rotate = 1;
					}
					if (cant_rotate == 1) {
						cant_rotate = 0;
						rotate_assist_x = 1;
						if (falling_block_x + s + rotate_assist_x >= stage_x || falling_block_x + s + rotate_assist_x < 0 || field[falling_block_x + s + rotate_assist_x][falling_block_y + t].get_flag() == 2) {
							cant_rotate = 1;
						}
					}
					if (cant_rotate == 1) {
						cant_rotate = 0;
						rotate_assist_x = -1;
						if (falling_block_x + s + rotate_assist_x >= stage_x || falling_block_x + s + rotate_assist_x < 0 || field[falling_block_x + s + rotate_assist_x][falling_block_y + t].get_flag() == 2) {
							cant_rotate = 1;
						}
					}
				}
				}
				

			}
		}

		if (cant_rotate == 0) {
			for (short t = 0; t < 4; t++) {
				for (short s = 0; s < 4; s++) {
					falling_block[t][s].block_make(falling_block_x + s + rotate_assist_x, falling_block_y + t, block_color_red[falling_block_type], block_color_green[falling_block_type], block_color_blue[falling_block_type], block_shape_1[falling_block_type][t][s]);
				}
			}
			falling_block_x += rotate_assist_x;
			falling_block_angle++;
			if (falling_block_angle == 4) {
				falling_block_angle = 0;
			}
		}
		
		break;

	case 1:
		for (short t = 0; t < 4; t++) {
			for (short s = 0; s < 4; s++) {
				if (cant_rotate != 1) {
					if (block_shape_2[falling_block_type][t][s] > 0) {
						if (falling_block_x + s >= stage_x || falling_block_x + s < 0 || field[falling_block_x + s][falling_block_y + t].get_flag() == 2) {

							cant_rotate = 1;
						}
						if (cant_rotate == 1) {
							cant_rotate = 0;
							rotate_assist_x = 1;
							if (falling_block_x + s + rotate_assist_x >= stage_x || falling_block_x + s + rotate_assist_x < 0 || field[falling_block_x + s + rotate_assist_x][falling_block_y + t].get_flag() == 2) {
								cant_rotate = 1;
							}
						}
						if (cant_rotate == 1) {
							cant_rotate = 0;
							rotate_assist_x = -1;
							if (falling_block_x + s + rotate_assist_x >= stage_x || falling_block_x + s + rotate_assist_x < 0 || field[falling_block_x + s + rotate_assist_x][falling_block_y + t].get_flag() == 2) {
								cant_rotate = 1;
							}
						}
					}
				
				}
			}
		}
		if (cant_rotate == 0) {
			for (short t = 0; t < 4; t++) {
				for (short s = 0; s < 4; s++) {
					falling_block[t][s].block_make(falling_block_x + s + rotate_assist_x, falling_block_y + t, block_color_red[falling_block_type], block_color_green[falling_block_type], block_color_blue[falling_block_type], block_shape_2[falling_block_type][t][s]);
				}
			}
			falling_block_x += rotate_assist_x;
			falling_block_angle++;
			if (falling_block_angle == 4) {
				falling_block_angle = 0;
			}
		}
		break;

	case 2:
		for (short t = 0; t < 4; t++) {
			for (short s = 0; s < 4; s++) {
				if (cant_rotate != 1) {
					if (block_shape_3[falling_block_type][t][s] > 0) {
						if (falling_block_x + s >= stage_x || falling_block_x + s < 0 || field[falling_block_x + s][falling_block_y + t].get_flag() == 2) {

							cant_rotate = 1;
						}
						if (cant_rotate == 1) {
							cant_rotate = 0;
							rotate_assist_x = 1;
							if (falling_block_x + s + rotate_assist_x >= stage_x || falling_block_x + s + rotate_assist_x < 0 || field[falling_block_x + s + rotate_assist_x][falling_block_y + t].get_flag() == 2) {
								cant_rotate = 1;
							}
						}
						if (cant_rotate == 1) {
							cant_rotate = 0;
							rotate_assist_x = -1;
							if (falling_block_x + s + rotate_assist_x >= stage_x || falling_block_x + s + rotate_assist_x < 0 || field[falling_block_x + s + rotate_assist_x][falling_block_y + t].get_flag() == 2) {
								cant_rotate = 1;
							}
						}
					}
				}
				
			}
		}
		if (cant_rotate == 0) {
			for (short t = 0; t < 4; t++) {
				for (short s = 0; s < 4; s++) {
					falling_block[t][s].block_make(falling_block_x + s + rotate_assist_x, falling_block_y + t, block_color_red[falling_block_type], block_color_green[falling_block_type], block_color_blue[falling_block_type], block_shape_3[falling_block_type][t][s]);
				}
			}
			falling_block_x += rotate_assist_x;
			falling_block_angle++;
			if (falling_block_angle == 4) {
				falling_block_angle = 0;
			}
		}
		break;

	case 3:
		for (short t = 0; t < 4; t++) {
			for (short s = 0; s < 4; s++) {
				if (cant_rotate != 1) {
					if (block_shape_4[falling_block_type][t][s] > 0) {
						if (falling_block_x + s >= stage_x || falling_block_x + s < 0 || field[falling_block_x + s][falling_block_y + t].get_flag() == 2) {

							cant_rotate = 1;
						}
						if (cant_rotate == 1) {
							cant_rotate = 0;
							rotate_assist_x = 1;
							if (falling_block_x + s + rotate_assist_x >= stage_x || falling_block_x + s + rotate_assist_x < 0 || field[falling_block_x + s + rotate_assist_x][falling_block_y + t].get_flag() == 2) {
								cant_rotate = 1;
							}
						}
						if (cant_rotate == 1) {
							cant_rotate = 0;
							rotate_assist_x = -1;
							if (falling_block_x + s + rotate_assist_x >= stage_x || falling_block_x + s + rotate_assist_x < 0 || field[falling_block_x + s + rotate_assist_x][falling_block_y + t].get_flag() == 2) {
								cant_rotate = 1;
							}
						}
					}
				}
			
			}
		}
		if (cant_rotate == 0) {
			for (short t = 0; t < 4; t++) {
				for (short s = 0; s < 4; s++) {
					falling_block[t][s].block_make(falling_block_x + s + rotate_assist_x, falling_block_y + t, block_color_red[falling_block_type], block_color_green[falling_block_type], block_color_blue[falling_block_type], block_shape_4[falling_block_type][t][s]);
				}
			}
			falling_block_x += rotate_assist_x;
			falling_block_angle++;
			if (falling_block_angle == 4) {
				falling_block_angle = 0;
			}
		}
		break;
	default:

		break;
	}

}

void stage::move_block()
{
	char move_x=0, move_y=0,stop_flag_x=0, stop_flag_y = 0;
	if (block_fall_flag == 1) {
		block_fall_count++;
		if (block_fall_count >= block_fall_time) {
			move_y++;
			block_fall_count = 0;
		}
		else if (Input::get_key_paramater(KEY_INPUT_DOWN) != 0) {
			move_y++;
			block_fall_count = 0;
		}
		if (Input::get_key_paramater(KEY_INPUT_LEFT) != 0) {
			if (button_left_flag == 0) {
				button_left_flag = 1;
				move_x--;
			}

		}
		else {
			button_left_flag = 0;
		}
		if (Input::get_key_paramater(KEY_INPUT_RIGHT) != 0) {
			if (button_right_flag == 0) {
				button_right_flag = 1;
				move_x++;
			}
		}
		else {
			button_right_flag = 0;
		}
		if (Input::get_key_paramater(KEY_INPUT_RSHIFT) != 0) {
			if (button_rotate_flag == 0) {
				button_rotate_flag = 1;
				rotate_block();
			}
		}
		else {
			button_rotate_flag = 0;
		}



		for (short t = 0; t < 4; t++) {
			for (short s = 0; s < 4; s++) {
				switch (falling_block_angle)
				{
				case 0:
					if (block_shape_1[falling_block_type][t][s] > 0) {
						if (falling_block_x + s + move_x >= stage_x || falling_block_x + s + move_x < 0 || field[falling_block_x + s + move_x][falling_block_y + t].get_flag() == 2) {
							stop_flag_x = 1;
						}
					}
					break;
				case 1:
					if (block_shape_2[falling_block_type][t][s] > 0) {
						if (falling_block_x + s + move_x >= stage_x || falling_block_x + s + move_x < 0 || field[falling_block_x + s + move_x][falling_block_y + t].get_flag() == 2) {
							stop_flag_x = 1;
						}
					}
					break;
				case 2:
					if (block_shape_3[falling_block_type][t][s] > 0) {
						if (falling_block_x + s + move_x >= stage_x || falling_block_x + s + move_x < 0 || field[falling_block_x + s + move_x][falling_block_y + t].get_flag() == 2) {
							stop_flag_x = 1;
						}
					}
					break;
				case 3:
					if (block_shape_4[falling_block_type][t][s] > 0) {
						if (falling_block_x + s + move_x >= stage_x || falling_block_x + s + move_x < 0 || field[falling_block_x + s + move_x][falling_block_y + t].get_flag() == 2) {
							stop_flag_x = 1;
						}
					}
					break;
				default:
					break;
				}
				
			}
		}

		if (stop_flag_x != 1) {
			//if (field[falling_block_x + (block_size_left[falling_block_type]) + move_x][falling_block_y + (block_size_down[falling_block_type] - 1)].get_flag() <= 1 && field[falling_block_x + (block_size_left[falling_block_type] - 1) + move_x][falling_block_y + (block_size_down[falling_block_type] - 1)].get_flag() <= 1 ) {
			falling_block_x += move_x;
			for (short t = 0; t < 4; t++) {
				for (short s = 0; s < 4; s++) {
					switch (falling_block_angle)
					{
					case 0:
						/*if (block_shape_1[falling_block_type][s][t] > 0) {*/
							/*falling_block[s][t].block_move(move_x, 0);*/
						/*}*/
						break;
					default:
						break;
					}
					falling_block[s][t].block_move(move_x, 0); 
				}
			}
			//}
		}

		for (short t = 0; t < 4; t++) {
			for (short s = 0; s < 4; s++) {
				switch (falling_block_angle)
				{
				case 0:
					if (block_shape_1[falling_block_type][t][s] > 0) {
						if (field[falling_block_x + s][falling_block_y + t + move_y].get_flag() == 2 || falling_block_y + t + move_y == stage_y) {
							stop_flag_y = 1;
						}
					}
					break;
				case 1:
					if (block_shape_2[falling_block_type][t][s] > 0) {
						if (field[falling_block_x + s][falling_block_y + t + move_y].get_flag() == 2 || falling_block_y + t + move_y == stage_y) {
							stop_flag_y = 1;
						}
					}
					break;
				case 2:
					if (block_shape_3[falling_block_type][t][s] > 0) {
						if (field[falling_block_x + s][falling_block_y + t + move_y].get_flag() == 2 || falling_block_y + t + move_y == stage_y) {
							stop_flag_y = 1;
						}
					}
					break;
				case 3:
					if (block_shape_4[falling_block_type][t][s] > 0) {
						if (field[falling_block_x + s][falling_block_y + t + move_y].get_flag() == 2 || falling_block_y + t + move_y == stage_y) {
							stop_flag_y = 1;
						}
					}
					break;
				default:

					break;
				}
			}
		}

		if (stop_flag_y != 1) {
			falling_block_y += move_y;
			for (short t = 0; t < 4; t++) {
				for (short s = 0; s < 4; s++) {
					/*if (block_shape_1[falling_block_type][s][t] > 0) {*/
						falling_block[s][t].block_move(0, move_y);
					/*}*/
				}
			}
		
		}
		else {
			block_fixation();
			stage_judge();
			block_fall_flag = 0;
			block_cooldown = 30;
		}
	}
	else if(block_cooldown>0) {
		block_cooldown--;
	}
	else {
		block_fall_flag = 1;
		make_block();
		block_cooldown = 30;
	}
}

void stage::block_draw()
{
	for (short t = 0; t < 4; t++) {
		for (short s = 0; s < 4; s++) {
			switch (falling_block_angle)
			{
			case 0:
				/*if (block_shape_1[falling_block_type][s][t] > 0) {*/
					falling_block[t][s].block_draw();
				//}
				break;
			case 1:
				//if (block_shape_2[falling_block_type][s][t] > 0) {
					falling_block[t][s].block_draw();
				//}
				break;
			case 2:
				//if (block_shape_3[falling_block_type][s][t] > 0) {
					falling_block[t][s].block_draw();
				//}
				break;
			case 3:
				//if (block_shape_4[falling_block_type][s][t] > 0) {
					falling_block[t][s].block_draw();
				//}
				break;
			default:

				break;
			}
		}
	}
}

void stage::block_fixation()
{
	for (short t = 0; t < 4; t++) {
		for (short s = 0; s < 4; s++) {
			switch (falling_block_angle)
			{
			case 0:
				if (block_shape_1[falling_block_type][t][s] > 0) {
					field[falling_block_x + s][falling_block_y + t].block_make(falling_block[t][s].get_x_num(), falling_block[t][s].get_y_num(), falling_block[t][s].get_red(), falling_block[t][s].get_green(), falling_block[t][s].get_blue());
				}
				break;
			case 1:
				if (block_shape_2[falling_block_type][t][s] > 0) {
					field[falling_block_x + s][falling_block_y + t].block_make(falling_block[t][s].get_x_num(), falling_block[t][s].get_y_num(), falling_block[t][s].get_red(), falling_block[t][s].get_green(), falling_block[t][s].get_blue());
				}
				break;
			case 2:
				if (block_shape_3[falling_block_type][t][s] > 0) {
					field[falling_block_x + s][falling_block_y + t].block_make(falling_block[t][s].get_x_num(), falling_block[t][s].get_y_num(), falling_block[t][s].get_red(), falling_block[t][s].get_green(), falling_block[t][s].get_blue());
				}
				break;
			case 3:
				if (block_shape_4[falling_block_type][t][s] > 0) {
					field[falling_block_x + s][falling_block_y + t].block_make(falling_block[t][s].get_x_num(), falling_block[t][s].get_y_num(), falling_block[t][s].get_red(), falling_block[t][s].get_green(), falling_block[t][s].get_blue());
				}
				break;
			default:
				break;
			}
			
		}
	}
	block_init();
}

void stage::block_init()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			falling_block[i][j].block_make(0, 0, 0, 0, 0, 0);
		}
	}
}

char stage::next_block_used()
{
	char ret_num = next_block[0];
	for (char c = 0; c < 19; c++) {
		next_block[c] = next_block[c + 1];
	}
	nect_block_num--;
	return ret_num;
}

void stage::next_block_draw()
{
	for (int u = 0; u < 3; u++) {
		for (short t = 0; t < 4; t++) {
			for (short s = 0; s < 4; s++) {
				/*if (block_shape_1[falling_block_type][t][s] > 0) {*/
				next_block_preview[u][t][s].block_draw();
				//}
			}
		}
	}
}

void stage::next_block_charge()
{
	if (nect_block_num < block_kind_max) {
		for (char c = 0; c < block_kind_max; c++) {
			next_block[c + 6] = block_order[c % block_kind_max];
			nect_block_num++;
		}
	}

	for (short u = 0; u < 3; u++) {
		for (short t = 0; t < 4; t++) {
			for (short s = 0; s < 4; s++) {
				/*if (block_shape_1[falling_block_type][t][s] > 0) {*/
				next_block_preview[u][t][s].block_init(next_pos_x, next_pos_y+(u*200), block_color_red[next_block[u]], block_color_green[next_block[u]], block_color_blue[next_block[u]],s, t, block_shape_1[next_block[u]][t][s]);
				//}
			}
		}
	}
}

void stage::score_draw()
{	
	DrawFormatStringToHandle(score_x, score_y, GetColor(255, 0, 0), Common::font1, "erazed@%d", erazed_counter);
}

void stage::game_over_judge()
{
	if (game_over_flag >= 1) {
		game_over_count--;
		DrawFormatStringToHandle(score_x, score_y, GetColor(255, 0, 0), Common::font1, "score %d", erazed_counter);
		DrawFormatStringToHandle(score_x, score_y-100, GetColor(255, 0, 255), Common::font1, "GAME OVER");
		if (game_over_count <= 0) {
			game_over_scene_change_flag = 1;
			
		}
	}
}

char stage::stage_all()
{
	stage_process();
	return game_over_scene_change_flag;
}
