//起動･終了処理
int Start(void) {
	SetGraphMode(48 * 17, 48 * 13, 32, 60);
	//SetOutApplicationLogValidFlag(false);
	SetWindowSize(48 * 17, 48 * 13);
	if (DxLib_Init() == -1) return -1;
	ChangeWindowMode(1);
	SetMainWindowText("RPG");
	SetWindowIconID(101);
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();

	AddFontResourceEx("resource/font/mplus-1m-medium.ttf", FR_PRIVATE, NULL);
	FontTitle = CreateFontToHandle("M+ 1m medium", 80, 8, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, DX_CHARSET_DEFAULT, 3);
	FontMain = CreateFontToHandle("M+ 1m medium", 24, 1, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, DX_CHARSET_DEFAULT);
	White = GetColor(255, 255, 255);
	Gray = GetColor(166, 161, 158);
	if (FontTitle == -1) {
		RemoveFontResourceEx("resource/font/mplus-1m-medium.ttf", FR_PRIVATE, NULL);
		DxLib_End();
		return 1;
	}
}

int End(void) {
	InitGraph();
	InitSoundMem();
	DxLib_End();
	return 0;
}

//メモリ読み込み処理
//画像
void LoadAllGraphs(void) {
	MSGLogGraph = LoadGraph("resource/System/window/main.png");
	SelectGraph = LoadGraph("resource/System/select.png");

	Map001Graph = LoadGraph("resource/MAP/001.png");
	Map001OverlayGraph = LoadGraph("resource/MAP/001o.png");
	Map001_ = LoadSoftImage("resource/MAP/001_.png");

	LoadDivGraph("resource/Character/Main/walk.png", 12, 3, 4, 48, 48, CharDiv);
}

//音
void LoadAllSounds(void) {
	BGM[TITLE] = LoadSoundMem("resource/sounds/BGM/Theme1.ogg");
	SE[SELECT] = LoadSoundMem("resource/sounds/SE/common/Cursor2.ogg");
	SE[DECISION] = LoadSoundMem("resource/sounds/SE/common/Decision1.ogg");
	SE[BUZZER] = LoadSoundMem("resource/sounds/SE/common/Buzzer1.ogg");
}

//音量設定
void SettingsSounds(int BGMVo, int MEVo, int BGSVo, int SEVo) {
	int i = 0;
	do {
		ChangeVolumeSoundMem(BGMVo, BGM[i]);
		i++;
	} while (i < 1);
	i = 0;
	do {
		ChangeVolumeSoundMem(MEVo, ME[i]);
		i++;
	} while (i < 0);
	i = 0;
	do {
		ChangeVolumeSoundMem(BGSVo, BGS[i]);
		i++;
	} while (i < 0);
	i = 0;
	do {
		ChangeVolumeSoundMem(SEVo, SE[i]);
		i++;
	} while (i < 3);
}

//キーの押下フレーム数取得関数
int UpdateKey() {
	char tmpKey[256];
	GetHitKeyStateAll(tmpKey);
	for (int i = 0; i<256; i++) {
		if (tmpKey[i] != 0) {
			Key[i]++;
		}
		else {
			Key[i] = 0;
		}
	}
	return 0;
}

//タイトル
void Title(void) {
	int TitleGraph, TitleLogGraph, Bright = 0, Pal = 255, Flag = 0, Select = 0, SelectY = 400, SelectHeight = 38;
	int LogBoxY = 0;
	PlaySoundMem(BGM[TITLE], DX_PLAYTYPE_BACK);
	TitleGraph = LoadGraph("resource/Title/title.png");
	do {
		SetDrawBright(Bright, Bright, Bright);
		DrawGraph(0, 0, TitleGraph, FALSE);
		DrawStringToHandle(305, 200, "Game", White, FontTitle);
		ScreenFlip();
		Bright = Bright + 5;
	} while (Bright < 256);
	WaitTimer(500);
	TitleLogGraph = LoadGraph("resource/System/window/title.png");
	do {
		ClearDrawScreen();
		DrawGraph(0, 0, TitleGraph, FALSE);
		DrawStringToHandle(305, 200, "Game", White, FontTitle);
		DrawModiGraph(288, 453 - LogBoxY, 527, 453 - LogBoxY, 527, 455 + LogBoxY, 288, 455 + LogBoxY, TitleLogGraph, TRUE);
		ScreenFlip();
		LogBoxY = LogBoxY + 7;
	} while (LogBoxY <= 70);
	while (1) {
		ClearDrawScreen();
		DrawGraph(0, 0, TitleGraph, FALSE);
		DrawStringToHandle(305, 200, "Game", White, FontTitle);
		DrawModiGraph(288, 383, 527, 383, 527, 525, 288, 525, TitleLogGraph, TRUE);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, Pal);
		DrawModiGraph(305, SelectY, 510, SelectY, 510, SelectY + 38, 305, SelectY + 38, SelectGraph, TRUE);
		if (Pal == 255) Flag = 1;
		if (Pal == 129) Flag = 0;

		if (Flag == 1) Pal = Pal - 6;
		if (Flag == 0) Pal = Pal + 6;

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		DrawStringToHandle(310, 405, "ニューゲーム", White, FontMain);
		DrawStringToHandle(310, 440, "コンティニュー", Gray, FontMain);
		DrawStringToHandle(310, 475, "オプション", White, FontMain);
		ScreenFlip();

		UpdateKey();
		if (Key[KEY_INPUT_DOWN] == 1) {
			if (SelectY == 434) { SelectY = 469; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
			if (SelectY == 400) { SelectY = 434; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
		}
		if (Key[KEY_INPUT_UP] == 1) {
			if (SelectY == 434) { SelectY = 400; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
			if (SelectY == 469) { SelectY = 434; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
		}
		if (Key[KEY_INPUT_RETURN] == 1) {
			if (SelectY == 400) {
				PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
				break;
			}
			if (SelectY == 434) { PlaySoundMem(SE[BUZZER], DX_PLAYTYPE_BACK); }
			if (SelectY == 469) {
				PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
			}
		}
		if (ProcessMessage() < 0) break;
	}
	int BGMVol;
	BGMVol = BGMVolume;
	LogBoxY = 70;
	do {
		ClearDrawScreen();
		SetDrawBright(Bright, Bright, Bright);
		DrawGraph(0, 0, TitleGraph, FALSE);
		DrawStringToHandle(305, 200, "Game", White, FontTitle);
		if (LogBoxY > 0) DrawModiGraph(288, 453 - LogBoxY, 527, 453 - LogBoxY, 527, 455 + LogBoxY, 288, 455 + LogBoxY, TitleLogGraph, TRUE);
		ScreenFlip();
		ChangeVolumeSoundMem(BGMVol, BGM[TITLE]);
		BGMVol = BGMVol - 2;
		Bright = Bright - 5;
		LogBoxY = LogBoxY - 7;
	} while (BGMVol >= 0);
	StopSoundMem(BGM[TITLE]);
	ChangeVolumeSoundMem(128, BGM[TITLE]);
	DeleteGraph(TitleGraph);
	SetDrawBright(255, 255, 255);
	WaitTimer(1000);
}

//キャラ描画関数
void CharMain(int i) {
	DrawGraph(CharMainRightX, CharMainRightY - 6, CharDiv[i], TRUE);
	//MAP001Overlay();
}

//関数Move用変数
int U = 0, D = 0, L = 0, R = 0;
int U1 = 0, U2 = 0, D1 = 0, D2 = 0, L1 = 0, L2 = 0, R1 = 0, R2 = 0;

//キャラ主体移動補助関数
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

//キャラ主体移動関数
void Move1(void) {
	if (CheckHitKey(KEY_INPUT_UP) == 1)
		{
			if (attackup(Map001_, 0, -24) != 1)
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
			if (attackup(Map001_, 0, -24) == 1)
			{
				MAP001();
				CharMain(10);
				ScreenFlip();
			}
		}
	if (CheckHitKey(KEY_INPUT_DOWN) == 1)
		{
			if (attackup(Map001_, 0, 48 + 24) != 1)
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
			if (attackup(Map001_, 0, 48 + 24) == 1)
			{
				MAP001();
				CharMain(1);
				ScreenFlip();
			}
		}
	if (CheckHitKey(KEY_INPUT_LEFT) == 1)
		{
			if (attackup(Map001_, -24, 0) != 1)
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
			if (attackup(Map001_, -24, 0) == 1)
			{
				MAP001();
				CharMain(4);
				ScreenFlip();
			}
		}
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
		{
			if (attackup(Map001_, 48 + 24, 0) != 1)
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
			if (attackup(Map001_, 48 + 24, 0) == 1)
			{
				MAP001();
				CharMain(7);
				ScreenFlip();
			}
		}
	}

//マップ主体移動補助関数
void Move2SupportUP(int i)
	{
		Map001RightY = Map001RightY + 3;
		ClearDrawScreen();
		MAP001();
		CharMain(i);
		ScreenFlip();
		WaitTimer(15);
	}
void Move2SupportDOWN(int i)
	{
		Map001RightY = Map001RightY - 3;
		ClearDrawScreen();
		MAP001();
		CharMain(i);
		ScreenFlip();
		WaitTimer(15);
	}
void Move2SupportLEFT(int i)
	{
		Map001RightX = Map001RightX + 3;
		ClearDrawScreen();
		MAP001();
		CharMain(i);
		ScreenFlip();
		WaitTimer(15);
	}
void Move2SupportRIGHT(int i)
	{
		Map001RightX = Map001RightX - 3;
		ClearDrawScreen();
		MAP001();
		CharMain(i);
		ScreenFlip();
		WaitTimer(15);
	}

void Move2SupportDashUP(int i)
	{
		Map001RightY = Map001RightY + 6;
		ClearDrawScreen();
		MAP001();
		CharMain(i);
		ScreenFlip();
		WaitTimer(5);
	}
void Move2SupportDashDOWN(int i)
	{
		Map001RightY = Map001RightY - 6;
		ClearDrawScreen();
		MAP001();
		CharMain(i);
		ScreenFlip();
		WaitTimer(5);
	}
void Move2SupportDashLEFT(int i)
	{
		Map001RightX = Map001RightX + 6;
		ClearDrawScreen();
		MAP001();
		CharMain(i);
		ScreenFlip();
		WaitTimer(5);
	}
void Move2SupportDashRIGHT(int i)
	{
		Map001RightX = Map001RightX - 6;
		ClearDrawScreen();
		MAP001();
		CharMain(i);
		ScreenFlip();
		WaitTimer(5);
	}

//マップ主体移動関数
void Move2(void) {
	if (CheckHitKey(KEY_INPUT_UP) == 1)
		{
			if (attackup(Map001_, 0, -24) != 1)
			{
				if (CheckHitKey(KEY_INPUT_LCONTROL) == 0)
				{
					if (U == 0)
					{
						Move2SupportUP(10);
						Move2SupportUP(10);
						Move2SupportUP(10);
						Move2SupportUP(10);
						Move2SupportUP(10);
						Move2SupportUP(10);
						Move2SupportUP(10);
						Move2SupportUP(9);
						Move2SupportUP(9);
						Move2SupportUP(9);
						Move2SupportUP(9);
						Move2SupportUP(9);
						Move2SupportUP(9);
						Move2SupportUP(10);
						Move2SupportUP(10);
						Move2SupportUP(10);
						Map001Y = (Map001RightY - 48) / -48;
						U1 = 1;
					}
					if (U == 1)
					{
						Move2SupportUP(10);
						Move2SupportUP(10);
						Move2SupportUP(10);
						Move2SupportUP(10);
						Move2SupportUP(10);
						Move2SupportUP(10);
						Move2SupportUP(10);
						Move2SupportUP(11);
						Move2SupportUP(11);
						Move2SupportUP(11);
						Move2SupportUP(11);
						Move2SupportUP(11);
						Move2SupportUP(11);
						Move2SupportUP(10);
						Move2SupportUP(10);
						Move2SupportUP(10);
						Map001Y = (Map001RightY - 48) / -48;
						U2 = 1;
					}

					if (U1 == 1) U = 1; U1 = 0;
					if (U2 == 1) U = 0; U2 = 0;
				}
				if (CheckHitKey(KEY_INPUT_LCONTROL) == 1)
				{
					if (U == 0)
					{
						Move2SupportDashUP(10);
						Move2SupportDashUP(10);
						Move2SupportDashUP(10);
						Move2SupportDashUP(10);
						Move2SupportDashUP(9);
						Move2SupportDashUP(9);
						Move2SupportDashUP(10);
						Move2SupportDashUP(10);
						Map001Y = (Map001RightY - 48) / -48;
						U1 = 1;
					}
					if (U == 1)
					{
						Move2SupportDashUP(10);
						Move2SupportDashUP(10);
						Move2SupportDashUP(10);
						Move2SupportDashUP(10);
						Move2SupportDashUP(11);
						Move2SupportDashUP(11);
						Move2SupportDashUP(10);
						Move2SupportDashUP(10);
						Map001Y = (Map001RightY - 48) / -48;
						U2 = 1;
					}

					if (U1 == 1) U = 1; U1 = 0;
					if (U2 == 1) U = 0; U2 = 0;
				}
			}
			if (attackup(Map001_, 0, -24) == 1)
			{
				MAP001();
				CharMain(10);
				ScreenFlip();
			}
		}
	if (CheckHitKey(KEY_INPUT_DOWN) == 1)
		{
			if (attackup(Map001_, 0, 48 + 24) != 1)
			{
				if (CheckHitKey(KEY_INPUT_LCONTROL) == 0)
				{
					if (D == 0)
					{
						Move2SupportDOWN(1);
						Move2SupportDOWN(1);
						Move2SupportDOWN(1);
						Move2SupportDOWN(1);
						Move2SupportDOWN(1);
						Move2SupportDOWN(1);
						Move2SupportDOWN(1);
						Move2SupportDOWN(0);
						Move2SupportDOWN(0);
						Move2SupportDOWN(0);
						Move2SupportDOWN(0);
						Move2SupportDOWN(0);
						Move2SupportDOWN(0);
						Move2SupportDOWN(1);
						Move2SupportDOWN(1);
						Move2SupportDOWN(1);
						Map001Y = (Map001RightY - 48) / -48;
						D1 = 1;
					}
					if (D == 1)
					{
						Move2SupportDOWN(1);
						Move2SupportDOWN(1);
						Move2SupportDOWN(1);
						Move2SupportDOWN(1);
						Move2SupportDOWN(1);
						Move2SupportDOWN(1);
						Move2SupportDOWN(1);
						Move2SupportDOWN(2);
						Move2SupportDOWN(2);
						Move2SupportDOWN(2);
						Move2SupportDOWN(2);
						Move2SupportDOWN(2);
						Move2SupportDOWN(2);
						Move2SupportDOWN(1);
						Move2SupportDOWN(1);
						Move2SupportDOWN(1);
						Map001Y = (Map001RightY - 48) / -48;
						D2 = 1;
					}

					if (D1 == 1) D = 1; D1 = 0;
					if (D2 == 1) D = 0; D2 = 0;
				}
				if (CheckHitKey(KEY_INPUT_LCONTROL) == 1)
				{
					if (D == 0)
					{
						Move2SupportDashDOWN(1);
						Move2SupportDashDOWN(1);
						Move2SupportDashDOWN(1);
						Move2SupportDashDOWN(1);
						Move2SupportDashDOWN(0);
						Move2SupportDashDOWN(0);
						Move2SupportDashDOWN(1);
						Move2SupportDashDOWN(1);
						Map001Y = (Map001RightY - 48) / -48;
						D1 = 1;
					}
					if (D == 1)
					{
						Move2SupportDashDOWN(1);
						Move2SupportDashDOWN(1);
						Move2SupportDashDOWN(1);
						Move2SupportDashDOWN(1);
						Move2SupportDashDOWN(2);
						Move2SupportDashDOWN(2);
						Move2SupportDashDOWN(1);
						Move2SupportDashDOWN(1);
						Map001Y = (Map001RightY - 48) / -48;
						D2 = 1;
					}

					if (D1 == 1) D = 1; D1 = 0;
					if (D2 == 1) D = 0; D2 = 0;
				}
			}
			if (attackup(Map001_, 0, 48 + 24) == 1)
			{
				MAP001();
				CharMain(1);
				ScreenFlip();
			}
		}
	if (CheckHitKey(KEY_INPUT_LEFT) == 1)
		{
			if (attackup(Map001_, -24, 0) != 1)
			{
				if (CheckHitKey(KEY_INPUT_LCONTROL) == 0)
				{
					if (L == 0)
					{
						Move2SupportLEFT(4);
						Move2SupportLEFT(4);
						Move2SupportLEFT(4);
						Move2SupportLEFT(4);
						Move2SupportLEFT(4);
						Move2SupportLEFT(4);
						Move2SupportLEFT(4);
						Move2SupportLEFT(3);
						Move2SupportLEFT(3);
						Move2SupportLEFT(3);
						Move2SupportLEFT(3);
						Move2SupportLEFT(3);
						Move2SupportLEFT(3);
						Move2SupportLEFT(4);
						Move2SupportLEFT(4);
						Move2SupportLEFT(4);
						Map001X = (Map001RightX - 48) / -48;
						L1 = 1;
					}
					if (L == 1)
					{
						Move2SupportLEFT(4);
						Move2SupportLEFT(4);
						Move2SupportLEFT(4);
						Move2SupportLEFT(4);
						Move2SupportLEFT(4);
						Move2SupportLEFT(4);
						Move2SupportLEFT(4);
						Move2SupportLEFT(5);
						Move2SupportLEFT(5);
						Move2SupportLEFT(5);
						Move2SupportLEFT(5);
						Move2SupportLEFT(5);
						Move2SupportLEFT(5);
						Move2SupportLEFT(4);
						Move2SupportLEFT(4);
						Move2SupportLEFT(4);
						Map001X = (Map001RightX - 48) / -48;
						L2 = 1;
					}

					if (L1 == 1) L = 1; L1 = 0;
					if (L2 == 1) L = 0; L2 = 0;
				}
				if (CheckHitKey(KEY_INPUT_LCONTROL) == 1)
				{
					if (L == 0)
					{
						Move2SupportDashLEFT(4);
						Move2SupportDashLEFT(4);
						Move2SupportDashLEFT(4);
						Move2SupportDashLEFT(4);
						Move2SupportDashLEFT(3);
						Move2SupportDashLEFT(3);
						Move2SupportDashLEFT(4);
						Move2SupportDashLEFT(4);
						Map001X = (Map001RightX - 48) / -48;
						L1 = 1;
					}
					if (L == 1)
					{
						Move2SupportDashLEFT(4);
						Move2SupportDashLEFT(4);
						Move2SupportDashLEFT(4);
						Move2SupportDashLEFT(4);
						Move2SupportDashLEFT(5);
						Move2SupportDashLEFT(5);
						Move2SupportDashLEFT(4);
						Move2SupportDashLEFT(4);
						Map001X = (Map001RightX - 48) / -48;
						L2 = 1;
					}

					if (L1 == 1) L = 1; L1 = 0;
					if (L2 == 1) L = 0; L2 = 0;
				}
			}
			if (attackup(Map001_, -24, 0) == 1)
			{
				MAP001();
				CharMain(4);
				ScreenFlip();
			}
		}
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
		{
			if (attackup(Map001_, 48 + 24, 0) != 1)
			{
				if (CheckHitKey(KEY_INPUT_LCONTROL) == 0)
				{
					if (R == 0)
					{
						Move2SupportRIGHT(7);
						Move2SupportRIGHT(7);
						Move2SupportRIGHT(7);
						Move2SupportRIGHT(7);
						Move2SupportRIGHT(7);
						Move2SupportRIGHT(7);
						Move2SupportRIGHT(7);
						Move2SupportRIGHT(6);
						Move2SupportRIGHT(6);
						Move2SupportRIGHT(6);
						Move2SupportRIGHT(6);
						Move2SupportRIGHT(6);
						Move2SupportRIGHT(6);
						Move2SupportRIGHT(7);
						Move2SupportRIGHT(7);
						Move2SupportRIGHT(7);
						Map001X = (Map001RightX - 48) / -48;
						R1 = 1;
					}
					if (R == 1)
					{
						Move2SupportRIGHT(7);
						Move2SupportRIGHT(7);
						Move2SupportRIGHT(7);
						Move2SupportRIGHT(7);
						Move2SupportRIGHT(7);
						Move2SupportRIGHT(7);
						Move2SupportRIGHT(7);
						Move2SupportRIGHT(8);
						Move2SupportRIGHT(8);
						Move2SupportRIGHT(8);
						Move2SupportRIGHT(8);
						Move2SupportRIGHT(8);
						Move2SupportRIGHT(8);
						Move2SupportRIGHT(7);
						Move2SupportRIGHT(7);
						Move2SupportRIGHT(7);
						Map001X = (Map001RightX - 48) / -48;
						R2 = 1;
					}

					if (R1 == 1) R = 1; R1 = 0;
					if (R2 == 1) R = 0; R2 = 0;
				}
				if (CheckHitKey(KEY_INPUT_LCONTROL) == 1)
				{
					if (R == 0)
					{
						Move2SupportDashRIGHT(7);
						Move2SupportDashRIGHT(7);
						Move2SupportDashRIGHT(7);
						Move2SupportDashRIGHT(7);
						Move2SupportDashRIGHT(6);
						Move2SupportDashRIGHT(6);
						Move2SupportDashRIGHT(7);
						Move2SupportDashRIGHT(7);
						Map001X = (Map001RightX - 48) / -48;
						R1 = 1;
					}
					if (R == 1)
					{
						Move2SupportDashRIGHT(7);
						Move2SupportDashRIGHT(7);
						Move2SupportDashRIGHT(7);
						Move2SupportDashRIGHT(7);
						Move2SupportDashRIGHT(8);
						Move2SupportDashRIGHT(8);
						Move2SupportDashRIGHT(7);
						Move2SupportDashRIGHT(7);
						Map001X = (Map001RightX - 48) / -48;
						R2 = 1;
					}

					if (R1 == 1) R = 1; R1 = 0;
					if (R2 == 1) R = 0; R2 = 0;
				}
			}
			if (attackup(Map001_, 48 + 24, 0) == 1)
			{
				MAP001();
				CharMain(7);
				ScreenFlip();
			}
		}
	}