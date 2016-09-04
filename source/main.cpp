#include <DxLib.h>
#include <string>
using namespace std;
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
#include "Function.h"
#include "define.h"
#include "resource.h"

int SelectMenu[6];
int GameEnd;
int BGMVolume = 256, MEVolume = 256, BGSVolume = 256, SEVolume = 256;
int BGM[2], ME[1], BGS[1], SE[8], BGMs = 2, MEs = 1, BGSs = 1, SEs = 8;
int Key[256];
int Dash = 0, Cheat = 0;
int FontTitle, FontMain, White, Gray, Blue, Yellow, Red;
int MenuGraph[6], MsgGraph, SelectGraph, BarBaseGraph, HPBarGraph, MPBarGraph, MenuScreen, MenuScreenGAUSS, MoveScreen, MsgScreen;
int MapGraph[MAPCOUNT], MapGraph2[MAPCOUNT], MapGraph3[MAPCOUNT], MapOverlayGraph[MAPCOUNT], MapEVGraphUP[EVCOUNT], MapEVGraphDOWN[EVCOUNT], MapEVGraphLEFT[EVCOUNT], MapEVGraphRIGHT[EVCOUNT], MapAttack[MAPCOUNT], MapWidth[MAPCOUNT], MapHeight[MAPCOUNT], MapRoop = 1, RoopCount = 0;
int FaceGraph[8], IconGraph[320], CursorGraph[4];
string Name;
int StatusMainChar[13];
int HPBarWidth, MPBarWidth;
float HPBar, MPBar;
long Money;
int MapNumber;
int MapX, MapY;
int CharMainX, CharMainY, Direction;
int CharDiv[12];
int CharMainRightX;
int CharMainRightY;
int MapRightX;
int MapRightY;
int MsgBoxY;
string EVMsg[1];

#include "save.h"
#include "map.h"
#include "battle.h"
#include "main.h"
#include "event.h"

#include "status.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Start();
	MsgLoad();
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
		printfDx("%d %d %d %d %d\n", CharMainX, CharMainY, MapX, MapY, MapNumber);
		UpdateKey();
		MAPMove();
		Move();
		if (CheckHitKey(KEY_INPUT_RETURN) == 1 || CheckHitKey(KEY_INPUT_Z) == 1) Event();
		else if (Key[KEY_INPUT_ESCAPE] == 1 || Key[KEY_INPUT_X] == 1) {
			PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
			Menu();
			DrawGraph(0, 0, MenuScreen, FALSE);
			ScreenFlip();
		}
		if (ProcessMessage() < 0) break;
	}
	End();
}