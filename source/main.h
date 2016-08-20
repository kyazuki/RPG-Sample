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
	Blue = GetColor(128, 165, 247);
	if (FontTitle == -1 || FontMain == -1) {
		RemoveFontResourceEx("resource/font/mplus-1m-medium.ttf", FR_PRIVATE, NULL);
		DxLib_End();
		return 1;
	}

	MenuScreen = MakeScreen(48 * 17, 48 * 13, FALSE);
	MenuScreenGAUSS = MakeScreen(48 * 17, 48 * 13, FALSE);

	SelectMenu[MAINMENU] = 18, SelectMenu[ITEMMENU] = 18, SelectMenu[SKILLMENU] = 18, SelectMenu[EQUIPMENU] = 18, SelectMenu[STATUSMENU] = 18;
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
	MenuGraph[MAINMENU] = LoadGraph("resource/System/window/menu.png");
	MenuGraph[ITEMMENU] = LoadGraph("resource/System/window/item.png");
	MenuGraph[SKILLMENU] = LoadGraph("resource/System/window/skill.png");
	MenuGraph[EQUIPMENU] = LoadGraph("resource/System/window/equip.png");
	MenuGraph[STATUSMENU] = LoadGraph("resource/System/window/status.png");
	MenuGraph[OPTIONMENU] = LoadGraph("resource/System/window/option.png");
	MsgGraph = LoadGraph("resource/System/window/msg.png");

	SelectGraph = LoadGraph("resource/System/select.png");

	LoadDivGraph("resource/faces/main.png", 8, 4, 2, 144, 144, FaceGraph);
	LoadDivGraph("resource/System/icon.png", 320, 16, 20, 32, 32, IconGraph);

	MapGraph[STARTMAP] = LoadGraph("resource/MAP/001.png");
	MapOverlayGraph[STARTMAP] = LoadGraph("resource/MAP/001o.png");
	MapAttack[STARTMAP] = LoadSoftImage("resource/MAP/001_.png");

	LoadDivGraph("resource/Character/Main/walk.png", 12, 3, 4, 48, 48, CharDiv);
}

//音
void LoadAllSounds(void) {
	BGM[TITLE] = LoadSoundMem("resource/sounds/BGM/Theme1.ogg");
	BGM[TOWN] = LoadSoundMem("resource/sounds/BGM/Town1.ogg");
	SE[SELECT] = LoadSoundMem("resource/sounds/SE/common/Cursor2.ogg");
	SE[DECISION] = LoadSoundMem("resource/sounds/SE/common/Decision1.ogg");
	SE[CANCEL] = LoadSoundMem("resource/sounds/SE/common/Cancel2.ogg");
	SE[BUZZER] = LoadSoundMem("resource/sounds/SE/common/Buzzer1.ogg");
	SE[EQUIP] = LoadSoundMem("resource/sounds/SE/Equip1.ogg");
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
			if (SelectOption == 348) { SelectOption = 384; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
			else if (SelectOption == 312) { SelectOption = 348; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
			else if (SelectOption == 276) { SelectOption = 312; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
			else if (SelectOption == 240) { SelectOption = 276; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
			else if (SelectOption == 204) { SelectOption = 240; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
		}
		else if (Key[KEY_INPUT_UP] == 1) {
			if (SelectOption == 240) { SelectOption = 204; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
			else if (SelectOption == 276) { SelectOption = 240; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
			else if (SelectOption == 312) { SelectOption = 276; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
			else if (SelectOption == 348) { SelectOption = 312; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
			else if (SelectOption == 384) { SelectOption = 348; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
		}
		else if (Key[KEY_INPUT_LEFT] == 1) {
			if (SelectOption == 204 && Dash == TRUE) {
				Dash = FALSE;
				PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK);
			}
			else if (SelectOption == 240 && Cheat == TRUE) {
				Cheat = FALSE;
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
		else if (Key[KEY_INPUT_RIGHT] == 1) {
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
		else if (Key[KEY_INPUT_ESCAPE] == 1 || Key[KEY_INPUT_X] == 1) {
			PlaySoundMem(SE[CANCEL], DX_PLAYTYPE_BACK);
			break;
		}

		if (ProcessMessage() < 0) break;
	}
	ConfigSave();
}

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
		DrawStringToHandle(24, 203, "セーブ", White, FontMain);
		if (Cheat == FALSE) DrawStringToHandle(24, 239, "チート", Gray, FontMain);
		else if (Cheat == TRUE) DrawStringToHandle(24, 239, "チート", White, FontMain);
		DrawStringToHandle(24, 275, "ゲーム終了", White, FontMain);

		DrawGraph(259, 19, FaceGraph[FACEMAIN], TRUE);
		DrawFormatStringToHandle(419, 42, White, FontMain, "%s", Name.c_str());
		DrawStringToHandle(419, 78, "Lv", Blue, FontMain);
		DrawFormatStringToHandle(508, 78, White, FontMain, "%3d", StatusMainChar[LV]);
		DrawStringToHandle(599, 42, "勇者", White, FontMain);
		DrawStringToHandle(599, 78, "HP", Blue, FontMain);
		DrawStringToHandle(599, 114, "MP", Blue, FontMain);
		DrawFormatStringToHandle(660, 78, White, FontMain, "%4d/%4d", StatusMainChar[HP], StatusMainChar[HPMAX]);
		DrawFormatStringToHandle(660, 114, White, FontMain, "%4d/%4d", StatusMainChar[MP], StatusMainChar[MPMAX]);

		DrawFormatStringToHandle(30, 574, White, FontMain, "%10ld", Money);
		DrawStringToHandle(190, 574, "G", Blue, FontMain);

		ScreenFlip();

		UpdateKey();
		if (Key[KEY_INPUT_DOWN] == 1) {
			if (SelectMenu[MAINMENU] == 234) { SelectMenu[MAINMENU] = 270; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
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
					DrawStringToHandle(24, 203, "セーブ", White, FontMain);
					if (Cheat == FALSE) DrawStringToHandle(24, 239, "チート", Gray, FontMain);
					else if (Cheat == TRUE) DrawStringToHandle(24, 239, "チート", White, FontMain);
					DrawStringToHandle(24, 275, "ゲーム終了", White, FontMain);

					DrawGraph(259, 19, FaceGraph[FACEMAIN], TRUE);
					DrawFormatStringToHandle(419, 42, White, FontMain, "%s", Name.c_str());
					DrawStringToHandle(419, 78, "Lv", Blue, FontMain);
					DrawFormatStringToHandle(508, 78, White, FontMain, "%3d", StatusMainChar[LV]);
					DrawStringToHandle(599, 42, "勇者", White, FontMain);
					DrawStringToHandle(599, 78, "HP", Blue, FontMain);
					DrawStringToHandle(599, 114, "MP", Blue, FontMain);
					DrawFormatStringToHandle(660, 78, White, FontMain, "%4d/%4d", StatusMainChar[HP], StatusMainChar[HPMAX]);
					DrawFormatStringToHandle(660, 114, White, FontMain, "%4d/%4d", StatusMainChar[MP], StatusMainChar[MPMAX]);

					DrawFormatStringToHandle(30, 574, White, FontMain, "%10ld", Money);
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

								DrawGraph(258, 126, FaceGraph[FACEMAIN], TRUE);
								DrawFormatStringToHandle(418, 149, White, FontMain, "%s", Name.c_str());
								DrawStringToHandle(418, 185, "Lv", Blue, FontMain);
								DrawFormatStringToHandle(507, 185, White, FontMain, "%3d", StatusMainChar[LV]);
								DrawStringToHandle(598, 149, "勇者", White, FontMain);
								DrawStringToHandle(598, 185, "HP", Blue, FontMain);
								DrawStringToHandle(598, 221, "MP", Blue, FontMain);
								DrawFormatStringToHandle(659, 185, White, FontMain, "%4d/%4d", StatusMainChar[HP], StatusMainChar[HPMAX]);
								DrawFormatStringToHandle(659, 221, White, FontMain, "%4d/%4d", StatusMainChar[MP], StatusMainChar[MPMAX]);

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

											DrawGraph(258, 126, FaceGraph[FACEMAIN], TRUE);
											DrawFormatStringToHandle(418, 149, White, FontMain, "%s", Name.c_str());
											DrawStringToHandle(418, 185, "Lv", Blue, FontMain);
											DrawFormatStringToHandle(507, 185, White, FontMain, "%3d", StatusMainChar[LV]);
											DrawStringToHandle(598, 149, "勇者", White, FontMain);
											DrawStringToHandle(598, 185, "HP", Blue, FontMain);
											DrawStringToHandle(598, 221, "MP", Blue, FontMain);
											DrawFormatStringToHandle(659, 185, White, FontMain, "%4d/%4d", StatusMainChar[HP], StatusMainChar[HPMAX]);
											DrawFormatStringToHandle(659, 221, White, FontMain, "%4d/%4d", StatusMainChar[MP], StatusMainChar[MPMAX]);

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
					DrawStringToHandle(24, 203, "セーブ", White, FontMain);
					if (Cheat == FALSE) DrawStringToHandle(24, 239, "チート", Gray, FontMain);
					else if (Cheat == TRUE) DrawStringToHandle(24, 239, "チート", White, FontMain);
					DrawStringToHandle(24, 275, "ゲーム終了", White, FontMain);

					DrawGraph(259, 19, FaceGraph[FACEMAIN], TRUE);
					DrawFormatStringToHandle(419, 42, White, FontMain, "%s", Name.c_str());
					DrawStringToHandle(419, 78, "Lv", Blue, FontMain);
					DrawFormatStringToHandle(508, 78, White, FontMain, "%3d", StatusMainChar[LV]);
					DrawStringToHandle(599, 42, "勇者", White, FontMain);
					DrawStringToHandle(599, 78, "HP", Blue, FontMain);
					DrawStringToHandle(599, 114, "MP", Blue, FontMain);
					DrawFormatStringToHandle(660, 78, White, FontMain, "%4d/%4d", StatusMainChar[HP], StatusMainChar[HPMAX]);
					DrawFormatStringToHandle(660, 114, White, FontMain, "%4d/%4d", StatusMainChar[MP], StatusMainChar[MPMAX]);

					DrawFormatStringToHandle(30, 574, White, FontMain, "%10ld", Money);
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

								DrawFormatStringToHandle(26, 131, White, FontMain, "%s", Name.c_str());
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

											DrawFormatStringToHandle(26, 131, White, FontMain, "%s", Name.c_str());
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

														DrawFormatStringToHandle(26, 131, White, FontMain, "%s", Name.c_str());
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

														DrawFormatStringToHandle(26, 131, White, FontMain, "%s", Name.c_str());
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

														DrawFormatStringToHandle(26, 131, White, FontMain, "%s", Name.c_str());
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

														DrawFormatStringToHandle(26, 131, White, FontMain, "%s", Name.c_str());
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

														DrawFormatStringToHandle(26, 131, White, FontMain, "%s", Name.c_str());
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
					DrawStringToHandle(24, 203, "セーブ", White, FontMain);
					if (Cheat == FALSE) DrawStringToHandle(24, 239, "チート", Gray, FontMain);
					else if (Cheat == TRUE) DrawStringToHandle(24, 239, "チート", White, FontMain);
					DrawStringToHandle(24, 275, "ゲーム終了", White, FontMain);

					DrawGraph(259, 19, FaceGraph[FACEMAIN], TRUE);
					DrawFormatStringToHandle(419, 42, White, FontMain, "%s", Name.c_str());
					DrawStringToHandle(419, 78, "Lv", Blue, FontMain);
					DrawFormatStringToHandle(508, 78, White, FontMain, "%3d", StatusMainChar[LV]);
					DrawStringToHandle(599, 42, "勇者", White, FontMain);
					DrawStringToHandle(599, 78, "HP", Blue, FontMain);
					DrawStringToHandle(599, 114, "MP", Blue, FontMain);
					DrawFormatStringToHandle(660, 78, White, FontMain, "%4d/%4d", StatusMainChar[HP], StatusMainChar[HPMAX]);
					DrawFormatStringToHandle(660, 114, White, FontMain, "%4d/%4d", StatusMainChar[MP], StatusMainChar[MPMAX]);

					DrawFormatStringToHandle(30, 574, White, FontMain, "%10ld", Money);
					DrawStringToHandle(190, 574, "G", Blue, FontMain);

					ScreenFlip();

					UpdateKey();
					if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) {
							PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
							while (1) {
								ClearDrawScreen();
								DrawGraph(0, 0, MenuScreenGAUSS, FALSE);
								DrawGraph(0, 0, MenuGraph[STATUSMENU], TRUE);

								DrawFormatStringToHandle(23, 23, White, FontMain, "%s", Name.c_str());
								DrawStringToHandle(209, 23, "勇者", White, FontMain);

								DrawGraph(30, 90, FaceGraph[FACEMAIN], TRUE);
								DrawStringToHandle(222, 95, "Lv", Blue, FontMain);
								DrawFormatStringToHandle(311, 95, White, FontMain, "%3d", StatusMainChar[LV]);
								DrawStringToHandle(222, 166, "HP", Blue, FontMain);
								DrawStringToHandle(222, 202, "MP", Blue, FontMain);
								DrawFormatStringToHandle(283, 166, White, FontMain, "%4d/%4d", StatusMainChar[HP], StatusMainChar[HPMAX]);
								DrawFormatStringToHandle(283, 202, White, FontMain, "%4d/%4d", StatusMainChar[MP], StatusMainChar[MPMAX]);
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
			else if (SelectMenu[MAINMENU] == 198) { PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK); }
			else if (SelectMenu[MAINMENU] == 234) {
				if (Cheat == FALSE) PlaySoundMem(SE[BUZZER], DX_PLAYTYPE_BACK);
				else if (Cheat == TRUE) { PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK); }
			}
			else if (SelectMenu[MAINMENU] == 270) {
				PlaySoundMem(SE[DECISION], DX_PLAYTYPE_NORMAL);
				GameEnd = 1;
				break;
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
	int TitleGraph, TitleLogGraph, Bright = 0, Pal = 255, Flag = 0, Select = 0, SelectY = 400, SelectHeight = 38;
	int LogBoxY = 0;
	PlaySoundMem(BGM[TITLE], DX_PLAYTYPE_BACK);
	TitleGraph = LoadGraph("resource/Title/title.png");
	TitleLogGraph = LoadGraph("resource/System/window/title.png");
	do {
		SetDrawBright(Bright, Bright, Bright);
		DrawGraph(0, 0, TitleGraph, FALSE);
		DrawStringToHandle(305, 200, "Game", White, FontTitle);
		ScreenFlip();
		Bright = Bright + 5;
	} while (Bright < 256);
	WaitTimer(500);
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
		DrawGraph(288, 383, TitleLogGraph, TRUE);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, Pal);
		DrawModiGraph(305, SelectY, 510, SelectY, 510, SelectY + 38, 305, SelectY + 38, SelectGraph, TRUE);
		if (Pal == 255) Flag = 1;
		else if (Pal == 129) Flag = 0;

		if (Flag == 1) Pal = Pal - 6;
		else if (Flag == 0) Pal = Pal + 6;

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		DrawStringToHandle(310, 405, "ニューゲーム", White, FontMain);
		DrawStringToHandle(310, 440, "コンティニュー", Gray, FontMain);
		DrawStringToHandle(310, 475, "オプション", White, FontMain);
		ScreenFlip();

		UpdateKey();
		if (Key[KEY_INPUT_DOWN] == 1) {
			if (SelectY == 434) { SelectY = 469; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
			else if (SelectY == 400) { SelectY = 434; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
		}
		else if (Key[KEY_INPUT_UP] == 1) {
			if (SelectY == 434) { SelectY = 400; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
			else if (SelectY == 469) { SelectY = 434; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
		}
		else if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) {
			if (SelectY == 400) {
				PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
				break;
			}
			else if (SelectY == 434) { PlaySoundMem(SE[BUZZER], DX_PLAYTYPE_BACK); }
			else if (SelectY == 469) {
				PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
				do {
					ClearDrawScreen();
					DrawGraph(0, 0, TitleGraph, FALSE);
					DrawStringToHandle(305, 200, "Game", White, FontTitle);
					if (LogBoxY > 0) DrawModiGraph(288, 453 - LogBoxY, 527, 453 - LogBoxY, 527, 455 + LogBoxY, 288, 455 + LogBoxY, TitleLogGraph, TRUE);
					ScreenFlip();
					LogBoxY = LogBoxY - 7;
				} while (LogBoxY > 0);
				ClearDrawScreen();
				DrawGraph(0, 0, TitleGraph, FALSE);
				DrawStringToHandle(305, 200, "Game", White, FontTitle);

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
						DrawStringToHandle(305, 200, "Game", White, FontTitle);
						DrawModiGraph(288, 453 - LogBoxY, 527, 453 - LogBoxY, 527, 455 + LogBoxY, 288, 455 + LogBoxY, TitleLogGraph, TRUE);
						ScreenFlip();
						LogBoxY = LogBoxY + 7;
					} while (LogBoxY <= 70);
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
		} while (BGMVol >= 0 || Bright > 0);
	StopSoundMem(BGM[TITLE]);
	ChangeVolumeSoundMem(128, BGM[TITLE]);
	DeleteGraph(TitleGraph);
	DeleteGraph(TitleLogGraph);
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
		MAPDraw(STARTMAP);
		CharMain(i);
		ScreenFlip();
		WaitTimer(15);
	}
void MoveSupportDOWN(int i)
	{
		MapRightY = MapRightY - 3;
		if (MapRightY < -720 + (48 * 13)) {
			MapRightY = -720 + (48 * 13);
			CharMainRightY = CharMainRightY + 3;
		}
		else if (CharMainRightY < 288) {
			MapRightY = MapRightY + 3;
			CharMainRightY = CharMainRightY + 3;
		}
		ClearDrawScreen();
		MAPDraw(STARTMAP);
		CharMain(i);
		ScreenFlip();
		WaitTimer(15);
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
		MAPDraw(STARTMAP);
		CharMain(i);
		ScreenFlip();
		WaitTimer(15);
	}
void MoveSupportRIGHT(int i)
	{
		MapRightX = MapRightX - 3;
		if (MapRightX < -912 + (48 * 17)) {
			MapRightX = -912 + (48 * 17);
			CharMainRightX = CharMainRightX + 3;
		}
		else if (CharMainRightX < 384) {
			MapRightX = MapRightX + 3;
			CharMainRightX = CharMainRightX + 3;
		}
		ClearDrawScreen();
		MAPDraw(STARTMAP);
		CharMain(i);
		ScreenFlip();
		WaitTimer(15);
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
		MAPDraw(STARTMAP);
		CharMain(i);
		ScreenFlip();
		WaitTimer(5);
	}
void MoveSupportDashDOWN(int i)
	{
		MapRightY = MapRightY - 6;
		if (MapRightY < -720 + (48 * 13)) {
			MapRightY = -720 + (48 * 13);
			CharMainRightY = CharMainRightY + 6;
		}
		else if (CharMainRightY < 288) {
			MapRightY = MapRightY + 6;
			CharMainRightY = CharMainRightY + 6;
		}
		ClearDrawScreen();
		MAPDraw(STARTMAP);
		CharMain(i);
		ScreenFlip();
		WaitTimer(5);
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
		MAPDraw(STARTMAP);
		CharMain(i);
		ScreenFlip();
		WaitTimer(5);
	}
void MoveSupportDashRIGHT(int i)
	{
		MapRightX = MapRightX - 6;
		if (MapRightX < -912 + (48 * 17)) {
			MapRightX = -912 + (48 * 17);
			CharMainRightX = CharMainRightX + 6;
		}
		else if (CharMainRightX < 384) {
			MapRightX = MapRightX + 6;
			CharMainRightX = CharMainRightX + 6;
		}
		ClearDrawScreen();
		MAPDraw(STARTMAP);
		CharMain(i);
		ScreenFlip();
		WaitTimer(5);
	}

//マップ移動関数
void Move(void) {
	if (CheckHitKey(KEY_INPUT_UP) == 1)
		{
			if (attackup(MapAttack[STARTMAP], 0, -24) != 1)
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
			}
			if (attackup(MapAttack[STARTMAP], 0, -24) == 1)
			{
				MAPDraw(STARTMAP);
				CharMain(10);
				ScreenFlip();
			}
			Direction = FACEUP;
		}
	else if (CheckHitKey(KEY_INPUT_DOWN) == 1)
		{
			if (attackup(MapAttack[STARTMAP], 0, 48 + 24) != 1)
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
			}
			else if (attackup(MapAttack[STARTMAP], 0, 48 + 24) == 1)
			{
				MAPDraw(STARTMAP);
				CharMain(1);
				ScreenFlip();
			}
			Direction = FACEDOWN;
		}
	else if (CheckHitKey(KEY_INPUT_LEFT) == 1)
		{
			if (attackup(MapAttack[STARTMAP], -24, 0) != 1)
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
			}
			else if (attackup(MapAttack[STARTMAP], -24, 0) == 1)
			{
				MAPDraw(STARTMAP);
				CharMain(4);
				ScreenFlip();
			}
			Direction = FACELEFT;
		}
	else if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
		{
			if (attackup(MapAttack[STARTMAP], 48 + 24, 0) != 1)
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
			}
			else if (attackup(MapAttack[STARTMAP], 48 + 24, 0) == 1)
			{
				MAPDraw(STARTMAP);
				CharMain(7);
				ScreenFlip();
			}
			Direction = FACERIGHT;
		}
	MapX = (MapRightX - 48) / -48;
	MapY = (MapRightY - 48) / -48;
	CharMainX = (CharMainRightX + 48) / 48;
	CharMainY = (CharMainRightY + 48) / 48;
	}