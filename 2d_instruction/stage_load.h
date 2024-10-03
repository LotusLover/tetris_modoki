#pragma once
#include<vector>
#include <string>


class stage_load
{
public:
	stage_load();
	~stage_load();
	void Stage_loading();
	void Stage_reset();

	char file_name[80] = { "stage/panel_s00.csv" };
	inline void file_rename() {
		file_name[13] = ('%c', stage_num / 10 + 48);
		file_name[14] = ('%c', stage_num % 10 + 48);
	}
private:
	std::vector<std::vector<int>> stage_vector;
	/*std::vector<short[1000]> stage_vector;*/
	char flag = 0;

	int n, num, i, fp,vector_num;
	int stage_num = 0;
};

