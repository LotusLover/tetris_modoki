#pragma once
class Common
{
private:
	static int scene_number;
	static long long score;
public:
	inline static bool scene_change(int scene_change_number) {
		if (scene_change_number >= 100 && scene_change_number <= 1000) {
			scene_number = scene_change_number;
			return 0;
		}
		return 1;
	}
	inline static int get_scene_number() {
		return scene_number;
	}

	inline static void score_change(int add_score) {
		score += add_score;
	}

	inline static int get_score() {
		return score;
	}

	inline static void stage_time_change(int add_time) {
		stage_time_count = add_time;
	}

	inline static void game_time_change(int add_time) {
		game_time_count = add_time;
	}

	inline static long get_stage_time_count() {
		return stage_time_count;
	}

	inline static long get_game_time_count() {
		return game_time_count;
	}

	static int m_font;
	static int font1;
	static int font2;
	static int quote_font;

	static int block_img;
	static int back_img;
	static int stage_img;
	static int menu_img[10];

	static int logo;
	static int start_sound;

	static int music[6];
	static int sound[10];

	static long game_time_count;
	static long stage_time_count;

	static char difficulty;

};




//難易度
constexpr char dif_Easy = 0;
constexpr char dif_Normal = 1;
constexpr char dif_Hard = 2;
constexpr char dif_Lunatic = 3;
constexpr char dif_Extra = 10;
//ゲームのどの場面か
constexpr int game_launch = 100;
constexpr int game_launch_loading = 101;

constexpr int game_menu_preload = 200;
constexpr int game_menu = 201;


constexpr int game_play_preload = 300;
constexpr int game_play = 301;

constexpr int game_end = 1000;

//メニュー内のどの場面か
constexpr char menu_start = 1;

constexpr char menu_menu = 10;

constexpr char menu_difficulty_select = 20;
constexpr char menu_player_select = 21;
constexpr char menu_skill_select = 22;
constexpr char menu_route_select = 23;
constexpr char menu_game_ready = 24;
constexpr char menu_end = 100;


//ゲームがどの状況か
constexpr char game_status_pause = 0;
constexpr char game_status_playing = 1;
constexpr char game_status_story = 2;
constexpr char game_status_over = 50;
constexpr char game_status_story_preload = 12;


//180/π 　　　？°/rad_angle = ?°のラジアンになる
//出来ることならあらかじめ計算した値を使いたいがいちいち電卓たたくのは・・・という人向け
//きっとコンパイラがいい感じにしてくれるさ
constexpr double rad_angle = 57.29577951308232;


//fps 書くのは別にここじゃなくてもいい
constexpr int fps = 60;

//ゲームの画面の上下左右の大きさ（ピクセル）
constexpr short game_screen_up = 0;
constexpr short game_screen_down = 1080;
constexpr short game_screen_left = 0;
constexpr short game_screen_right = 1920;
//画面外も含むゲームフィールドの上下左右の大きさ
constexpr short game_field_up = -320;
constexpr short game_field_down = 1600;
constexpr short game_field_left = -480;
constexpr short game_field_right = 2400;
//画面外も含むゲームフィールドの広さ
constexpr short game_field_all_y = 1920;
constexpr short game_field_all_x = 2880;
//画面外も含むゲームフィールドをいくつに区切るか
//これの使い方がわかれば弾幕ゲーで派手な弾幕・ボムが作れるようになる
constexpr short game_area_y = 24;
constexpr short game_area_x = 36;
//一区切りどれくらいか
constexpr short game_area_partition_x = game_field_all_x / game_area_x;
constexpr short game_area_partition_y = game_field_all_y / game_area_y;
