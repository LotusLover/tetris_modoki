#pragma once
#include <vector>
#include "Button.h"
constexpr int menu_num = 4;

class menu
{
public:
	menu();
	~menu();
	
	void menu_move();
	int menu_draw();
	void menu_init();


private:
	std::vector<Button>Buttons;

	short menu_scene;
	short selected_pointer,selected_counter[menu_num];
	
	short now_pointer = 0, select_cool = 0;
};

