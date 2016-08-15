//ãNìÆ•èIóπèàóù
int Start(void) {
	SetGraphMode(48 * 17, 48 * 13, 32);
	SetWindowSize(48 * 17, 48 * 13);
	if (DxLib_Init() == -1) return -1;
	ChangeWindowMode(1);
	SetMainWindowText("RPG");
	SetWindowIconID(101);
	SetDrawScreen(DX_SCREEN_BACK);
	map001Graph = LoadGraph("resource/MAP/001.png");
	map001OverlayGraph = LoadGraph("resource/MAP/001o.png");
	map001_ = LoadSoftImage("resource/MAP/001_.png");
	LoadDivGraph("resource/Character/Main/walk.png", 12, 3, 4, 48, 48, CharDiv);
}

int End(void) {
	DxLib_End();
	return 0;
}


//ÉLÉÉÉâì«Ç›çûÇ›
void CharMain(int i) {
	DrawGraph(CharMainRightX, CharMainRightY - 6, CharDiv[i], TRUE);
	//MAP001Overlay();
}

//à⁄ìÆ
void MoveSupportUP(int i)
{
	CharMainRightY = CharMainRightY - 3;
	ClearDrawScreen();
	MAP001();
	CharMain(i);
	ScreenFlip();
	WaitTimer(15);
}
void MoveSupportDOWN(int i)
{
	CharMainRightY = CharMainRightY + 3;
	ClearDrawScreen();
	MAP001();
	CharMain(i);
	ScreenFlip();
	WaitTimer(15);
}
void MoveSupportLEFT(int i)
{
	CharMainRightX = CharMainRightX - 3;
	ClearDrawScreen();
	MAP001();
	CharMain(i);
	ScreenFlip();
	WaitTimer(15);
}
void MoveSupportRIGHT(int i)
{
	CharMainRightX = CharMainRightX + 3;
	ClearDrawScreen();
	MAP001();
	CharMain(i);
	ScreenFlip();
	WaitTimer(15);
}

void MoveSupportDashUP(int i)
{
	CharMainRightY = CharMainRightY - 6;
	ClearDrawScreen();
	MAP001();
	CharMain(i);
	ScreenFlip();
	WaitTimer(5);
}
void MoveSupportDashDOWN(int i)
{
	CharMainRightY = CharMainRightY + 6;
	ClearDrawScreen();
	MAP001();
	CharMain(i);
	ScreenFlip();
	WaitTimer(5);
}
void MoveSupportDashLEFT(int i)
{
	CharMainRightX = CharMainRightX - 6;
	ClearDrawScreen();
	MAP001();
	CharMain(i);
	ScreenFlip();
	WaitTimer(5);
}
void MoveSupportDashRIGHT(int i)
{
	CharMainRightX = CharMainRightX + 6;
	ClearDrawScreen();
	MAP001();
	CharMain(i);
	ScreenFlip();
	WaitTimer(5);
}


void Move1() {
	int U = 0, D = 0, L = 0, R = 0;
	int U1 = 0, U2 = 0, D1 = 0, D2 = 0, L1 = 0, L2 = 0, R1 = 0, R2 = 0;
	while (1) {
		ClearDrawScreen();
		
		if (CheckHitKey(KEY_INPUT_UP) == 1)
		{
			if (attackup(map001_, 0, -24) != 1)
			{
				if (CheckHitKey(KEY_INPUT_LCONTROL) == 0)
				{
					if (U == 0)
					{
						MoveSupportUP(10);
						MoveSupportUP(10);
						MoveSupportUP(10);
						MoveSupportUP(10);
						MoveSupportUP(10);
						MoveSupportUP(10);
						MoveSupportUP(10);
						MoveSupportUP(9);
						MoveSupportUP(9);
						MoveSupportUP(9);
						MoveSupportUP(9);
						MoveSupportUP(9);
						MoveSupportUP(9);
						MoveSupportUP(10);
						MoveSupportUP(10);
						MoveSupportUP(10);
						CharMainY = (CharMainRightY + 48) / 48;
						U1 = 1;
					}
					if (U == 1)
					{
						MoveSupportUP(10);
						MoveSupportUP(10);
						MoveSupportUP(10);
						MoveSupportUP(10);
						MoveSupportUP(10);
						MoveSupportUP(10);
						MoveSupportUP(10);
						MoveSupportUP(11);
						MoveSupportUP(11);
						MoveSupportUP(11);
						MoveSupportUP(11);
						MoveSupportUP(11);
						MoveSupportUP(11);
						MoveSupportUP(10);
						MoveSupportUP(10);
						MoveSupportUP(10);
						CharMainY = (CharMainRightY + 48) / 48;
						U2 = 1;
					}

					if (U1 == 1) U = 1; U1 = 0;
					if (U2 == 1) U = 0; U2 = 0;
				}
				if (CheckHitKey(KEY_INPUT_LCONTROL) == 1)
				{
					if (U == 0)
					{
						MoveSupportDashUP(10);
						MoveSupportDashUP(10);
						MoveSupportDashUP(10);
						MoveSupportDashUP(10);
						MoveSupportDashUP(9);
						MoveSupportDashUP(9);
						MoveSupportDashUP(10);
						MoveSupportDashUP(10);
						CharMainY = (CharMainRightY + 48) / 48;
						U1 = 1;
					}
					if (U == 1)
					{
						MoveSupportDashUP(10);
						MoveSupportDashUP(10);
						MoveSupportDashUP(10);
						MoveSupportDashUP(10);
						MoveSupportDashUP(11);
						MoveSupportDashUP(11);
						MoveSupportDashUP(10);
						MoveSupportDashUP(10);
						CharMainY = (CharMainRightY + 48) / 48;
						U2 = 1;
					}

					if (U1 == 1) U = 1; U1 = 0;
					if (U2 == 1) U = 0; U2 = 0;
				}
			}
			if (attackup(map001_, 0, -24) == 1)
			{
				MAP001();
				CharMain(10);
				ScreenFlip();
			}
		}
		if (CheckHitKey(KEY_INPUT_DOWN) == 1)
		{
			if (attackup(map001_, 0, 48 + 24) != 1)
			{
				if (CheckHitKey(KEY_INPUT_LCONTROL) == 0)
				{
					if (D == 0)
					{
						MoveSupportDOWN(1);
						MoveSupportDOWN(1);
						MoveSupportDOWN(1);
						MoveSupportDOWN(1);
						MoveSupportDOWN(1);
						MoveSupportDOWN(1);
						MoveSupportDOWN(1);
						MoveSupportDOWN(0);
						MoveSupportDOWN(0);
						MoveSupportDOWN(0);
						MoveSupportDOWN(0);
						MoveSupportDOWN(0);
						MoveSupportDOWN(0);
						MoveSupportDOWN(1);
						MoveSupportDOWN(1);
						MoveSupportDOWN(1);
						CharMainY = (CharMainRightY + 48) / 48;
						D1 = 1;
					}
					if (D == 1)
					{
						MoveSupportDOWN(1);
						MoveSupportDOWN(1);
						MoveSupportDOWN(1);
						MoveSupportDOWN(1);
						MoveSupportDOWN(1);
						MoveSupportDOWN(1);
						MoveSupportDOWN(1);
						MoveSupportDOWN(2);
						MoveSupportDOWN(2);
						MoveSupportDOWN(2);
						MoveSupportDOWN(2);
						MoveSupportDOWN(2);
						MoveSupportDOWN(2);
						MoveSupportDOWN(1);
						MoveSupportDOWN(1);
						MoveSupportDOWN(1);
						CharMainY = (CharMainRightY + 48) / 48;
						D2 = 1;
					}

					if (D1 == 1) D = 1; D1 = 0;
					if (D2 == 1) D = 0; D2 = 0;
				}
				if (CheckHitKey(KEY_INPUT_LCONTROL) == 1)
				{
					if (D == 0)
					{
						MoveSupportDashDOWN(1);
						MoveSupportDashDOWN(1);
						MoveSupportDashDOWN(1);
						MoveSupportDashDOWN(1);
						MoveSupportDashDOWN(0);
						MoveSupportDashDOWN(0);
						MoveSupportDashDOWN(1);
						MoveSupportDashDOWN(1);
						CharMainY = (CharMainRightY + 48) / 48;
						D1 = 1;
					}
					if (D == 1)
					{
						MoveSupportDashDOWN(1);
						MoveSupportDashDOWN(1);
						MoveSupportDashDOWN(1);
						MoveSupportDashDOWN(1);
						MoveSupportDashDOWN(2);
						MoveSupportDashDOWN(2);
						MoveSupportDashDOWN(1);
						MoveSupportDashDOWN(1);
						CharMainY = (CharMainRightY + 48) / 48;
						D2 = 1;
					}

					if (D1 == 1) D = 1; D1 = 0;
					if (D2 == 1) D = 0; D2 = 0;
				}
			}
			if (attackup(map001_, 0, 48 + 24) == 1)
			{
				MAP001();
				CharMain(1);
				ScreenFlip();
			}
		}
		if (CheckHitKey(KEY_INPUT_LEFT) == 1)
		{
			if (attackup(map001_, -24, 0) != 1)
			{
				if (CheckHitKey(KEY_INPUT_LCONTROL) == 0)
				{
					if (L == 0)
					{
						MoveSupportLEFT(4);
						MoveSupportLEFT(4);
						MoveSupportLEFT(4);
						MoveSupportLEFT(4);
						MoveSupportLEFT(4);
						MoveSupportLEFT(4);
						MoveSupportLEFT(4);
						MoveSupportLEFT(3);
						MoveSupportLEFT(3);
						MoveSupportLEFT(3);
						MoveSupportLEFT(3);
						MoveSupportLEFT(3);
						MoveSupportLEFT(3);
						MoveSupportLEFT(4);
						MoveSupportLEFT(4);
						MoveSupportLEFT(4);
						CharMainX = (CharMainRightX + 48) / 48;
						L1 = 1;
					}
					if (L == 1)
					{
						MoveSupportLEFT(4);
						MoveSupportLEFT(4);
						MoveSupportLEFT(4);
						MoveSupportLEFT(4);
						MoveSupportLEFT(4);
						MoveSupportLEFT(4);
						MoveSupportLEFT(4);
						MoveSupportLEFT(5);
						MoveSupportLEFT(5);
						MoveSupportLEFT(5);
						MoveSupportLEFT(5);
						MoveSupportLEFT(5);
						MoveSupportLEFT(5);
						MoveSupportLEFT(4);
						MoveSupportLEFT(4);
						MoveSupportLEFT(4);
						CharMainX = (CharMainRightX + 48) / 48;
						L2 = 1;
					}

					if (L1 == 1) L = 1; L1 = 0;
					if (L2 == 1) L = 0; L2 = 0;
				}
				if (CheckHitKey(KEY_INPUT_LCONTROL) == 1)
				{
					if (L == 0)
					{
						MoveSupportDashLEFT(4);
						MoveSupportDashLEFT(4);
						MoveSupportDashLEFT(4);
						MoveSupportDashLEFT(4);
						MoveSupportDashLEFT(3);
						MoveSupportDashLEFT(3);
						MoveSupportDashLEFT(4);
						MoveSupportDashLEFT(4);
						CharMainX = (CharMainRightX + 48) / 48;
						L1 = 1;
					}
					if (L == 1)
					{
						MoveSupportDashLEFT(4);
						MoveSupportDashLEFT(4);
						MoveSupportDashLEFT(4);
						MoveSupportDashLEFT(4);
						MoveSupportDashLEFT(5);
						MoveSupportDashLEFT(5);
						MoveSupportDashLEFT(4);
						MoveSupportDashLEFT(4);
						CharMainX = (CharMainRightX + 48) / 48;
						L2 = 1;
					}

					if (L1 == 1) L = 1; L1 = 0;
					if (L2 == 1) L = 0; L2 = 0;
				}
			}
			if (attackup(map001_, -24, 0) == 1)
			{
				MAP001();
				CharMain(4);
				ScreenFlip();
			}
		}
		if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
		{
			if (attackup(map001_, 48 + 24, 0) != 1)
			{
				if (CheckHitKey(KEY_INPUT_LCONTROL) == 0)
				{
					if (R == 0)
					{
						MoveSupportRIGHT(7);
						MoveSupportRIGHT(7);
						MoveSupportRIGHT(7);
						MoveSupportRIGHT(7);
						MoveSupportRIGHT(7);
						MoveSupportRIGHT(7);
						MoveSupportRIGHT(7);
						MoveSupportRIGHT(6);
						MoveSupportRIGHT(6);
						MoveSupportRIGHT(6);
						MoveSupportRIGHT(6);
						MoveSupportRIGHT(6);
						MoveSupportRIGHT(6);
						MoveSupportRIGHT(7);
						MoveSupportRIGHT(7);
						MoveSupportRIGHT(7);
						CharMainX = (CharMainRightX + 48) / 48;
						R1 = 1;
					}
					if (R == 1)
					{
						MoveSupportRIGHT(7);
						MoveSupportRIGHT(7);
						MoveSupportRIGHT(7);
						MoveSupportRIGHT(7);
						MoveSupportRIGHT(7);
						MoveSupportRIGHT(7);
						MoveSupportRIGHT(7);
						MoveSupportRIGHT(8);
						MoveSupportRIGHT(8);
						MoveSupportRIGHT(8);
						MoveSupportRIGHT(8);
						MoveSupportRIGHT(8);
						MoveSupportRIGHT(8);
						MoveSupportRIGHT(7);
						MoveSupportRIGHT(7);
						MoveSupportRIGHT(7);
						CharMainX = (CharMainRightX + 48) / 48;
						R2 = 1;
					}

					if (R1 == 1) R = 1; R1 = 0;
					if (R2 == 1) R = 0; R2 = 0;
				}
				if (CheckHitKey(KEY_INPUT_LCONTROL) == 1)
				{
					if (R == 0)
					{
						MoveSupportDashRIGHT(7);
						MoveSupportDashRIGHT(7);
						MoveSupportDashRIGHT(7);
						MoveSupportDashRIGHT(7);
						MoveSupportDashRIGHT(6);
						MoveSupportDashRIGHT(6);
						MoveSupportDashRIGHT(7);
						MoveSupportDashRIGHT(7);
						CharMainX = (CharMainRightX + 48) / 48;
						R1 = 1;
					}
					if (R == 1)
					{
						MoveSupportDashRIGHT(7);
						MoveSupportDashRIGHT(7);
						MoveSupportDashRIGHT(7);
						MoveSupportDashRIGHT(7);
						MoveSupportDashRIGHT(8);
						MoveSupportDashRIGHT(8);
						MoveSupportDashRIGHT(7);
						MoveSupportDashRIGHT(7);
						CharMainX = (CharMainRightX + 48) / 48;
						R2 = 1;
					}

					if (R1 == 1) R = 1; R1 = 0;
					if (R2 == 1) R = 0; R2 = 0;
				}
			}
			if (attackup(map001_, 48 + 24, 0) == 1)
			{
				MAP001();
				CharMain(7);
				ScreenFlip();
			}
		}

		if (ProcessMessage() < 0) break;
	}
}

void Move2() {
	while (1) {
		ClearDrawScreen();
		if (CheckHitKey(KEY_INPUT_UP) == 1 && attackup2(map001_, 0, -24) != 1) map001Y = map001Y--;
		if (CheckHitKey(KEY_INPUT_DOWN) == 1 && attackup2(map001_, 0, 48 + 24) != 1) map001Y = map001Y++;
		if (CheckHitKey(KEY_INPUT_LEFT) == 1 && attackup2(map001_, -24, 0) != 1) map001X = map001X--;
		if (CheckHitKey(KEY_INPUT_RIGHT) == 1 && attackup2(map001_, 48 + 24, 0) != 1) map001X = map001X++;
		MAP001();
		CharMain(2);
		ScreenFlip();
		WaitTimer(10);
		if (ProcessMessage() < 0) break;
	}
}