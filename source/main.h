//起動･終了処理
int Start(void) {
	SetGraphMode(48 * 17, 48 * 13, 32, 60);
	SetOutApplicationLogValidFlag(false);
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
	Blue = GetColor(128, 165, 247);
	Yellow = GetColor(255, 255, 64);
	Red = GetColor(255, 32, 32);
	if (FontTitle == -1 || FontMain == -1) {
		RemoveFontResourceEx("resource/font/mplus-1m-medium.ttf", FR_PRIVATE, NULL);
		DxLib_End();
		return 1;
	}

	MenuScreen = MakeScreen(48 * 17, 48 * 13, FALSE);
	MenuScreenGAUSS = MakeScreen(48 * 17, 48 * 13, FALSE);
	MoveScreen = MakeScreen(48 * 17, 48 * 13, FALSE);
	MsgScreen = MakeScreen(48 * 17, 48 * 13, FALSE);
	EncountScreen = MakeScreen(48 * 17, 48 * 13, FALSE);
	FilterScreen = MakeScreen(48 * 17, 48 * 13, FALSE);
	FilterMob[SLIME] = MakeScreen(127, 106, TRUE);

	SelectMenu[MAINMENU] = 18, SelectMenu[ITEMMENU] = 18, SelectMenu[SKILLMENU] = 18, SelectMenu[EQUIPMENU] = 18, SelectMenu[STATUSMENU] = 18;
	MobExp[SLIME] = 5;
	MobMoney[SLIME] = 5;
}

int End(void) {
	InitGraph();
	InitSoundMem();
	DxLib_End();
	return 0;
}

//OP
void OP(void) {
	WaitTimer(1000);
	int Noise = LoadSoundMem("resource/sounds/Noise.ogg");
	int OPGraph[2];
	OPGraph[0] = LoadGraph("resource/OP/1.png");
	OPGraph[1] = LoadGraph("resource/OP/2.png");
	int Bright = 0;
	do {
		SetDrawBright(Bright, Bright, Bright);
		DrawGraph(0, 0, OPGraph[0], FALSE);
		ScreenFlip();
		if (Bright != 255) Bright = Bright + 5;
	} while (Bright != 255);
	WaitTimer(1500);
	DrawGraph(0, 0, OPGraph[1], FALSE);
	ScreenFlip();
	ChangeVolumeSoundMem(128, Noise);
	PlaySoundMem(Noise, DX_PLAYTYPE_LOOP);

	MsgLoad();
	LoadAllGraphs();
	LoadAllSounds();
	ConfigLoad();
	SettingsSounds(BGMVolume, MEVolume, BGSVolume, SEVolume);

	int Vol = 128;
	do {
		SetDrawBright(Bright, Bright, Bright);
		DrawGraph(0, 0, OPGraph[1], FALSE);
		ScreenFlip();
		if (Bright != 0) Bright = Bright - 5;

		ChangeVolumeSoundMem(Vol, Noise);
		if (Vol != 0) Vol = Vol - 4;
	} while (Bright != 0);
	StopSoundMem(Noise);
	ChangeVolumeSoundMem(128, Noise);

	DeleteGraph(OPGraph[0]);
	DeleteGraph(OPGraph[1]);
	DeleteSoundMem(Noise);
}

//メモリ読み込み処理
//セリフ
//システムメッセージ
char SYMsg1[14 * 2 + 1];
char SYMsg2[19 * 2 + 1];
//イベントセリフ
char EVMsg1[12 * 2 + 1];
char EVMsg2[15 * 2 + 1];
char EVMsg3[16 * 2 + 1];
char EVMsg4[8 * 2 + 1];
char EVMsg5[8 * 2 + 1];
char EVMsg6[14 * 2 + 1];
//バトルセリフ
char VSMsg1[9 * 2 + 1];
char VSMsg2[12 * 2 + 1];
char VSMsg3[12 * 2 + 1];
char VSMsg4[10 * 2 + 1];
char VSMsg5[4 * 2 + 1];
char VSMsg6[6 * 2 + 1];
char ECMsgSlime[11 * 2 + 1];
//オープニング・エンディングメッセージ
char OPMsg1[14 * 2 + 1];
char OPMsg2[13 * 2 + 1];
char OPMsg3[19 * 2 + 1];
char OPMsg4[17 * 2 + 1];
char EDMsg1[24 * 2 + 1];
char EDMsg2[12 * 2 + 1];
char EDMsg3[36 * 2 + 1];
char EDMsg4[12 * 2 + 1];
//char型配列へ変換
void MsgLoad(void) {
	EDMsg[0] = "ここらへんでやめとくか…";
	strncpy_s(EDMsg1, EDMsg[0].c_str(), 24);
	EDMsg[1] = "ん？メール？";
	strncpy_s(EDMsg2, EDMsg[1].c_str(), 12);
	EDMsg[2] = "なんだこれは…このゲームの運営から？";
	strncpy_s(EDMsg3, EDMsg[2].c_str(), 36);
	EDMsg[3] = "これは…！！";
	strncpy_s(EDMsg4, EDMsg[3].c_str(), 12);
	OPMsg[0] = "今日はこのゲームでもやるか…";
	strncpy_s(OPMsg1, OPMsg[0].c_str(), 28);
	OPMsg[1] = "なるほどよくあるＲＰＧだな";
	strncpy_s(OPMsg2, OPMsg[1].c_str(), 26);
	OPMsg[2] = "ふむふむ。それで魔王を倒しに行く、と。";
	strncpy_s(OPMsg3, OPMsg[2].c_str(), 38);
	OPMsg[3] = "家からのスタートか。やっていこうか";
	strncpy_s(OPMsg4, OPMsg[3].c_str(), 34);
	SYMsg[0] = "本当にゲームを終了しますか？";
	strncpy_s(SYMsg1, SYMsg[0].c_str(), 28);
	SYMsg[1] = "エンカウント無効、当たり判定無効中です";
	strncpy_s(SYMsg2, SYMsg[1].c_str(), 28);
	EVMsg[0] = "気をつけて行っておいで。";
	strncpy_s(EVMsg1, EVMsg[0].c_str(), 24);
	EVMsg[1] = "一泊100Gだ。泊まっていくかい？";
	strncpy_s(EVMsg2, EVMsg[1].c_str(), 30);
	EVMsg[2] = "ええとあれがこれでそれがあれで…";
	strncpy_s(EVMsg3, EVMsg[2].c_str(), 32);
	EVMsg[3] = "ご飯まだかなあ…";
	strncpy_s(EVMsg4, EVMsg[3].c_str(), 16);
	EVMsg[4] = "この先は危険だ。";
	strncpy_s(EVMsg5, EVMsg[4].c_str(), 16);
	EVMsg[5] = "もっと強くなってから来なさい";
	strncpy_s(EVMsg6, EVMsg[5].c_str(), 28);
	ECMsg[SLIME] = "スライムがあらわれた！";
	strncpy_s(ECMsgSlime, ECMsg[SLIME].c_str(), 22);
	VSMsg[0] = "チロルはどうする？";
	strncpy_s(VSMsg1, VSMsg[0].c_str(), 18);
	VSMsg[1] = "チロルたちは逃げ出した！";
	strncpy_s(VSMsg2, VSMsg[1].c_str(), 24);
	VSMsg[2] = "しかし逃げられなかった！";
	strncpy_s(VSMsg3, VSMsg[2].c_str(), 24);
	VSMsg[3] = "モンスターを倒した！";
	strncpy_s(VSMsg4, VSMsg[3].c_str(), 20);
	VSMsg[4] = "レベルが";
	strncpy_s(VSMsg5, VSMsg[4].c_str(), 8);
	VSMsg[5] = "つ上がった！";
	strncpy_s(VSMsg6, VSMsg[5].c_str(), 12);
}

//画像
void LoadAllGraphs(void) {
	MenuGraph[MAINMENU] = LoadGraph("resource/System/window/menu.png");
	MenuGraph[ITEMMENU] = LoadGraph("resource/System/window/item.png");
	MenuGraph[SKILLMENU] = LoadGraph("resource/System/window/skill.png");
	MenuGraph[EQUIPMENU] = LoadGraph("resource/System/window/equip.png");
	MenuGraph[STATUSMENU] = LoadGraph("resource/System/window/status.png");
	MenuGraph[OPTIONMENU] = LoadGraph("resource/System/window/option.png");
	MsgGraph = LoadGraph("resource/System/window/msg.png");
	YesNoGraph = LoadGraph("resource/System/window/yesno.png");
	BattleGraph[0] = LoadGraph("resource/System/window/battle1.png");
	BattleGraph[1] = LoadGraph("resource/System/window/battle2.png");
	BattleGraph[2] = LoadGraph("resource/System/window/battle3.png");
	LoadDivGraph("resource/Battle/Effect/Hit1.png", 4, 4, 1, 192, 192, EffectAttack);
	GameOverGraph = LoadGraph("resource/System/GameOver.png");
	OpeningGraph = LoadGraph("resource/base.png");

	SelectGraph = LoadGraph("resource/System/select.png");
	BarBaseGraph = LoadGraph("resource/System/BarBase.png");
	HPBarGraph = LoadGraph("resource/System/HP.png");
	MPBarGraph = LoadGraph("resource/System/MP.png");

	LoadDivGraph("resource/faces/1.png", 8, 4, 2, 144, 144, FaceGraph);
	LoadDivGraph("resource/System/icon.png", 320, 16, 20, 32, 32, IconGraph);
	LoadDivGraph("resource/System/cursor.png", 4, 2, 2, 24, 24, CursorGraph);

	MapGraph[ROOM] = LoadGraph("resource/MAP/ROOM/001-1.png");
	MapGraph2[ROOM] = LoadGraph("resource/MAP/ROOM/001-2.png");
	MapGraph3[ROOM] = LoadGraph("resource/MAP/ROOM/001-3.png");
	MapOverlayGraph[ROOM] = LoadGraph("resource/MAP/ROOM/001o.png");
	MapAttack[ROOM] = LoadSoftImage("resource/MAP/ROOM/001_.png");
	MapWidth[ROOM] = 816, MapHeight[ROOM] = 624;
	MapGraph[FIELDMAP] = LoadGraph("resource/MAP/FIELD/001-1.png");
	MapGraph2[FIELDMAP] = LoadGraph("resource/MAP/FIELD/001-2.png");
	MapGraph3[FIELDMAP] = LoadGraph("resource/MAP/FIELD/001-3.png");
	MapOverlayGraph[FIELDMAP] = LoadGraph("resource/MAP/FIELD/001o.png");
	MapAttack[FIELDMAP] = LoadSoftImage("resource/MAP/FIELD/001_.png");
	MapWidth[FIELDMAP] = 6720, MapHeight[FIELDMAP] = 6720;
	MapGraph[STARTMAP] = LoadGraph("resource/MAP/START/001-1.png");
	MapGraph2[STARTMAP] = LoadGraph("resource/MAP/START/001-2.png");
	MapGraph3[STARTMAP] = LoadGraph("resource/MAP/START/001-3.png");
	MapOverlayGraph[STARTMAP] = LoadGraph("resource/MAP/START/001o.png");
	MapEVGraphDOWN[STARTMAPEV1] = LoadGraph("resource/MAP/START/EV/ev1d.png");
	MapEVGraphLEFT[STARTMAPEV1] = LoadGraph("resource/MAP/START/EV/ev1l.png");
	MapEVGraphRIGHT[STARTMAPEV1] = LoadGraph("resource/MAP/START/EV/ev1r.png");
	MapAttack[STARTMAP] = LoadSoftImage("resource/MAP/START/001_.png");
	MapWidth[STARTMAP] = 912, MapHeight[STARTMAP] = 720;
	MapGraph[TOWN1MAP] = LoadGraph("resource/MAP/TOWN1/001-1.png");
	MapGraph2[TOWN1MAP] = LoadGraph("resource/MAP/TOWN1/001-2.png");
	MapGraph3[TOWN1MAP] = LoadGraph("resource/MAP/TOWN1/001-3.png");
	MapOverlayGraph[TOWN1MAP] = LoadGraph("resource/MAP/TOWN1/001o.png");
	MapAttack[TOWN1MAP] = LoadSoftImage("resource/MAP/TOWN1/001_.png");
	MapWidth[TOWN1MAP] = 1920, MapHeight[TOWN1MAP] = 1920;
	MapGraph[TOWN1INN1FMAP] = LoadGraph("resource/MAP/TOWN1INN/001-1.png");
	MapGraph2[TOWN1INN1FMAP] = LoadGraph("resource/MAP/TOWN1INN/001-2.png");
	MapGraph3[TOWN1INN1FMAP] = LoadGraph("resource/MAP/TOWN1INN/001-3.png");
	MapOverlayGraph[TOWN1INN1FMAP] = LoadGraph("resource/MAP/TOWN1INN/001o.png");
	MapAttack[TOWN1INN1FMAP] = LoadSoftImage("resource/MAP/TOWN1INN/001_.png");
	MapWidth[TOWN1INN1FMAP] = 1008, MapHeight[TOWN1INN1FMAP] = 960;
	MapGraph[TOWN1INN2FMAP] = LoadGraph("resource/MAP/TOWN1INN/002-1.png");
	MapGraph2[TOWN1INN2FMAP] = LoadGraph("resource/MAP/TOWN1INN/002-2.png");
	MapGraph3[TOWN1INN2FMAP] = LoadGraph("resource/MAP/TOWN1INN/002-3.png");
	MapOverlayGraph[TOWN1INN2FMAP] = LoadGraph("resource/MAP/TOWN1INN/002o.png");
	MapAttack[TOWN1INN2FMAP] = LoadSoftImage("resource/MAP/TOWN1INN/002_.png");
	MapWidth[TOWN1INN2FMAP] = 816, MapHeight[TOWN1INN2FMAP] = 720;

	LoadDivGraph("resource/Character/walk.png", 12, 3, 4, 48, 48, CharDiv);

	BattleBackGraph[GRASS] = LoadGraph("resource/Battle/Back/001.png");
	BattleBackOverGraph[GRASSOVER] = LoadGraph("resource/Battle/BackOver/001.png");
	MobGraph[SLIME] = LoadGraph("resource/Battle/Mob/001.png");
}

//音
void LoadAllSounds(void) {
	BGM[TITLE] = LoadSoundMem("resource/sounds/BGM/Arrive.mp3");
	BGM[TOWN] = LoadSoundMem("resource/sounds/BGM/Town1.ogg");
	BGM[FIELD] = LoadSoundMem("resource/sounds/BGM/Field1.ogg");
	BGM[BATTLE] = LoadSoundMem("resource/sounds/BGM/Battle1.ogg");
	BGM[GAMEOVER] = LoadSoundMem("resource/sounds/BGM/Gameover1.ogg");
	SE[TITLESELECT] = LoadSoundMem("resource/sounds/se/Cursor1.ogg");
	SE[TITLEDECISION] = LoadSoundMem("resource/sounds/se/Decision2.ogg");
	SE[TITLECANCEL] = LoadSoundMem("resource/sounds/se/Cancel1.ogg");
	SE[TITLEBUZZER] = LoadSoundMem("resource/sounds/se/Buzzer3.ogg");
	SE[SELECT] = LoadSoundMem("resource/sounds/SE/common/Cursor2.ogg");
	SE[DECISION] = LoadSoundMem("resource/sounds/SE/common/Decision1.ogg");
	SE[CANCEL] = LoadSoundMem("resource/sounds/SE/common/Cancel2.ogg");
	SE[BUZZER] = LoadSoundMem("resource/sounds/SE/common/Buzzer1.ogg");
	SE[EQUIP] = LoadSoundMem("resource/sounds/SE/Equip1.ogg");
	SE[MOVE] = LoadSoundMem("resource/sounds/SE/Move1.ogg");
	SE[SAVE] = LoadSoundMem("resource/sounds/SE/Save.ogg");
	SE[LOAD] = LoadSoundMem("resource/sounds/SE/Load2.ogg");
	SE[ENCOUNT] = LoadSoundMem("resource/sounds/SE/Absorb1.ogg");
	SE[HIT] = LoadSoundMem("resource/sounds/SE/Damage1.ogg");
	SE[HIT2] = LoadSoundMem("resource/sounds/SE/Damage4.ogg");
}

//音量設定
void SettingsSounds(int BGMVo, int MEVo, int BGSVo, int SEVo) {
	int i = 0;
	do {
		ChangeVolumeSoundMem(BGMVo, BGM[i]);
		i++;
	} while (i < BGMs);
	i = 0;
	do {
		ChangeVolumeSoundMem(MEVo, ME[i]);
		i++;
	} while (i < MEs);
	i = 0;
	do {
		ChangeVolumeSoundMem(BGSVo, BGS[i]);
		i++;
	} while (i < BGSs);
	i = 0;
	do {
		ChangeVolumeSoundMem(SEVo, SE[i]);
		i++;
	} while (i < SEs);
}
void SettingsBGMs(int BGMVo) {
	int i = 0;
	do {
		ChangeVolumeSoundMem(BGMVo, BGM[i]);
		i++;
	} while (i < BGMs);
}
void SettingsMEs(int MEVo) {
	int i = 0;
	do {
		ChangeVolumeSoundMem(MEVo, ME[i]);
		i++;
	} while (i < MEs);
}
void SettingsBGSs(int BGSVo) {
	int i = 0;
	do {
		ChangeVolumeSoundMem(BGSVo, BGS[i]);
		i++;
	} while (i < BGSs);
}
void SettingsSEs(int SEVo) {
	int i = 0;
	do {
		ChangeVolumeSoundMem(SEVo, SE[i]);
		i++;
	} while (i < SEs);
}

//キーの押下フレーム数取得関数
int UpdateKey(void) {
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

void Opening(void) {
	int Bright = 0;
	do {
		SetDrawBright(Bright, Bright, Bright);
		DrawGraph(0, 0, OpeningGraph, FALSE);
		ScreenFlip();
		Bright = Bright + 5;
	} while (Bright <= 255);
	SetDrawBright(255, 255, 255);
	DrawGraph(0, 0, OpeningGraph, FALSE);
	GetDrawScreenGraph(0, 0, 48 * 17, 48 * 13, MsgScreen);
	ClearDrawScreen();
	MsgBoxY = 0;
	do {
		ClearDrawScreen();
		DrawGraph(0, 0, MsgScreen, FALSE);
		DrawModiGraph(0, 532 - MsgBoxY, 816, 532 - MsgBoxY, 816, 536 + MsgBoxY, 0, 536 + MsgBoxY, MsgGraph, TRUE);
		ScreenFlip();
		MsgBoxY = MsgBoxY + 8;
	} while (MsgBoxY <= 88);
	ClearDrawScreen();
	DrawGraph(0, 0, MsgScreen, FALSE);
	DrawGraph(0, 444, MsgGraph, TRUE);
	ScreenFlip();
	int i = 0;
	do {
		DrawFormatStringToHandle(20 + (i * 14), 465, White, FontMain, "%c%c", OPMsg1[i], OPMsg1[i + 1]);
		ScreenFlip();
		WaitTimer(15);
		i = i + 2;
	} while (i + 1 <= 28);
	int j = 0;
	while (1) {
		ClearDrawScreen();
		DrawGraph(0, 0, MsgScreen, FALSE);
		DrawGraph(0, 444, MsgGraph, TRUE);
		DrawFormatStringToHandle(20, 465, White, FontMain, "%s", OPMsg[0].c_str());
		if (j <= 15) DrawGraph(396, 600, CursorGraph[0], TRUE);
		else if (j > 15 && j <= 30) DrawGraph(396, 600, CursorGraph[1], TRUE);
		else if (j > 30 && j <= 45) DrawGraph(396, 600, CursorGraph[2], TRUE);
		else if (j > 45) { DrawGraph(396, 600, CursorGraph[3], TRUE); j = 0; }
		ScreenFlip();
		j++;
		UpdateKey();
		if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) break;
	}
	i = 0;
	ClearDrawScreen();
	DrawGraph(0, 0, MsgScreen, FALSE);
	DrawGraph(0, 444, MsgGraph, TRUE);
	ScreenFlip();
	do {
		DrawFormatStringToHandle(20 + (i * 14), 465, White, FontMain, "%c%c", OPMsg2[i], OPMsg2[i + 1]);
		ScreenFlip();
		WaitTimer(15);
		i = i + 2;
	} while (i + 1 <= 26);
	j = 0;
	while (1) {
		ClearDrawScreen();
		DrawGraph(0, 0, MsgScreen, FALSE);
		DrawGraph(0, 444, MsgGraph, TRUE);
		DrawFormatStringToHandle(20, 465, White, FontMain, "%s", OPMsg[1].c_str());
		if (j <= 15) DrawGraph(396, 600, CursorGraph[0], TRUE);
		else if (j > 15 && j <= 30) DrawGraph(396, 600, CursorGraph[1], TRUE);
		else if (j > 30 && j <= 45) DrawGraph(396, 600, CursorGraph[2], TRUE);
		else if (j > 45) { DrawGraph(396, 600, CursorGraph[3], TRUE); j = 0; }
		ScreenFlip();
		j++;
		UpdateKey();
		if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) break;
	}
	i = 0;
	ClearDrawScreen();
	DrawGraph(0, 0, MsgScreen, FALSE);
	DrawGraph(0, 444, MsgGraph, TRUE);
	ScreenFlip();
	do {
		DrawFormatStringToHandle(20 + (i * 14), 465, White, FontMain, "%c%c", OPMsg3[i], OPMsg3[i + 1]);
		ScreenFlip();
		WaitTimer(15);
		i = i + 2;
	} while (i + 1 <= 38);
	j = 0;
	while (1) {
		ClearDrawScreen();
		DrawGraph(0, 0, MsgScreen, FALSE);
		DrawGraph(0, 444, MsgGraph, TRUE);
		DrawFormatStringToHandle(20, 465, White, FontMain, "%s", OPMsg[2].c_str());
		if (j <= 15) DrawGraph(396, 600, CursorGraph[0], TRUE);
		else if (j > 15 && j <= 30) DrawGraph(396, 600, CursorGraph[1], TRUE);
		else if (j > 30 && j <= 45) DrawGraph(396, 600, CursorGraph[2], TRUE);
		else if (j > 45) { DrawGraph(396, 600, CursorGraph[3], TRUE); j = 0; }
		ScreenFlip();
		j++;
		UpdateKey();
		if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) break;
	}
	i = 0;
	ClearDrawScreen();
	DrawGraph(0, 0, MsgScreen, FALSE);
	DrawGraph(0, 444, MsgGraph, TRUE);
	ScreenFlip();
	do {
		DrawFormatStringToHandle(20 + (i * 14), 465, White, FontMain, "%c%c", OPMsg4[i], OPMsg4[i + 1]);
		ScreenFlip();
		WaitTimer(15);
		i = i + 2;
	} while (i + 1 <= 34);
	j = 0;
	while (1) {
		ClearDrawScreen();
		DrawGraph(0, 0, MsgScreen, FALSE);
		DrawGraph(0, 444, MsgGraph, TRUE);
		DrawFormatStringToHandle(20, 465, White, FontMain, "%s", OPMsg[3].c_str());
		if (j <= 15) DrawGraph(396, 600, CursorGraph[0], TRUE);
		else if (j > 15 && j <= 30) DrawGraph(396, 600, CursorGraph[1], TRUE);
		else if (j > 30 && j <= 45) DrawGraph(396, 600, CursorGraph[2], TRUE);
		else if (j > 45) { DrawGraph(396, 600, CursorGraph[3], TRUE); j = 0; }
		ScreenFlip();
		j++;
		UpdateKey();
		if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) break;
	}
	MsgBoxY = 88;
	do {
		ClearDrawScreen();
		DrawGraph(0, 0, MsgScreen, FALSE);
		DrawModiGraph(0, 532 - MsgBoxY, 816, 532 - MsgBoxY, 816, 536 + MsgBoxY, 0, 536 + MsgBoxY, MsgGraph, TRUE);
		ScreenFlip();
		MsgBoxY = MsgBoxY - 8;
	} while (MsgBoxY >= 0);
	MsgBoxY = 0;
	Bright = 255;
	do {
		SetDrawBright(Bright, Bright, Bright);
		DrawGraph(0, 0, OpeningGraph, FALSE);
		ScreenFlip();
		Bright = Bright - 17;
	} while (Bright >= 0);
	SetDrawBright(255, 255, 255);
}

void Ending(void) {
	float Vol = 1.0;
	do {
		ChangeVolumeSoundMem((float)BGMVolume * Vol, BGM[FIELD]);
		Vol = Vol - 0.04;
	} while (Vol >= 0);
	StopSoundMem(BGM[FIELD]);
	ChangeVolumeSoundMem(BGMVolume, BGM[FIELD]);
	GetDrawScreenGraph(0, 0, 816, 624, MsgScreen);
	int Bright = 255;
	do {
		SetDrawBright(Bright, Bright, Bright);
		DrawGraph(0, 0, MsgScreen, FALSE);
		ScreenFlip();
		Bright = Bright - 5;
	} while (Bright >= 0);
	Bright = 255;
	WaitTimer(1000);
	do {
		SetDrawBright(Bright, Bright, Bright);
		DrawGraph(0, 0, OpeningGraph, FALSE);
		ScreenFlip();
		Bright = Bright + 5;
	} while (Bright <= 255);
	SetDrawBright(255, 255, 255);
	DrawGraph(0, 0, OpeningGraph, FALSE);
	GetDrawScreenGraph(0, 0, 48 * 17, 48 * 13, MsgScreen);
	ClearDrawScreen();
	MsgBoxY = 0;
	do {
		ClearDrawScreen();
		DrawGraph(0, 0, MsgScreen, FALSE);
		DrawModiGraph(0, 532 - MsgBoxY, 816, 532 - MsgBoxY, 816, 536 + MsgBoxY, 0, 536 + MsgBoxY, MsgGraph, TRUE);
		ScreenFlip();
		MsgBoxY = MsgBoxY + 8;
	} while (MsgBoxY <= 88);
	ClearDrawScreen();
	DrawGraph(0, 0, MsgScreen, FALSE);
	DrawGraph(0, 444, MsgGraph, TRUE);
	ScreenFlip();
	int i = 0;
	do {
		DrawFormatStringToHandle(20 + (i * 14), 465, White, FontMain, "%c%c", EDMsg1[i], EDMsg1[i + 1]);
		ScreenFlip();
		WaitTimer(15);
		i = i + 2;
	} while (i + 1 <= 24);
	int j = 0;
	while (1) {
		ClearDrawScreen();
		DrawGraph(0, 0, MsgScreen, FALSE);
		DrawGraph(0, 444, MsgGraph, TRUE);
		DrawFormatStringToHandle(20, 465, White, FontMain, "%s", EDMsg[0].c_str());
		if (j <= 15) DrawGraph(396, 600, CursorGraph[0], TRUE);
		else if (j > 15 && j <= 30) DrawGraph(396, 600, CursorGraph[1], TRUE);
		else if (j > 30 && j <= 45) DrawGraph(396, 600, CursorGraph[2], TRUE);
		else if (j > 45) { DrawGraph(396, 600, CursorGraph[3], TRUE); j = 0; }
		ScreenFlip();
		j++;
		UpdateKey();
		if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) break;
	}
	i = 0;
	ClearDrawScreen();
	DrawGraph(0, 0, MsgScreen, FALSE);
	DrawGraph(0, 444, MsgGraph, TRUE);
	ScreenFlip();
	do {
		DrawFormatStringToHandle(20 + (i * 14), 465, White, FontMain, "%c%c", EDMsg2[i], EDMsg2[i + 1]);
		ScreenFlip();
		WaitTimer(15);
		i = i + 2;
	} while (i + 1 <= 12);
	j = 0;
	while (1) {
		ClearDrawScreen();
		DrawGraph(0, 0, MsgScreen, FALSE);
		DrawGraph(0, 444, MsgGraph, TRUE);
		DrawFormatStringToHandle(20, 465, White, FontMain, "%s", EDMsg[1].c_str());
		if (j <= 15) DrawGraph(396, 600, CursorGraph[0], TRUE);
		else if (j > 15 && j <= 30) DrawGraph(396, 600, CursorGraph[1], TRUE);
		else if (j > 30 && j <= 45) DrawGraph(396, 600, CursorGraph[2], TRUE);
		else if (j > 45) { DrawGraph(396, 600, CursorGraph[3], TRUE); j = 0; }
		ScreenFlip();
		j++;
		UpdateKey();
		if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) break;
	}
	i = 0;
	ClearDrawScreen();
	DrawGraph(0, 0, MsgScreen, FALSE);
	DrawGraph(0, 444, MsgGraph, TRUE);
	ScreenFlip();
	do {
		DrawFormatStringToHandle(20 + (i * 14), 465, White, FontMain, "%c%c", EDMsg3[i], EDMsg3[i + 1]);
		ScreenFlip();
		WaitTimer(15);
		i = i + 2;
	} while (i + 1 <= 36);
	j = 0;
	while (1) {
		ClearDrawScreen();
		DrawGraph(0, 0, MsgScreen, FALSE);
		DrawGraph(0, 444, MsgGraph, TRUE);
		DrawFormatStringToHandle(20, 465, White, FontMain, "%s", EDMsg[2].c_str());
		if (j <= 15) DrawGraph(396, 600, CursorGraph[0], TRUE);
		else if (j > 15 && j <= 30) DrawGraph(396, 600, CursorGraph[1], TRUE);
		else if (j > 30 && j <= 45) DrawGraph(396, 600, CursorGraph[2], TRUE);
		else if (j > 45) { DrawGraph(396, 600, CursorGraph[3], TRUE); j = 0; }
		ScreenFlip();
		j++;
		UpdateKey();
		if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) break;
	}
	i = 0;
	ClearDrawScreen();
	DrawGraph(0, 0, MsgScreen, FALSE);
	DrawGraph(0, 444, MsgGraph, TRUE);
	ScreenFlip();
	do {
		DrawFormatStringToHandle(20 + (i * 14), 465, White, FontMain, "%c%c", EDMsg4[i], EDMsg4[i + 1]);
		ScreenFlip();
		WaitTimer(15);
		i = i + 2;
	} while (i + 1 <= 12);
	j = 0;
	while (1) {
		ClearDrawScreen();
		DrawGraph(0, 0, MsgScreen, FALSE);
		DrawGraph(0, 444, MsgGraph, TRUE);
		DrawFormatStringToHandle(20, 465, White, FontMain, "%s", EDMsg[3].c_str());
		if (j <= 15) DrawGraph(396, 600, CursorGraph[0], TRUE);
		else if (j > 15 && j <= 30) DrawGraph(396, 600, CursorGraph[1], TRUE);
		else if (j > 30 && j <= 45) DrawGraph(396, 600, CursorGraph[2], TRUE);
		else if (j > 45) { DrawGraph(396, 600, CursorGraph[3], TRUE); j = 0; }
		ScreenFlip();
		j++;
		UpdateKey();
		if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) break;
	}
	MsgBoxY = 88;
	do {
		ClearDrawScreen();
		DrawGraph(0, 0, MsgScreen, FALSE);
		DrawModiGraph(0, 532 - MsgBoxY, 816, 532 - MsgBoxY, 816, 536 + MsgBoxY, 0, 536 + MsgBoxY, MsgGraph, TRUE);
		ScreenFlip();
		MsgBoxY = MsgBoxY - 8;
	} while (MsgBoxY >= 0);
	MsgBoxY = 0;
	Bright = 255;
	do {
		SetDrawBright(Bright, Bright, Bright);
		DrawGraph(0, 0, OpeningGraph, FALSE);
		ScreenFlip();
		Bright = Bright - 17;
	} while (Bright >= 0);
	SetDrawBright(255, 255, 255);
	WaitTimer(3000);
}

//オプション
void Option(void) {
	ClearDrawScreen();
	DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
	DrawGraph(208, 186, MenuGraph[OPTIONMENU], TRUE);
	ScreenFlip();

	int SelectOption = 204, OptionPal = 255, OptionFlag = 0;
	while (1) {
		ClearDrawScreen();
		DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
		DrawGraph(208, 186, MenuGraph[OPTIONMENU], TRUE);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, OptionPal);
		DrawModiGraph(226, SelectOption, 590, SelectOption, 590, SelectOption + 36, 226, SelectOption + 36, SelectGraph, TRUE);
		if (OptionPal == 255) OptionFlag = 1;
		else if (OptionPal == 129) OptionFlag = 0;

		if (OptionFlag == 1) OptionPal = OptionPal - 6;
		else if (OptionFlag == 0) OptionPal = OptionPal + 6;

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		if (Dash == FALSE) {
			DrawStringToHandle(233, 208, "常時ダッシュ　　　　 OFF", White, FontMain);
		}
		else if (Dash == TRUE) {
			DrawStringToHandle(233, 208, "常時ダッシュ　　　　  ON", White, FontMain);
		}

		if (Cheat == FALSE) {
			DrawStringToHandle(233, 244, "チートモード　　　　 OFF", White, FontMain);
		}
		else if (Cheat == TRUE) {
			DrawStringToHandle(233, 244, "チートモード　　　　  ON", White, FontMain);
		}

		if (BGMVolume == 256) {
			DrawStringToHandle(233, 280, "BGM 音量　　　　　　100%", White, FontMain);
		}
		else if (BGMVolume == 205) {
			DrawStringToHandle(233, 280, "BGM 音量　　　　　　 80%", White, FontMain);
		}
		else if (BGMVolume == 154) {
			DrawStringToHandle(233, 280, "BGM 音量　　　　　　 60%", White, FontMain);
		}
		else if (BGMVolume == 102) {
			DrawStringToHandle(233, 280, "BGM 音量　　　　　　 40%", White, FontMain);
		}
		else if (BGMVolume == 51) {
			DrawStringToHandle(233, 280, "BGM 音量　　　　　　 20%", White, FontMain);
		}
		else if (BGMVolume == 0) {
			DrawStringToHandle(233, 280, "BGM 音量　　　　　　  0%", White, FontMain);
		}

		if (MEVolume == 256) {
			DrawStringToHandle(233, 316, "ME 音量 　　　　　　100%", White, FontMain);
		}
		else if (MEVolume == 205) {
			DrawStringToHandle(233, 316, "ME 音量 　　　　　　 80%", White, FontMain);
		}
		else if (MEVolume == 154) {
			DrawStringToHandle(233, 316, "ME 音量 　　　　　　 60%", White, FontMain);
		}
		else if (MEVolume == 102) {
			DrawStringToHandle(233, 316, "ME 音量 　　　　　　 40%", White, FontMain);
		}
		else if (MEVolume == 51) {
			DrawStringToHandle(233, 316, "ME 音量 　　　　　　 20%", White, FontMain);
		}
		else if (MEVolume == 0) {
			DrawStringToHandle(233, 316, "ME 音量 　　　　　　  0%", White, FontMain);
		}

		if (BGSVolume == 256) {
			DrawStringToHandle(233, 352, "BGS 音量　　　　　　100%", White, FontMain);
		}
		else if (BGSVolume == 205) {
			DrawStringToHandle(233, 352, "BGS 音量　　　　　　 80%", White, FontMain);
		}
		else if (BGSVolume == 154) {
			DrawStringToHandle(233, 352, "BGS 音量　　　　　　 60%", White, FontMain);
		}
		else if (BGSVolume == 102) {
			DrawStringToHandle(233, 352, "BGS 音量　　　　　　 40%", White, FontMain);
		}
		else if (BGSVolume == 51) {
			DrawStringToHandle(233, 352, "BGS 音量　　　　　　 20%", White, FontMain);
		}
		else if (BGSVolume == 0) {
			DrawStringToHandle(233, 352, "BGS 音量　　　　　　  0%", White, FontMain);
		}

		if (SEVolume == 256) {
			DrawStringToHandle(233, 388, "SE 音量 　　　　　　100%", White, FontMain);
		}
		else if (SEVolume == 205) {
			DrawStringToHandle(233, 388, "SE 音量 　　　　　　 80%", White, FontMain);
		}
		else if (SEVolume == 154) {
			DrawStringToHandle(233, 388, "SE 音量 　　　　　　 60%", White, FontMain);
		}
		else if (SEVolume == 102) {
			DrawStringToHandle(233, 388, "SE 音量 　　　　　　 40%", White, FontMain);
		}
		else if (SEVolume == 51) {
			DrawStringToHandle(233, 388, "SE 音量 　　　　　　 20%", White, FontMain);
		}
		else if (SEVolume == 0) {
			DrawStringToHandle(233, 388, "SE 音量 　　　　　　  0%", White, FontMain);
		}

		ScreenFlip();

		UpdateKey();
		if (Key[KEY_INPUT_DOWN] == 1) {
			if (NowTitle == FALSE) {
				if (SelectOption == 348) { SelectOption = 384; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
				else if (SelectOption == 312) { SelectOption = 348; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
				else if (SelectOption == 276) { SelectOption = 312; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
				else if (SelectOption == 240) { SelectOption = 276; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
				else if (SelectOption == 204) { SelectOption = 240; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
			}
			else if (NowTitle == TRUE) {
				if (SelectOption == 348) { SelectOption = 384; PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK); }
				else if (SelectOption == 312) { SelectOption = 348; PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK); }
				else if (SelectOption == 276) { SelectOption = 312; PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK); }
				else if (SelectOption == 240) { SelectOption = 276; PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK); }
				else if (SelectOption == 204) { SelectOption = 240; PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK); }
			}
		}
		else if (Key[KEY_INPUT_UP] == 1) {
			if (NowTitle == FALSE) {
				if (SelectOption == 240) { SelectOption = 204; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
				else if (SelectOption == 276) { SelectOption = 240; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
				else if (SelectOption == 312) { SelectOption = 276; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
				else if (SelectOption == 348) { SelectOption = 312; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
				else if (SelectOption == 384) { SelectOption = 348; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
			}
			else if (NowTitle == TRUE) {
				if (SelectOption == 240) { SelectOption = 204; PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK); }
				else if (SelectOption == 276) { SelectOption = 240; PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK); }
				else if (SelectOption == 312) { SelectOption = 276; PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK); }
				else if (SelectOption == 348) { SelectOption = 312; PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK); }
				else if (SelectOption == 384) { SelectOption = 348; PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK); }
			}
		}
		else if (Key[KEY_INPUT_LEFT] == 1) {
			if (NowTitle == FALSE) {
				if (SelectOption == 204 && Dash == TRUE) {
					Dash = FALSE;
					PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
				}
				else if (SelectOption == 240 && Cheat == TRUE) {
					Cheat = FALSE;
					Walk = 0;
					PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
				}
				else if (SelectOption == 276) {
					if (BGMVolume == 51) {
						BGMVolume = 0;
						SettingsBGMs(BGMVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
					else if (BGMVolume == 102) {
						BGMVolume = 51;
						SettingsBGMs(BGMVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
					else if (BGMVolume == 154) {
						BGMVolume = 102;
						SettingsBGMs(BGMVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
					else if (BGMVolume == 205) {
						BGMVolume = 154;
						SettingsBGMs(BGMVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
					else if (BGMVolume == 256) {
						BGMVolume = 205;
						SettingsBGMs(BGMVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
				}
				else if (SelectOption == 312) {
					if (MEVolume == 51) {
						MEVolume = 0;
						SettingsMEs(MEVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
					else if (MEVolume == 102) {
						MEVolume = 51;
						SettingsMEs(MEVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
					else if (MEVolume == 154) {
						MEVolume = 102;
						SettingsMEs(MEVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
					else if (MEVolume == 205) {
						MEVolume = 154;
						SettingsMEs(MEVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
					else if (MEVolume == 256) {
						MEVolume = 205;
						SettingsMEs(MEVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
				}
				else if (SelectOption == 348) {
					if (BGSVolume == 51) {
						BGSVolume = 0;
						SettingsBGSs(BGSVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
					else if (BGSVolume == 102) {
						BGSVolume = 51;
						SettingsBGSs(BGSVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
					else if (BGSVolume == 154) {
						BGSVolume = 102;
						SettingsBGSs(BGSVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
					else if (BGSVolume == 205) {
						BGSVolume = 154;
						SettingsBGSs(BGSVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
					else if (BGSVolume == 256) {
						BGSVolume = 205;
						SettingsBGSs(BGSVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
				}
				else if (SelectOption == 384) {
					if (SEVolume == 51) {
						SEVolume = 0;
						SettingsSEs(SEVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
					else if (SEVolume == 102) {
						SEVolume = 51;
						SettingsSEs(SEVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
					else if (SEVolume == 154) {
						SEVolume = 102;
						SettingsSEs(SEVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
					else if (SEVolume == 205) {
						SEVolume = 154;
						SettingsSEs(SEVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
					else if (SEVolume == 256) {
						SEVolume = 205;
						SettingsSEs(SEVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
				}
			}
			else if (NowTitle == TRUE) {
				if (SelectOption == 204 && Dash == TRUE) {
					Dash = FALSE;
					PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
				}
				else if (SelectOption == 240 && Cheat == TRUE) {
					Cheat = FALSE;
					PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
				}
				else if (SelectOption == 276) {
					if (BGMVolume == 51) {
						BGMVolume = 0;
						SettingsBGMs(BGMVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
					else if (BGMVolume == 102) {
						BGMVolume = 51;
						SettingsBGMs(BGMVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
					else if (BGMVolume == 154) {
						BGMVolume = 102;
						SettingsBGMs(BGMVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
					else if (BGMVolume == 205) {
						BGMVolume = 154;
						SettingsBGMs(BGMVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
					else if (BGMVolume == 256) {
						BGMVolume = 205;
						SettingsBGMs(BGMVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
				}
				else if (SelectOption == 312) {
					if (MEVolume == 51) {
						MEVolume = 0;
						SettingsMEs(MEVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
					else if (MEVolume == 102) {
						MEVolume = 51;
						SettingsMEs(MEVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
					else if (MEVolume == 154) {
						MEVolume = 102;
						SettingsMEs(MEVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
					else if (MEVolume == 205) {
						MEVolume = 154;
						SettingsMEs(MEVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
					else if (MEVolume == 256) {
						MEVolume = 205;
						SettingsMEs(MEVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
				}
				else if (SelectOption == 348) {
					if (BGSVolume == 51) {
						BGSVolume = 0;
						SettingsBGSs(BGSVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
					else if (BGSVolume == 102) {
						BGSVolume = 51;
						SettingsBGSs(BGSVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
					else if (BGSVolume == 154) {
						BGSVolume = 102;
						SettingsBGSs(BGSVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
					else if (BGSVolume == 205) {
						BGSVolume = 154;
						SettingsBGSs(BGSVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
					else if (BGSVolume == 256) {
						BGSVolume = 205;
						SettingsBGSs(BGSVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
				}
				else if (SelectOption == 384) {
					if (SEVolume == 51) {
						SEVolume = 0;
						SettingsSEs(SEVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
					else if (SEVolume == 102) {
						SEVolume = 51;
						SettingsSEs(SEVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
					else if (SEVolume == 154) {
						SEVolume = 102;
						SettingsSEs(SEVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
					else if (SEVolume == 205) {
						SEVolume = 154;
						SettingsSEs(SEVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
					else if (SEVolume == 256) {
						SEVolume = 205;
						SettingsSEs(SEVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
				}
			}
		}
		else if (Key[KEY_INPUT_RIGHT] == 1) {
			if (NowTitle == FALSE) {
				if (SelectOption == 204 && Dash == FALSE) {
					Dash = TRUE;
					PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
				}
				else if (SelectOption == 240 && Cheat == FALSE) {
					Cheat = TRUE;
					PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
				}
				else if (SelectOption == 276) {
					if (BGMVolume == 205) {
						BGMVolume = 256;
						SettingsBGMs(BGMVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
					else if (BGMVolume == 154) {
						BGMVolume = 205;
						SettingsBGMs(BGMVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
					else if (BGMVolume == 102) {
						BGMVolume = 154;
						SettingsBGMs(BGMVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
					else if (BGMVolume == 51) {
						BGMVolume = 102;
						SettingsBGMs(BGMVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
					else if (BGMVolume == 0) {
						BGMVolume = 51;
						SettingsBGMs(BGMVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
				}
				else if (SelectOption == 312) {
					if (MEVolume == 205) {
						MEVolume = 256;
						SettingsMEs(MEVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
					else if (MEVolume == 154) {
						MEVolume = 205;
						SettingsMEs(MEVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
					else if (MEVolume == 102) {
						MEVolume = 154;
						SettingsMEs(MEVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
					else if (MEVolume == 51) {
						MEVolume = 102;
						SettingsMEs(MEVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
					else if (MEVolume == 0) {
						MEVolume = 51;
						SettingsMEs(MEVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
				}
				else if (SelectOption == 348) {
					if (BGSVolume == 205) {
						BGSVolume = 256;
						SettingsBGSs(BGSVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
					else if (BGSVolume == 154) {
						BGSVolume = 205;
						SettingsBGSs(BGSVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
					else if (BGSVolume == 102) {
						BGSVolume = 154;
						SettingsBGSs(BGSVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
					else if (BGSVolume == 51) {
						BGSVolume = 102;
						SettingsBGSs(BGSVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
					else if (BGSVolume == 0) {
						BGSVolume = 51;
						SettingsBGSs(BGSVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
				}
				else if (SelectOption == 384) {
					if (SEVolume == 205) {
						SEVolume = 256;
						SettingsSEs(SEVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
					else if (SEVolume == 154) {
						SEVolume = 205;
						SettingsSEs(SEVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
					else if (SEVolume == 102) {
						SEVolume = 154;
						SettingsSEs(SEVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
					else if (SEVolume == 51) {
						SEVolume = 102;
						SettingsSEs(SEVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
					else if (SEVolume == 0) {
						SEVolume = 51;
						SettingsSEs(SEVolume);
						PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
					}
				}
			}
			else if (NowTitle == TRUE) {
				if (SelectOption == 204 && Dash == FALSE) {
					Dash = TRUE;
					PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
				}
				else if (SelectOption == 240 && Cheat == FALSE) {
					Cheat = TRUE;
					PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
				}
				else if (SelectOption == 276) {
					if (BGMVolume == 205) {
						BGMVolume = 256;
						SettingsBGMs(BGMVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
					else if (BGMVolume == 154) {
						BGMVolume = 205;
						SettingsBGMs(BGMVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
					else if (BGMVolume == 102) {
						BGMVolume = 154;
						SettingsBGMs(BGMVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
					else if (BGMVolume == 51) {
						BGMVolume = 102;
						SettingsBGMs(BGMVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
					else if (BGMVolume == 0) {
						BGMVolume = 51;
						SettingsBGMs(BGMVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
				}
				else if (SelectOption == 312) {
					if (MEVolume == 205) {
						MEVolume = 256;
						SettingsMEs(MEVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
					else if (MEVolume == 154) {
						MEVolume = 205;
						SettingsMEs(MEVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
					else if (MEVolume == 102) {
						MEVolume = 154;
						SettingsMEs(MEVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
					else if (MEVolume == 51) {
						MEVolume = 102;
						SettingsMEs(MEVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
					else if (MEVolume == 0) {
						MEVolume = 51;
						SettingsMEs(MEVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
				}
				else if (SelectOption == 348) {
					if (BGSVolume == 205) {
						BGSVolume = 256;
						SettingsBGSs(BGSVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
					else if (BGSVolume == 154) {
						BGSVolume = 205;
						SettingsBGSs(BGSVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
					else if (BGSVolume == 102) {
						BGSVolume = 154;
						SettingsBGSs(BGSVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
					else if (BGSVolume == 51) {
						BGSVolume = 102;
						SettingsBGSs(BGSVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
					else if (BGSVolume == 0) {
						BGSVolume = 51;
						SettingsBGSs(BGSVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
				}
				else if (SelectOption == 384) {
					if (SEVolume == 205) {
						SEVolume = 256;
						SettingsSEs(SEVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
					else if (SEVolume == 154) {
						SEVolume = 205;
						SettingsSEs(SEVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
					else if (SEVolume == 102) {
						SEVolume = 154;
						SettingsSEs(SEVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
					else if (SEVolume == 51) {
						SEVolume = 102;
						SettingsSEs(SEVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
					else if (SEVolume == 0) {
						SEVolume = 51;
						SettingsSEs(SEVolume);
						PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK);
					}
				}
			}
		}
		else if (Key[KEY_INPUT_ESCAPE] == 1 || Key[KEY_INPUT_X] == 1) {
			if (NowTitle == FALSE) PlaySoundMem(SE[CANCEL], DX_PLAYTYPE_BACK);
			else if (NowTitle == TRUE) PlaySoundMem(SE[TITLECANCEL], DX_PLAYTYPE_BACK);
			break;
		}

		if (ProcessMessage() < 0) break;
	}
	ConfigSave();
}

//メニュー
void Menu(void) {
	int Gauss = 0;
	GetDrawScreenGraph(0, 0, 48 * 17, 48 * 13, MenuScreen);
	do {
		ClearDrawScreen();
		GraphFilterBlt(MenuScreen, MenuScreenGAUSS, DX_GRAPH_FILTER_GAUSS, 8, Gauss);
		DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
		ScreenFlip();
		Gauss = Gauss + 10;
	} while (Gauss <= 100);
	WaitTimer(500);
	ClearDrawScreen();
	DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
	DrawGraph(0, 0, MenuGraph[MAINMENU], TRUE);
	ScreenFlip();
	
	int MenuPal = 255, MenuFlag = 0;
	while (1) {
		ClearDrawScreen();
		DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
		DrawGraph(0, 0, MenuGraph[MAINMENU], TRUE);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, MenuPal);
		DrawModiGraph(18, SelectMenu[MAINMENU], 222, SelectMenu[MAINMENU], 222, SelectMenu[MAINMENU] + 36, 18, SelectMenu[MAINMENU] + 36, SelectGraph, TRUE);
		if (MenuPal == 255) MenuFlag = 1;
		else if (MenuPal == 129) MenuFlag = 0;

		if (MenuFlag == 1) MenuPal = MenuPal - 6;
		else if (MenuFlag == 0) MenuPal = MenuPal + 6;

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		DrawStringToHandle(24, 23, "アイテム", White, FontMain);
		DrawStringToHandle(24, 59, "スキル", White, FontMain);
		DrawStringToHandle(24, 95, "装備", White, FontMain);
		DrawStringToHandle(24, 131, "ステータス", White, FontMain);
		DrawStringToHandle(24, 167, "オプション", White, FontMain);
		if (BattleMap == FALSE) DrawStringToHandle(24, 203, "セーブ", White, FontMain);
		else if (BattleMap == TRUE) DrawStringToHandle(24, 203, "セーブ", Gray, FontMain);
		if (Cheat == FALSE) DrawStringToHandle(24, 239, "チート", Gray, FontMain);
		else if (Cheat == TRUE) DrawStringToHandle(24, 239, "チート", White, FontMain);
		DrawStringToHandle(24, 275, "ゲーム終了", White, FontMain);

		HPBar = (float)StatusMainChar[HP] / StatusMainChar[HPMAX] * 186;
		MPBar = (float)StatusMainChar[MP] / StatusMainChar[MPMAX] * 186;
		HPBarWidth = HPBar;
		MPBarWidth = MPBar;

		DrawGraph(259, 19, FaceGraph[FACEMAIN], TRUE);
		if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(419, 42, White, FontMain, "%s", Name.c_str());
		else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(419, 42, Yellow, FontMain, "%s", Name.c_str());
		else if (HPBarWidth == 0) { DrawFormatStringToHandle(419, 42, Red, FontMain, "%s", Name.c_str()); DrawGraph(420, 112, IconGraph[1], TRUE); }
		DrawStringToHandle(419, 78, "Lv", Blue, FontMain);
		DrawFormatStringToHandle(508, 78, White, FontMain, "%3d", StatusMainChar[LV]);
		DrawStringToHandle(599, 42, "勇者", White, FontMain);
		DrawGraph(600, 101, BarBaseGraph, TRUE);
		DrawGraph(600, 137, BarBaseGraph, TRUE);
		DrawRectGraph(600, 101, 0, 0, HPBarWidth, 7, HPBarGraph, TRUE, FALSE);
		DrawRectGraph(600, 137, 0, 0, MPBarWidth, 7, MPBarGraph, TRUE, FALSE);
		DrawStringToHandle(599, 78, "HP", Blue, FontMain);
		DrawStringToHandle(599, 114, "MP", Blue, FontMain);
		if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(652, 78, White, FontMain, "%4d", StatusMainChar[HP]);
		else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(652, 78, Yellow, FontMain, "%4d", StatusMainChar[HP]);
		else if (HPBarWidth == 0) DrawFormatStringToHandle(652, 78, Red, FontMain, "%4d", StatusMainChar[HP]);
		if (MPBarWidth <= 186 && MPBarWidth > 56) DrawFormatStringToHandle(652, 114, White, FontMain, "%4d", StatusMainChar[MP]);
		else if (MPBarWidth <= 56 && MPBarWidth > 0) DrawFormatStringToHandle(652, 114, Yellow, FontMain, "%4d", StatusMainChar[MP]);
		else if (MPBarWidth == 0) DrawFormatStringToHandle(652, 114, Red, FontMain, "%4d", StatusMainChar[MP]);
		DrawFormatStringToHandle(652, 78, White, FontMain, "    /%4d", StatusMainChar[HPMAX]);
		DrawFormatStringToHandle(652, 114, White, FontMain, "    /%4d", StatusMainChar[MPMAX]);

		if (Money >= 0) DrawFormatStringToHandle(30, 574, White, FontMain, "%10ld", Money);
		else if (Money < 0) DrawFormatStringToHandle(30, 574, Red, FontMain, "%10ld", Money);
		DrawStringToHandle(190, 574, "G", Blue, FontMain);

		ScreenFlip();

		UpdateKey();
		if (Key[KEY_INPUT_DOWN] == 1) {
			if (SelectMenu[MAINMENU] == 270) { SelectMenu[MAINMENU] = 18; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
			else if (SelectMenu[MAINMENU] == 234) { SelectMenu[MAINMENU] = 270; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
			else if (SelectMenu[MAINMENU] == 198) { SelectMenu[MAINMENU] = 234; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
			else if (SelectMenu[MAINMENU] == 162) { SelectMenu[MAINMENU] = 198; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
			else if (SelectMenu[MAINMENU] == 126) { SelectMenu[MAINMENU] = 162; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
			else if (SelectMenu[MAINMENU] == 90) { SelectMenu[MAINMENU] = 126; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
			else if (SelectMenu[MAINMENU] == 54) { SelectMenu[MAINMENU] = 90; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
			else if (SelectMenu[MAINMENU] == 18) { SelectMenu[MAINMENU] = 54; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
		}
		else if (Key[KEY_INPUT_UP] == 1) {
			if (SelectMenu[MAINMENU] == 54) { SelectMenu[MAINMENU] = 18; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
			else if (SelectMenu[MAINMENU] == 90) { SelectMenu[MAINMENU] = 54; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
			else if (SelectMenu[MAINMENU] == 126) { SelectMenu[MAINMENU] = 90; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
			else if (SelectMenu[MAINMENU] == 162) { SelectMenu[MAINMENU] = 126; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
			else if (SelectMenu[MAINMENU] == 198) { SelectMenu[MAINMENU] = 162; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
			else if (SelectMenu[MAINMENU] == 234) { SelectMenu[MAINMENU] = 198; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
			else if (SelectMenu[MAINMENU] == 270) { SelectMenu[MAINMENU] = 234; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
			else if (SelectMenu[MAINMENU] == 18) { SelectMenu[MAINMENU] = 270; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
		}
		else if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) {
			if (SelectMenu[MAINMENU] == 18) {
				PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
				int ItemMenuPal1 = 255, ItemMenuPal2 = 255;
				while (1) {
					ClearDrawScreen();
					DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
					DrawGraph(0, 0, MenuGraph[ITEMMENU], TRUE);

					SetDrawBlendMode(DX_BLENDMODE_ALPHA, ItemMenuPal1);
					DrawModiGraph(SelectMenu[ITEMMENU], 126, SelectMenu[ITEMMENU] + 186, 126, SelectMenu[ITEMMENU] + 186, 162, SelectMenu[ITEMMENU], 162, SelectGraph, TRUE);
					if (ItemMenuPal1 == 255) MenuFlag = 1;
					else if (ItemMenuPal1 == 129) MenuFlag = 0;

					if (MenuFlag == 1) ItemMenuPal1 = ItemMenuPal1 - 6;
					else if (MenuFlag == 0) ItemMenuPal1 = ItemMenuPal1 + 6;

					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
					DrawStringToHandle(54, 131, "アイテム", White, FontMain);
					DrawStringToHandle(280, 131, "武器", White, FontMain);
					DrawStringToHandle(479, 131, "防具", White, FontMain);
					DrawStringToHandle(638, 131, "大事なもの", White, FontMain);

					ScreenFlip();

					UpdateKey();
					if (Key[KEY_INPUT_LEFT] == 1) {
						if (SelectMenu[ITEMMENU] == 216) { SelectMenu[ITEMMENU] = 18; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
						else if (SelectMenu[ITEMMENU] == 414) { SelectMenu[ITEMMENU] = 216; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
						else if (SelectMenu[ITEMMENU] == 612) { SelectMenu[ITEMMENU] = 414; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
					}
					else if (Key[KEY_INPUT_RIGHT] == 1) {
						if (SelectMenu[ITEMMENU] == 414) { SelectMenu[ITEMMENU] = 612; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
						else if (SelectMenu[ITEMMENU] == 216) { SelectMenu[ITEMMENU] = 414; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
						else if (SelectMenu[ITEMMENU] == 18) { SelectMenu[ITEMMENU] = 216; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
					}
					else if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) {
						int SelectItemMenuX = 18, SelectItemMenuY = 198;
						if (SelectMenu[ITEMMENU] == 18) {
							PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
							while (1) {
								ClearDrawScreen();
								DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
								DrawGraph(0, 0, MenuGraph[ITEMMENU], TRUE);
								DrawModiGraph(18, 126, 18 + 186, 126, 18 + 186, 162, 18, 162, SelectGraph, TRUE);

								SetDrawBlendMode(DX_BLENDMODE_ALPHA, ItemMenuPal1);
								DrawModiGraph(SelectItemMenuX, SelectItemMenuY, SelectItemMenuX + 366, SelectItemMenuY, SelectItemMenuX + 366, SelectItemMenuY + 36, SelectItemMenuX, SelectItemMenuY + 36, SelectGraph, TRUE);
								if (ItemMenuPal1 == 255) MenuFlag = 1;
								else if (ItemMenuPal1 == 129) MenuFlag = 0;

								if (MenuFlag == 1) ItemMenuPal1 = ItemMenuPal1 - 6;
								else if (MenuFlag == 0) ItemMenuPal1 = ItemMenuPal1 + 6;

								SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
								DrawStringToHandle(54, 131, "アイテム", White, FontMain);
								DrawStringToHandle(280, 131, "武器", White, FontMain);
								DrawStringToHandle(479, 131, "防具", White, FontMain);
								DrawStringToHandle(638, 131, "大事なもの", White, FontMain);

								ScreenFlip();

								UpdateKey();
								if (Key[KEY_INPUT_ESCAPE] == 1 || Key[KEY_INPUT_X] == 1) {
									PlaySoundMem(SE[CANCEL], DX_PLAYTYPE_BACK);
									break;
								}

								if (ProcessMessage() < 0) break;
							}
						}
						else if (SelectMenu[ITEMMENU] == 216) {
							PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
							while (1) {
								ClearDrawScreen();
								DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
								DrawGraph(0, 0, MenuGraph[ITEMMENU], TRUE);
								DrawModiGraph(216, 126, 216 + 186, 126, 216 + 186, 162, 216, 162, SelectGraph, TRUE);

								SetDrawBlendMode(DX_BLENDMODE_ALPHA, ItemMenuPal1);
								DrawModiGraph(SelectItemMenuX, SelectItemMenuY, SelectItemMenuX + 366, SelectItemMenuY, SelectItemMenuX + 366, SelectItemMenuY + 36, SelectItemMenuX, SelectItemMenuY + 36, SelectGraph, TRUE);
								if (ItemMenuPal1 == 255) MenuFlag = 1;
								else if (ItemMenuPal1 == 129) MenuFlag = 0;

								if (MenuFlag == 1) ItemMenuPal1 = ItemMenuPal1 - 6;
								else if (MenuFlag == 0) ItemMenuPal1 = ItemMenuPal1 + 6;

								SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
								DrawStringToHandle(54, 131, "アイテム", White, FontMain);
								DrawStringToHandle(280, 131, "武器", White, FontMain);
								DrawStringToHandle(479, 131, "防具", White, FontMain);
								DrawStringToHandle(638, 131, "大事なもの", White, FontMain);

								ScreenFlip();

								UpdateKey();
								if (Key[KEY_INPUT_ESCAPE] == 1 || Key[KEY_INPUT_X] == 1) {
									PlaySoundMem(SE[CANCEL], DX_PLAYTYPE_BACK);
									break;
								}

								if (ProcessMessage() < 0) break;
							}
						}
						else if (SelectMenu[ITEMMENU] == 414) {
							PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
							while (1) {
								ClearDrawScreen();
								DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
								DrawGraph(0, 0, MenuGraph[ITEMMENU], TRUE);
								DrawModiGraph(414, 126, 414 + 186, 126, 414 + 186, 162, 414, 162, SelectGraph, TRUE);

								SetDrawBlendMode(DX_BLENDMODE_ALPHA, ItemMenuPal1);
								DrawModiGraph(SelectItemMenuX, SelectItemMenuY, SelectItemMenuX + 366, SelectItemMenuY, SelectItemMenuX + 366, SelectItemMenuY + 36, SelectItemMenuX, SelectItemMenuY + 36, SelectGraph, TRUE);
								if (ItemMenuPal1 == 255) MenuFlag = 1;
								else if (ItemMenuPal1 == 129) MenuFlag = 0;

								if (MenuFlag == 1) ItemMenuPal1 = ItemMenuPal1 - 6;
								else if (MenuFlag == 0) ItemMenuPal1 = ItemMenuPal1 + 6;

								SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
								DrawStringToHandle(54, 131, "アイテム", White, FontMain);
								DrawStringToHandle(280, 131, "武器", White, FontMain);
								DrawStringToHandle(479, 131, "防具", White, FontMain);
								DrawStringToHandle(638, 131, "大事なもの", White, FontMain);

								ScreenFlip();

								UpdateKey();
								if (Key[KEY_INPUT_ESCAPE] == 1 || Key[KEY_INPUT_X] == 1) {
									PlaySoundMem(SE[CANCEL], DX_PLAYTYPE_BACK);
									break;
								}

								if (ProcessMessage() < 0) break;
							}
						}
						else if (SelectMenu[ITEMMENU] == 612) {
							PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
							while (1) {
								ClearDrawScreen();
								DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
								DrawGraph(0, 0, MenuGraph[ITEMMENU], TRUE);
								DrawModiGraph(612, 126, 612 + 186, 126, 612 + 186, 162, 612, 162, SelectGraph, TRUE);

								SetDrawBlendMode(DX_BLENDMODE_ALPHA, ItemMenuPal1);
								DrawModiGraph(SelectItemMenuX, SelectItemMenuY, SelectItemMenuX + 366, SelectItemMenuY, SelectItemMenuX + 366, SelectItemMenuY + 36, SelectItemMenuX, SelectItemMenuY + 36, SelectGraph, TRUE);
								if (ItemMenuPal1 == 255) MenuFlag = 1;
								else if (ItemMenuPal1 == 129) MenuFlag = 0;

								if (MenuFlag == 1) ItemMenuPal1 = ItemMenuPal1 - 6;
								else if (MenuFlag == 0) ItemMenuPal1 = ItemMenuPal1 + 6;

								SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
								DrawStringToHandle(54, 131, "アイテム", White, FontMain);
								DrawStringToHandle(280, 131, "武器", White, FontMain);
								DrawStringToHandle(479, 131, "防具", White, FontMain);
								DrawStringToHandle(638, 131, "大事なもの", White, FontMain);

								ScreenFlip();

								UpdateKey();
								if (Key[KEY_INPUT_ESCAPE] == 1 || Key[KEY_INPUT_X] == 1) {
									PlaySoundMem(SE[CANCEL], DX_PLAYTYPE_BACK);
									break;
								}

								if (ProcessMessage() < 0) break;
							}
						}
					}
					else if (Key[KEY_INPUT_ESCAPE] == 1 || Key[KEY_INPUT_X] == 1) {
						PlaySoundMem(SE[CANCEL], DX_PLAYTYPE_BACK);
						break;
					}

					if (ProcessMessage() < 0) break;
				}
			}
			else if (SelectMenu[MAINMENU] == 54) {
				PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
				int SkillMenuPal1 = 255;
				while (1) {
					ClearDrawScreen();
					DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
					DrawGraph(0, 0, MenuGraph[MAINMENU], TRUE);
					DrawModiGraph(18, 54, 222, 54, 222, 54 + 36, 18, 54 + 36, SelectGraph, TRUE);

					SetDrawBlendMode(DX_BLENDMODE_ALPHA, SkillMenuPal1);
					DrawModiGraph(258, SelectMenu[SKILLMENU], 798, SelectMenu[SKILLMENU], 798, SelectMenu[SKILLMENU] + 147, 258, SelectMenu[SKILLMENU] + 147, SelectGraph, TRUE);
					if (SkillMenuPal1 == 255) MenuFlag = 1;
					else if (SkillMenuPal1 == 129) MenuFlag = 0;

					if (MenuFlag == 1) SkillMenuPal1 = SkillMenuPal1 - 6;
					else if (MenuFlag == 0) SkillMenuPal1 = SkillMenuPal1 + 6;

					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
					DrawStringToHandle(24, 23, "アイテム", White, FontMain);
					DrawStringToHandle(24, 59, "スキル", White, FontMain);
					DrawStringToHandle(24, 95, "装備", White, FontMain);
					DrawStringToHandle(24, 131, "ステータス", White, FontMain);
					DrawStringToHandle(24, 167, "オプション", White, FontMain);
					if (BattleMap == FALSE) DrawStringToHandle(24, 203, "セーブ", White, FontMain);
					else if (BattleMap == TRUE) DrawStringToHandle(24, 203, "セーブ", Gray, FontMain);
					if (Cheat == FALSE) DrawStringToHandle(24, 239, "チート", Gray, FontMain);
					else if (Cheat == TRUE) DrawStringToHandle(24, 239, "チート", White, FontMain);
					DrawStringToHandle(24, 275, "ゲーム終了", White, FontMain);

					HPBar = (float)StatusMainChar[HP] / StatusMainChar[HPMAX] * 186;
					MPBar = (float)StatusMainChar[MP] / StatusMainChar[MPMAX] * 186;
					HPBarWidth = HPBar;
					MPBarWidth = MPBar;

					DrawGraph(259, 19, FaceGraph[FACEMAIN], TRUE);
					if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(419, 42, White, FontMain, "%s", Name.c_str());
					else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(419, 42, Yellow, FontMain, "%s", Name.c_str());
					else if (HPBarWidth == 0) { DrawFormatStringToHandle(419, 42, Red, FontMain, "%s", Name.c_str()); DrawGraph(420, 112, IconGraph[1], TRUE); }
					DrawStringToHandle(419, 78, "Lv", Blue, FontMain);
					DrawFormatStringToHandle(508, 78, White, FontMain, "%3d", StatusMainChar[LV]);
					DrawStringToHandle(599, 42, "勇者", White, FontMain);
					DrawGraph(600, 101, BarBaseGraph, TRUE);
					DrawGraph(600, 137, BarBaseGraph, TRUE);
					DrawRectGraph(600, 101, 0, 0, HPBarWidth, 7, HPBarGraph, TRUE, FALSE);
					DrawRectGraph(600, 137, 0, 0, MPBarWidth, 7, MPBarGraph, TRUE, FALSE);
					DrawStringToHandle(599, 78, "HP", Blue, FontMain);
					DrawStringToHandle(599, 114, "MP", Blue, FontMain);
					if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(652, 78, White, FontMain, "%4d", StatusMainChar[HP]);
					else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(652, 78, Yellow, FontMain, "%4d", StatusMainChar[HP]);
					else if (HPBarWidth == 0) DrawFormatStringToHandle(652, 78, Red, FontMain, "%4d", StatusMainChar[HP]);
					if (MPBarWidth <= 186 && MPBarWidth > 56) DrawFormatStringToHandle(652, 114, White, FontMain, "%4d", StatusMainChar[MP]);
					else if (MPBarWidth <= 56 && MPBarWidth > 0) DrawFormatStringToHandle(652, 114, Yellow, FontMain, "%4d", StatusMainChar[MP]);
					else if (MPBarWidth == 0) DrawFormatStringToHandle(652, 114, Red, FontMain, "%4d", StatusMainChar[MP]);
					DrawFormatStringToHandle(652, 78, White, FontMain, "    /%4d", StatusMainChar[HPMAX]);
					DrawFormatStringToHandle(652, 114, White, FontMain, "    /%4d", StatusMainChar[MPMAX]);

					if (Money >= 0) DrawFormatStringToHandle(30, 574, White, FontMain, "%10ld", Money);
					else if (Money < 0) DrawFormatStringToHandle(30, 574, Red, FontMain, "%10ld", Money);
					DrawStringToHandle(190, 574, "G", Blue, FontMain);

					ScreenFlip();

					UpdateKey();
					if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) {
						int SelectSkillMenu = 126, SkillMenuPal2 = 255;
						if (SelectMenu[SKILLMENU] == 18) {
							PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
							while (1) {
								ClearDrawScreen();
								DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
								DrawGraph(0, 0, MenuGraph[SKILLMENU], TRUE);

								SetDrawBlendMode(DX_BLENDMODE_ALPHA, SkillMenuPal2);
								DrawModiGraph(18, SelectSkillMenu, 222, SelectSkillMenu, 222, SelectSkillMenu + 36, 18, SelectSkillMenu + 36, SelectGraph, TRUE);
								if (SkillMenuPal2 == 255) MenuFlag = 1;
								else if (SkillMenuPal2 == 129) MenuFlag = 0;

								if (MenuFlag == 1) SkillMenuPal2 = SkillMenuPal2 - 6;
								else if (MenuFlag == 0) SkillMenuPal2 = SkillMenuPal2 + 6;

								SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
								DrawStringToHandle(25, 130, "魔法", White, FontMain);

								HPBar = (float)StatusMainChar[HP] / StatusMainChar[HPMAX] * 186;
								MPBar = (float)StatusMainChar[MP] / StatusMainChar[MPMAX] * 186;
								HPBarWidth = HPBar;
								MPBarWidth = MPBar;

								DrawGraph(258, 126, FaceGraph[FACEMAIN], TRUE);
								if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(418, 149, White, FontMain, "%s", Name.c_str());
								else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(418, 149, Yellow, FontMain, "%s", Name.c_str());
								else if (HPBarWidth == 0) { DrawFormatStringToHandle(418, 149, Red, FontMain, "%s", Name.c_str()); DrawGraph(420, 218, IconGraph[1], TRUE); }		
								DrawStringToHandle(418, 185, "Lv", Blue, FontMain);
								DrawFormatStringToHandle(507, 185, White, FontMain, "%3d", StatusMainChar[LV]);
								DrawStringToHandle(598, 149, "勇者", White, FontMain);
								DrawGraph(599, 208, BarBaseGraph, TRUE);
								DrawGraph(599, 244, BarBaseGraph, TRUE);
								DrawRectGraph(599, 208, 0, 0, HPBarWidth, 7, HPBarGraph, TRUE, FALSE);
								DrawRectGraph(599, 244, 0, 0, MPBarWidth, 7, MPBarGraph, TRUE, FALSE);
								DrawStringToHandle(598, 185, "HP", Blue, FontMain);
								DrawStringToHandle(598, 221, "MP", Blue, FontMain);
								if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(651, 185, White, FontMain, "%4d", StatusMainChar[HP]);
								else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(651, 185, Yellow, FontMain, "%4d", StatusMainChar[HP]);
								else if (HPBarWidth == 0) DrawFormatStringToHandle(651, 185, Red, FontMain, "%4d", StatusMainChar[HP]);
								if (MPBarWidth <= 186 && MPBarWidth > 56) DrawFormatStringToHandle(651, 221, White, FontMain, "%4d", StatusMainChar[MP]);
								else if (MPBarWidth <= 56 && MPBarWidth > 0) DrawFormatStringToHandle(651, 221, Yellow, FontMain, "%4d", StatusMainChar[MP]);
								else if (MPBarWidth == 0) DrawFormatStringToHandle(651, 221, Red, FontMain, "%4d", StatusMainChar[MP]);
								DrawFormatStringToHandle(651, 185, White, FontMain, "    /%4d", StatusMainChar[HPMAX]);
								DrawFormatStringToHandle(651, 221, White, FontMain, "    /%4d", StatusMainChar[MPMAX]);

								ScreenFlip();

								UpdateKey();
								if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) {
									int SelectSkillMenu2X = 18, SelectSkillMenu2Y = 306, SkillMenuPal3 = 255;
									if (SelectSkillMenu == 126) {
										PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
										while (1) {
											ClearDrawScreen();
											DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
											DrawGraph(0, 0, MenuGraph[SKILLMENU], TRUE);
											DrawModiGraph(18, 126, 222, 126, 222, 126 + 36, 18, 126 + 36, SelectGraph, TRUE);

											SetDrawBlendMode(DX_BLENDMODE_ALPHA, SkillMenuPal3);
											DrawModiGraph(SelectSkillMenu2X, SelectSkillMenu2Y, SelectSkillMenu2X + 366, SelectSkillMenu2Y, SelectSkillMenu2X + 366, SelectSkillMenu2Y + 36, SelectSkillMenu2X, SelectSkillMenu2Y + 36, SelectGraph, TRUE);
											if (SkillMenuPal3 == 255) MenuFlag = 1;
											else if (SkillMenuPal3 == 129) MenuFlag = 0;

											if (MenuFlag == 1) SkillMenuPal3 = SkillMenuPal3 - 6;
											else if (MenuFlag == 0) SkillMenuPal3 = SkillMenuPal3 + 6;

											SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
											DrawStringToHandle(25, 130, "魔法", White, FontMain);

											HPBar = (float)StatusMainChar[HP] / StatusMainChar[HPMAX] * 186;
											MPBar = (float)StatusMainChar[MP] / StatusMainChar[MPMAX] * 186;
											HPBarWidth = HPBar;
											MPBarWidth = MPBar;

											DrawGraph(258, 126, FaceGraph[FACEMAIN], TRUE);
											if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(418, 149, White, FontMain, "%s", Name.c_str());
											else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(418, 149, Yellow, FontMain, "%s", Name.c_str());
											else if (HPBarWidth == 0) { DrawFormatStringToHandle(418, 149, Red, FontMain, "%s", Name.c_str()); DrawGraph(420, 218, IconGraph[1], TRUE); }
											DrawStringToHandle(418, 185, "Lv", Blue, FontMain);
											DrawFormatStringToHandle(507, 185, White, FontMain, "%3d", StatusMainChar[LV]);
											DrawStringToHandle(598, 149, "勇者", White, FontMain);
											DrawGraph(599, 208, BarBaseGraph, TRUE);
											DrawGraph(599, 244, BarBaseGraph, TRUE);
											DrawRectGraph(599, 208, 0, 0, HPBarWidth, 7, HPBarGraph, TRUE, FALSE);
											DrawRectGraph(599, 244, 0, 0, MPBarWidth, 7, MPBarGraph, TRUE, FALSE);
											DrawStringToHandle(598, 185, "HP", Blue, FontMain);
											DrawStringToHandle(598, 221, "MP", Blue, FontMain);
											if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(651, 185, White, FontMain, "%4d", StatusMainChar[HP]);
											else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(651, 185, Yellow, FontMain, "%4d", StatusMainChar[HP]);
											else if (HPBarWidth == 0) DrawFormatStringToHandle(651, 185, Red, FontMain, "%4d", StatusMainChar[HP]);
											if (MPBarWidth <= 186 && MPBarWidth > 56) DrawFormatStringToHandle(651, 221, White, FontMain, "%4d", StatusMainChar[MP]);
											else if (MPBarWidth <= 56 && MPBarWidth > 0) DrawFormatStringToHandle(651, 221, Yellow, FontMain, "%4d", StatusMainChar[MP]);
											else if (MPBarWidth == 0) DrawFormatStringToHandle(651, 221, Red, FontMain, "%4d", StatusMainChar[MP]);
											DrawFormatStringToHandle(651, 185, White, FontMain, "    /%4d", StatusMainChar[HPMAX]);
											DrawFormatStringToHandle(651, 221, White, FontMain, "    /%4d", StatusMainChar[MPMAX]);

											ScreenFlip();

											UpdateKey();
											if (Key[KEY_INPUT_ESCAPE] == 1 || Key[KEY_INPUT_X] == 1) {
												PlaySoundMem(SE[CANCEL], DX_PLAYTYPE_BACK);
												break;
											}
											
											if (ProcessMessage() < 0) break;
										}
									}
								}
								else if (Key[KEY_INPUT_ESCAPE] == 1 || Key[KEY_INPUT_X] == 1) {
									PlaySoundMem(SE[CANCEL], DX_PLAYTYPE_BACK);
									break;
								}

								if (ProcessMessage() < 0) break;
							}
						}
					}
					else if (Key[KEY_INPUT_ESCAPE] == 1 || Key[KEY_INPUT_X] == 1) {
						PlaySoundMem(SE[CANCEL], DX_PLAYTYPE_BACK);
						break;
					}

					if (ProcessMessage() < 0) break;
				}
			}
			else if (SelectMenu[MAINMENU] == 90) {
				PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
				int EquipMenuPal1 = 255;
				while (1) {
					ClearDrawScreen();
					DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
					DrawGraph(0, 0, MenuGraph[MAINMENU], TRUE);
					DrawModiGraph(18, 90, 222, 90, 222, 90 + 36, 18, 90 + 36, SelectGraph, TRUE);

					SetDrawBlendMode(DX_BLENDMODE_ALPHA, EquipMenuPal1);
					DrawModiGraph(258, SelectMenu[EQUIPMENU], 798, SelectMenu[EQUIPMENU], 798, SelectMenu[EQUIPMENU] + 147, 258, SelectMenu[EQUIPMENU] + 147, SelectGraph, TRUE);
					if (EquipMenuPal1 == 255) MenuFlag = 1;
					else if (EquipMenuPal1 == 129) MenuFlag = 0;

					if (MenuFlag == 1) EquipMenuPal1 = EquipMenuPal1 - 6;
					else if (MenuFlag == 0) EquipMenuPal1 = EquipMenuPal1 + 6;

					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
					DrawStringToHandle(24, 23, "アイテム", White, FontMain);
					DrawStringToHandle(24, 59, "スキル", White, FontMain);
					DrawStringToHandle(24, 95, "装備", White, FontMain);
					DrawStringToHandle(24, 131, "ステータス", White, FontMain);
					DrawStringToHandle(24, 167, "オプション", White, FontMain);
					if (BattleMap == FALSE) DrawStringToHandle(24, 203, "セーブ", White, FontMain);
					else if (BattleMap == TRUE) DrawStringToHandle(24, 203, "セーブ", Gray, FontMain);
					if (Cheat == FALSE) DrawStringToHandle(24, 239, "チート", Gray, FontMain);
					else if (Cheat == TRUE) DrawStringToHandle(24, 239, "チート", White, FontMain);
					DrawStringToHandle(24, 275, "ゲーム終了", White, FontMain);

					HPBar = (float)StatusMainChar[HP] / StatusMainChar[HPMAX] * 186;
					MPBar = (float)StatusMainChar[MP] / StatusMainChar[MPMAX] * 186;
					HPBarWidth = HPBar;
					MPBarWidth = MPBar;

					DrawGraph(259, 19, FaceGraph[FACEMAIN], TRUE);
					if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(419, 42, White, FontMain, "%s", Name.c_str());
					else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(419, 42, Yellow, FontMain, "%s", Name.c_str());
					else if (HPBarWidth == 0) { DrawFormatStringToHandle(419, 42, Red, FontMain, "%s", Name.c_str()); DrawGraph(420, 112, IconGraph[1], TRUE); }
					DrawStringToHandle(419, 78, "Lv", Blue, FontMain);
					DrawFormatStringToHandle(508, 78, White, FontMain, "%3d", StatusMainChar[LV]);
					DrawStringToHandle(599, 42, "勇者", White, FontMain);
					DrawGraph(600, 101, BarBaseGraph, TRUE);
					DrawGraph(600, 137, BarBaseGraph, TRUE);
					DrawRectGraph(600, 101, 0, 0, HPBarWidth, 7, HPBarGraph, TRUE, FALSE);
					DrawRectGraph(600, 137, 0, 0, MPBarWidth, 7, MPBarGraph, TRUE, FALSE);
					DrawStringToHandle(599, 78, "HP", Blue, FontMain);
					DrawStringToHandle(599, 114, "MP", Blue, FontMain);
					if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(652, 78, White, FontMain, "%4d", StatusMainChar[HP]);
					else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(652, 78, Yellow, FontMain, "%4d", StatusMainChar[HP]);
					else if (HPBarWidth == 0) DrawFormatStringToHandle(652, 78, Red, FontMain, "%4d", StatusMainChar[HP]);
					if (MPBarWidth <= 186 && MPBarWidth > 56) DrawFormatStringToHandle(652, 114, White, FontMain, "%4d", StatusMainChar[MP]);
					else if (MPBarWidth <= 56 && MPBarWidth > 0) DrawFormatStringToHandle(652, 114, Yellow, FontMain, "%4d", StatusMainChar[MP]);
					else if (MPBarWidth == 0) DrawFormatStringToHandle(652, 114, Red, FontMain, "%4d", StatusMainChar[MP]);
					DrawFormatStringToHandle(652, 78, White, FontMain, "    /%4d", StatusMainChar[HPMAX]);
					DrawFormatStringToHandle(652, 114, White, FontMain, "    /%4d", StatusMainChar[MPMAX]);

					if (Money >= 0) DrawFormatStringToHandle(30, 574, White, FontMain, "%10ld", Money);
					else if (Money < 0) DrawFormatStringToHandle(30, 574, Red, FontMain, "%10ld", Money);
					DrawStringToHandle(190, 574, "G", Blue, FontMain);

					ScreenFlip();

					UpdateKey();
					if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) {
						int SelectEquipMenu = 330, EquipMenuPal2 = 255;
						if (SelectMenu[EQUIPMENU] == 18) {
							PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
							while (1) {
								ClearDrawScreen();
								DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
								DrawGraph(0, 0, MenuGraph[EQUIPMENU], TRUE);

								SetDrawBlendMode(DX_BLENDMODE_ALPHA, EquipMenuPal2);
								DrawModiGraph(SelectEquipMenu, 126, SelectEquipMenu + 148, 126, SelectEquipMenu + 148, 162, SelectEquipMenu, 162, SelectGraph, TRUE);
								if (EquipMenuPal2 == 255) MenuFlag = 1;
								else if (EquipMenuPal2 == 129) MenuFlag = 0;

								if (MenuFlag == 1) EquipMenuPal2 = EquipMenuPal2 - 6;
								else if (MenuFlag == 0) EquipMenuPal2 = EquipMenuPal2 + 6;

								SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
								DrawStringToHandle(375, 130, "装備", White, FontMain);
								DrawStringToHandle(510, 130, "最強装備", White, FontMain);
								DrawStringToHandle(667, 130, "全て外す", White, FontMain);

								if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(26, 131, White, FontMain, "%s", Name.c_str());
								else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(26, 131, Yellow, FontMain, "%s", Name.c_str());
								else if (HPBarWidth == 0) DrawFormatStringToHandle(26, 131, Red, FontMain, "%s", Name.c_str());
								DrawStringToHandle(26, 167, "攻撃力　　　 →", Blue, FontMain);
								DrawStringToHandle(26, 203, "防御力　　　 →", Blue, FontMain);
								DrawStringToHandle(26, 239, "魔法攻撃　　 →", Blue, FontMain);
								DrawStringToHandle(26, 275, "魔法防御　　 →", Blue, FontMain);
								DrawStringToHandle(26, 311, "敏捷性　　　 →", Blue, FontMain);
								DrawStringToHandle(26, 347, "運　　　　　 →", Blue, FontMain);
								DrawFormatStringToHandle(163, 167, White, FontMain, "%3d", StatusMainChar[ATK]);
								DrawFormatStringToHandle(163, 203, White, FontMain, "%3d", StatusMainChar[DEF]);
								DrawFormatStringToHandle(163, 239, White, FontMain, "%3d", StatusMainChar[MATK]);
								DrawFormatStringToHandle(163, 275, White, FontMain, "%3d", StatusMainChar[MDEF]);
								DrawFormatStringToHandle(163, 311, White, FontMain, "%3d", StatusMainChar[AGI]);
								DrawFormatStringToHandle(163, 347, White, FontMain, "%3d", StatusMainChar[LUCK]);

								DrawStringToHandle(338, 203, "武器", Blue, FontMain);
								DrawStringToHandle(338, 239, "盾", Blue, FontMain);
								DrawStringToHandle(338, 275, "頭", Blue, FontMain);
								DrawStringToHandle(338, 311, "服", Blue, FontMain);
								DrawStringToHandle(338, 347, "装飾品", Blue, FontMain);

								DrawGraph(476, 200, IconGraph[97], TRUE);
								DrawGraph(476, 236, IconGraph[128], TRUE);
								DrawGraph(476, 272, IconGraph[130], TRUE);
								DrawGraph(476, 308, IconGraph[135], TRUE);

								DrawStringToHandle(511, 203, "剣", White, FontMain);
								DrawStringToHandle(511, 239, "盾", White, FontMain);
								DrawStringToHandle(511, 275, "帽子", White, FontMain);
								DrawStringToHandle(511, 311, "服", White, FontMain);

								ScreenFlip();

								UpdateKey();
								if (Key[KEY_INPUT_LEFT] == 1) {
									if (SelectEquipMenu == 490) { SelectEquipMenu = 330; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
									if (SelectEquipMenu == 650) { SelectEquipMenu = 490; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
								}
								else if (Key[KEY_INPUT_RIGHT] == 1) {
									if (SelectEquipMenu == 490) { SelectEquipMenu = 650; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
									if (SelectEquipMenu == 330) { SelectEquipMenu = 490; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
								}
								else if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) {
									int SelectEquipMenu2 = 198, EquipMenuPal3 = 255;
									if (SelectEquipMenu == 330) {
										PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
										while (1) {
											ClearDrawScreen();
											DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
											DrawGraph(0, 0, MenuGraph[EQUIPMENU], TRUE);
											DrawModiGraph(330, 126, 330 + 148, 126, 330 + 148, 162, 330, 162, SelectGraph, TRUE);

											SetDrawBlendMode(DX_BLENDMODE_ALPHA, EquipMenuPal3);
											DrawModiGraph(330, SelectEquipMenu2, 798, SelectEquipMenu2, 798, SelectEquipMenu2 + 36, 330, SelectEquipMenu2 + 36, SelectGraph, TRUE);
											if (EquipMenuPal3 == 255) MenuFlag = 1;
											else if (EquipMenuPal3 == 129) MenuFlag = 0;

											if (MenuFlag == 1) EquipMenuPal3 = EquipMenuPal3 - 6;
											else if (MenuFlag == 0) EquipMenuPal3 = EquipMenuPal3 + 6;

											SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
											DrawStringToHandle(375, 130, "装備", White, FontMain);
											DrawStringToHandle(510, 130, "最強装備", White, FontMain);
											DrawStringToHandle(667, 130, "全て外す", White, FontMain);

											if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(26, 131, White, FontMain, "%s", Name.c_str());
											else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(26, 131, Yellow, FontMain, "%s", Name.c_str());
											else if (HPBarWidth == 0) DrawFormatStringToHandle(26, 131, Red, FontMain, "%s", Name.c_str());											
											DrawStringToHandle(26, 167, "攻撃力　　　 →", Blue, FontMain);
											DrawStringToHandle(26, 203, "防御力　　　 →", Blue, FontMain);
											DrawStringToHandle(26, 239, "魔法攻撃　　 →", Blue, FontMain);
											DrawStringToHandle(26, 275, "魔法防御　　 →", Blue, FontMain);
											DrawStringToHandle(26, 311, "敏捷性　　　 →", Blue, FontMain);
											DrawStringToHandle(26, 347, "運　　　　　 →", Blue, FontMain);
											DrawFormatStringToHandle(163, 167, White, FontMain, "%3d", StatusMainChar[ATK]);
											DrawFormatStringToHandle(163, 203, White, FontMain, "%3d", StatusMainChar[DEF]);
											DrawFormatStringToHandle(163, 239, White, FontMain, "%3d", StatusMainChar[MATK]);
											DrawFormatStringToHandle(163, 275, White, FontMain, "%3d", StatusMainChar[MDEF]);
											DrawFormatStringToHandle(163, 311, White, FontMain, "%3d", StatusMainChar[AGI]);
											DrawFormatStringToHandle(163, 347, White, FontMain, "%3d", StatusMainChar[LUCK]);

											DrawStringToHandle(338, 203, "武器", Blue, FontMain);
											DrawStringToHandle(338, 239, "盾", Blue, FontMain);
											DrawStringToHandle(338, 275, "頭", Blue, FontMain);
											DrawStringToHandle(338, 311, "服", Blue, FontMain);
											DrawStringToHandle(338, 347, "装飾品", Blue, FontMain);

											DrawGraph(476, 200, IconGraph[97], TRUE);
											DrawGraph(476, 236, IconGraph[128], TRUE);
											DrawGraph(476, 272, IconGraph[130], TRUE);
											DrawGraph(476, 308, IconGraph[135], TRUE);

											DrawStringToHandle(511, 203, "剣", White, FontMain);
											DrawStringToHandle(511, 239, "盾", White, FontMain);
											DrawStringToHandle(511, 275, "帽子", White, FontMain);
											DrawStringToHandle(511, 311, "服", White, FontMain);

											ScreenFlip();

											UpdateKey();
											if (Key[KEY_INPUT_UP] == 1) {
												if (SelectEquipMenu2 == 234) { SelectEquipMenu2 = 198; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
												else if (SelectEquipMenu2 == 270) { SelectEquipMenu2 = 234; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
												else if (SelectEquipMenu2 == 306) { SelectEquipMenu2 = 270; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
												else if (SelectEquipMenu2 == 342) { SelectEquipMenu2 = 306; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
											}
											else if (Key[KEY_INPUT_DOWN] == 1) {
												if (SelectEquipMenu2 == 306) { SelectEquipMenu2 = 342; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
												else if (SelectEquipMenu2 == 270) { SelectEquipMenu2 = 306; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
												else if (SelectEquipMenu2 == 234) { SelectEquipMenu2 = 270; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
												else if (SelectEquipMenu2 == 198) { SelectEquipMenu2 = 234; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
											}
											else if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) {
												int SelectEquipMenu3X = 18, SelectEquipMenu3Y = 414, EquipMenuPal4 = 255;
												if (SelectEquipMenu2 == 198) {
													PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
													while (1) {
														ClearDrawScreen();
														DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
														DrawGraph(0, 0, MenuGraph[EQUIPMENU], TRUE);
														DrawModiGraph(330, 126, 330 + 148, 126, 330 + 148, 162, 330, 162, SelectGraph, TRUE);
														DrawModiGraph(330, 198, 798, 198, 798, 198 + 36, 330, 198 + 36, SelectGraph, TRUE);

														SetDrawBlendMode(DX_BLENDMODE_ALPHA, EquipMenuPal4);
														DrawModiGraph(SelectEquipMenu3X, SelectEquipMenu3Y, SelectEquipMenu3X + 366, SelectEquipMenu3Y, SelectEquipMenu3X + 366, SelectEquipMenu3Y + 36, SelectEquipMenu3X, SelectEquipMenu3Y + 36, SelectGraph, TRUE);
														if (EquipMenuPal4 == 255) MenuFlag = 1;
														else if (EquipMenuPal4 == 129) MenuFlag = 0;

														if (MenuFlag == 1) EquipMenuPal4 = EquipMenuPal4 - 6;
														else if (MenuFlag == 0) EquipMenuPal4 = EquipMenuPal4 + 6;

														SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
														DrawStringToHandle(375, 130, "装備", White, FontMain);
														DrawStringToHandle(510, 130, "最強装備", White, FontMain);
														DrawStringToHandle(667, 130, "全て外す", White, FontMain);

														if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(26, 131, White, FontMain, "%s", Name.c_str());
														else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(26, 131, Yellow, FontMain, "%s", Name.c_str());
														else if (HPBarWidth == 0) DrawFormatStringToHandle(26, 131, Red, FontMain, "%s", Name.c_str());
														DrawStringToHandle(26, 167, "攻撃力　　　 →", Blue, FontMain);
														DrawStringToHandle(26, 203, "防御力　　　 →", Blue, FontMain);
														DrawStringToHandle(26, 239, "魔法攻撃　　 →", Blue, FontMain);
														DrawStringToHandle(26, 275, "魔法防御　　 →", Blue, FontMain);
														DrawStringToHandle(26, 311, "敏捷性　　　 →", Blue, FontMain);
														DrawStringToHandle(26, 347, "運　　　　　 →", Blue, FontMain);
														DrawFormatStringToHandle(163, 167, White, FontMain, "%3d", StatusMainChar[ATK]);
														DrawFormatStringToHandle(163, 203, White, FontMain, "%3d", StatusMainChar[DEF]);
														DrawFormatStringToHandle(163, 239, White, FontMain, "%3d", StatusMainChar[MATK]);
														DrawFormatStringToHandle(163, 275, White, FontMain, "%3d", StatusMainChar[MDEF]);
														DrawFormatStringToHandle(163, 311, White, FontMain, "%3d", StatusMainChar[AGI]);
														DrawFormatStringToHandle(163, 347, White, FontMain, "%3d", StatusMainChar[LUCK]);

														DrawStringToHandle(338, 203, "武器", Blue, FontMain);
														DrawStringToHandle(338, 239, "盾", Blue, FontMain);
														DrawStringToHandle(338, 275, "頭", Blue, FontMain);
														DrawStringToHandle(338, 311, "服", Blue, FontMain);
														DrawStringToHandle(338, 347, "装飾品", Blue, FontMain);

														DrawGraph(476, 200, IconGraph[97], TRUE);
														DrawGraph(476, 236, IconGraph[128], TRUE);
														DrawGraph(476, 272, IconGraph[130], TRUE);
														DrawGraph(476, 308, IconGraph[135], TRUE);

														DrawStringToHandle(511, 203, "剣", White, FontMain);
														DrawStringToHandle(511, 239, "盾", White, FontMain);
														DrawStringToHandle(511, 275, "帽子", White, FontMain);
														DrawStringToHandle(511, 311, "服", White, FontMain);

														ScreenFlip();

														UpdateKey();
														if (Key[KEY_INPUT_ESCAPE] == 1 || Key[KEY_INPUT_X] == 1) {
															PlaySoundMem(SE[CANCEL], DX_PLAYTYPE_BACK);
															break;
														}

														if (ProcessMessage() < 0) break;
													}
												}
												else if (SelectEquipMenu2 == 234) {
													PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
													while (1) {
														ClearDrawScreen();
														DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
														DrawGraph(0, 0, MenuGraph[EQUIPMENU], TRUE);
														DrawModiGraph(330, 126, 330 + 148, 126, 330 + 148, 162, 330, 162, SelectGraph, TRUE);
														DrawModiGraph(330, 234, 798, 234, 798, 234 + 36, 330, 234 + 36, SelectGraph, TRUE);

														SetDrawBlendMode(DX_BLENDMODE_ALPHA, EquipMenuPal4);
														DrawModiGraph(SelectEquipMenu3X, SelectEquipMenu3Y, SelectEquipMenu3X + 366, SelectEquipMenu3Y, SelectEquipMenu3X + 366, SelectEquipMenu3Y + 36, SelectEquipMenu3X, SelectEquipMenu3Y + 36, SelectGraph, TRUE);
														if (EquipMenuPal4 == 255) MenuFlag = 1;
														else if (EquipMenuPal4 == 129) MenuFlag = 0;

														if (MenuFlag == 1) EquipMenuPal4 = EquipMenuPal4 - 6;
														else if (MenuFlag == 0) EquipMenuPal4 = EquipMenuPal4 + 6;

														SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
														DrawStringToHandle(375, 130, "装備", White, FontMain);
														DrawStringToHandle(510, 130, "最強装備", White, FontMain);
														DrawStringToHandle(667, 130, "全て外す", White, FontMain);

														if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(26, 131, White, FontMain, "%s", Name.c_str());
														else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(26, 131, Yellow, FontMain, "%s", Name.c_str());
														else if (HPBarWidth == 0) DrawFormatStringToHandle(26, 131, Red, FontMain, "%s", Name.c_str());
														DrawStringToHandle(26, 167, "攻撃力　　　 →", Blue, FontMain);
														DrawStringToHandle(26, 203, "防御力　　　 →", Blue, FontMain);
														DrawStringToHandle(26, 239, "魔法攻撃　　 →", Blue, FontMain);
														DrawStringToHandle(26, 275, "魔法防御　　 →", Blue, FontMain);
														DrawStringToHandle(26, 311, "敏捷性　　　 →", Blue, FontMain);
														DrawStringToHandle(26, 347, "運　　　　　 →", Blue, FontMain);
														DrawFormatStringToHandle(163, 167, White, FontMain, "%3d", StatusMainChar[ATK]);
														DrawFormatStringToHandle(163, 203, White, FontMain, "%3d", StatusMainChar[DEF]);
														DrawFormatStringToHandle(163, 239, White, FontMain, "%3d", StatusMainChar[MATK]);
														DrawFormatStringToHandle(163, 275, White, FontMain, "%3d", StatusMainChar[MDEF]);
														DrawFormatStringToHandle(163, 311, White, FontMain, "%3d", StatusMainChar[AGI]);
														DrawFormatStringToHandle(163, 347, White, FontMain, "%3d", StatusMainChar[LUCK]);

														DrawStringToHandle(338, 203, "武器", Blue, FontMain);
														DrawStringToHandle(338, 239, "盾", Blue, FontMain);
														DrawStringToHandle(338, 275, "頭", Blue, FontMain);
														DrawStringToHandle(338, 311, "服", Blue, FontMain);
														DrawStringToHandle(338, 347, "装飾品", Blue, FontMain);

														DrawGraph(476, 200, IconGraph[97], TRUE);
														DrawGraph(476, 236, IconGraph[128], TRUE);
														DrawGraph(476, 272, IconGraph[130], TRUE);
														DrawGraph(476, 308, IconGraph[135], TRUE);

														DrawStringToHandle(511, 203, "剣", White, FontMain);
														DrawStringToHandle(511, 239, "盾", White, FontMain);
														DrawStringToHandle(511, 275, "帽子", White, FontMain);
														DrawStringToHandle(511, 311, "服", White, FontMain);

														ScreenFlip();

														UpdateKey();
														if (Key[KEY_INPUT_ESCAPE] == 1 || Key[KEY_INPUT_X] == 1) {
															PlaySoundMem(SE[CANCEL], DX_PLAYTYPE_BACK);
															break;
														}

														if (ProcessMessage() < 0) break;
													}
												}
												else if (SelectEquipMenu2 == 270) {
													PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
													while (1) {
														ClearDrawScreen();
														DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
														DrawGraph(0, 0, MenuGraph[EQUIPMENU], TRUE);
														DrawModiGraph(330, 126, 330 + 148, 126, 330 + 148, 162, 330, 162, SelectGraph, TRUE);
														DrawModiGraph(330, 270, 798, 270, 798, 270 + 36, 330, 270 + 36, SelectGraph, TRUE);

														SetDrawBlendMode(DX_BLENDMODE_ALPHA, EquipMenuPal4);
														DrawModiGraph(SelectEquipMenu3X, SelectEquipMenu3Y, SelectEquipMenu3X + 366, SelectEquipMenu3Y, SelectEquipMenu3X + 366, SelectEquipMenu3Y + 36, SelectEquipMenu3X, SelectEquipMenu3Y + 36, SelectGraph, TRUE);
														if (EquipMenuPal4 == 255) MenuFlag = 1;
														else if (EquipMenuPal4 == 129) MenuFlag = 0;

														if (MenuFlag == 1) EquipMenuPal4 = EquipMenuPal4 - 6;
														else if (MenuFlag == 0) EquipMenuPal4 = EquipMenuPal4 + 6;

														SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
														DrawStringToHandle(375, 130, "装備", White, FontMain);
														DrawStringToHandle(510, 130, "最強装備", White, FontMain);
														DrawStringToHandle(667, 130, "全て外す", White, FontMain);

														if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(26, 131, White, FontMain, "%s", Name.c_str());
														else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(26, 131, Yellow, FontMain, "%s", Name.c_str());
														else if (HPBarWidth == 0) DrawFormatStringToHandle(26, 131, Red, FontMain, "%s", Name.c_str());
														DrawStringToHandle(26, 167, "攻撃力　　　 →", Blue, FontMain);
														DrawStringToHandle(26, 203, "防御力　　　 →", Blue, FontMain);
														DrawStringToHandle(26, 239, "魔法攻撃　　 →", Blue, FontMain);
														DrawStringToHandle(26, 275, "魔法防御　　 →", Blue, FontMain);
														DrawStringToHandle(26, 311, "敏捷性　　　 →", Blue, FontMain);
														DrawStringToHandle(26, 347, "運　　　　　 →", Blue, FontMain);
														DrawFormatStringToHandle(163, 167, White, FontMain, "%3d", StatusMainChar[ATK]);
														DrawFormatStringToHandle(163, 203, White, FontMain, "%3d", StatusMainChar[DEF]);
														DrawFormatStringToHandle(163, 239, White, FontMain, "%3d", StatusMainChar[MATK]);
														DrawFormatStringToHandle(163, 275, White, FontMain, "%3d", StatusMainChar[MDEF]);
														DrawFormatStringToHandle(163, 311, White, FontMain, "%3d", StatusMainChar[AGI]);
														DrawFormatStringToHandle(163, 347, White, FontMain, "%3d", StatusMainChar[LUCK]);

														DrawStringToHandle(338, 203, "武器", Blue, FontMain);
														DrawStringToHandle(338, 239, "盾", Blue, FontMain);
														DrawStringToHandle(338, 275, "頭", Blue, FontMain);
														DrawStringToHandle(338, 311, "服", Blue, FontMain);
														DrawStringToHandle(338, 347, "装飾品", Blue, FontMain);

														DrawGraph(476, 200, IconGraph[97], TRUE);
														DrawGraph(476, 236, IconGraph[128], TRUE);
														DrawGraph(476, 272, IconGraph[130], TRUE);
														DrawGraph(476, 308, IconGraph[135], TRUE);

														DrawStringToHandle(511, 203, "剣", White, FontMain);
														DrawStringToHandle(511, 239, "盾", White, FontMain);
														DrawStringToHandle(511, 275, "帽子", White, FontMain);
														DrawStringToHandle(511, 311, "服", White, FontMain);

														ScreenFlip();

														UpdateKey();
														if (Key[KEY_INPUT_ESCAPE] == 1 || Key[KEY_INPUT_X] == 1) {
															PlaySoundMem(SE[CANCEL], DX_PLAYTYPE_BACK);
															break;
														}

														if (ProcessMessage() < 0) break;
													}
												}
												else if (SelectEquipMenu2 == 306) {
													PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
													while (1) {
														ClearDrawScreen();
														DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
														DrawGraph(0, 0, MenuGraph[EQUIPMENU], TRUE);
														DrawModiGraph(330, 126, 330 + 148, 126, 330 + 148, 162, 330, 162, SelectGraph, TRUE);
														DrawModiGraph(330, 306, 798, 306, 798, 306 + 36, 330, 306 + 36, SelectGraph, TRUE);

														SetDrawBlendMode(DX_BLENDMODE_ALPHA, EquipMenuPal4);
														DrawModiGraph(SelectEquipMenu3X, SelectEquipMenu3Y, SelectEquipMenu3X + 366, SelectEquipMenu3Y, SelectEquipMenu3X + 366, SelectEquipMenu3Y + 36, SelectEquipMenu3X, SelectEquipMenu3Y + 36, SelectGraph, TRUE);
														if (EquipMenuPal4 == 255) MenuFlag = 1;
														else if (EquipMenuPal4 == 129) MenuFlag = 0;

														if (MenuFlag == 1) EquipMenuPal4 = EquipMenuPal4 - 6;
														else if (MenuFlag == 0) EquipMenuPal4 = EquipMenuPal4 + 6;

														SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
														DrawStringToHandle(375, 130, "装備", White, FontMain);
														DrawStringToHandle(510, 130, "最強装備", White, FontMain);
														DrawStringToHandle(667, 130, "全て外す", White, FontMain);

														if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(26, 131, White, FontMain, "%s", Name.c_str());
														else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(26, 131, Yellow, FontMain, "%s", Name.c_str());
														else if (HPBarWidth == 0) DrawFormatStringToHandle(26, 131, Red, FontMain, "%s", Name.c_str());
														DrawStringToHandle(26, 167, "攻撃力　　　 →", Blue, FontMain);
														DrawStringToHandle(26, 203, "防御力　　　 →", Blue, FontMain);
														DrawStringToHandle(26, 239, "魔法攻撃　　 →", Blue, FontMain);
														DrawStringToHandle(26, 275, "魔法防御　　 →", Blue, FontMain);
														DrawStringToHandle(26, 311, "敏捷性　　　 →", Blue, FontMain);
														DrawStringToHandle(26, 347, "運　　　　　 →", Blue, FontMain);
														DrawFormatStringToHandle(163, 167, White, FontMain, "%3d", StatusMainChar[ATK]);
														DrawFormatStringToHandle(163, 203, White, FontMain, "%3d", StatusMainChar[DEF]);
														DrawFormatStringToHandle(163, 239, White, FontMain, "%3d", StatusMainChar[MATK]);
														DrawFormatStringToHandle(163, 275, White, FontMain, "%3d", StatusMainChar[MDEF]);
														DrawFormatStringToHandle(163, 311, White, FontMain, "%3d", StatusMainChar[AGI]);
														DrawFormatStringToHandle(163, 347, White, FontMain, "%3d", StatusMainChar[LUCK]);

														DrawStringToHandle(338, 203, "武器", Blue, FontMain);
														DrawStringToHandle(338, 239, "盾", Blue, FontMain);
														DrawStringToHandle(338, 275, "頭", Blue, FontMain);
														DrawStringToHandle(338, 311, "服", Blue, FontMain);
														DrawStringToHandle(338, 347, "装飾品", Blue, FontMain);

														DrawGraph(476, 200, IconGraph[97], TRUE);
														DrawGraph(476, 236, IconGraph[128], TRUE);
														DrawGraph(476, 272, IconGraph[130], TRUE);
														DrawGraph(476, 308, IconGraph[135], TRUE);

														DrawStringToHandle(511, 203, "剣", White, FontMain);
														DrawStringToHandle(511, 239, "盾", White, FontMain);
														DrawStringToHandle(511, 275, "帽子", White, FontMain);
														DrawStringToHandle(511, 311, "服", White, FontMain);

														ScreenFlip();

														UpdateKey();
														if (Key[KEY_INPUT_ESCAPE] == 1 || Key[KEY_INPUT_X] == 1) {
															PlaySoundMem(SE[CANCEL], DX_PLAYTYPE_BACK);
															break;
														}

														if (ProcessMessage() < 0) break;
													}
												}
												else if (SelectEquipMenu2 == 342) {
													PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
													while (1) {
														ClearDrawScreen();
														DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
														DrawGraph(0, 0, MenuGraph[EQUIPMENU], TRUE);
														DrawModiGraph(330, 126, 330 + 148, 126, 330 + 148, 162, 330, 162, SelectGraph, TRUE);
														DrawModiGraph(330, 342, 798, 342, 798, 342 + 36, 330, 342 + 36, SelectGraph, TRUE);

														SetDrawBlendMode(DX_BLENDMODE_ALPHA, EquipMenuPal4);
														DrawModiGraph(SelectEquipMenu3X, SelectEquipMenu3Y, SelectEquipMenu3X + 366, SelectEquipMenu3Y, SelectEquipMenu3X + 366, SelectEquipMenu3Y + 36, SelectEquipMenu3X, SelectEquipMenu3Y + 36, SelectGraph, TRUE);
														if (EquipMenuPal4 == 255) MenuFlag = 1;
														else if (EquipMenuPal4 == 129) MenuFlag = 0;

														if (MenuFlag == 1) EquipMenuPal4 = EquipMenuPal4 - 6;
														else if (MenuFlag == 0) EquipMenuPal4 = EquipMenuPal4 + 6;

														SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
														DrawStringToHandle(375, 130, "装備", White, FontMain);
														DrawStringToHandle(510, 130, "最強装備", White, FontMain);
														DrawStringToHandle(667, 130, "全て外す", White, FontMain);

														if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(26, 131, White, FontMain, "%s", Name.c_str());
														else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(26, 131, Yellow, FontMain, "%s", Name.c_str());
														else if (HPBarWidth == 0) DrawFormatStringToHandle(26, 131, Red, FontMain, "%s", Name.c_str());
														DrawStringToHandle(26, 167, "攻撃力　　　 →", Blue, FontMain);
														DrawStringToHandle(26, 203, "防御力　　　 →", Blue, FontMain);
														DrawStringToHandle(26, 239, "魔法攻撃　　 →", Blue, FontMain);
														DrawStringToHandle(26, 275, "魔法防御　　 →", Blue, FontMain);
														DrawStringToHandle(26, 311, "敏捷性　　　 →", Blue, FontMain);
														DrawStringToHandle(26, 347, "運　　　　　 →", Blue, FontMain);
														DrawFormatStringToHandle(163, 167, White, FontMain, "%3d", StatusMainChar[ATK]);
														DrawFormatStringToHandle(163, 203, White, FontMain, "%3d", StatusMainChar[DEF]);
														DrawFormatStringToHandle(163, 239, White, FontMain, "%3d", StatusMainChar[MATK]);
														DrawFormatStringToHandle(163, 275, White, FontMain, "%3d", StatusMainChar[MDEF]);
														DrawFormatStringToHandle(163, 311, White, FontMain, "%3d", StatusMainChar[AGI]);
														DrawFormatStringToHandle(163, 347, White, FontMain, "%3d", StatusMainChar[LUCK]);

														DrawStringToHandle(338, 203, "武器", Blue, FontMain);
														DrawStringToHandle(338, 239, "盾", Blue, FontMain);
														DrawStringToHandle(338, 275, "頭", Blue, FontMain);
														DrawStringToHandle(338, 311, "服", Blue, FontMain);
														DrawStringToHandle(338, 347, "装飾品", Blue, FontMain);

														DrawGraph(476, 200, IconGraph[97], TRUE);
														DrawGraph(476, 236, IconGraph[128], TRUE);
														DrawGraph(476, 272, IconGraph[130], TRUE);
														DrawGraph(476, 308, IconGraph[135], TRUE);

														DrawStringToHandle(511, 203, "剣", White, FontMain);
														DrawStringToHandle(511, 239, "盾", White, FontMain);
														DrawStringToHandle(511, 275, "帽子", White, FontMain);
														DrawStringToHandle(511, 311, "服", White, FontMain);

														ScreenFlip();

														UpdateKey();
														if (Key[KEY_INPUT_ESCAPE] == 1 || Key[KEY_INPUT_X] == 1) {
															PlaySoundMem(SE[CANCEL], DX_PLAYTYPE_BACK);
															break;
														}

														if (ProcessMessage() < 0) break;
													}
												}
											}
											else if (Key[KEY_INPUT_ESCAPE] == 1 || Key[KEY_INPUT_X] == 1) {
												PlaySoundMem(SE[CANCEL], DX_PLAYTYPE_BACK);
												break;
											}

											if (ProcessMessage() < 0) break;
										}
									}
									else if (SelectEquipMenu == 490) { PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK); PlaySoundMem(SE[EQUIP], DX_PLAYTYPE_BACK); }
									else if (SelectEquipMenu == 650) { PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK); PlaySoundMem(SE[EQUIP], DX_PLAYTYPE_BACK); }
								}
								else if (Key[KEY_INPUT_ESCAPE] == 1 || Key[KEY_INPUT_X] == 1) {
									PlaySoundMem(SE[CANCEL], DX_PLAYTYPE_BACK);
									break;
								}

								if (ProcessMessage() < 0) break;
							}
						}
					}
					else if (Key[KEY_INPUT_ESCAPE] == 1 || Key[KEY_INPUT_X] == 1) {
						PlaySoundMem(SE[CANCEL], DX_PLAYTYPE_BACK);
						break;
					}

					if (ProcessMessage() < 0) break;
				}
			}
			else if (SelectMenu[MAINMENU] == 126) {
				PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
				int StatusMenuPal = 255;
				while (1) {
					ClearDrawScreen();
					DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
					DrawGraph(0, 0, MenuGraph[MAINMENU], TRUE);
					DrawModiGraph(18, 126, 222, 126, 222, 126 + 36, 18, 126 + 36, SelectGraph, TRUE);

					SetDrawBlendMode(DX_BLENDMODE_ALPHA, StatusMenuPal);
					DrawModiGraph(258, SelectMenu[STATUSMENU], 798, SelectMenu[STATUSMENU], 798, SelectMenu[STATUSMENU] + 147, 258, SelectMenu[STATUSMENU] + 147, SelectGraph, TRUE);
					if (StatusMenuPal == 255) MenuFlag = 1;
					else if (StatusMenuPal == 129) MenuFlag = 0;

					if (MenuFlag == 1) StatusMenuPal = StatusMenuPal - 6;
					else if (MenuFlag == 0) StatusMenuPal = StatusMenuPal + 6;

					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
					DrawStringToHandle(24, 23, "アイテム", White, FontMain);
					DrawStringToHandle(24, 59, "スキル", White, FontMain);
					DrawStringToHandle(24, 95, "装備", White, FontMain);
					DrawStringToHandle(24, 131, "ステータス", White, FontMain);
					DrawStringToHandle(24, 167, "オプション", White, FontMain);
					if (BattleMap == FALSE) DrawStringToHandle(24, 203, "セーブ", White, FontMain);
					else if (BattleMap == TRUE) DrawStringToHandle(24, 203, "セーブ", Gray, FontMain);
					if (Cheat == FALSE) DrawStringToHandle(24, 239, "チート", Gray, FontMain);
					else if (Cheat == TRUE) DrawStringToHandle(24, 239, "チート", White, FontMain);
					DrawStringToHandle(24, 275, "ゲーム終了", White, FontMain);

					HPBar = (float)StatusMainChar[HP] / StatusMainChar[HPMAX] * 186;
					MPBar = (float)StatusMainChar[MP] / StatusMainChar[MPMAX] * 186;
					HPBarWidth = HPBar;
					MPBarWidth = MPBar;

					DrawGraph(259, 19, FaceGraph[FACEMAIN], TRUE);
					if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(419, 42, White, FontMain, "%s", Name.c_str());
					else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(419, 42, Yellow, FontMain, "%s", Name.c_str());
					else if (HPBarWidth == 0) { DrawFormatStringToHandle(419, 42, Red, FontMain, "%s", Name.c_str()); DrawGraph(420, 112, IconGraph[1], TRUE); }
					DrawStringToHandle(419, 78, "Lv", Blue, FontMain);
					DrawFormatStringToHandle(508, 78, White, FontMain, "%3d", StatusMainChar[LV]);
					DrawStringToHandle(599, 42, "勇者", White, FontMain);
					DrawGraph(600, 101, BarBaseGraph, TRUE);
					DrawGraph(600, 137, BarBaseGraph, TRUE);
					DrawRectGraph(600, 101, 0, 0, HPBarWidth, 7, HPBarGraph, TRUE, FALSE);
					DrawRectGraph(600, 137, 0, 0, MPBarWidth, 7, MPBarGraph, TRUE, FALSE);
					DrawStringToHandle(599, 78, "HP", Blue, FontMain);
					DrawStringToHandle(599, 114, "MP", Blue, FontMain);
					if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(652, 78, White, FontMain, "%4d", StatusMainChar[HP]);
					else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(652, 78, Yellow, FontMain, "%4d", StatusMainChar[HP]);
					else if (HPBarWidth == 0) DrawFormatStringToHandle(652, 78, Red, FontMain, "%4d", StatusMainChar[HP]);
					if (MPBarWidth <= 186 && MPBarWidth > 56) DrawFormatStringToHandle(652, 114, White, FontMain, "%4d", StatusMainChar[MP]);
					else if (MPBarWidth <= 56 && MPBarWidth > 0) DrawFormatStringToHandle(652, 114, Yellow, FontMain, "%4d", StatusMainChar[MP]);
					else if (MPBarWidth == 0) DrawFormatStringToHandle(652, 114, Red, FontMain, "%4d", StatusMainChar[MP]);
					DrawFormatStringToHandle(652, 78, White, FontMain, "    /%4d", StatusMainChar[HPMAX]);
					DrawFormatStringToHandle(652, 114, White, FontMain, "    /%4d", StatusMainChar[MPMAX]);

					if (Money >= 0) DrawFormatStringToHandle(30, 574, White, FontMain, "%10ld", Money);
					else if (Money < 0) DrawFormatStringToHandle(30, 574, Red, FontMain, "%10ld", Money);
					DrawStringToHandle(190, 574, "G", Blue, FontMain);

					ScreenFlip();

					UpdateKey();
					if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) {
							PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
							while (1) {
								ClearDrawScreen();
								DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
								DrawGraph(0, 0, MenuGraph[STATUSMENU], TRUE);

								if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(23, 23, White, FontMain, "%s", Name.c_str());
								else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(23, 23, Yellow, FontMain, "%s", Name.c_str());
								else if (HPBarWidth == 0) { DrawFormatStringToHandle(23, 23, Red, FontMain, "%s", Name.c_str()); DrawGraph(497, 211, IconGraph[1], TRUE); }								
								DrawStringToHandle(209, 23, "勇者", White, FontMain);

								DrawGraph(30, 90, FaceGraph[FACEMAIN], TRUE);
								DrawStringToHandle(222, 95, "Lv", Blue, FontMain);
								DrawFormatStringToHandle(311, 95, White, FontMain, "%3d", StatusMainChar[LV]);
								DrawGraph(223, 189, BarBaseGraph, TRUE);
								DrawGraph(223, 225, BarBaseGraph, TRUE);
								DrawRectGraph(223, 189, 0, 0, HPBarWidth, 7, HPBarGraph, TRUE, FALSE);
								DrawRectGraph(223, 225, 0, 0, MPBarWidth, 7, MPBarGraph, TRUE, FALSE);
								DrawStringToHandle(222, 166, "HP", Blue, FontMain);
								DrawStringToHandle(222, 202, "MP", Blue, FontMain);
								if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(275, 166, White, FontMain, "%4d", StatusMainChar[HP]);
								else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(275, 166, Yellow, FontMain, "%4d", StatusMainChar[HP]);
								else if (HPBarWidth == 0) DrawFormatStringToHandle(275, 166, Red, FontMain, "%4d", StatusMainChar[HP]);
								if (MPBarWidth <= 186 && MPBarWidth > 56) DrawFormatStringToHandle(275, 202, White, FontMain, "%4d", StatusMainChar[MP]);
								else if (MPBarWidth <= 56 && MPBarWidth > 0) DrawFormatStringToHandle(275, 202, Yellow, FontMain, "%4d", StatusMainChar[MP]);
								else if (MPBarWidth == 0) DrawFormatStringToHandle(275, 202, Red, FontMain, "%4d", StatusMainChar[MP]);
								DrawFormatStringToHandle(275, 166, White, FontMain, "    /%4d", StatusMainChar[HPMAX]);
								DrawFormatStringToHandle(275, 202, White, FontMain, "    /%4d", StatusMainChar[MPMAX]);
								DrawStringToHandle(472, 95, "現在の経験値", Blue, FontMain);
								DrawFormatStringToHandle(662, 135, White, FontMain, "%6d", StatusMainChar[EXP]);
								DrawStringToHandle(472, 166, "次のレベルまで", Blue, FontMain);
								DrawFormatStringToHandle(662, 202, White, FontMain, "%6d", StatusMainChar[NEXTLV]);

								DrawStringToHandle(66, 275, "攻撃力", Blue, FontMain);
								DrawStringToHandle(66, 311, "防御力", Blue, FontMain);
								DrawStringToHandle(66, 347, "魔法攻撃", Blue, FontMain);
								DrawStringToHandle(66, 383, "魔法防御", Blue, FontMain);
								DrawStringToHandle(66, 419, "敏捷性", Blue, FontMain);
								DrawStringToHandle(66, 455, "運", Blue, FontMain);
								DrawFormatStringToHandle(243, 275, White, FontMain, "%3d", StatusMainChar[ATK]);
								DrawFormatStringToHandle(243, 311, White, FontMain, "%3d", StatusMainChar[DEF]);
								DrawFormatStringToHandle(243, 347, White, FontMain, "%3d", StatusMainChar[MATK]);
								DrawFormatStringToHandle(243, 383, White, FontMain, "%3d", StatusMainChar[MDEF]);
								DrawFormatStringToHandle(243, 419, White, FontMain, "%3d", StatusMainChar[AGI]);
								DrawFormatStringToHandle(243, 455, White, FontMain, "%3d", StatusMainChar[LUCK]);

								DrawGraph(452, 272, IconGraph[97], TRUE);
								DrawGraph(452, 308, IconGraph[128], TRUE);
								DrawGraph(452, 344, IconGraph[130], TRUE);
								DrawGraph(452, 380, IconGraph[135], TRUE);

								DrawStringToHandle(487, 275, "剣", White, FontMain);
								DrawStringToHandle(487, 311, "盾", White, FontMain);
								DrawStringToHandle(487, 347, "帽子", White, FontMain);
								DrawStringToHandle(487, 383, "服", White, FontMain);

								ScreenFlip();

								UpdateKey();
								if (Key[KEY_INPUT_ESCAPE] == 1 || Key[KEY_INPUT_X] == 1) {
									PlaySoundMem(SE[CANCEL], DX_PLAYTYPE_BACK);
									break;
								}

								if (ProcessMessage() < 0) break;
							}
					}
					if (Key[KEY_INPUT_ESCAPE] == 1 || Key[KEY_INPUT_X] == 1) {
						PlaySoundMem(SE[CANCEL], DX_PLAYTYPE_BACK);
						break;
					}

					if (ProcessMessage() < 0) break;
				}
			}
			else if (SelectMenu[MAINMENU] == 162) {
				PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
				Option();
			}
			else if (SelectMenu[MAINMENU] == 198) {
				if (BattleMap == FALSE) {
					PlaySoundMem(SE[SAVE], DX_PLAYTYPE_BACK);
					Save();
				}
				else if (BattleMap == TRUE) PlaySoundMem(SE[BUZZER], DX_PLAYTYPE_BACK);
			}
			else if (SelectMenu[MAINMENU] == 234) {
				if (Cheat == FALSE) PlaySoundMem(SE[BUZZER], DX_PLAYTYPE_BACK);
				else if (Cheat == TRUE) {
					PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
					ClearDrawScreen();
					MsgBoxY = 0;
					do {
						ClearDrawScreen();
						DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
						DrawModiGraph(0, 532 - MsgBoxY, 816, 532 - MsgBoxY, 816, 536 + MsgBoxY, 0, 536 + MsgBoxY, MsgGraph, TRUE);
						ScreenFlip();
						MsgBoxY = MsgBoxY + 8;
					} while (MsgBoxY <= 88);
					ClearDrawScreen();
					DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
					DrawGraph(0, 444, MsgGraph, TRUE);
					ScreenFlip();
					int i = 0;
					do {
						DrawFormatStringToHandle(20 + (i * 14), 465, White, FontMain, "%c%c", SYMsg2[i], SYMsg2[i + 1]);
						ScreenFlip();
						WaitTimer(15);
						i = i + 2;
						if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) break;
					} while (i + 1 <= 28);
					int j = 0;
					while (1) {
						ClearDrawScreen();
						DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
						DrawGraph(0, 444, MsgGraph, TRUE);
						DrawFormatStringToHandle(20, 465, White, FontMain, "%s", SYMsg[1].c_str());
						if (j <= 15) DrawGraph(396, 600, CursorGraph[0], TRUE);
						else if (j > 15 && j <= 30) DrawGraph(396, 600, CursorGraph[1], TRUE);
						else if (j > 30 && j <= 45) DrawGraph(396, 600, CursorGraph[2], TRUE);
						else if (j > 45) { DrawGraph(396, 600, CursorGraph[3], TRUE); j = 0; }
						ScreenFlip();
						j++;
						UpdateKey();
						if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) break;
					}
					MsgBoxY = 88;
					do {
						ClearDrawScreen();
						DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
						DrawModiGraph(0, 532 - MsgBoxY, 816, 532 - MsgBoxY, 816, 536 + MsgBoxY, 0, 536 + MsgBoxY, MsgGraph, TRUE);
						ScreenFlip();
						MsgBoxY = MsgBoxY - 8;
					} while (MsgBoxY >= 0);
					MsgBoxY = 0;
					break;
				}
			}
			else if (SelectMenu[MAINMENU] == 270) {
				PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
				ClearDrawScreen();
				MsgBoxY = 0;
				do {
					ClearDrawScreen();
					DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
					DrawModiGraph(0, 532 - MsgBoxY, 816, 532 - MsgBoxY, 816, 536 + MsgBoxY, 0, 536 + MsgBoxY, MsgGraph, TRUE);
					ScreenFlip();
					MsgBoxY = MsgBoxY + 8;
				} while (MsgBoxY <= 88);
				ClearDrawScreen();
				DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
				DrawGraph(0, 444, MsgGraph, TRUE);
				ScreenFlip();
				int i = 0;
				do {
					DrawFormatStringToHandle(20 + (i * 14), 465, White, FontMain, "%c%c", SYMsg1[i], SYMsg1[i + 1]);
					ScreenFlip();
					WaitTimer(15);
					i = i + 2;
					if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) break;
				} while (i + 1 <= 28);
				int YesNoBoxY = 0;
				do {
					ClearDrawScreen();
					DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
					DrawGraph(0, 444, MsgGraph, TRUE);
					DrawFormatStringToHandle(20, 465, White, FontMain, "%s", SYMsg[0].c_str());
					DrawModiGraph(684, 382 - YesNoBoxY, 816, 382 - YesNoBoxY, 816, 392 + YesNoBoxY, 684, 392 + YesNoBoxY, YesNoGraph, TRUE);
					ScreenFlip();
					YesNoBoxY = YesNoBoxY + 4;
				} while (YesNoBoxY <= 52);
				int Pal = 255, SelectY = 390, Flag = TRUE;
				while (1) {
					ClearDrawScreen();
					DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
					DrawGraph(0, 444, MsgGraph, TRUE);
					DrawFormatStringToHandle(20, 465, White, FontMain, "%s", SYMsg[0].c_str());
					DrawGraph(684, 336, YesNoGraph, TRUE);

					SetDrawBlendMode(DX_BLENDMODE_ALPHA, Pal);
					DrawModiGraph(702, SelectY, 797, SelectY, 797, SelectY + 36, 702, SelectY + 36, SelectGraph, TRUE);
					if (Pal == 255) Flag = 1;
					else if (Pal == 129) Flag = 0;

					if (Flag == 1) Pal = Pal - 6;
					else if (Flag == 0) Pal = Pal + 6;

					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
					DrawStringToHandle(707, 358, "はい", White, FontMain);
					DrawStringToHandle(707, 395, "いいえ", White, FontMain);
					ScreenFlip();

					UpdateKey();
					if (Key[KEY_INPUT_UP] == 1 && SelectY == 390) { PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); SelectY = 354; }
					else if (Key[KEY_INPUT_DOWN] == 1 && SelectY == 354) { PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); SelectY = 390; }
					else if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) {
						if (SelectY == 354) {
							PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
							GameEnd = 1;
							break;
						}
						else if (SelectY == 390) {
							PlaySoundMem(SE[CANCEL], DX_PLAYTYPE_BACK);
							do {
								ClearDrawScreen();
								DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
								if (YesNoBoxY >= 0) DrawModiGraph(0, 532 - MsgBoxY, 816, 532 - MsgBoxY, 816, 536 + MsgBoxY, 0, 536 + MsgBoxY, MsgGraph, TRUE);
								if (MsgBoxY >= 0)DrawModiGraph(684, 382 - YesNoBoxY, 816, 382 - YesNoBoxY, 816, 392 + YesNoBoxY, 684, 392 + YesNoBoxY, YesNoGraph, TRUE);
								ScreenFlip();
								YesNoBoxY = YesNoBoxY - 4;
								MsgBoxY = MsgBoxY - 8;
							} while (YesNoBoxY >= 0 || MsgBoxY >= 0);
							break;
						}
					}
					else if (Key[KEY_INPUT_ESCAPE] == 1 || Key[KEY_INPUT_X] == 1) {
						PlaySoundMem(SE[CANCEL], DX_PLAYTYPE_BACK);
						do {
							ClearDrawScreen();
							DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
							if (YesNoBoxY >= 0) DrawModiGraph(0, 532 - MsgBoxY, 816, 532 - MsgBoxY, 816, 536 + MsgBoxY, 0, 536 + MsgBoxY, MsgGraph, TRUE);
							if (MsgBoxY >= 0)DrawModiGraph(684, 382 - YesNoBoxY, 816, 382 - YesNoBoxY, 816, 392 + YesNoBoxY, 684, 392 + YesNoBoxY, YesNoGraph, TRUE);
							ScreenFlip();
							YesNoBoxY = YesNoBoxY - 4;
							MsgBoxY = MsgBoxY - 8;
						} while (YesNoBoxY >= 0 || MsgBoxY >= 0);
						break;
					}
				}
				if (GameEnd == 1) break;
			}
		}
		else if (Key[KEY_INPUT_ESCAPE] == 1 || Key[KEY_INPUT_X] == 1) {
			PlaySoundMem(SE[CANCEL], DX_PLAYTYPE_BACK);
			break;
		}

		if (ProcessMessage() < 0) break;
	}
}

//タイトル
void Title(void) {
	NowTitle = TRUE;
	int TitleGraph, TitleLogGraph, Bright = 0, Pal = 255, Flag = 0, Select = 0, SelectY = 400, SelectHeight = 38;
	int LogBoxY = 0;
	PlaySoundMem(BGM[TITLE], DX_PLAYTYPE_LOOP);
	TitleGraph = LoadGraph("resource/Title/title.png");
	TitleLogGraph = LoadGraph("resource/System/window/title.png");
	do {
		SetDrawBright(Bright, Bright, Bright);
		DrawGraph(0, 0, TitleGraph, FALSE);
		ScreenFlip();
		Bright = Bright + 5;
	} while (Bright < 256);
	WaitTimer(500);
	do {
		ClearDrawScreen();
		DrawGraph(0, 0, TitleGraph, FALSE);
		DrawModiGraph(288, 453 - LogBoxY, 527, 453 - LogBoxY, 527, 455 + LogBoxY, 288, 455 + LogBoxY, TitleLogGraph, TRUE);
		ScreenFlip();
		LogBoxY = LogBoxY + 7;
	} while (LogBoxY <= 70);
	int saveExist;
	if (PathFileExistsA("save.dat") == TRUE) { saveExist = TRUE, SelectY = 434; }
	else if (PathFileExistsA("save.dat") == FALSE) saveExist = FALSE;
	while (1) {
		ClearDrawScreen();
		DrawGraph(0, 0, TitleGraph, FALSE);
		DrawGraph(288, 383, TitleLogGraph, TRUE);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, Pal);
		DrawModiGraph(305, SelectY, 510, SelectY, 510, SelectY + 38, 305, SelectY + 38, SelectGraph, TRUE);
		if (Pal == 255) Flag = 1;
		else if (Pal == 129) Flag = 0;

		if (Flag == 1) Pal = Pal - 6;
		else if (Flag == 0) Pal = Pal + 6;

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		DrawStringToHandle(310, 405, "ニューゲーム", White, FontMain);
		if (saveExist == FALSE)	DrawStringToHandle(310, 440, "コンティニュー", Gray, FontMain);
		else if (saveExist == TRUE)	DrawStringToHandle(310, 440, "コンティニュー", White, FontMain);
		DrawStringToHandle(310, 475, "オプション", White, FontMain);
		ScreenFlip();

		UpdateKey();
		if (Key[KEY_INPUT_DOWN] == 1) {
			if (SelectY == 469) { SelectY = 400; PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK); }
			else if (SelectY == 434) { SelectY = 469; PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK); }
			else if (SelectY == 400) { SelectY = 434; PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK); }
		}
		else if (Key[KEY_INPUT_UP] == 1) {
		if (SelectY == 400) { SelectY = 469; PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK); }
		else if (SelectY == 434) { SelectY = 400; PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK); }
		else if (SelectY == 469) { SelectY = 434; PlaySoundMem(SE[TITLESELECT], DX_PLAYTYPE_BACK); }
		}
		else if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) {
			if (SelectY == 400) {
				FirstPlay = TRUE;
				PlaySoundMem(SE[TITLEDECISION], DX_PLAYTYPE_BACK);
				MapNumber = STARTMAP;
				BattleMap = FALSE;
				Walk = 0;
				MapX = 2; MapY = 2;
				CharMainX = 9; CharMainY = 7; Direction = 1;
				CharMainRightX = CharMainX * 48 - 48;
				CharMainRightY = CharMainY * 48 - 48;
				MapRightX = MapX * -48 + 48;
				MapRightY = MapY * -48 + 48;
				StatusSet();
				Opening();
				int BGMVol;
				BGMVol = BGMVolume;
				do {
					ChangeVolumeSoundMem(BGMVol, BGM[TITLE]);
					BGMVol = BGMVol - 2;
				} while (BGMVol >= 0);
				StopSoundMem(BGM[TITLE]);
				ChangeVolumeSoundMem(BGMVolume, BGM[TITLE]);
				DeleteGraph(TitleGraph);
				DeleteGraph(TitleLogGraph);
				SetDrawBright(255, 255, 255);
				WaitTimer(1000);
				NowTitle = FALSE;
				break;
			}
			else if (SelectY == 434) {
				if (saveExist == FALSE)	PlaySoundMem(SE[TITLEBUZZER], DX_PLAYTYPE_BACK);
				else if (saveExist == TRUE) { PlaySoundMem(SE[LOAD], DX_PLAYTYPE_BACK); Load(); break; }
			}
			else if (SelectY == 469) {
				PlaySoundMem(SE[TITLEDECISION], DX_PLAYTYPE_BACK);
				do {
					ClearDrawScreen();
					DrawGraph(0, 0, TitleGraph, FALSE);
					if (LogBoxY > 0) DrawModiGraph(288, 453 - LogBoxY, 527, 453 - LogBoxY, 527, 455 + LogBoxY, 288, 455 + LogBoxY, TitleLogGraph, TRUE);
					ScreenFlip();
					LogBoxY = LogBoxY - 7;
				} while (LogBoxY > 0);
				ClearDrawScreen();
				DrawGraph(0, 0, TitleGraph, FALSE);

				int Gauss = 0;
				GetDrawScreenGraph(0, 0, 48 * 17, 48 * 13, MenuScreen);
				do {
					ClearDrawScreen();
					GraphFilterBlt(MenuScreen, MenuScreenGAUSS, DX_GRAPH_FILTER_GAUSS, 8, Gauss);
					DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
					ScreenFlip();
					Gauss = Gauss + 10;
				} while (Gauss <= 100);
				WaitTimer(500);
				Option();
				do {
						ClearDrawScreen();
						DrawGraph(0, 0, TitleGraph, FALSE);
						DrawModiGraph(288, 453 - LogBoxY, 527, 453 - LogBoxY, 527, 455 + LogBoxY, 288, 455 + LogBoxY, TitleLogGraph, TRUE);
						ScreenFlip();
						LogBoxY = LogBoxY + 7;
					} while (LogBoxY <= 70);
			}
		}
		if (ProcessMessage() < 0) break;
	}
	if (FirstPlay == FALSE) {
		int BGMVol;
		BGMVol = BGMVolume;
		LogBoxY = 70;
		do {
			ClearDrawScreen();
			SetDrawBright(Bright, Bright, Bright);
			DrawGraph(0, 0, TitleGraph, FALSE);
			if (LogBoxY > 0) DrawModiGraph(288, 453 - LogBoxY, 527, 453 - LogBoxY, 527, 455 + LogBoxY, 288, 455 + LogBoxY, TitleLogGraph, TRUE);
			ScreenFlip();
			ChangeVolumeSoundMem(BGMVol, BGM[TITLE]);
			BGMVol = BGMVol - 2;
			Bright = Bright - 5;
			LogBoxY = LogBoxY - 7;
		} while (BGMVol >= 0 || Bright > 0);
		StopSoundMem(BGM[TITLE]);
		ChangeVolumeSoundMem(BGMVolume, BGM[TITLE]);
		DeleteGraph(TitleGraph);
		DeleteGraph(TitleLogGraph);
		SetDrawBright(255, 255, 255);
		WaitTimer(1000);
		NowTitle = FALSE;
	}
}

//キャラ描画関数
void CharMain(int i) {
	DrawGraph(CharMainRightX, CharMainRightY - 6, CharDiv[i], TRUE);
}

//関数Move用変数
int U = 0, D = 0, L = 0, R = 0;
int U1 = 0, U2 = 0, D1 = 0, D2 = 0, L1 = 0, L2 = 0, R1 = 0, R2 = 0;

//マップ移動補助関数
void MoveSupportUP(int i)
	{
		MapRightY = MapRightY + 3;
		if (MapRightY > 0) {
			MapRightY = 0;
			CharMainRightY = CharMainRightY - 3;
		}
		else if (CharMainRightY > 288) {
			MapRightY = MapRightY - 3;
			CharMainRightY = CharMainRightY - 3;
		}
		ClearDrawScreen();
		MAPDraw(MapNumber, MapRoop);
		CharMain(i);
		MAPOverlayDraw(MapNumber);
		ScreenFlip();
		WaitTimer(15);
		RoopCount = RoopCount + 20;
		if (RoopCount > 500) { RoopCount = 0; MapRoop++; }
		if (MapRoop == 5) MapRoop = 1;
	}
void MoveSupportDOWN(int i)
	{
		MapRightY = MapRightY - 3;
		if (MapRightY < (MapHeight[MapNumber] * -1) + (48 * 13)) {
			MapRightY = (MapHeight[MapNumber] * -1) + (48 * 13);
			CharMainRightY = CharMainRightY + 3;
		}
		else if (CharMainRightY < 288) {
			MapRightY = MapRightY + 3;
			CharMainRightY = CharMainRightY + 3;
		}
		ClearDrawScreen();
		MAPDraw(MapNumber, MapRoop);
		CharMain(i);
		MAPOverlayDraw(MapNumber);
		ScreenFlip();
		WaitTimer(15);
		RoopCount = RoopCount + 20;
		if (RoopCount > 500) { RoopCount = 0; MapRoop++; }
		if (MapRoop == 5) MapRoop = 1;
	}
void MoveSupportLEFT(int i)
	{
		MapRightX = MapRightX + 3;
		if (MapRightX > 0) {
			MapRightX = 0;
			CharMainRightX = CharMainRightX - 3;
		}
		else if (CharMainRightX > 384) {
			MapRightX = MapRightX - 3;
			CharMainRightX = CharMainRightX - 3;
		}
		ClearDrawScreen();
		MAPDraw(MapNumber, MapRoop);
		CharMain(i);
		MAPOverlayDraw(MapNumber);
		ScreenFlip();
		WaitTimer(15);
		RoopCount = RoopCount + 20;
		if (RoopCount > 500) { RoopCount = 0; MapRoop++; }
		if (MapRoop == 5) MapRoop = 1;
	}
void MoveSupportRIGHT(int i)
	{
		MapRightX = MapRightX - 3;
		if (MapRightX < (MapWidth[MapNumber] * -1) + (48 * 17)) {
			MapRightX = (MapWidth[MapNumber] * -1) + (48 * 17);
			CharMainRightX = CharMainRightX + 3;
		}
		else if (CharMainRightX < 384) {
			MapRightX = MapRightX + 3;
			CharMainRightX = CharMainRightX + 3;
		}
		ClearDrawScreen();
		MAPDraw(MapNumber, MapRoop);
		CharMain(i);
		MAPOverlayDraw(MapNumber);
		ScreenFlip();
		WaitTimer(15);
		RoopCount = RoopCount + 20;
		if (RoopCount > 500) { RoopCount = 0; MapRoop++; }
		if (MapRoop == 5) MapRoop = 1;
	}

void MoveSupportDashUP(int i)
	{
		MapRightY = MapRightY + 6;
		if (MapRightY > 0) {
			MapRightY = 0;
			CharMainRightY = CharMainRightY - 6;
		}
		else if (CharMainRightY > 288) {
			MapRightY = MapRightY - 6;
			CharMainRightY = CharMainRightY - 6;
		}
		ClearDrawScreen();
		MAPDraw(MapNumber, MapRoop);
		CharMain(i);
		MAPOverlayDraw(MapNumber);
		ScreenFlip();
		WaitTimer(5);
		RoopCount = RoopCount + 20;
		if (RoopCount > 500) { RoopCount = 0; MapRoop++; }
		if (MapRoop == 5) MapRoop = 1;
	}
void MoveSupportDashDOWN(int i)
	{
		MapRightY = MapRightY - 6;
		if (MapRightY < (MapHeight[MapNumber] * -1) + (48 * 13)) {
			MapRightY = (MapHeight[MapNumber] * -1) + (48 * 13);
			CharMainRightY = CharMainRightY + 6;
		}
		else if (CharMainRightY < 288) {
			MapRightY = MapRightY + 6;
			CharMainRightY = CharMainRightY + 6;
		}
		ClearDrawScreen();
		MAPDraw(MapNumber, MapRoop);
		CharMain(i);
		MAPOverlayDraw(MapNumber);
		ScreenFlip();
		WaitTimer(5);
		RoopCount = RoopCount + 20;
		if (RoopCount > 500) { RoopCount = 0; MapRoop++; }
		if (MapRoop == 5) MapRoop = 1;
	}
void MoveSupportDashLEFT(int i)
	{
		MapRightX = MapRightX + 6;
		if (MapRightX > 0) {
			MapRightX = 0;
			CharMainRightX = CharMainRightX - 6;
		}
		else if (CharMainRightX > 384) {
			MapRightX = MapRightX - 6;
			CharMainRightX = CharMainRightX - 6;
		}
		ClearDrawScreen();
		MAPDraw(MapNumber, MapRoop);
		CharMain(i);
		MAPOverlayDraw(MapNumber);
		ScreenFlip();
		WaitTimer(5);
		RoopCount = RoopCount + 20;
		if (RoopCount > 500) { RoopCount = 0; MapRoop++; }
		if (MapRoop == 5) MapRoop = 1;
	}
void MoveSupportDashRIGHT(int i)
	{
		MapRightX = MapRightX - 6;
		if (MapRightX < (MapWidth[MapNumber] * -1) + (48 * 17)) {
			MapRightX = (MapWidth[MapNumber] * -1) + (48 * 17);
			CharMainRightX = CharMainRightX + 6;
		}
		else if (CharMainRightX < 384) {
			MapRightX = MapRightX + 6;
			CharMainRightX = CharMainRightX + 6;
		}
		ClearDrawScreen();
		MAPDraw(MapNumber, MapRoop);
		CharMain(i);
		MAPOverlayDraw(MapNumber);
		ScreenFlip();
		WaitTimer(5);
		RoopCount = RoopCount + 20;
		if (RoopCount > 500) { RoopCount = 0; MapRoop++; }
		if (MapRoop == 5) MapRoop = 1;
	}

//マップ移動関数
void Move(void) {
	if (CheckHitKey(KEY_INPUT_UP) == 1)
		{
			if (attackup(MapAttack[MapNumber], 24, -24) != 1 || Cheat == TRUE)
			{
				if (CheckHitKey(KEY_INPUT_LCONTROL) == 0 && Dash == FALSE)
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
						U1 = 1;
					}
					else if (U == 1)
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
						U2 = 1;
					}

					if (U1 == 1) { U = 1; U1 = 0; }
					else if (U2 == 1) { U = 0; U2 = 0; }
				}
				else if (CheckHitKey(KEY_INPUT_LCONTROL) == 1 || Dash == TRUE)
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
						U1 = 1;
					}
					else if (U == 1)
					{
						MoveSupportDashUP(10);
						MoveSupportDashUP(10);
						MoveSupportDashUP(10);
						MoveSupportDashUP(10);
						MoveSupportDashUP(11);
						MoveSupportDashUP(11);
						MoveSupportDashUP(10);
						MoveSupportDashUP(10);
						U2 = 1;
					}

					if (U1 == 1) { U = 1; U1 = 0; }
					else if (U2 == 1) { U = 0; U2 = 0; }
				}

				if (BattleMap == TRUE) Walk++;
			}
			else if (attackup(MapAttack[MapNumber], 24, -24) == 1 && Cheat == FALSE)
			{
				MAPDraw(MapNumber, MapRoop);
				CharMain(10);
				MAPOverlayDraw(MapNumber);
				ScreenFlip();
				WaitTimer(1);
				RoopCount = RoopCount + 20;
				if (RoopCount > 500) { RoopCount = 0; MapRoop++; }
				if (MapRoop == 5) MapRoop = 1;
			}
			Direction = FACEUP;
		}
	else if (CheckHitKey(KEY_INPUT_DOWN) == 1)
		{
			if (attackdown(MapAttack[MapNumber], 24, 48 + 24) != 1 || Cheat == TRUE)
			{
				if (CheckHitKey(KEY_INPUT_LCONTROL) == 0 && Dash == FALSE)
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
						D1 = 1;
					}
					else if (D == 1)
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
						D2 = 1;
					}

					if (D1 == 1) { D = 1; D1 = 0; }
					else if (D2 == 1) { D = 0; D2 = 0; }
				}
				else if (CheckHitKey(KEY_INPUT_LCONTROL) == 1 || Dash == TRUE)
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
						D1 = 1;
					}
					else if (D == 1)
					{
						MoveSupportDashDOWN(1);
						MoveSupportDashDOWN(1);
						MoveSupportDashDOWN(1);
						MoveSupportDashDOWN(1);
						MoveSupportDashDOWN(2);
						MoveSupportDashDOWN(2);
						MoveSupportDashDOWN(1);
						MoveSupportDashDOWN(1);
						D2 = 1;
					}

					if (D1 == 1) { D = 1; D1 = 0; }
					else if (D2 == 1) { D = 0; D2 = 0; }
				}

				if (BattleMap == TRUE) Walk++;
			}
			else if (attackdown(MapAttack[MapNumber], 24, 48 + 24) == 1 && Cheat == FALSE)
			{
				MAPDraw(MapNumber, MapRoop);
				CharMain(1);
				MAPOverlayDraw(MapNumber);
				ScreenFlip();
				WaitTimer(1);
				RoopCount = RoopCount + 20;
				if (RoopCount > 500) { RoopCount = 0; MapRoop++; }
				if (MapRoop == 5) MapRoop = 1;
			}
			Direction = FACEDOWN;
		}
	else if (CheckHitKey(KEY_INPUT_LEFT) == 1)
		{
			if (attackleft(MapAttack[MapNumber], -24, 24) != 1 || Cheat == TRUE)
			{
				if (CheckHitKey(KEY_INPUT_LCONTROL) == 0 && Dash == FALSE)
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
						L1 = 1;
					}
					else if (L == 1)
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
						L2 = 1;
					}

					if (L1 == 1) { L = 1; L1 = 0; }
					else if (L2 == 1) { L = 0; L2 = 0; }
				}
				else if (CheckHitKey(KEY_INPUT_LCONTROL) == 1 || Dash == TRUE)
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
						L1 = 1;
					}
					else if (L == 1)
					{
						MoveSupportDashLEFT(4);
						MoveSupportDashLEFT(4);
						MoveSupportDashLEFT(4);
						MoveSupportDashLEFT(4);
						MoveSupportDashLEFT(5);
						MoveSupportDashLEFT(5);
						MoveSupportDashLEFT(4);
						MoveSupportDashLEFT(4);
						L2 = 1;
					}

					if (L1 == 1) { L = 1; L1 = 0; }
					else if (L2 == 1) { L = 0; L2 = 0; }
				}

				if (BattleMap == TRUE) Walk++;
			}
			else if (attackleft(MapAttack[MapNumber], -24, 24) == 1 && Cheat == FALSE)
			{
				MAPDraw(MapNumber, MapRoop);
				CharMain(4);
				MAPOverlayDraw(MapNumber);
				ScreenFlip();
				WaitTimer(1);
				RoopCount = RoopCount + 20;
				if (RoopCount > 500) { RoopCount = 0; MapRoop++; }
				if (MapRoop == 5) MapRoop = 1;
			}
			Direction = FACELEFT;
		}
	else if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
		{
			if (attackright(MapAttack[MapNumber], 48 + 24, 24) != 1 || Cheat == TRUE)
			{
				if (CheckHitKey(KEY_INPUT_LCONTROL) == 0 && Dash == FALSE)
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
						R1 = 1;
					}
					else if (R == 1)
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
						R2 = 1;
					}

					if (R1 == 1) { R = 1; R1 = 0; }
					else if (R2 == 1) { R = 0; R2 = 0; }
				}
				else if (CheckHitKey(KEY_INPUT_LCONTROL) == 1 || Dash == TRUE)
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
						R1 = 1;
					}
					else if (R == 1)
					{
						MoveSupportDashRIGHT(7);
						MoveSupportDashRIGHT(7);
						MoveSupportDashRIGHT(7);
						MoveSupportDashRIGHT(7);
						MoveSupportDashRIGHT(8);
						MoveSupportDashRIGHT(8);
						MoveSupportDashRIGHT(7);
						MoveSupportDashRIGHT(7);
						R2 = 1;
					}

					if (R1 == 1) { R = 1; R1 = 0; }
					else if (R2 == 1) { R = 0; R2 = 0; }
				}

				if (BattleMap == TRUE) Walk++;
			}
			else if (attackright(MapAttack[MapNumber], 48 + 24, 24) == 1 && Cheat == FALSE)
			{
				MAPDraw(MapNumber, MapRoop);
				CharMain(7);
				MAPOverlayDraw(MapNumber);
				ScreenFlip();
				WaitTimer(1);
				RoopCount = RoopCount + 20;
				if (RoopCount > 500) { RoopCount = 0; MapRoop++; }
				if (MapRoop == 5) MapRoop = 1;
			}
			Direction = FACERIGHT;
		}
	else if (CheckHitKey(KEY_INPUT_UP) == 0 && CheckHitKey(KEY_INPUT_DOWN) == 0 && CheckHitKey(KEY_INPUT_LEFT) == 0 && CheckHitKey(KEY_INPUT_RIGHT) == 0) {
		MAPDraw(MapNumber, MapRoop);
		if (Direction == FACEUP) CharMain(10);
		else if (Direction == FACEDOWN) CharMain(1);
		else if (Direction == FACELEFT) CharMain(4);
		else if (Direction == FACERIGHT) CharMain(7);
		MAPOverlayDraw(MapNumber);
		ScreenFlip();
		RoopCount = RoopCount + 20;
		if (RoopCount > 500) { RoopCount = 0; MapRoop++; }
		if (MapRoop == 5) MapRoop = 1;
	}
	MapX = (MapRightX - 48) / -48;
	MapY = (MapRightY - 48) / -48;
	CharMainX = (CharMainRightX + 48) / 48;
	CharMainY = (CharMainRightY + 48) / 48;
	}

//マップ移動処理
void MAPMove(void) {
	if (MapNumber == FIELDMAP) {
		if (MapX == 41 && MapY == 14 || MapX == 42 && MapY == 14 || MapX == 42 && MapY == 13 || MapX == 41 && MapY == 13) {
			if (CharMainX == 9 && CharMainY == 7) {
				MapNumber = TOWN1MAP; MapX = 7; MapY = 28; CharMainX = 9; CharMainY = 12, Direction = FACEUP; BattleMap = FALSE; Encount = 0;
				MapRightX = MapX * -48 + 48;
				MapRightY = MapY * -48 + 48;
				CharMainRightX = CharMainX * 48 - 48;
				CharMainRightY = CharMainY * 48 - 48;

				PlaySoundMem(SE[MOVE], DX_PLAYTYPE_BACK);
				GetDrawScreenGraph(0, 0, 48 * 17, 48 * 13, MoveScreen);
				int Bright = 255;
				float Vol = 1.00;
				do {
					SetDrawBright(Bright, Bright, Bright);
					DrawGraph(0, 0, MoveScreen, FALSE);
					ScreenFlip();
					ChangeVolumeSoundMem((float)BGMVolume * Vol, BGM[FIELD]);
					if (Vol != 0.00) Vol = Vol - 0.04;
					Bright = Bright - 10;
				} while (Bright >= 0);
				StopSoundMem(BGM[FIELD]);
				ChangeVolumeSoundMem(BGMVolume, BGM[FIELD]);
				do {
					SetDrawBright(Bright, Bright, Bright);
					MAPDraw(MapNumber, MapRoop);
					CharMain(10);
					ScreenFlip();
					Bright = Bright + 10;
				} while (Bright <= 255);
				SetDrawBright(255, 255, 255);
				PlaySoundMem(BGM[TOWN], DX_PLAYTYPE_LOOP);
			}
		}
	}
	else if (MapNumber == STARTMAP) {
			if (MapX == 2 && MapY == 3) {
				if (CharMainX == 9 && CharMainY == 13) {
					MapNumber = TOWN1MAP; MapX = 1; MapY = 5; CharMainX = 6; CharMainY = 7; Direction = FACEDOWN;
					MapRightX = MapX * -48 + 48;
					MapRightY = MapY * -48 + 48;
					CharMainRightX = CharMainX * 48 - 48;
					CharMainRightY = CharMainY * 48 - 48;

					PlaySoundMem(SE[MOVE], DX_PLAYTYPE_BACK);
					GetDrawScreenGraph(0, 0, 48 * 17, 48 * 13, MoveScreen);
					int Bright = 255;
					do {
						SetDrawBright(Bright, Bright, Bright);
						DrawGraph(0, 0, MoveScreen, FALSE);
						ScreenFlip();
						Bright = Bright - 10;
					} while (Bright >= 0);
					do {
						SetDrawBright(Bright, Bright, Bright);
						MAPDraw(MapNumber, MapRoop);
						CharMain(1);
						ScreenFlip();
						Bright = Bright + 10;
					} while (Bright <= 255);
					SetDrawBright(255, 255, 255);
				}
			}
		}
	else if (MapNumber == TOWN1MAP) {
			if (MapX == 1 && MapY == 4) {
				if (CharMainX == 6 && CharMainY == 7) {
					MapNumber = STARTMAP; MapX = 2; MapY = 3; CharMainX = 9; CharMainY = 12; Direction = FACEUP;
					MapRightX = MapX * -48 + 48;
					MapRightY = MapY * -48 + 48;
					CharMainRightX = CharMainX * 48 - 48;
					CharMainRightY = CharMainY * 48 - 48;

					PlaySoundMem(SE[MOVE], DX_PLAYTYPE_BACK);
					GetDrawScreenGraph(0, 0, 48 * 17, 48 * 13, MoveScreen);
					int Bright = 255;
					do {
						SetDrawBright(Bright, Bright, Bright);
						DrawGraph(0, 0, MoveScreen, FALSE);
						ScreenFlip();
						Bright = Bright - 10;
					} while (Bright >= 0);
					do {
						SetDrawBright(Bright, Bright, Bright);
						MAPDraw(MapNumber, MapRoop);
						CharMain(10);
						ScreenFlip();
						Bright = Bright + 10;
					} while (Bright <= 255);
					SetDrawBright(255, 255, 255);
				}
			}
			if (MapX == 7 && MapY == 27) {
				if (CharMainX == 9 && CharMainY == 7) {
					MapNumber = TOWN1INN1FMAP; MapX = 3; MapY = 8; CharMainX = 9; CharMainY = 12; Direction = FACEUP;
					MapRightX = MapX * -48 + 48;
					MapRightY = MapY * -48 + 48;
					CharMainRightX = CharMainX * 48 - 48;
					CharMainRightY = CharMainY * 48 - 48;

					PlaySoundMem(SE[MOVE], DX_PLAYTYPE_BACK);
					GetDrawScreenGraph(0, 0, 48 * 17, 48 * 13, MoveScreen);
					int Bright = 255;
					do {
						SetDrawBright(Bright, Bright, Bright);
						DrawGraph(0, 0, MoveScreen, FALSE);
						ScreenFlip();
						Bright = Bright - 10;
					} while (Bright >= 0);
					do {
						SetDrawBright(Bright, Bright, Bright);
						MAPDraw(MapNumber, MapRoop);
						CharMain(10);
						ScreenFlip();
						Bright = Bright + 10;
					} while (Bright <= 255);
					SetDrawBright(255, 255, 255);
				}
			}
			if (MapX == 7 && MapY == 28) {
				if (CharMainX == 9 && CharMainY == 13) {
					MapNumber = FIELDMAP; MapX = 41; MapY = 15; CharMainX = 9; CharMainY = 7; Direction = FACEDOWN; BattleMap = TRUE; Walk = 0;
					MapRightX = MapX * -48 + 48;
					MapRightY = MapY * -48 + 48;
					CharMainRightX = CharMainX * 48 - 48;
					CharMainRightY = CharMainY * 48 - 48;

					PlaySoundMem(SE[MOVE], DX_PLAYTYPE_BACK);
					GetDrawScreenGraph(0, 0, 48 * 17, 48 * 13, MoveScreen);
					int Bright = 255;
					float Vol = 1.00;
					do {
						SetDrawBright(Bright, Bright, Bright);
						DrawGraph(0, 0, MoveScreen, FALSE);
						ScreenFlip();
						ChangeVolumeSoundMem((float)BGMVolume * Vol, BGM[TOWN]);
						if (Vol != 0.00) Vol = Vol - 0.04;
						Bright = Bright - 10;
					} while (Bright >= 0);
					StopSoundMem(BGM[TOWN]);
					ChangeVolumeSoundMem(BGMVolume, BGM[TOWN]);
					do {
						SetDrawBright(Bright, Bright, Bright);
						MAPDraw(MapNumber, MapRoop);
						CharMain(1);
						ScreenFlip();
						Bright = Bright + 10;
					} while (Bright <= 255);
					SetDrawBright(255, 255, 255);
					PlaySoundMem(BGM[FIELD], DX_PLAYTYPE_LOOP);
				}
			}
		}
	else if (MapNumber == TOWN1INN1FMAP) {
			if (MapX == 3 && MapY == 8) {
				if (CharMainX == 9 && CharMainY == 13) {
					MapNumber = TOWN1MAP; MapX = 7; MapY = 28; CharMainX = 9; CharMainY = 7; Direction = FACEDOWN;
					MapRightX = MapX * -48 + 48;
					MapRightY = MapY * -48 + 48;
					CharMainRightX = CharMainX * 48 - 48;
					CharMainRightY = CharMainY * 48 - 48;

					PlaySoundMem(SE[MOVE], DX_PLAYTYPE_BACK);
					GetDrawScreenGraph(0, 0, 48 * 17, 48 * 13, MoveScreen);
					int Bright = 255;
					do {
						SetDrawBright(Bright, Bright, Bright);
						DrawGraph(0, 0, MoveScreen, FALSE);
						ScreenFlip();
						Bright = Bright - 10;
					} while (Bright >= 0);
					do {
						SetDrawBright(Bright, Bright, Bright);
						MAPDraw(MapNumber, MapRoop);
						CharMain(1);
						ScreenFlip();
						Bright = Bright + 10;
					} while (Bright <= 255);
					SetDrawBright(255, 255, 255);
				}
			}
			if (MapX == 5 && MapY == 8) {
				if (CharMainX == 12 && CharMainY == 8) {
					MapNumber = TOWN1INN2FMAP; MapX = 1; MapY = 3; CharMainX = 12; CharMainY = 10; Direction = FACELEFT;
					MapRightX = MapX * -48 + 48;
					MapRightY = MapY * -48 + 48;
					CharMainRightX = CharMainX * 48 - 48;
					CharMainRightY = CharMainY * 48 - 48;

					PlaySoundMem(SE[MOVE], DX_PLAYTYPE_BACK);
					GetDrawScreenGraph(0, 0, 48 * 17, 48 * 13, MoveScreen);
					int Bright = 255;
					do {
						SetDrawBright(Bright, Bright, Bright);
						DrawGraph(0, 0, MoveScreen, FALSE);
						ScreenFlip();
						Bright = Bright - 10;
					} while (Bright >= 0);
					do {
						SetDrawBright(Bright, Bright, Bright);
						MAPDraw(MapNumber, MapRoop);
						CharMain(4);
						ScreenFlip();
						Bright = Bright + 10;
					} while (Bright <= 255);
					SetDrawBright(255, 255, 255);
				}
			}
		}
	else if (MapNumber == TOWN1INN2FMAP) {
				if (MapX == 1 && MapY == 3) {
					if (CharMainX == 13 && CharMainY == 10 && Direction != FACELEFT) {
						MapNumber = TOWN1INN1FMAP; MapX = 5; MapY = 8; CharMainX = 11; CharMainY = 8; Direction = FACELEFT;
						MapRightX = MapX * -48 + 48;
						MapRightY = MapY * -48 + 48;
						CharMainRightX = CharMainX * 48 - 48;
						CharMainRightY = CharMainY * 48 - 48;

						PlaySoundMem(SE[MOVE], DX_PLAYTYPE_BACK);
						GetDrawScreenGraph(0, 0, 48 * 17, 48 * 13, MoveScreen);
						int Bright = 255;
						do {
							SetDrawBright(Bright, Bright, Bright);
							DrawGraph(0, 0, MoveScreen, FALSE);
							ScreenFlip();
							Bright = Bright - 10;
						} while (Bright >= 0);
						do {
							SetDrawBright(Bright, Bright, Bright);
							MAPDraw(MapNumber, MapRoop);
							CharMain(4);
							ScreenFlip();
							Bright = Bright + 10;
						} while (Bright <= 255);
						SetDrawBright(255, 255, 255);
					}
				}
		}
}