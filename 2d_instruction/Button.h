#pragma once
class Button
{
public:
	Button();
	~Button();

	int button_init(int get_address,int get_img,short get_x,short get_y, float get_size,int button_num);

	
	int button_all(short is_selected,short is_push,short now_scene);
private:
	int button_draw();
	int button_move();


	int address, img, count,selected_count,num;
	char flag;
	short x, y;
	float size;
};

