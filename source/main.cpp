#include <DxLib.h>
#include "define.h"
#include "resource.h"

int BGMVolume = 256, MEVolume = 256, BGSVolume = 256, SEVolume = 256;
int BGM[2], ME[1], BGS[1], SE[4], BGMs = 2, MEs = 1, BGSs = 1, SEs = 4;
int Key[256];
int Dash = 0, Cheat = 0;
int FontTitle, FontMain, White, Gray;
int OptionScreen, OptionScreenGAUSS, MSGLogGraph, SelectGraph, OptionGraph, Map001Graph, Map001OverlayGraph, Map001_;
int MapX = 2, MapY = 2;
int CharMainX = 9, CharMainY = 7;
int CharDiv[12];
int CharMainRightX = CharMainX * 48 - 48;
int CharMainRightY = CharMainY * 48 - 48;
int MapRightX = MapX * -48 + 48;
int MapRightY = MapY * -48 + 48;

#include "map.h"
#include "battle.h"
#include "main.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Start();
	LoadAllGraphs();
	LoadAllSounds();
	SettingsSounds(BGMVolume, MEVolume, BGSVolume, SEVolume);
	Title();
	MAP001();
	CharMain(1);
	ScreenFlip();
	PlaySoundMem(BGM[TOWN], DX_PLAYTYPE_BACK);
	while(1) {
		UpdateKey();
		Move();
		if (Key[KEY_INPUT_ESCAPE] == 1 || Key[KEY_INPUT_X] == 1) { 
			Option();
			DrawGraph(0, 0, OptionScreen, FALSE);
			ScreenFlip();
		}
		if (ProcessMessage() < 0) break;
	}
	End();
}