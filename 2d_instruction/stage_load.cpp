#include "stage_load.h"
#include "DxLib.h"

constexpr int STAGE_XY_MAX = 1000;

stage_load::stage_load()
{
}

stage_load::~stage_load()
{
}

void stage_load::Stage_loading()
{

	int input[STAGE_XY_MAX];
	char inputc[STAGE_XY_MAX];

	short event_flag = 0;

	short writing_vec_num = 0;
	file_rename();
	fp = FileRead_open(file_name);
	if (fp == NULL) {
		return;
	}
	for (short s = 0; s < 1; s++) {
		while (FileRead_getc(fp) != '\n');
	}
	n = 0; num = 0;
	/*auto itr = PANEL_list.begin();*/
	stage_vector.resize(1);
	auto itr = stage_vector.begin();
	auto itr2 = itr->begin();
	vector_num = 1;
	while (1) {

		for (i = 0; i < STAGE_XY_MAX; i++) {
			inputc[i] = input[i] = FileRead_getc(fp);
			if (inputc[i] == '/') {
				while (FileRead_getc(fp) != '\n');
				i = -1;
				continue;
			}
			if (input[i] == ',') {
				inputc[i] = '\0';
				break;
			}
			if (input[i] == '\n') {
				inputc[i] = '\0';
				vector_num += 1;
				stage_vector.resize(vector_num);
				break;
			}
			if (input[i] == EOF) {
				goto EXFILE;
			}
		}

		//if (num == 0) {
		//	//event_flag = 0;
		//	if (inputc[0] != '#') {
		//		if (inputc[0] == 0) {
		//			goto EXFILE;
		//		}
		//		PANEL_list.push_front(Panel());
		//		itr = PANEL_list.begin();
		//	}
		//	else {
		//		event_flag = 1;
		//	}
		//}

		/*if (event_flag == 0) {*/
			/*switch (num) {
			case 0:itr->x = atoi(inputc); break;
			case 1:itr->y = atoi(inputc); break;
			case 2:itr->danmaku_type = atoi(inputc); break;
			case 3:itr->danmaku_kind = atoi(inputc); break;
			case 4:itr->radius = atoi(inputc); break;
			case 5:itr->hp = atoi(inputc); break;
			case 6:itr->flag = atoi(inputc); break;
			case 7:itr->kind = atoi(inputc); break;
			case 8:itr->r = atoi(inputc); break;
			case 9:itr->g = atoi(inputc); break;
			case 10:itr->b = atoi(inputc); break;
			case 11:itr->item_type = atoi(inputc); break;
			}
			num++;
			if (num == 12) {
				num = 0;
				itr->panel_number = n;
				n++;
			}*/

		if (writing_vec_num != vector_num - 1) {
			writing_vec_num = vector_num - 1;
		}
		
		itr[writing_vec_num].push_back(atoi(inputc));
		
			continue;
		/*}*/
				
	}

EXFILE:
	FileRead_close(fp);
	//	panel_memset(); 
}

void stage_load::Stage_reset()
{
	for (auto itr = stage_vector.begin(); itr != stage_vector.end();) {
		itr->clear();
	}
	stage_vector.clear();
	vector_num = 0;
}
