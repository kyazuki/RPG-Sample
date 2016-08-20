#include <DxLib.h>
#include <string>
using namespace std;
#include "define.h"
#include "resource.h"

int SelectMenu[6];
int GameEnd;
int BGMVolume = 256, MEVolume = 256, BGSVolume = 256, SEVolume = 256;
int BGM[2], ME[1], BGS[1], SE[6], BGMs = 2, MEs = 1, BGSs = 1, SEs = 6;
int Key[256];
int Dash = 0, Cheat = 0;
int FontTitle, FontMain, White, Gray, Blue;
int MenuGraph[6], MsgGraph, SelectGraph, MenuScreen, MenuScreenGAUSS, MoveScreen;
int MapGraph[2], MapGraph2[2], MapGraph3[2], MapOverlayGraph[2], MapAttack[2], MapWidth[2], MapHeight[2], MapRoop = 1, RoopCount = 0;
int FaceGraph[8], IconGraph[320];
string Name;
int StatusMainChar[13];
long Money;
int MapNumber = 0;
int MapX = 2, MapY = 2;
int CharMainX = 9, CharMainY = 7, Direction = 1;
int CharDiv[12];
int CharMainRightX = CharMainX * 48 - 48;
int CharMainRightY = CharMainY * 48 - 48;
int MapRightX = MapX * -48 + 48;
int MapRightY = MapY * -48 + 48;

#include "save.h"
#include "map.h"
#include "battle.h"
#include "main.h"

#include "status.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Start();
	StatusSet();
	LoadAllGraphs();
	LoadAllSounds();
	ConfigLoad();
	SettingsSounds(BGMVolume, MEVolume, BGSVolume, SEVolume);
	Title();
	MAPDraw(MapNumber, MapRoop);
	CharMain(1);
	ScreenFlip();
	PlaySoundMem(BGM[TOWN], DX_PLAYTYPE_BACK);
	while(GameEnd != 1) {
		UpdateKey();
		MAPMove();
		Move();
		if (Key[KEY_INPUT_ESCAPE] == 1 || Key[KEY_INPUT_X] == 1) {
			PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
			Menu();
			DrawGraph(0, 0, MenuScreen, FALSE);
			ScreenFlip();
		}
		if (ProcessMessage() < 0) break;
	}
	End();
}