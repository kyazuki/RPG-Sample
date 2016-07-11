//起動･終了処理
int Start(void) {
	SetGraphMode(48 * 17, 48 * 13, 32);
	SetWindowSize(48 * 17, 48 * 13);
	if (DxLib_Init() == -1) return -1;
	ChangeWindowMode(1);
	SetMainWindowText("RPG");
	SetWindowIconID(101);
	SetDrawScreen(DX_SCREEN_BACK);
	GHandle = MakeGraph(48 * 17 + 1, 48 * 13 + 1);
	map001Graph = LoadGraph("resource/MAP/001.png");
	map001_ = LoadSoftImage("resource/MAP/001_.png");
	LoadDivGraph("resource/Character/Main/walk.png", 12, 3, 4, 48, 48, CharDiv);
}

int End(void) {
	DxLib_End();
	return 0;
}


//キャラ画像
//int CharMainX = 9, CharMainY = 7;

//キャラ読み込み
void CharMain(void) {
	DrawGraph(CharMainX * 48 - 48, CharMainY * 48 - 48, CharDiv[2], TRUE);
}

//移動
void Move() {
	while (1) {
		ClearDrawScreen();
			if (CheckHitKey(KEY_INPUT_UP) == 1 && attackup(map001_, 0, -24) != 1) CharMainY = CharMainY--;
			if (CheckHitKey(KEY_INPUT_DOWN) == 1 && attackup(map001_, 0, 48 + 24) != 1) CharMainY = CharMainY++;
			if (CheckHitKey(KEY_INPUT_LEFT) == 1 && attackup(map001_, -24, 0) != 1) CharMainX = CharMainX--;
			if (CheckHitKey(KEY_INPUT_RIGHT) == 1 && attackup(map001_, 48 + 24, 0) != 1) CharMainX = CharMainX++;
			if (CharMainX < 1) CharMainX = 1;
			if (CharMainX > 17) CharMainX = 17;
			if (CharMainY < 1) CharMainY = 1;
			if (CharMainY > 13) CharMainY = 13;
		MAP001();
		CharMain();
		int x1 = (CharMainX - 9) * 48, y1 = (CharMainY - 7) * 48, x2 = (CharMainX + 8) * 48 + 1, y2 = (CharMainY + 6) * 48 + 1;
		//GetDrawScreenGraph(x1, y1, x2, y2, GHandle);
		BltDrawValidGraph(DX_SCREEN_BACK, x1, y1, x2, y2, 48 * 17 + 1, 48 * 13 + 1, GHandle);
		//GetDrawScreenGraph((CharMainX - 9) * 48, (CharMainY - 7) * 48, (CharMainX + 8) * 48 + 1, (CharMainY + 6) * 48 + 1, GHandle);
		//ClearDrawScreen();
		DrawGraph(0, 0, GHandle, TRUE);
		ScreenFlip();
		WaitTimer(100);
		if (ProcessMessage() < 0) break;
		printfDx("%d, %d, %d, %d, %d, %d, %d, %d\n",x1,y1,x2,y2,CharMainX,CharMainY,map001X,map001Y);
	}
}

void Move2() {
	while (1) {
		ClearDrawScreen();
		if (CheckHitKey(KEY_INPUT_UP) == 1 && attackup2(map001_, 0, -24) != 1) map001Y = map001Y--;
		if (CheckHitKey(KEY_INPUT_DOWN) == 1 && attackup2(map001_, 0, 48 + 24) != 1) map001Y = map001Y++;
		if (CheckHitKey(KEY_INPUT_LEFT) == 1 && attackup2(map001_, -24, 0) != 1) map001X = map001X--;
		if (CheckHitKey(KEY_INPUT_RIGHT) == 1 && attackup2(map001_, 48 + 24, 0) != 1) map001X = map001X++;
		/**if (map001X < 1) map001X = 1;
		if (map001X > 17) map001X = 17;
		if (map001Y < 1) map001Y = 1;
		if (map001Y > 13) map001Y = 13;**/
		MAP001();
		CharMain();
		ScreenFlip();
		WaitTimer(100);
		if (ProcessMessage() < 0) break;
	}
}