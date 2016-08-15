#include <DxLib.h>
#include "resource.h"

int Map001Graph, Map001OverlayGraph, Map001_;
int Map001X = 2, Map001Y = 2;
int CharMainX = 9, CharMainY = 7;
int CharDiv[12];
int CharMainRightX = CharMainX * 48 - 48;
int CharMainRightY = CharMainY * 48 - 48;
int Map001RightX = Map001X * -48 + 48;
int Map001RightY = Map001Y * -48 + 48;

#include "map.h"
#include "battle.h"
#include "main.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Start();
	MAP001();
	CharMain(1);
	while(1) {
		Move1();
		if (ProcessMessage() < 0) break;
	}
	WaitKey();
	End();
}