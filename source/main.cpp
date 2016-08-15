#include <DxLib.h>
#include "resource.h"

int map001Graph, map001OverlayGraph, map001_;
int map001X = 2, map001Y = 2;
int CharMainX = 9, CharMainY = 7;
int CharDiv[12];
int CharMainRightX = CharMainX * 48 - 48;
int CharMainRightY = CharMainY * 48 - 48;

#include "map.h"
#include "battle.h"
#include "main.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Start();
	Move1();
	WaitKey();
	End();
}