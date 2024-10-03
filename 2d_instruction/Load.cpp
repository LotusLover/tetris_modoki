#include "Load.h"
#include"DxLib.h"
#include"Common.h"

short Load::first_loading_status;

short Load::img_load()
{
	/*switch (img_loading_status) {
	case 1:
		Common::block_img = LoadGraph("picture/mino_default.png");
		break;

	case 100:
		Common::font1 = CreateFontToHandle("OCR A Extended", 70, 3, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
		Common::font2 = CreateFontToHandle("OCR A Extended", 70, 3, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
		Common::m_font = CreateFontToHandle("OCR A Extended", 70, 3, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
		Common::quote_font = CreateFontToHandle("HGSGothicE", 40, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
		break;

	}*/
	return 0;
}

short Load::music_load()
{
	return 0;
}

short Load::load_first()
{
	if (first_loading_status == 0) {
		Common::logo = LoadGraph("picture/logo.png");
		Common::start_sound= LoadSoundMem("sound/説明ウインドウが開く.mp3");
		first_loading_status = 1;
		return 0;
	}
	if (GetASyncLoadNum() == 0) {
		first_loading_status = 0;
		return 1;
	}
	return 0;
}

short Load::load_second()
{
	if (first_loading_status == 0) {
		
		Common::block_img = LoadGraph("picture/mino_default.png");
		Common::font1 = CreateFontToHandle("OCR A Extended", 70, 3, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
		Common::font2 = CreateFontToHandle("OCR A Extended", 70, 3, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
		Common::m_font = CreateFontToHandle("OCR A Extended", 70, 3, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
		Common::quote_font = CreateFontToHandle("HGSGothicE", 40, 1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
		SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);
		Common::music[0] = LoadSoundMem("sound/kimigayo_koshin.mp3");
		Common::music[1] = LoadSoundMem("sound/ozora.mp3");
		Common::music[2] = LoadSoundMem("sound/bunretsu_koshin.mp3");
		Common::music[3] = LoadSoundMem("sound/onigunso.mp3");
		Common::music[4] = LoadSoundMem("sound/gaisen.mp3");
		Common::music[5] = LoadSoundMem("sound/shukuten_gallop.mp3");
		Common::sound[0] = LoadSoundMem("sound/カーソル移動8.mp3");
		Common::sound[1] = LoadSoundMem("sound/電子ルーレット停止ボタンを押す.mp3");
		Common::menu_img[0] = LoadGraph("picture/hitoride.png");
		Common::menu_img[1] = LoadGraph("picture/do it your self.png");
		Common::menu_img[2] = LoadGraph("picture/murewonasazuni.png");
		Common::menu_img[3] = LoadGraph("picture/QUIT.png");
		Common::menu_img[4] = LoadGraph("picture/start.png");
		Common::menu_img[5] = LoadGraph("picture/foggy-forest1.jpg");
		Common::menu_img[6] = LoadGraph("picture/ogp_image (1).png");

		
		PlaySoundMem(Common::start_sound, DX_PLAYTYPE_BACK, 1);
		first_loading_status = 1;
		return 0;
	}
	if (GetASyncLoadNum() <= 0) {
		first_loading_status = 0;
		return 1;
	}
	DrawRotaGraph(game_screen_right / 2, game_screen_down / 2, 1, 0, Common::logo, TRUE);

	return 0;
	

}
