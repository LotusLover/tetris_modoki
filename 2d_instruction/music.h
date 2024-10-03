#pragma once
class music
{
public:
	static void play_music(char kind);
	static void stop_music();

private:
	static char music_kind;

};