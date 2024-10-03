#pragma once
#include "Common.h"
class block
{
private:
	//unsigned int color;
	unsigned int flag, type, x, y, x_num, y_num, red, green, blue;

public:
	void destroy_check();
	void block_move(char move_x,char move_y);
	void block_init(unsigned int set_x, unsigned int set_y, unsigned int set_red, unsigned int set_green, unsigned int set_blue, unsigned char set_x_num, unsigned char set_y_num,unsigned int set_flag);
	void block_draw();
	void block_make(unsigned int set_x, unsigned int set_y, unsigned int set_red, unsigned int set_green, unsigned int set_blue, unsigned int set_flag=2);

	void block_all();


	inline unsigned char get_x_num() {
		return x_num;
	}
	inline unsigned char get_y_num() {
		return y_num;
	}
	inline unsigned char get_flag() {
		return flag;
	}
	/*inline unsigned char get_color() {
		return color;
	}*/

	inline unsigned char get_red() {
		return red;
	}
	inline unsigned char get_green() {
		return green;
	}
	inline unsigned char get_blue() {
		return blue;
	}

	block();
	~block();
};