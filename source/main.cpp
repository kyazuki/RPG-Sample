#include <DxLib.h>
#include "resource.h"

int BGMVolume = 128, MEVolume = 128, BGSVolume = 128, SEVolume = 128;
int BGM[1], ME[1], BGS[1], SE[3];
int Key[256];
int FontTitle, FontMain, White, Gray;
int Map001Graph, Map001OverlayGraph, Map001_, MSGLogGraph, SelectGraph;
int Map001X = 2, Map001Y = 2;
int CharMainX = 9, CharMainY = 7;
int CharDiv[12];
int CharMainRightX = CharMainX * 48 - 48;
int CharMainRightY = CharMainY * 48 - 48;
int Map001RightX = Map001X * -48 + 48;
int Map001RightY = Map001Y * -48 + 48;

#include "define.h"
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
	while(1) {
		Move1();
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
		if (ProcessMessage() < 0) break;
	}
	End();
}