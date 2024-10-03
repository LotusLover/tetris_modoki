#include "music.h"
#include"DxLib.h"
#include "Common.h"
char music::music_kind;

void music::play_music(char kind)
{
	if (kind != music_kind) {
		StopSoundMem(Common::music[music_kind]);

		PlaySoundMem(Common::music[kind], DX_PLAYTYPE_LOOP);
		music_kind = kind;
	}

}

void music::stop_music()
{
	StopSoundMem(Common::music[music_kind]);
	music_kind = 0;
}
