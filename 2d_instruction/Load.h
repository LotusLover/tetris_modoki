#pragma once
class Load
{
	static short img_loading_status,music_loading_status,first_loading_status;

public:
	static short img_load();
	
	static short music_load();

	static short load_second();

	static short load_first();
};

