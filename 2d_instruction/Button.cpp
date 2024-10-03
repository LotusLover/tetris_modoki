#include "Button.h"
#include "DxLib.h"
#include "Common.h"

Button::Button()
{
}

Button::~Button()
{
}

int Button::button_init(int get_address, int get_img, short get_x, short get_y,float get_size,int button_num)
{
	address = get_address;
	img = get_img;
	x = get_x;
	y = get_y;
	size = get_size;
	num = button_num;
	selected_count = 0;
	return 0;
}

int Button::button_draw()
{
	DrawRotaGraph(x - (selected_count * 15), y, size, 0, img, TRUE);
	return 0;
}

int Button::button_move()
{
	return 0;
}

int Button::button_all(short selected_button_num, short is_push, short now_scene)
{
	if (selected_button_num == num) {
		if (selected_count < 10) {
			selected_count++;
		}
	}
	else {
		if (selected_count >0) {
			selected_count--;
		}
	}
	button_draw();
	if (is_push) {
		return address;
	}
	else {
		return now_scene;
	}
}
