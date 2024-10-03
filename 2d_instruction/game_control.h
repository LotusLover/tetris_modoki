#pragma once
#include <memory>
#include"menu.h"
#include "stage.h"
class game_control
{
public:
	int game_process();
	game_control();
	~game_control();
private:
	void delete_ptr();

	std::unique_ptr<menu>MENU_PTR;
	std::unique_ptr<stage>STAGE_PTR;
};

