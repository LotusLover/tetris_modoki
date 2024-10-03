#include "block.h"
#include "DxLib.h"
#include "stage.h"
void block::destroy_check()
{

}

void block::block_move(char move_x_num, char move_y_num)
{
	x_num += move_x_num;
	y_num += move_y_num;
}

void block::block_init(unsigned int set_x, unsigned int set_y, unsigned int set_red, unsigned int set_green, unsigned int set_blue, unsigned char set_x_num, unsigned char set_y_num,unsigned int set_flag)
{
	x = set_x;
	y = set_y;
	red=set_red;
	green = set_green;
	blue = set_blue;
	x_num = set_x_num;
	y_num = set_y_num;

	flag = set_flag;
}

void block::block_draw()
{
	if (flag > 0) {
		SetDrawBright(red, green, blue);
		DrawRotaGraph(x+x_num*40, y+y_num*40, 0.1, 0, Common::block_img, TRUE);
		SetDrawBright(255, 255, 255);
	}
}

void block::block_make(unsigned int set_x_num, unsigned int set_y_num, unsigned int set_red, unsigned int set_green, unsigned int set_blue, unsigned int set_flag)
{
	x_num = set_x_num;
	y_num = set_y_num;
	red = set_red;
	green = set_green;
	blue = set_blue;
	flag = set_flag;
}

void block::block_all()
{
	if (flag > 0) {
		block_draw();
	}
}

block::block()
{
}

block::~block()
{
}
