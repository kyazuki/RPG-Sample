#include <DxLib.h>
#include <string>
#include <random>
using namespace std;
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
#include "Function.h"
#include "define.h"
#include "resource.h"

int SelectMenu[6];
int NowTitle, GameEnd = FALSE, GameOver = FALSE;
int BGMVolume = 256, MEVolume = 256, BGSVolume = 256, SEVolume = 256;
int BGM[BGMs], ME[MEs], BGS[BGSs], SE[SEs];
int Key[256];
int Dash = 0, Cheat = 0;
int FontTitle, FontMain, White, Gray, Blue, Yellow, Red;
int MenuGraph[6], MsgGraph, YesNoGraph, SelectGraph, BattleGraph[3], GameOverGraph, BarBaseGraph, HPBarGraph, MPBarGraph, MenuScreen, MenuScreenGAUSS, MoveScreen, MsgScreen, EncountScreen, FilterScreen;
int MapGraph[MAPCOUNT], MapGraph2[MAPCOUNT], MapGraph3[MAPCOUNT], MapOverlayGraph[MAPCOUNT], MapEVGraphUP[EVCOUNT], MapEVGraphDOWN[EVCOUNT], MapEVGraphLEFT[EVCOUNT], MapEVGraphRIGHT[EVCOUNT], MapAttack[MAPCOUNT], MapWidth[MAPCOUNT], MapHeight[MAPCOUNT], MapRoop = 1, RoopCount = 0;
int BattleBackGraph[BATTLEBACK], BattleBackOverGraph[BATTLEBACKOVER], MobGraph[MOBNUM];
int FaceGraph[8], IconGraph[320], CursorGraph[4], OpeningGraph;
string Name = "É`ÉçÉã";
int StatusMainChar[13];
int HPBarWidth, MPBarWidth;
float HPBar, MPBar;
long Money;
int MapNumber, BattleMap, Encount, Walk, BattleMobID, TurnEnd = FALSE, BattleDamage, BattleEnd = FALSE, MobY, Defence, NoAttack = FALSE, RunAway = FALSE, FilterMob[MOBNUM], MobExp[MOBNUM], MobMoney[MOBNUM], LVUP = 0;
int MobStatus[2];
int EffectAttack[4];
int MapX, MapY;
int CharMainX, CharMainY, Direction, FirstPlay = FALSE;
int CharDiv[12];
int CharMainRightX;
int CharMainRightY;
int MapRightX;
int MapRightY;
int MsgBoxX, MsgBoxY;
string ECMsg[MOBNUM], VSMsg[6], EVMsg[6], SYMsg[2], OPMsg[4], EDMsg[4];
random_device rd;
mt19937 mt(rd());
uniform_int_distribution<int> Percent(1, 100);
uniform_int_distribution<int> MobCount(1, 1);
uniform_int_distribution<int> MobID(0, MOBNUM - 1);
uniform_int_distribution<int> AddDamage(0, 10);

#include "save.h"
#include "map.h"
#include "main.h"
#include "battle.h"
#include "event.h"
#include "status.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Start();
	OP();
	while (GameEnd != 1) {
		GameOver = FALSE;
		Title();
		MAPDraw(MapNumber, MapRoop);
		CharMain(1);
		ScreenFlip();
		PlaySoundMem(BGM[TOWN], DX_PLAYTYPE_LOOP);
		while (GameEnd != 1) {
			UpdateKey();
			MAPMove();
			Move();
			if (BattleMap == TRUE && Walk == 1 && Cheat == FALSE) { Encount = Encount + Percent(mt); Walk = 0; }
			if (BattleMap == TRUE && Encount >= 600) Battle();
			if (StatusMainChar[LV] >= 20) { Ending(); break; }
			if (GameOver == TRUE) break;
			if (CheckHitKey(KEY_INPUT_RETURN) == 1 || CheckHitKey(KEY_INPUT_Z) == 1) Event();
			else if (Key[KEY_INPUT_ESCAPE] == 1 || Key[KEY_INPUT_X] == 1) {
				PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
				Menu();
				DrawGraph(0, 0, MenuScreen, FALSE);
				ScreenFlip();
			}
			if (ProcessMessage() < 0) break;
		}
	}
	End();
}