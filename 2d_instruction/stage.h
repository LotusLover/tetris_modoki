#pragma once
#include "block.h"


//テトリスのステージ縦横の大きさ
constexpr int stage_x = 10;
constexpr int stage_y = 20;
constexpr int stage_len = stage_x * stage_y;

constexpr int block_x = 40, block_y = 40;


constexpr int stage_pos_x = 300;
constexpr int stage_pos_y = 200;

constexpr int next_pos_x = stage_pos_x + (stage_x * block_x)+100;
constexpr int next_pos_y = stage_pos_y;

constexpr int score_x = next_pos_x + 200;
constexpr int score_y = next_pos_x;

constexpr int game_over_draw_time = 180;


constexpr int block_kind_max = 7;

constexpr int block_fall_time = 30;
constexpr char block_size_left[7] = { 0,0,0,0,0,1,1 };
constexpr char block_size_right[7] = { 2,2,2,2,2,2,1 };
constexpr char block_size_up[7] = { 1,0,0,0,0,1,0 };
constexpr char block_size_down[7] = { 2,1,1,1,1,2,3 };
										//0 1 2 3
constexpr short block_shape_1[7][4][4] = { {{0,0,0,0}, 
										 {1,1,1,0},
										 {0,1,0,0},
										 {0,0,0,0},},
											
										 {										 
										 {1,1,0,0},
										 {0,1,1,0},
										 {0,0,0,0},
										 {0,0,0,0},},
										 {
										 {0,1,1,0},
										 {1,1,0,0},
										 {0,0,0,0},
										 {0,0,0,0},},
										 {
										 {0,0,1,0},
										 {1,1,1,0},
										 {0,0,0,0},
										 {0,0,0,0},},
										 {
										 {1,0,0,0},
										 {1,1,1,0},
										 {0,0,0,0},
										 {0,0,0,0},},
										 {
										 {0,0,0,0},
										 {0,1,1,0},
										 {0,1,1,0},
										 {0,0,0,0},},
										 {
										 {0,1,0,0},
										 {0,1,0,0},
										 {0,1,0,0},
										 {0,1,0,0},}, };

constexpr short block_shape_2[7][4][4] = {
										{{0,1,0,0},
										 {0,1,1,0},
										 {0,1,0,0},
										 {0,0,0,0},},

										 {
										 {0,1,0,0},
										 {1,1,0,0},
										 {1,0,0,0},
										 {0,0,0,0},},
										 {
										 {1,0,0,0},
										 {1,1,0,0},
										 {0,1,0,0},
										 {0,0,0,0},},
										 {
										 {1,1,0,0},
										 {0,1,0,0},
										 {0,1,0,0},
										 {0,0,0,0},},
										 {
										 {0,1,0,0},
										 {0,1,0,0},
										 {1,1,0,0},
										 {0,0,0,0},},
										 {
										 {0,0,0,0},
										 {0,1,1,0},
										 {0,1,1,0},
										 {0,0,0,0},},
										 {
										 {0,0,0,0},
										 {0,0,0,0},
										 {1,1,1,1},
										 {0,0,0,0},}, };

constexpr short block_shape_3[7][4][4] = {
										{{0,1,0,0},
										 {1,1,1,0},
										 {0,0,0,0},
										 {0,0,0,0},},

										 {
										 {0,0,0,0},
										 {1,1,0,0},
										 {0,1,1,0},
										 {0,0,0,0},},
										 {
										 {0,0,0,0},
										 {0,1,1,0},
										 {1,1,0,0},
										 {0,0,0,0},},
										 {
										 {0,0,0,0},
										 {1,1,1,0},
										 {1,0,0,0},
										 {0,0,0,0},},
										 {
										 {0,0,0,0},
										 {1,1,1,0},
										 {0,0,1,0},
										 {0,0,0,0},},
										 {
										 {0,0,0,0},
										 {0,1,1,0},
										 {0,1,1,0},
										 {0,0,0,0},},
										 {
										 {0,0,1,0},
										 {0,0,1,0},
										 {0,0,1,0},
										 {0,0,1,0},}, };

constexpr short block_shape_4[7][4][4] = {
										{{0,1,0,0},
										 {1,1,0,0},
										 {0,1,0,0},
										 {0,0,0,0},},

										 {
										 {0,0,1,0},
										 {0,1,1,0},
										 {0,1,0,0},
										 {0,0,0,0},},
										 {
										 {0,1,0,0},
										 {0,1,1,0},
										 {0,0,1,0},
										 {0,0,0,0},},
										 {
										 {0,1,0,0},
										 {0,1,0,0},
										 {0,1,1,0},
										 {0,0,0,0},},
										 {
										 {0,1,1,0},
										 {0,1,0,0},
										 {0,1,0,0},
										 {0,0,0,0},},
										 {
										 {0,0,0,0},
										 {0,1,1,0},
										 {0,1,1,0},
										 {0,0,0,0},},
										 {
										 {0,0,0,0},
										 {1,1,1,1},
										 {0,0,0,0},
										 {0,0,0,0},}, };

class stage
{
private:
	char stage_type = 0;
	//char stage_array[stage_x][stage_y];

	char falling_block_x, falling_block_y,falling_block_type, falling_block_angle,falling_size_left, falling_size_right, falling_size_up, falling_size_down;
	block falling_block[4][4];
	block next_block_preview[3][4][4];
	
	unsigned char button_down_flag, button_up_flag, button_right_flag, button_left_flag,button_rotate_flag;

	char block_order[7];
	char next_block[20],nect_block_num;
	int block_fall_count = 0,block_fall_flag=0,block_cooldown=0;
	
	block field[stage_x][stage_y];

	short stage_position_x = 0;
	short stage_position_y = 0;

	short erazed_counter = 0;

	short game_over_flag = 0,game_over_count = 0,game_over_scene_change_flag=0;
public:
	stage();
	~stage();
	
	void stage_init();
	void stage_draw();
	void stage_process();
	void stage_judge();
	void make_block();
	void rotate_block();
	void move_block();
	void block_draw();
	void block_fixation();
	void block_init();

	char next_block_used();
	void next_block_draw();
	void next_block_charge();

	void score_draw();

	void game_over_judge();

	char stage_all();
};

