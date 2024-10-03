#include "Input.h"
#include "DxLib.h"

int Input::keyboard[];

int Input::get_keyboard()
{
	char key_state[256];
	GetHitKeyStateAll(key_state);
	for (short s = 0; s < 256; s++) {
		if (key_state[s] != 0) {
			keyboard[s]++;
		}
		else {
			keyboard[s] = 0;
		}
	}



	return 0;
}

int Input::get_key_paramater(unsigned int key)
{
	return keyboard[key];
}