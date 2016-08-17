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

	OptionScreen = MakeScreen(48 * 17, 48 * 13, FALSE);
	OptionScreenGAUSS = MakeScreen(48 * 17, 48 * 13, FALSE);
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
	OptionGraph = LoadGraph("resource/System/window/option.png");

	Map001Graph = LoadGraph("resource/MAP/001.png");
	Map001OverlayGraph = LoadGraph("resource/MAP/001o.png");
	Map001_ = LoadSoftImage("resource/MAP/001_.png");

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
	int Gauss = 0;
	GetDrawScreenGraph(0, 0, 48 * 17, 48 * 13, OptionScreen);
	do {
		ClearDrawScreen();
		GraphFilterBlt(OptionScreen, OptionScreenGAUSS, DX_GRAPH_FILTER_GAUSS, 8, Gauss);
		DrawGraph(0, 0, OptionScreenGAUSS, FALSE);
		ScreenFlip();
		Gauss = Gauss + 10;
	} while (Gauss <= 100);

	WaitTimer(500);
	ClearDrawScreen();
	DrawGraph(0, 0, OptionScreenGAUSS, FALSE);
	DrawGraph(208, 186, OptionGraph, TRUE);
	ScreenFlip();

	int SelectOption = 204, OptionPal = 255, OptionFlag = 0;
	while (1) {
		ClearDrawScreen();
		DrawGraph(0, 0, OptionScreenGAUSS, FALSE);
		DrawGraph(208, 186, OptionGraph, TRUE);

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
		MAP001();
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
		MAP001();
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
		MAP001();
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
		MAP001();
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
		MAP001();
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
		MAP001();
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
		MAP001();
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
		MAP001();
		CharMain(i);
		ScreenFlip();
		WaitTimer(5);
	}

//マップ移動関数
void Move(void) {
	if (CheckHitKey(KEY_INPUT_UP) == 1)
		{
			if (attackup(Map001_, 0, -24) != 1)
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
						MapY = (MapRightY - 48) / -48;
						CharMainY = (CharMainRightY + 48) / 48;
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
						MapY = (MapRightY - 48) / -48;
						CharMainY = (CharMainRightY + 48) / 48;
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
						MapY = (MapRightY - 48) / -48;
						CharMainY = (CharMainRightY + 48) / 48;
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
						MapY = (MapRightY - 48) / -48;
						CharMainY = (CharMainRightY + 48) / 48;
						U2 = 1;
					}

					if (U1 == 1) { U = 1; U1 = 0; }
					else if (U2 == 1) { U = 0; U2 = 0; }
				}
			}
			if (attackup(Map001_, 0, -24) == 1)
			{
				MAP001();
				CharMain(10);
				ScreenFlip();
			}
		}
	else if (CheckHitKey(KEY_INPUT_DOWN) == 1)
		{
			if (attackup(Map001_, 0, 48 + 24) != 1)
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
						MapY = (MapRightY - 48) / -48;
						CharMainY = (CharMainRightY + 48) / 48;
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
						MapY = (MapRightY - 48) / -48;
						CharMainY = (CharMainRightY + 48) / 48;
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
						MapY = (MapRightY - 48) / -48;
						CharMainY = (CharMainRightY + 48) / 48;
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
						MapY = (MapRightY - 48) / -48;
						CharMainY = (CharMainRightY + 48) / 48;
						D2 = 1;
					}

					if (D1 == 1) { D = 1; D1 = 0; }
					else if (D2 == 1) { D = 0; D2 = 0; }
				}
			}
			else if (attackup(Map001_, 0, 48 + 24) == 1)
			{
				MAP001();
				CharMain(1);
				ScreenFlip();
			}
		}
	else if (CheckHitKey(KEY_INPUT_LEFT) == 1)
		{
			if (attackup(Map001_, -24, 0) != 1)
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
						MapX = (MapRightX - 48) / -48;
						CharMainX = (CharMainRightX + 48) / 48;
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
						MapX = (MapRightX - 48) / -48;
						CharMainX = (CharMainRightX + 48) / 48;
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
						MapX = (MapRightX - 48) / -48;
						CharMainX = (CharMainRightX + 48) / 48;
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
						MapX = (MapRightX - 48) / -48;
						CharMainX = (CharMainRightX + 48) / 48;
						L2 = 1;
					}

					if (L1 == 1) { L = 1; L1 = 0; }
					else if (L2 == 1) { L = 0; L2 = 0; }
				}
			}
			else if (attackup(Map001_, -24, 0) == 1)
			{
				MAP001();
				CharMain(4);
				ScreenFlip();
			}
		}
	else if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
		{
			if (attackup(Map001_, 48 + 24, 0) != 1)
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
						MapX = (MapRightX - 48) / -48;
						CharMainX = (CharMainRightX + 48) / 48;
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
						MapX = (MapRightX - 48) / -48;
						CharMainX = (CharMainRightX + 48) / 48;
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
						MapX = (MapRightX - 48) / -48;
						CharMainX = (CharMainRightX + 48) / 48;
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
						MapX = (MapRightX - 48) / -48;
						CharMainX = (CharMainRightX + 48) / 48;
						R2 = 1;
					}

					if (R1 == 1) { R = 1; R1 = 0; }
					else if (R2 == 1) { R = 0; R2 = 0; }
				}
			}
			else if (attackup(Map001_, 48 + 24, 0) == 1)
			{
				MAP001();
				CharMain(7);
				ScreenFlip();
			}
		}
	}