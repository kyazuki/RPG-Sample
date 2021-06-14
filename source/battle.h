void BattleAssist(void) {
	ClearDrawScreen();
	DrawGraph(0, 0, EncountScreen, FALSE);
	DrawModiGraph(193 - 97, 444, 816 - 97, 444, 816 - 97, 624, 193 - 97, 624, BattleGraph[1], TRUE);

	HPBar = (float)StatusMainChar[HP] / StatusMainChar[HPMAX] * 150;
	MPBar = (float)StatusMainChar[MP] / StatusMainChar[MPMAX] * 150;
	HPBarWidth = HPBar;
	MPBarWidth = MPBar;

	if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(213 - 97, 466, White, FontMain, "%s", Name.c_str());
	else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(213 - 97, 466, Yellow, FontMain, "%s", Name.c_str());
	else if (HPBarWidth == 0) { DrawFormatStringToHandle(213 - 97, 466, Red, FontMain, "%s", Name.c_str()); DrawGraph(372 - 97, 463, IconGraph[1], TRUE); }
	DrawRectGraph(462 - 97, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
	DrawRectGraph(642 - 97, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
	DrawRectGraph(462 - 97, 490, 0, 0, HPBarWidth, 7, HPBarGraph, TRUE, FALSE);
	DrawRectGraph(642 - 97, 490, 0, 0, MPBarWidth, 7, MPBarGraph, TRUE, FALSE);
	DrawStringToHandle(461 - 97, 467, "HP", Blue, FontMain);
	DrawStringToHandle(641 - 97, 467, "MP", Blue, FontMain);
	if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(554 - 97, 467, White, FontMain, "%4d", StatusMainChar[HP]);
	else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(554 - 97, 467, Yellow, FontMain, "%4d", StatusMainChar[HP]);
	else if (HPBarWidth == 0) DrawFormatStringToHandle(554 - 97, 467, Red, FontMain, "%4d", StatusMainChar[HP]);
	if (MPBarWidth <= 186 && MPBarWidth > 56) DrawFormatStringToHandle(733 - 97, 467, White, FontMain, "%4d", StatusMainChar[MP]);
	else if (MPBarWidth <= 56 && MPBarWidth > 0) DrawFormatStringToHandle(733 - 97, 467, Yellow, FontMain, "%4d", StatusMainChar[MP]);
	else if (MPBarWidth == 0) DrawFormatStringToHandle(733 - 97, 467, Red, FontMain, "%4d", StatusMainChar[MP]);
}

void Battle(void) {
	Encount = 0;
	GetDrawScreenGraph(0, 0, 48 * 17, 48 * 13, EncountScreen);
	StopSoundMem(BGM[FIELD]);
	PlaySoundMem(SE[ENCOUNT], DX_PLAYTYPE_BACK);
	int Light = 0, ExtendWidth = 0, ExtendHeight = 0;
	do {
		ClearDrawScreen();
		GraphFilterBlt(EncountScreen, FilterScreen, DX_GRAPH_FILTER_HSB, 0, 0, 0, Light);
		DrawExtendGraph(0 - ExtendWidth, 0 - ExtendHeight, 48 * 17 + ExtendWidth, 48 * 13 + ExtendHeight, FilterScreen, FALSE);
		ScreenFlip();
		Light = Light + 17;
		ExtendWidth = ExtendWidth + 34;
		ExtendHeight = ExtendHeight + 26;
	} while (Light <= 255);
	Light = 255;
	do {
		ClearDrawScreen();
		GraphFilterBlt(EncountScreen, FilterScreen, DX_GRAPH_FILTER_HSB, 0, 0, 0, Light);
		DrawExtendGraph(0 - ExtendWidth, 0 - ExtendHeight, 48 * 17 + ExtendWidth, 48 * 13 + ExtendHeight, FilterScreen, FALSE);
		ScreenFlip();
		Light = Light - 17;
		ExtendWidth = ExtendWidth - 34;
		ExtendHeight = ExtendHeight - 26;
	} while (Light >= 0);
	Light = 0;
	GraphFilterBlt(EncountScreen, FilterScreen, DX_GRAPH_FILTER_HSB, 0, 0, 0, Light);
	int Bright = 255;
	do {
		ClearDrawScreen();
		SetDrawBright(Bright, Bright, Bright);
		DrawExtendGraph(0 - ExtendWidth, 0 - ExtendHeight, 48 * 17 + ExtendWidth, 48 * 13 + ExtendHeight, EncountScreen, FALSE);
		ScreenFlip();
		Bright = Bright - 17;
		ExtendWidth = ExtendWidth + 34;
		ExtendHeight = ExtendHeight + 26;
	} while (Bright >= 0);
	SetDrawBright(255, 255, 255);
	PlaySoundMem(BGM[BATTLE], DX_PLAYTYPE_LOOP);
	WaitTimer(500);
	if (MobCount(mt) == 1) {
		BattleMobID = MobID(mt);
		if (BattleMobID == SLIME) {
			MobStatus[MOBHP] = SLIMEHP;
			MobStatus[MOBATK] = SLIMEATK;
			do {
				ClearDrawScreen();
				SetDrawBright(Bright, Bright, Bright);
				DrawGraph(0, 0, BattleBackGraph[GRASS], FALSE);
				DrawGraph(0, 0, BattleBackOverGraph[GRASSOVER], TRUE);
				DrawGraph(344, 330, MobGraph[SLIME], TRUE);
				ScreenFlip();
				Bright = Bright + 17;
			} while (Bright <= 255);
			Bright = 255;
			GetDrawScreenGraph(0, 0, 48 * 17, 48 * 13, EncountScreen);
			MsgBoxY = 0;
			do {
				ClearDrawScreen();
				DrawGraph(0, 0, EncountScreen, FALSE);
				DrawModiGraph(0, 532 - MsgBoxY, 816, 532 - MsgBoxY, 816, 536 + MsgBoxY, 0, 536 + MsgBoxY, MsgGraph, TRUE);
				ScreenFlip();
				MsgBoxY = MsgBoxY + 8;
			} while (MsgBoxY <= 88);
			MsgBoxY = 88;
			ClearDrawScreen();
			DrawGraph(0, 0, EncountScreen, FALSE);
			DrawGraph(0, 444, MsgGraph, TRUE);
			ScreenFlip();
			int i = 0;
			do {
				DrawFormatStringToHandle(20 + (i * 14), 465, White, FontMain, "%c%c", ECMsgSlime[i], ECMsgSlime[i + 1]);
				ScreenFlip();
				WaitTimer(15);
				i = i + 2;
				if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) break;
			} while (i + 1 <= 22);
			int j = 0;
			while (1) {
				ClearDrawScreen();
				DrawGraph(0, 0, EncountScreen, FALSE);
				DrawGraph(0, 444, MsgGraph, TRUE);
				DrawFormatStringToHandle(20, 465, White, FontMain, "%s", ECMsg[SLIME].c_str());
				if (j <= 15) DrawGraph(396, 600, CursorGraph[0], TRUE);
				else if (j > 15 && j <= 30) DrawGraph(396, 600, CursorGraph[1], TRUE);
				else if (j > 30 && j <= 45) DrawGraph(396, 600, CursorGraph[2], TRUE);
				else if (j > 45) { DrawGraph(396, 600, CursorGraph[3], TRUE); j = 0; }
				ScreenFlip();
				j++;
				if (CheckHitKey(KEY_INPUT_RETURN) == 1 || CheckHitKey(KEY_INPUT_Z) == 1) break;
			}
			do {
				ClearDrawScreen();
				DrawGraph(0, 0, EncountScreen, FALSE);
				DrawModiGraph(0, 532 - MsgBoxY, 816, 532 - MsgBoxY, 816, 536 + MsgBoxY, 0, 536 + MsgBoxY, MsgGraph, TRUE);
				ScreenFlip();
				MsgBoxY = MsgBoxY - 11;
			} while (MsgBoxY >= 0);
			MsgBoxY = 0;
			do {
				ClearDrawScreen();
				DrawGraph(0, 0, EncountScreen, FALSE);
				DrawModiGraph(0, 532 - MsgBoxY, 192, 532 - MsgBoxY, 192, 536 + MsgBoxY, 0, 536 + MsgBoxY, BattleGraph[0], TRUE);
				DrawModiGraph(193, 532 - MsgBoxY, 816, 532 - MsgBoxY, 816, 536 + MsgBoxY, 193, 536 + MsgBoxY, BattleGraph[1], TRUE);
				ScreenFlip();
				MsgBoxY = MsgBoxY + 11;
			} while (MsgBoxY <= 88);
			MsgBoxY = 88;
			int SelectY = 462, Flag = 1, Pal = 255;
			while (GameOver != TRUE) {
				Defence = StatusMainChar[DEF];
				SelectY = 462;
				NoAttack = FALSE;
				while (TurnEnd == FALSE && GameOver == FALSE) {
					ClearDrawScreen();
					DrawGraph(0, 0, EncountScreen, FALSE);
					DrawGraph(0, 444, BattleGraph[0], TRUE);
					DrawGraph(193, 444, BattleGraph[1], TRUE);
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, Pal);
					DrawModiGraph(18, SelectY, 173, SelectY, 173, SelectY + 36, 18, SelectY + 36, SelectGraph, TRUE);
					if (Pal == 255) Flag = 1;
					else if (Pal == 129) Flag = 0;

					if (Flag == 1) Pal = Pal - 6;
					else if (Flag == 0) Pal = Pal + 6;

					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
					DrawStringToHandle(20, 467, "戦う", White, FontMain);
					DrawStringToHandle(20, 503, "逃げる", White, FontMain);

					HPBar = (float)StatusMainChar[HP] / StatusMainChar[HPMAX] * 150;
					MPBar = (float)StatusMainChar[MP] / StatusMainChar[MPMAX] * 150;
					HPBarWidth = HPBar;
					MPBarWidth = MPBar;

					if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(213, 466, White, FontMain, "%s", Name.c_str());
					else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(213, 466, Yellow, FontMain, "%s", Name.c_str());
					else if (HPBarWidth == 0) { DrawFormatStringToHandle(213, 466, Red, FontMain, "%s", Name.c_str()); DrawGraph(372, 463, IconGraph[1], TRUE); }
					DrawRectGraph(462, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
					DrawRectGraph(642, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
					DrawRectGraph(462, 490, 0, 0, HPBarWidth, 7, HPBarGraph, TRUE, FALSE);
					DrawRectGraph(642, 490, 0, 0, MPBarWidth, 7, MPBarGraph, TRUE, FALSE);
					DrawStringToHandle(461, 467, "HP", Blue, FontMain);
					DrawStringToHandle(641, 467, "MP", Blue, FontMain);
					if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(554, 467, White, FontMain, "%4d", StatusMainChar[HP]);
					else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(554, 467, Yellow, FontMain, "%4d", StatusMainChar[HP]);
					else if (HPBarWidth == 0) DrawFormatStringToHandle(554, 467, Red, FontMain, "%4d", StatusMainChar[HP]);
					if (MPBarWidth <= 186 && MPBarWidth > 56) DrawFormatStringToHandle(733, 467, White, FontMain, "%4d", StatusMainChar[MP]);
					else if (MPBarWidth <= 56 && MPBarWidth > 0) DrawFormatStringToHandle(733, 467, Yellow, FontMain, "%4d", StatusMainChar[MP]);
					else if (MPBarWidth == 0) DrawFormatStringToHandle(733, 467, Red, FontMain, "%4d", StatusMainChar[MP]);

					ScreenFlip();
					UpdateKey();
					if (Key[KEY_INPUT_DOWN] == 1) {
						if (SelectY == 462) { SelectY = 498; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
					}
					else if (Key[KEY_INPUT_UP] == 1) {
						if (SelectY == 498) { SelectY = 462; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
					}
					else if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) {
						if (SelectY == 462) {
							PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
							do {
								ClearDrawScreen();
								DrawGraph(0, 0, EncountScreen, FALSE);
								DrawModiGraph(0, 532 - MsgBoxY, 192, 532 - MsgBoxY, 192, 536 + MsgBoxY, 0, 536 + MsgBoxY, BattleGraph[0], TRUE);
								DrawGraph(193, 444, BattleGraph[1], TRUE);

								HPBar = (float)StatusMainChar[HP] / StatusMainChar[HPMAX] * 150;
								MPBar = (float)StatusMainChar[MP] / StatusMainChar[MPMAX] * 150;
								HPBarWidth = HPBar;
								MPBarWidth = MPBar;

								if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(213, 466, White, FontMain, "%s", Name.c_str());
								else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(213, 466, Yellow, FontMain, "%s", Name.c_str());
								else if (HPBarWidth == 0) { DrawFormatStringToHandle(213, 466, Red, FontMain, "%s", Name.c_str()); DrawGraph(372, 463, IconGraph[1], TRUE); }
								DrawRectGraph(462, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
								DrawRectGraph(642, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
								DrawRectGraph(462, 490, 0, 0, HPBarWidth, 7, HPBarGraph, TRUE, FALSE);
								DrawRectGraph(642, 490, 0, 0, MPBarWidth, 7, MPBarGraph, TRUE, FALSE);
								DrawStringToHandle(461, 467, "HP", Blue, FontMain);
								DrawStringToHandle(641, 467, "MP", Blue, FontMain);
								if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(554, 467, White, FontMain, "%4d", StatusMainChar[HP]);
								else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(554, 467, Yellow, FontMain, "%4d", StatusMainChar[HP]);
								else if (HPBarWidth == 0) DrawFormatStringToHandle(554, 467, Red, FontMain, "%4d", StatusMainChar[HP]);
								if (MPBarWidth <= 186 && MPBarWidth > 56) DrawFormatStringToHandle(733, 467, White, FontMain, "%4d", StatusMainChar[MP]);
								else if (MPBarWidth <= 56 && MPBarWidth > 0) DrawFormatStringToHandle(733, 467, Yellow, FontMain, "%4d", StatusMainChar[MP]);
								else if (MPBarWidth == 0) DrawFormatStringToHandle(733, 467, Red, FontMain, "%4d", StatusMainChar[MP]);

								ScreenFlip();
								MsgBoxY = MsgBoxY - 11;
							} while (MsgBoxY >= 0);
							do {
								ClearDrawScreen();
								DrawGraph(0, 0, EncountScreen, FALSE);
								DrawModiGraph(0, 532 - MsgBoxY, 192, 532 - MsgBoxY, 192, 536 + MsgBoxY, 0, 536 + MsgBoxY, BattleGraph[0], TRUE);
								DrawGraph(193, 444, BattleGraph[1], TRUE);

								HPBar = (float)StatusMainChar[HP] / StatusMainChar[HPMAX] * 150;
								MPBar = (float)StatusMainChar[MP] / StatusMainChar[MPMAX] * 150;
								HPBarWidth = HPBar;
								MPBarWidth = MPBar;

								if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(213, 466, White, FontMain, "%s", Name.c_str());
								else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(213, 466, Yellow, FontMain, "%s", Name.c_str());
								else if (HPBarWidth == 0) { DrawFormatStringToHandle(213, 466, Red, FontMain, "%s", Name.c_str()); DrawGraph(372, 463, IconGraph[1], TRUE); }
								DrawRectGraph(462, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
								DrawRectGraph(642, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
								DrawRectGraph(462, 490, 0, 0, HPBarWidth, 7, HPBarGraph, TRUE, FALSE);
								DrawRectGraph(642, 490, 0, 0, MPBarWidth, 7, MPBarGraph, TRUE, FALSE);
								DrawStringToHandle(461, 467, "HP", Blue, FontMain);
								DrawStringToHandle(641, 467, "MP", Blue, FontMain);
								if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(554, 467, White, FontMain, "%4d", StatusMainChar[HP]);
								else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(554, 467, Yellow, FontMain, "%4d", StatusMainChar[HP]);
								else if (HPBarWidth == 0) DrawFormatStringToHandle(554, 467, Red, FontMain, "%4d", StatusMainChar[HP]);
								if (MPBarWidth <= 186 && MPBarWidth > 56) DrawFormatStringToHandle(733, 467, White, FontMain, "%4d", StatusMainChar[MP]);
								else if (MPBarWidth <= 56 && MPBarWidth > 0) DrawFormatStringToHandle(733, 467, Yellow, FontMain, "%4d", StatusMainChar[MP]);
								else if (MPBarWidth == 0) DrawFormatStringToHandle(733, 467, Red, FontMain, "%4d", StatusMainChar[MP]);

								ScreenFlip();
								MsgBoxY = MsgBoxY + 11;
							} while (MsgBoxY <= 88);
							while (TurnEnd == FALSE) {
								ClearDrawScreen();
								DrawGraph(0, 0, EncountScreen, FALSE);
								DrawGraph(0, 444, BattleGraph[0], TRUE);
								DrawGraph(193, 444, BattleGraph[1], TRUE);
								SetDrawBlendMode(DX_BLENDMODE_ALPHA, Pal);
								DrawModiGraph(18, SelectY, 173, SelectY, 173, SelectY + 36, 18, SelectY + 36, SelectGraph, TRUE);
								if (Pal == 255) Flag = 1;
								else if (Pal == 129) Flag = 0;

								if (Flag == 1) Pal = Pal - 6;
								else if (Flag == 0) Pal = Pal + 6;

								SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
								DrawStringToHandle(20, 467, "攻撃", White, FontMain);
								DrawStringToHandle(20, 503, "魔法", White, FontMain);
								DrawStringToHandle(20, 539, "防御", White, FontMain);
								DrawStringToHandle(20, 575, "アイテム", White, FontMain);
								DrawModiGraph(210, 462, 798, 462, 798, 498, 210, 498, SelectGraph, TRUE);

								HPBar = (float)StatusMainChar[HP] / StatusMainChar[HPMAX] * 150;
								MPBar = (float)StatusMainChar[MP] / StatusMainChar[MPMAX] * 150;
								HPBarWidth = HPBar;
								MPBarWidth = MPBar;

								if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(213, 466, White, FontMain, "%s", Name.c_str());
								else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(213, 466, Yellow, FontMain, "%s", Name.c_str());
								else if (HPBarWidth == 0) { DrawFormatStringToHandle(213, 466, Red, FontMain, "%s", Name.c_str()); DrawGraph(372, 463, IconGraph[1], TRUE); }
								DrawRectGraph(462, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
								DrawRectGraph(642, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
								DrawRectGraph(462, 490, 0, 0, HPBarWidth, 7, HPBarGraph, TRUE, FALSE);
								DrawRectGraph(642, 490, 0, 0, MPBarWidth, 7, MPBarGraph, TRUE, FALSE);
								DrawStringToHandle(461, 467, "HP", Blue, FontMain);
								DrawStringToHandle(641, 467, "MP", Blue, FontMain);
								if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(554, 467, White, FontMain, "%4d", StatusMainChar[HP]);
								else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(554, 467, Yellow, FontMain, "%4d", StatusMainChar[HP]);
								else if (HPBarWidth == 0) DrawFormatStringToHandle(554, 467, Red, FontMain, "%4d", StatusMainChar[HP]);
								if (MPBarWidth <= 186 && MPBarWidth > 56) DrawFormatStringToHandle(733, 467, White, FontMain, "%4d", StatusMainChar[MP]);
								else if (MPBarWidth <= 56 && MPBarWidth > 0) DrawFormatStringToHandle(733, 467, Yellow, FontMain, "%4d", StatusMainChar[MP]);
								else if (MPBarWidth == 0) DrawFormatStringToHandle(733, 467, Red, FontMain, "%4d", StatusMainChar[MP]);

								ScreenFlip();
								UpdateKey();
								if (Key[KEY_INPUT_DOWN] == 1) {
									if (SelectY == 462) { SelectY = 498; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
									else if (SelectY == 498) { SelectY = 534; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
									else if (SelectY == 534) { SelectY = 570; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
								}
								else if (Key[KEY_INPUT_UP] == 1) {
									if (SelectY == 570) { SelectY = 534; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
									else if (SelectY == 534) { SelectY = 498; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
									else if (SelectY == 498) { SelectY = 462; PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); }
								}
								else if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) {
									if (SelectY == 462) {
										PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
										while (TurnEnd == FALSE) {
											ClearDrawScreen();
											DrawGraph(0, 0, EncountScreen, FALSE);
											DrawGraph(0, 444, BattleGraph[0], TRUE);
											DrawGraph(193, 444, BattleGraph[1], TRUE);
											DrawModiGraph(18, 462, 173, 462, 173, 462 + 36, 18, 462 + 36, SelectGraph, TRUE);
											SetDrawBlendMode(DX_BLENDMODE_ALPHA, Pal);
											DrawModiGraph(210, 462, 498, 462, 498, 498, 210, 498, SelectGraph, TRUE);
											if (Pal == 255) Flag = 1;
											else if (Pal == 129) Flag = 0;

											if (Flag == 1) Pal = Pal - 6;
											else if (Flag == 0) Pal = Pal + 6;

											SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
											DrawStringToHandle(20, 467, "攻撃", White, FontMain);
											DrawStringToHandle(20, 503, "魔法", White, FontMain);
											DrawStringToHandle(20, 539, "防御", White, FontMain);
											DrawStringToHandle(20, 575, "アイテム", White, FontMain);

											DrawStringToHandle(216, 466, "スライム", White, FontMain);

											ScreenFlip();
											UpdateKey();
											if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) {
												PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
												TurnEnd = TRUE;
												do {
													ClearDrawScreen();
													DrawGraph(0, 0, EncountScreen, FALSE);
													DrawModiGraph(0, 532 - MsgBoxY, 192, 532 - MsgBoxY, 192, 536 + MsgBoxY, 0, 536 + MsgBoxY, BattleGraph[0], TRUE);
													DrawModiGraph(193, 444, 816, 444, 816, 624, 193, 624, BattleGraph[1], TRUE);

													HPBar = (float)StatusMainChar[HP] / StatusMainChar[HPMAX] * 150;
													MPBar = (float)StatusMainChar[MP] / StatusMainChar[MPMAX] * 150;
													HPBarWidth = HPBar;
													MPBarWidth = MPBar;

													if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(213, 466, White, FontMain, "%s", Name.c_str());
													else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(213, 466, Yellow, FontMain, "%s", Name.c_str());
													else if (HPBarWidth == 0) { DrawFormatStringToHandle(213, 466, Red, FontMain, "%s", Name.c_str()); DrawGraph(372, 463, IconGraph[1], TRUE); }
													DrawRectGraph(462, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
													DrawRectGraph(642, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
													DrawRectGraph(462, 490, 0, 0, HPBarWidth, 7, HPBarGraph, TRUE, FALSE);
													DrawRectGraph(642, 490, 0, 0, MPBarWidth, 7, MPBarGraph, TRUE, FALSE);
													DrawStringToHandle(461, 467, "HP", Blue, FontMain);
													DrawStringToHandle(641, 467, "MP", Blue, FontMain);
													if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(554, 467, White, FontMain, "%4d", StatusMainChar[HP]);
													else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(554, 467, Yellow, FontMain, "%4d", StatusMainChar[HP]);
													else if (HPBarWidth == 0) DrawFormatStringToHandle(554, 467, Red, FontMain, "%4d", StatusMainChar[HP]);
													if (MPBarWidth <= 186 && MPBarWidth > 56) DrawFormatStringToHandle(733, 467, White, FontMain, "%4d", StatusMainChar[MP]);
													else if (MPBarWidth <= 56 && MPBarWidth > 0) DrawFormatStringToHandle(733, 467, Yellow, FontMain, "%4d", StatusMainChar[MP]);
													else if (MPBarWidth == 0) DrawFormatStringToHandle(733, 467, Red, FontMain, "%4d", StatusMainChar[MP]);

													ScreenFlip();
													MsgBoxY = MsgBoxY - 11;
												} while (MsgBoxY >= 0);
												do {
													ClearDrawScreen();
													DrawGraph(0, 0, EncountScreen, FALSE);
													DrawModiGraph(193 - MsgBoxX, 444, 816 - MsgBoxX, 444, 816 - MsgBoxX, 624, 193 - MsgBoxX, 624, BattleGraph[1], TRUE);

													HPBar = (float)StatusMainChar[HP] / StatusMainChar[HPMAX] * 150;
													MPBar = (float)StatusMainChar[MP] / StatusMainChar[MPMAX] * 150;
													HPBarWidth = HPBar;
													MPBarWidth = MPBar;

													if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(213 - MsgBoxX, 466, White, FontMain, "%s", Name.c_str());
													else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(213 - MsgBoxX, 466, Yellow, FontMain, "%s", Name.c_str());
													else if (HPBarWidth == 0) { DrawFormatStringToHandle(213 - MsgBoxX, 466, Red, FontMain, "%s", Name.c_str()); DrawGraph(372 - MsgBoxX, 463, IconGraph[1], TRUE); }
													DrawRectGraph(462 - MsgBoxX, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
													DrawRectGraph(642 - MsgBoxX, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
													DrawRectGraph(462 - MsgBoxX, 490, 0, 0, HPBarWidth, 7, HPBarGraph, TRUE, FALSE);
													DrawRectGraph(642 - MsgBoxX, 490, 0, 0, MPBarWidth, 7, MPBarGraph, TRUE, FALSE);
													DrawStringToHandle(461 - MsgBoxX, 467, "HP", Blue, FontMain);
													DrawStringToHandle(641 - MsgBoxX, 467, "MP", Blue, FontMain);
													if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(554 - MsgBoxX, 467, White, FontMain, "%4d", StatusMainChar[HP]);
													else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(554 - MsgBoxX, 467, Yellow, FontMain, "%4d", StatusMainChar[HP]);
													else if (HPBarWidth == 0) DrawFormatStringToHandle(554 - MsgBoxX, 467, Red, FontMain, "%4d", StatusMainChar[HP]);
													if (MPBarWidth <= 186 && MPBarWidth > 56) DrawFormatStringToHandle(733 - MsgBoxX, 467, White, FontMain, "%4d", StatusMainChar[MP]);
													else if (MPBarWidth <= 56 && MPBarWidth > 0) DrawFormatStringToHandle(733 - MsgBoxX, 467, Yellow, FontMain, "%4d", StatusMainChar[MP]);
													else if (MPBarWidth == 0) DrawFormatStringToHandle(733 - MsgBoxX, 467, Red, FontMain, "%4d", StatusMainChar[MP]);

													ScreenFlip();
													MsgBoxX = MsgBoxX + 16;
												} while (MsgBoxX <= 96);
												MsgBoxX = 96;
												break;
											}
											else if (Key[KEY_INPUT_ESCAPE] == 1 || Key[KEY_INPUT_X] == 1) {
												PlaySoundMem(SE[CANCEL], DX_PLAYTYPE_BACK);
												break;
											}

											if (ProcessMessage() < 0) break;
										}
									}
									else if (SelectY == 498) {
										PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
										while (1) {
											ClearDrawScreen();
											DrawGraph(0, 0, EncountScreen, FALSE);
											DrawGraph(0, 444, BattleGraph[0], TRUE);
											DrawGraph(193, 444, BattleGraph[1], TRUE);
											DrawGraph(0, 0, BattleGraph[2], TRUE);
											DrawModiGraph(18, 498, 173, 498, 173, 498 + 36, 18, 498 + 36, SelectGraph, TRUE);
											SetDrawBlendMode(DX_BLENDMODE_ALPHA, Pal);
											DrawModiGraph(18, 126, 385, 126, 385, 126 + 36, 18, 126 + 36, SelectGraph, TRUE);
											if (Pal == 255) Flag = 1;
											else if (Pal == 129) Flag = 0;

											if (Flag == 1) Pal = Pal - 6;
											else if (Flag == 0) Pal = Pal + 6;

											SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
											DrawStringToHandle(20, 467, "攻撃", White, FontMain);
											DrawStringToHandle(20, 503, "魔法", White, FontMain);
											DrawStringToHandle(20, 539, "防御", White, FontMain);
											DrawStringToHandle(20, 575, "アイテム", White, FontMain);
											DrawModiGraph(210, 462, 798, 462, 798, 498, 210, 498, SelectGraph, TRUE);

											HPBar = (float)StatusMainChar[HP] / StatusMainChar[HPMAX] * 150;
											MPBar = (float)StatusMainChar[MP] / StatusMainChar[MPMAX] * 150;
											HPBarWidth = HPBar;
											MPBarWidth = MPBar;

											if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(213, 466, White, FontMain, "%s", Name.c_str());
											else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(213, 466, Yellow, FontMain, "%s", Name.c_str());
											else if (HPBarWidth == 0) { DrawFormatStringToHandle(213, 466, Red, FontMain, "%s", Name.c_str()); DrawGraph(372, 463, IconGraph[1], TRUE); }
											DrawRectGraph(462, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
											DrawRectGraph(642, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
											DrawRectGraph(462, 490, 0, 0, HPBarWidth, 7, HPBarGraph, TRUE, FALSE);
											DrawRectGraph(642, 490, 0, 0, MPBarWidth, 7, MPBarGraph, TRUE, FALSE);
											DrawStringToHandle(461, 467, "HP", Blue, FontMain);
											DrawStringToHandle(641, 467, "MP", Blue, FontMain);
											if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(554, 467, White, FontMain, "%4d", StatusMainChar[HP]);
											else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(554, 467, Yellow, FontMain, "%4d", StatusMainChar[HP]);
											else if (HPBarWidth == 0) DrawFormatStringToHandle(554, 467, Red, FontMain, "%4d", StatusMainChar[HP]);
											if (MPBarWidth <= 186 && MPBarWidth > 56) DrawFormatStringToHandle(733, 467, White, FontMain, "%4d", StatusMainChar[MP]);
											else if (MPBarWidth <= 56 && MPBarWidth > 0) DrawFormatStringToHandle(733, 467, Yellow, FontMain, "%4d", StatusMainChar[MP]);
											else if (MPBarWidth == 0) DrawFormatStringToHandle(733, 467, Red, FontMain, "%4d", StatusMainChar[MP]);

											ScreenFlip();
											UpdateKey();
											if (Key[KEY_INPUT_ESCAPE] == 1 || Key[KEY_INPUT_X] == 1) {
												PlaySoundMem(SE[CANCEL], DX_PLAYTYPE_BACK);
												break;
											}

											if (ProcessMessage() < 0) break;
										}
									}
									else if (SelectY == 534) {
										PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
										Defence = StatusMainChar[DEF] * 2;
										NoAttack = TRUE;
										TurnEnd = TRUE;
										do {
											ClearDrawScreen();
											DrawGraph(0, 0, EncountScreen, FALSE);
											DrawModiGraph(0, 532 - MsgBoxY, 192, 532 - MsgBoxY, 192, 536 + MsgBoxY, 0, 536 + MsgBoxY, BattleGraph[0], TRUE);
											DrawModiGraph(193, 444, 816, 444, 816, 624, 193, 624, BattleGraph[1], TRUE);

											HPBar = (float)StatusMainChar[HP] / StatusMainChar[HPMAX] * 150;
											MPBar = (float)StatusMainChar[MP] / StatusMainChar[MPMAX] * 150;
											HPBarWidth = HPBar;
											MPBarWidth = MPBar;

											if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(213, 466, White, FontMain, "%s", Name.c_str());
											else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(213, 466, Yellow, FontMain, "%s", Name.c_str());
											else if (HPBarWidth == 0) { DrawFormatStringToHandle(213, 466, Red, FontMain, "%s", Name.c_str()); DrawGraph(372, 463, IconGraph[1], TRUE); }
											DrawRectGraph(462, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
											DrawRectGraph(642, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
											DrawRectGraph(462, 490, 0, 0, HPBarWidth, 7, HPBarGraph, TRUE, FALSE);
											DrawRectGraph(642, 490, 0, 0, MPBarWidth, 7, MPBarGraph, TRUE, FALSE);
											DrawStringToHandle(461, 467, "HP", Blue, FontMain);
											DrawStringToHandle(641, 467, "MP", Blue, FontMain);
											if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(554, 467, White, FontMain, "%4d", StatusMainChar[HP]);
											else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(554, 467, Yellow, FontMain, "%4d", StatusMainChar[HP]);
											else if (HPBarWidth == 0) DrawFormatStringToHandle(554, 467, Red, FontMain, "%4d", StatusMainChar[HP]);
											if (MPBarWidth <= 186 && MPBarWidth > 56) DrawFormatStringToHandle(733, 467, White, FontMain, "%4d", StatusMainChar[MP]);
											else if (MPBarWidth <= 56 && MPBarWidth > 0) DrawFormatStringToHandle(733, 467, Yellow, FontMain, "%4d", StatusMainChar[MP]);
											else if (MPBarWidth == 0) DrawFormatStringToHandle(733, 467, Red, FontMain, "%4d", StatusMainChar[MP]);

											ScreenFlip();
											MsgBoxY = MsgBoxY - 11;
										} while (MsgBoxY >= 0);
										do {
											ClearDrawScreen();
											DrawGraph(0, 0, EncountScreen, FALSE);
											DrawModiGraph(193 - MsgBoxX, 444, 816 - MsgBoxX, 444, 816 - MsgBoxX, 624, 193 - MsgBoxX, 624, BattleGraph[1], TRUE);

											HPBar = (float)StatusMainChar[HP] / StatusMainChar[HPMAX] * 150;
											MPBar = (float)StatusMainChar[MP] / StatusMainChar[MPMAX] * 150;
											HPBarWidth = HPBar;
											MPBarWidth = MPBar;

											if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(213 - MsgBoxX, 466, White, FontMain, "%s", Name.c_str());
											else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(213 - MsgBoxX, 466, Yellow, FontMain, "%s", Name.c_str());
											else if (HPBarWidth == 0) { DrawFormatStringToHandle(213 - MsgBoxX, 466, Red, FontMain, "%s", Name.c_str()); DrawGraph(372 - MsgBoxX, 463, IconGraph[1], TRUE); }
											DrawRectGraph(462 - MsgBoxX, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
											DrawRectGraph(642 - MsgBoxX, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
											DrawRectGraph(462 - MsgBoxX, 490, 0, 0, HPBarWidth, 7, HPBarGraph, TRUE, FALSE);
											DrawRectGraph(642 - MsgBoxX, 490, 0, 0, MPBarWidth, 7, MPBarGraph, TRUE, FALSE);
											DrawStringToHandle(461 - MsgBoxX, 467, "HP", Blue, FontMain);
											DrawStringToHandle(641 - MsgBoxX, 467, "MP", Blue, FontMain);
											if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(554 - MsgBoxX, 467, White, FontMain, "%4d", StatusMainChar[HP]);
											else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(554 - MsgBoxX, 467, Yellow, FontMain, "%4d", StatusMainChar[HP]);
											else if (HPBarWidth == 0) DrawFormatStringToHandle(554 - MsgBoxX, 467, Red, FontMain, "%4d", StatusMainChar[HP]);
											if (MPBarWidth <= 186 && MPBarWidth > 56) DrawFormatStringToHandle(733 - MsgBoxX, 467, White, FontMain, "%4d", StatusMainChar[MP]);
											else if (MPBarWidth <= 56 && MPBarWidth > 0) DrawFormatStringToHandle(733 - MsgBoxX, 467, Yellow, FontMain, "%4d", StatusMainChar[MP]);
											else if (MPBarWidth == 0) DrawFormatStringToHandle(733 - MsgBoxX, 467, Red, FontMain, "%4d", StatusMainChar[MP]);

											ScreenFlip();
											MsgBoxX = MsgBoxX + 16;
										} while (MsgBoxX <= 96);
										MsgBoxX = 96;
									}
									else if (SelectY == 570) {
										PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
										while (1) {
											ClearDrawScreen();
											DrawGraph(0, 0, EncountScreen, FALSE);
											DrawGraph(0, 444, BattleGraph[0], TRUE);
											DrawGraph(193, 444, BattleGraph[1], TRUE);
											DrawGraph(0, 0, BattleGraph[2], TRUE);
											DrawModiGraph(18, 570, 173, 570, 173, 570 + 36, 18, 570 + 36, SelectGraph, TRUE);
											SetDrawBlendMode(DX_BLENDMODE_ALPHA, Pal);
											DrawModiGraph(18, 126, 385, 126, 385, 126 + 36, 18, 126 + 36, SelectGraph, TRUE);
											if (Pal == 255) Flag = 1;
											else if (Pal == 129) Flag = 0;

											if (Flag == 1) Pal = Pal - 6;
											else if (Flag == 0) Pal = Pal + 6;

											SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
											DrawStringToHandle(20, 467, "攻撃", White, FontMain);
											DrawStringToHandle(20, 503, "魔法", White, FontMain);
											DrawStringToHandle(20, 539, "防御", White, FontMain);
											DrawStringToHandle(20, 575, "アイテム", White, FontMain);
											DrawModiGraph(210, 462, 798, 462, 798, 498, 210, 498, SelectGraph, TRUE);

											HPBar = (float)StatusMainChar[HP] / StatusMainChar[HPMAX] * 150;
											MPBar = (float)StatusMainChar[MP] / StatusMainChar[MPMAX] * 150;
											HPBarWidth = HPBar;
											MPBarWidth = MPBar;

											if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(213, 466, White, FontMain, "%s", Name.c_str());
											else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(213, 466, Yellow, FontMain, "%s", Name.c_str());
											else if (HPBarWidth == 0) { DrawFormatStringToHandle(213, 466, Red, FontMain, "%s", Name.c_str()); DrawGraph(372, 463, IconGraph[1], TRUE); }
											DrawRectGraph(462, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
											DrawRectGraph(642, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
											DrawRectGraph(462, 490, 0, 0, HPBarWidth, 7, HPBarGraph, TRUE, FALSE);
											DrawRectGraph(642, 490, 0, 0, MPBarWidth, 7, MPBarGraph, TRUE, FALSE);
											DrawStringToHandle(461, 467, "HP", Blue, FontMain);
											DrawStringToHandle(641, 467, "MP", Blue, FontMain);
											if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(554, 467, White, FontMain, "%4d", StatusMainChar[HP]);
											else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(554, 467, Yellow, FontMain, "%4d", StatusMainChar[HP]);
											else if (HPBarWidth == 0) DrawFormatStringToHandle(554, 467, Red, FontMain, "%4d", StatusMainChar[HP]);
											if (MPBarWidth <= 186 && MPBarWidth > 56) DrawFormatStringToHandle(733, 467, White, FontMain, "%4d", StatusMainChar[MP]);
											else if (MPBarWidth <= 56 && MPBarWidth > 0) DrawFormatStringToHandle(733, 467, Yellow, FontMain, "%4d", StatusMainChar[MP]);
											else if (MPBarWidth == 0) DrawFormatStringToHandle(733, 467, Red, FontMain, "%4d", StatusMainChar[MP]);

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
									do {
										ClearDrawScreen();
										DrawGraph(0, 0, EncountScreen, FALSE);
										DrawModiGraph(0, 532 - MsgBoxY, 192, 532 - MsgBoxY, 192, 536 + MsgBoxY, 0, 536 + MsgBoxY, BattleGraph[0], TRUE);
										DrawGraph(193, 444, BattleGraph[1], TRUE);

										HPBar = (float)StatusMainChar[HP] / StatusMainChar[HPMAX] * 150;
										MPBar = (float)StatusMainChar[MP] / StatusMainChar[MPMAX] * 150;
										HPBarWidth = HPBar;
										MPBarWidth = MPBar;

										if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(213, 466, White, FontMain, "%s", Name.c_str());
										else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(213, 466, Yellow, FontMain, "%s", Name.c_str());
										else if (HPBarWidth == 0) { DrawFormatStringToHandle(213, 466, Red, FontMain, "%s", Name.c_str()); DrawGraph(372, 463, IconGraph[1], TRUE); }
										DrawRectGraph(462, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
										DrawRectGraph(642, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
										DrawRectGraph(462, 490, 0, 0, HPBarWidth, 7, HPBarGraph, TRUE, FALSE);
										DrawRectGraph(642, 490, 0, 0, MPBarWidth, 7, MPBarGraph, TRUE, FALSE);
										DrawStringToHandle(461, 467, "HP", Blue, FontMain);
										DrawStringToHandle(641, 467, "MP", Blue, FontMain);
										if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(554, 467, White, FontMain, "%4d", StatusMainChar[HP]);
										else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(554, 467, Yellow, FontMain, "%4d", StatusMainChar[HP]);
										else if (HPBarWidth == 0) DrawFormatStringToHandle(554, 467, Red, FontMain, "%4d", StatusMainChar[HP]);
										if (MPBarWidth <= 186 && MPBarWidth > 56) DrawFormatStringToHandle(733, 467, White, FontMain, "%4d", StatusMainChar[MP]);
										else if (MPBarWidth <= 56 && MPBarWidth > 0) DrawFormatStringToHandle(733, 467, Yellow, FontMain, "%4d", StatusMainChar[MP]);
										else if (MPBarWidth == 0) DrawFormatStringToHandle(733, 467, Red, FontMain, "%4d", StatusMainChar[MP]);

										ScreenFlip();
										MsgBoxY = MsgBoxY - 11;
									} while (MsgBoxY >= 0);
									do {
										ClearDrawScreen();
										DrawGraph(0, 0, EncountScreen, FALSE);
										DrawModiGraph(0, 532 - MsgBoxY, 192, 532 - MsgBoxY, 192, 536 + MsgBoxY, 0, 536 + MsgBoxY, BattleGraph[0], TRUE);
										DrawGraph(193, 444, BattleGraph[1], TRUE);

										HPBar = (float)StatusMainChar[HP] / StatusMainChar[HPMAX] * 150;
										MPBar = (float)StatusMainChar[MP] / StatusMainChar[MPMAX] * 150;
										HPBarWidth = HPBar;
										MPBarWidth = MPBar;

										if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(213, 466, White, FontMain, "%s", Name.c_str());
										else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(213, 466, Yellow, FontMain, "%s", Name.c_str());
										else if (HPBarWidth == 0) { DrawFormatStringToHandle(213, 466, Red, FontMain, "%s", Name.c_str()); DrawGraph(372, 463, IconGraph[1], TRUE); }
										DrawRectGraph(462, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
										DrawRectGraph(642, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
										DrawRectGraph(462, 490, 0, 0, HPBarWidth, 7, HPBarGraph, TRUE, FALSE);
										DrawRectGraph(642, 490, 0, 0, MPBarWidth, 7, MPBarGraph, TRUE, FALSE);
										DrawStringToHandle(461, 467, "HP", Blue, FontMain);
										DrawStringToHandle(641, 467, "MP", Blue, FontMain);
										if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(554, 467, White, FontMain, "%4d", StatusMainChar[HP]);
										else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(554, 467, Yellow, FontMain, "%4d", StatusMainChar[HP]);
										else if (HPBarWidth == 0) DrawFormatStringToHandle(554, 467, Red, FontMain, "%4d", StatusMainChar[HP]);
										if (MPBarWidth <= 186 && MPBarWidth > 56) DrawFormatStringToHandle(733, 467, White, FontMain, "%4d", StatusMainChar[MP]);
										else if (MPBarWidth <= 56 && MPBarWidth > 0) DrawFormatStringToHandle(733, 467, Yellow, FontMain, "%4d", StatusMainChar[MP]);
										else if (MPBarWidth == 0) DrawFormatStringToHandle(733, 467, Red, FontMain, "%4d", StatusMainChar[MP]);

										ScreenFlip();
										MsgBoxY = MsgBoxY + 11;
									} while (MsgBoxY <= 88);
									SelectY = 462;
									break;
								}

								if (ProcessMessage() < 0) break;
							}
						}
						else if (SelectY == 498) {
							PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
							if (Percent(mt) >= 60) RunAway = TRUE;
							else if (Percent(mt) < 60) RunAway = FALSE;
							
							if (RunAway == TRUE) {
								MsgBoxY = 88;
								do {
									ClearDrawScreen();
									DrawGraph(0, 0, EncountScreen, FALSE);
									DrawModiGraph(0, 532 - MsgBoxY, 192, 532 - MsgBoxY, 192, 536 + MsgBoxY, 0, 536 + MsgBoxY, BattleGraph[0], TRUE);
									DrawModiGraph(193, 532 - MsgBoxY, 816, 532 - MsgBoxY, 816, 536 + MsgBoxY, 193, 536 + MsgBoxY, BattleGraph[1], TRUE);
									ScreenFlip();
									MsgBoxY = MsgBoxY - 11;
								} while (MsgBoxY >= 0);
								MsgBoxY = 0;
								do {
									ClearDrawScreen();
									DrawGraph(0, 0, EncountScreen, FALSE);
									DrawModiGraph(0, 532 - MsgBoxY, 816, 532 - MsgBoxY, 816, 536 + MsgBoxY, 0, 536 + MsgBoxY, MsgGraph, TRUE);
									ScreenFlip();
									MsgBoxY = MsgBoxY + 8;
								} while (MsgBoxY <= 88);
								int i = 0;
								do {
									DrawFormatStringToHandle(20 + (i * 14), 465, White, FontMain, "%c%c", VSMsg2[i], VSMsg2[i + 1]);
									ScreenFlip();
									WaitTimer(15);
									i = i + 2;
									if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) break;
								} while (i + 1 <= 24);
								int j = 0;
								while (1) {
									ClearDrawScreen();
									DrawGraph(0, 0, EncountScreen, FALSE);
									DrawGraph(0, 444, MsgGraph, TRUE);
									DrawFormatStringToHandle(20, 465, White, FontMain, "%s", VSMsg[1].c_str());
									if (j <= 15) DrawGraph(396, 600, CursorGraph[0], TRUE);
									else if (j > 15 && j <= 30) DrawGraph(396, 600, CursorGraph[1], TRUE);
									else if (j > 30 && j <= 45) DrawGraph(396, 600, CursorGraph[2], TRUE);
									else if (j > 45) { DrawGraph(396, 600, CursorGraph[3], TRUE); j = 0; }
									ScreenFlip();
									j++;
									UpdateKey();
									if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) break;
								}
								do {
									ClearDrawScreen();
									DrawGraph(0, 0, EncountScreen, FALSE);
									DrawModiGraph(0, 532 - MsgBoxY, 816, 532 - MsgBoxY, 816, 536 + MsgBoxY, 0, 536 + MsgBoxY, MsgGraph, TRUE);
									ScreenFlip();
									MsgBoxY = MsgBoxY - 11;
								} while (MsgBoxY >= 0);
								MsgBoxY = 0;
								Bright = 255;
								float Vol = 1.0;
								do {
									ClearDrawScreen();
									SetDrawBright(Bright, Bright, Bright);
									ChangeVolumeSoundMem((float)BGMVolume * Vol, BGM[BATTLE]);
									if (Vol != 0.00) Vol = Vol - 0.04;
									DrawGraph(0, 0, BattleBackGraph[GRASS], FALSE);
									DrawGraph(0, 0, BattleBackOverGraph[GRASSOVER], TRUE);
									DrawGraph(344, 330, MobGraph[SLIME], TRUE);
									ScreenFlip();
									Bright = Bright - 10;
								} while (Bright >= 0);
								StopSoundMem(BGM[BATTLE]);
								ChangeVolumeSoundMem(BGMVolume, BGM[BATTLE]);
								SetDrawBright(255, 255, 255);
								break;
							}
							else if (RunAway == FALSE) {
								MsgBoxY = 88;
								do {
									ClearDrawScreen();
									DrawGraph(0, 0, EncountScreen, FALSE);
									DrawModiGraph(0, 532 - MsgBoxY, 192, 532 - MsgBoxY, 192, 536 + MsgBoxY, 0, 536 + MsgBoxY, BattleGraph[0], TRUE);
									DrawModiGraph(193, 532 - MsgBoxY, 816, 532 - MsgBoxY, 816, 536 + MsgBoxY, 193, 536 + MsgBoxY, BattleGraph[1], TRUE);
									ScreenFlip();
									MsgBoxY = MsgBoxY - 11;
								} while (MsgBoxY >= 0);
								MsgBoxY = 0;
								do {
									ClearDrawScreen();
									DrawGraph(0, 0, EncountScreen, FALSE);
									DrawModiGraph(0, 532 - MsgBoxY, 816, 532 - MsgBoxY, 816, 536 + MsgBoxY, 0, 536 + MsgBoxY, MsgGraph, TRUE);
									ScreenFlip();
									MsgBoxY = MsgBoxY + 8;
								} while (MsgBoxY <= 88);
								int i = 0;
								do {
									DrawFormatStringToHandle(20 + (i * 14), 465, White, FontMain, "%c%c", VSMsg2[i], VSMsg2[i + 1]);
									ScreenFlip();
									WaitTimer(15);
									i = i + 2;
								} while (i + 1 <= 24);
								WaitTimer(500);
								i = 0;
								do {
									DrawFormatStringToHandle(20, 465, White, FontMain, "%s", VSMsg[1].c_str());
									DrawFormatStringToHandle(20 + (i * 14), 501, White, FontMain, "%c%c", VSMsg3[i], VSMsg3[i + 1]);
									ScreenFlip();
									WaitTimer(15);
									i = i + 2;
								} while (i + 1 <= 24);
								int j = 0;
								while (1) {
									ClearDrawScreen();
									DrawGraph(0, 0, EncountScreen, FALSE);
									DrawGraph(0, 444, MsgGraph, TRUE);
									DrawFormatStringToHandle(20, 465, White, FontMain, "%s", VSMsg[1].c_str());
									DrawFormatStringToHandle(20, 501, White, FontMain, "%s", VSMsg[2].c_str());
									if (j <= 15) DrawGraph(396, 600, CursorGraph[0], TRUE);
									else if (j > 15 && j <= 30) DrawGraph(396, 600, CursorGraph[1], TRUE);
									else if (j > 30 && j <= 45) DrawGraph(396, 600, CursorGraph[2], TRUE);
									else if (j > 45) { DrawGraph(396, 600, CursorGraph[3], TRUE); j = 0; }
									ScreenFlip();
									j++;
									UpdateKey();
									if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) break;
								}
								do {
									ClearDrawScreen();
									DrawGraph(0, 0, EncountScreen, FALSE);
									DrawModiGraph(0, 532 - MsgBoxY, 816, 532 - MsgBoxY, 816, 536 + MsgBoxY, 0, 536 + MsgBoxY, MsgGraph, TRUE);
									ScreenFlip();
									MsgBoxY = MsgBoxY - 11;
								} while (MsgBoxY >= 0);
								MsgBoxY = 0;
								do {
									ClearDrawScreen();
									DrawGraph(0, 0, EncountScreen, FALSE);
									DrawModiGraph(193 - 97, 532 - MsgBoxY, 816 - 97, 532 - MsgBoxY, 816 - 97, 536 + MsgBoxY, 193 - 97, 536 + MsgBoxY, BattleGraph[1], TRUE);
									ScreenFlip();
									MsgBoxY = MsgBoxY + 11;
								} while (MsgBoxY <= 88);
								MsgBoxY = 88;
								BattleAssist();
								ScreenFlip();
								WaitTimer(800);
								i = 0;
								BattleDamage = MobStatus[MOBATK] + AddDamage(mt) - Defence;
								if (BattleDamage < 0) BattleDamage = 0;
								MobY = 330;
								i = 0;
								do {
									ClearDrawScreen();
									DrawGraph(0, 0, BattleBackGraph[GRASS], FALSE);
									DrawGraph(0, 0, BattleBackOverGraph[GRASSOVER], TRUE);
									DrawGraph(344, MobY + i, MobGraph[SLIME], TRUE);
									DrawModiGraph(193 - 97, 444, 816 - 97, 444, 816 - 97, 624, 193 - 97, 624, BattleGraph[1], TRUE);

									HPBar = (float)StatusMainChar[HP] / StatusMainChar[HPMAX] * 150;
									MPBar = (float)StatusMainChar[MP] / StatusMainChar[MPMAX] * 150;
									HPBarWidth = HPBar;
									MPBarWidth = MPBar;

									if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(213 - 97, 466, White, FontMain, "%s", Name.c_str());
									else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(213 - 97, 466, Yellow, FontMain, "%s", Name.c_str());
									else if (HPBarWidth == 0) { DrawFormatStringToHandle(213 - 97, 466, Red, FontMain, "%s", Name.c_str()); DrawGraph(372, 463, IconGraph[1], TRUE); }
									DrawRectGraph(462 - 97, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
									DrawRectGraph(642 - 97, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
									DrawRectGraph(462 - 97, 490, 0, 0, HPBarWidth, 7, HPBarGraph, TRUE, FALSE);
									DrawRectGraph(642 - 97, 490, 0, 0, MPBarWidth, 7, MPBarGraph, TRUE, FALSE);
									DrawStringToHandle(461 - 97, 467, "HP", Blue, FontMain);
									DrawStringToHandle(641 - 97, 467, "MP", Blue, FontMain);
									if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(554 - 97, 467, White, FontMain, "%4d", StatusMainChar[HP]);
									else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(554 - 97, 467, Yellow, FontMain, "%4d", StatusMainChar[HP]);
									else if (HPBarWidth == 0) DrawFormatStringToHandle(554 - 97, 467, Red, FontMain, "%4d", StatusMainChar[HP]);
									if (MPBarWidth <= 186 && MPBarWidth > 56) DrawFormatStringToHandle(733 - 97, 467, White, FontMain, "%4d", StatusMainChar[MP]);
									else if (MPBarWidth <= 56 && MPBarWidth > 0) DrawFormatStringToHandle(733 - 97, 467, Yellow, FontMain, "%4d", StatusMainChar[MP]);
									else if (MPBarWidth == 0) DrawFormatStringToHandle(733 - 97, 467, Red, FontMain, "%4d", StatusMainChar[MP]);

									ScreenFlip();
									i = i + 2;
								} while (i <= 20);
								i = 20;
								do {
									ClearDrawScreen();
									DrawGraph(0, 0, BattleBackGraph[GRASS], FALSE);
									DrawGraph(0, 0, BattleBackOverGraph[GRASSOVER], TRUE);
									DrawGraph(344, MobY + i, MobGraph[SLIME], TRUE);
									DrawModiGraph(193 - 97, 444, 816 - 97, 444, 816 - 97, 624, 193 - 97, 624, BattleGraph[1], TRUE);

									HPBar = (float)StatusMainChar[HP] / StatusMainChar[HPMAX] * 150;
									MPBar = (float)StatusMainChar[MP] / StatusMainChar[MPMAX] * 150;
									HPBarWidth = HPBar;
									MPBarWidth = MPBar;

									if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(213 - 97, 466, White, FontMain, "%s", Name.c_str());
									else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(213 - 97, 466, Yellow, FontMain, "%s", Name.c_str());
									else if (HPBarWidth == 0) { DrawFormatStringToHandle(213 - 97, 466, Red, FontMain, "%s", Name.c_str()); DrawGraph(372, 463, IconGraph[1], TRUE); }
									DrawRectGraph(462 - 97, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
									DrawRectGraph(642 - 97, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
									DrawRectGraph(462 - 97, 490, 0, 0, HPBarWidth, 7, HPBarGraph, TRUE, FALSE);
									DrawRectGraph(642 - 97, 490, 0, 0, MPBarWidth, 7, MPBarGraph, TRUE, FALSE);
									DrawStringToHandle(461 - 97, 467, "HP", Blue, FontMain);
									DrawStringToHandle(641 - 97, 467, "MP", Blue, FontMain);
									if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(554 - 97, 467, White, FontMain, "%4d", StatusMainChar[HP]);
									else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(554 - 97, 467, Yellow, FontMain, "%4d", StatusMainChar[HP]);
									else if (HPBarWidth == 0) DrawFormatStringToHandle(554 - 97, 467, Red, FontMain, "%4d", StatusMainChar[HP]);
									if (MPBarWidth <= 186 && MPBarWidth > 56) DrawFormatStringToHandle(733 - 97, 467, White, FontMain, "%4d", StatusMainChar[MP]);
									else if (MPBarWidth <= 56 && MPBarWidth > 0) DrawFormatStringToHandle(733 - 97, 467, Yellow, FontMain, "%4d", StatusMainChar[MP]);
									else if (MPBarWidth == 0) DrawFormatStringToHandle(733 - 97, 467, Red, FontMain, "%4d", StatusMainChar[MP]);

									ScreenFlip();
									i = i - 2;
								} while (i >= 0);
								WaitTimer(500);
								PlaySoundMem(SE[HIT2], DX_PLAYTYPE_BACK);
								WaitTimer(1000);
								i = 0;
								do {
									ClearDrawScreen();
									StatusMainChar[HP] = StatusMainChar[HP] - 1;
									BattleAssist();
									ScreenFlip();
									i++;
									if (StatusMainChar[HP] <= 0) { StatusMainChar[HP] = 0; break; }
								} while (i <= BattleDamage);
								if (StatusMainChar[HP] == 0) GameOver = TRUE;
								if (GameOver == FALSE) {
									WaitTimer(500);
									MsgBoxX = 96;
									do {
										ClearDrawScreen();
										DrawGraph(0, 0, EncountScreen, FALSE);
										DrawModiGraph(193 - MsgBoxX, 444, 816 - MsgBoxX, 444, 816 - MsgBoxX, 624, 193 - MsgBoxX, 624, BattleGraph[1], TRUE);

										HPBar = (float)StatusMainChar[HP] / StatusMainChar[HPMAX] * 150;
										MPBar = (float)StatusMainChar[MP] / StatusMainChar[MPMAX] * 150;
										HPBarWidth = HPBar;
										MPBarWidth = MPBar;

										if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(213 - MsgBoxX, 466, White, FontMain, "%s", Name.c_str());
										else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(213 - MsgBoxX, 466, Yellow, FontMain, "%s", Name.c_str());
										else if (HPBarWidth == 0) { DrawFormatStringToHandle(213 - MsgBoxX, 466, Red, FontMain, "%s", Name.c_str()); DrawGraph(372, 463, IconGraph[1], TRUE); }
										DrawRectGraph(462 - MsgBoxX, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
										DrawRectGraph(642 - MsgBoxX, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
										DrawRectGraph(462 - MsgBoxX, 490, 0, 0, HPBarWidth, 7, HPBarGraph, TRUE, FALSE);
										DrawRectGraph(642 - MsgBoxX, 490, 0, 0, MPBarWidth, 7, MPBarGraph, TRUE, FALSE);
										DrawStringToHandle(461 - MsgBoxX, 467, "HP", Blue, FontMain);
										DrawStringToHandle(641 - MsgBoxX, 467, "MP", Blue, FontMain);
										if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(554 - MsgBoxX, 467, White, FontMain, "%4d", StatusMainChar[HP]);
										else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(554 - MsgBoxX, 467, Yellow, FontMain, "%4d", StatusMainChar[HP]);
										else if (HPBarWidth == 0) DrawFormatStringToHandle(554 - MsgBoxX, 467, Red, FontMain, "%4d", StatusMainChar[HP]);
										if (MPBarWidth <= 186 && MPBarWidth > 56) DrawFormatStringToHandle(733 - MsgBoxX, 467, White, FontMain, "%4d", StatusMainChar[MP]);
										else if (MPBarWidth <= 56 && MPBarWidth > 0) DrawFormatStringToHandle(733 - MsgBoxX, 467, Yellow, FontMain, "%4d", StatusMainChar[MP]);
										else if (MPBarWidth == 0) DrawFormatStringToHandle(733 - MsgBoxX, 467, Red, FontMain, "%4d", StatusMainChar[MP]);

										ScreenFlip();
										MsgBoxX = MsgBoxX - 16;
									} while (MsgBoxX >= 0);
									MsgBoxX = 0;
									MsgBoxY = 0;
									do {
										ClearDrawScreen();
										DrawGraph(0, 0, EncountScreen, FALSE);
										DrawModiGraph(0, 532 - MsgBoxY, 192, 532 - MsgBoxY, 192, 536 + MsgBoxY, 0, 536 + MsgBoxY, BattleGraph[0], TRUE);
										DrawModiGraph(193, 444, 816, 444, 816, 624, 193, 624, BattleGraph[1], TRUE);

										HPBar = (float)StatusMainChar[HP] / StatusMainChar[HPMAX] * 150;
										MPBar = (float)StatusMainChar[MP] / StatusMainChar[MPMAX] * 150;
										HPBarWidth = HPBar;
										MPBarWidth = MPBar;

										if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(213, 466, White, FontMain, "%s", Name.c_str());
										else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(213, 466, Yellow, FontMain, "%s", Name.c_str());
										else if (HPBarWidth == 0) { DrawFormatStringToHandle(213, 466, Red, FontMain, "%s", Name.c_str()); DrawGraph(372, 463, IconGraph[1], TRUE); }
										DrawRectGraph(462, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
										DrawRectGraph(642, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
										DrawRectGraph(462, 490, 0, 0, HPBarWidth, 7, HPBarGraph, TRUE, FALSE);
										DrawRectGraph(642, 490, 0, 0, MPBarWidth, 7, MPBarGraph, TRUE, FALSE);
										DrawStringToHandle(461, 467, "HP", Blue, FontMain);
										DrawStringToHandle(641, 467, "MP", Blue, FontMain);
										if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(554, 467, White, FontMain, "%4d", StatusMainChar[HP]);
										else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(554, 467, Yellow, FontMain, "%4d", StatusMainChar[HP]);
										else if (HPBarWidth == 0) DrawFormatStringToHandle(554, 467, Red, FontMain, "%4d", StatusMainChar[HP]);
										if (MPBarWidth <= 186 && MPBarWidth > 56) DrawFormatStringToHandle(733, 467, White, FontMain, "%4d", StatusMainChar[MP]);
										else if (MPBarWidth <= 56 && MPBarWidth > 0) DrawFormatStringToHandle(733, 467, Yellow, FontMain, "%4d", StatusMainChar[MP]);
										else if (MPBarWidth == 0) DrawFormatStringToHandle(733, 467, Red, FontMain, "%4d", StatusMainChar[MP]);

										ScreenFlip();
										MsgBoxY = MsgBoxY + 11;
									} while (MsgBoxY <= 88);
									MsgBoxY = 88;
								}
								else if (GameOver == TRUE) {
									WaitTimer(2000);
									GetDrawScreenGraph(0, 0, 816, 624, EncountScreen);
									Bright = 255;
									float Vol = 1.0;
									do {
										ClearDrawScreen();
										SetDrawBright(Bright, Bright, Bright);
										ChangeVolumeSoundMem((float)BGMVolume * Vol, BGM[BATTLE]);
										if (Vol != 0.00) Vol = Vol - 0.04;
										DrawGraph(0, 0, EncountScreen, FALSE);
										ScreenFlip();
										Bright = Bright - 10;
									} while (Bright >= 0);
									StopSoundMem(BGM[BATTLE]);
									ChangeVolumeSoundMem(BGMVolume, BGM[BATTLE]);
									PlaySoundMem(BGM[GAMEOVER], DX_PLAYTYPE_LOOP);
									do {
										ClearDrawScreen();
										SetDrawBright(Bright, Bright, Bright);
										DrawGraph(0, 0, GameOverGraph, FALSE);
										ScreenFlip();
										Bright = Bright + 10;
									} while (Bright <= 255);
									SetDrawBright(255, 255, 255);
									WaitTimer(2000);
									while (1) {
										ClearDrawScreen();
										DrawGraph(0, 0, GameOverGraph, FALSE);
										ScreenFlip();
										UpdateKey();
										if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) {
											float Vol = 1.00;
											Bright = 255;
											GetDrawScreenGraph(0, 0, 816, 624, EncountScreen);
											do {
												SetDrawBright(Bright, Bright, Bright);
												ChangeVolumeSoundMem((float)BGMVolume * Vol, BGM[GAMEOVER]);
												if (Vol != 0.00) Vol = Vol - 0.04;
												DrawGraph(0, 0, EncountScreen, FALSE);
												ScreenFlip();
												Bright = Bright - 10;
											} while (Bright >= 0);
											SetDrawBright(255, 255, 255);
											StopSoundMem(BGM[GAMEOVER]);
											ChangeVolumeSoundMem(BGMVolume, BGM[GAMEOVER]);
											break;
										}
									}
								}
							}
						}
					}

					if (ProcessMessage() < 0) break;
				}
				if (RunAway == TRUE) { RunAway = FALSE; PlaySoundMem(BGM[FIELD], DX_PLAYTYPE_LOOP); break; }
				if (GameOver != TRUE) {
					TurnEnd = FALSE;
					BattleAssist();
					ScreenFlip();
					WaitTimer(800);
					int i = 0;
					if (NoAttack != TRUE) {
					PlaySoundMem(SE[HIT], DX_PLAYTYPE_BACK);
					do {
						BattleAssist();
						DrawGraph(315, 285, EffectAttack[i], TRUE);
						ScreenFlip();
						i++;
						WaitTimer(60);
					} while (i <= 4);
					MobStatus[MOBHP] = MobStatus[MOBHP] - (StatusMainChar[ATK] + AddDamage(mt));
					WaitTimer(1000);
					if (MobStatus[MOBHP] <= 0) BattleEnd = TRUE;
				}
					if (BattleEnd == FALSE) {
					BattleDamage = MobStatus[MOBATK] + AddDamage(mt) - Defence;
					if (BattleDamage < 0) BattleDamage = 0;
					MobY = 330;
					i = 0;
					do {
						ClearDrawScreen();
						DrawGraph(0, 0, BattleBackGraph[GRASS], FALSE);
						DrawGraph(0, 0, BattleBackOverGraph[GRASSOVER], TRUE);
						DrawGraph(344, MobY + i, MobGraph[SLIME], TRUE);
						DrawModiGraph(193 - 97, 444, 816 - 97, 444, 816 - 97, 624, 193 - 97, 624, BattleGraph[1], TRUE);

						HPBar = (float)StatusMainChar[HP] / StatusMainChar[HPMAX] * 150;
						MPBar = (float)StatusMainChar[MP] / StatusMainChar[MPMAX] * 150;
						HPBarWidth = HPBar;
						MPBarWidth = MPBar;

						if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(213 - 97, 466, White, FontMain, "%s", Name.c_str());
						else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(213 - 97, 466, Yellow, FontMain, "%s", Name.c_str());
						else if (HPBarWidth == 0) { DrawFormatStringToHandle(213 - 97, 466, Red, FontMain, "%s", Name.c_str()); DrawGraph(372 - 97, 463, IconGraph[1], TRUE); }
						DrawRectGraph(462 - 97, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
						DrawRectGraph(642 - 97, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
						DrawRectGraph(462 - 97, 490, 0, 0, HPBarWidth, 7, HPBarGraph, TRUE, FALSE);
						DrawRectGraph(642 - 97, 490, 0, 0, MPBarWidth, 7, MPBarGraph, TRUE, FALSE);
						DrawStringToHandle(461 - 97, 467, "HP", Blue, FontMain);
						DrawStringToHandle(641 - 97, 467, "MP", Blue, FontMain);
						if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(554 - 97, 467, White, FontMain, "%4d", StatusMainChar[HP]);
						else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(554 - 97, 467, Yellow, FontMain, "%4d", StatusMainChar[HP]);
						else if (HPBarWidth == 0) DrawFormatStringToHandle(554 - 97, 467, Red, FontMain, "%4d", StatusMainChar[HP]);
						if (MPBarWidth <= 186 && MPBarWidth > 56) DrawFormatStringToHandle(733 - 97, 467, White, FontMain, "%4d", StatusMainChar[MP]);
						else if (MPBarWidth <= 56 && MPBarWidth > 0) DrawFormatStringToHandle(733 - 97, 467, Yellow, FontMain, "%4d", StatusMainChar[MP]);
						else if (MPBarWidth == 0) DrawFormatStringToHandle(733 - 97, 467, Red, FontMain, "%4d", StatusMainChar[MP]);

						ScreenFlip();
						i = i + 2;
					} while (i <= 20);
					i = 20;
					do {
						ClearDrawScreen();
						DrawGraph(0, 0, BattleBackGraph[GRASS], FALSE);
						DrawGraph(0, 0, BattleBackOverGraph[GRASSOVER], TRUE);
						DrawGraph(344, MobY + i, MobGraph[SLIME], TRUE);
						DrawModiGraph(193 - 97, 444, 816 - 97, 444, 816 - 97, 624, 193 - 97, 624, BattleGraph[1], TRUE);

						HPBar = (float)StatusMainChar[HP] / StatusMainChar[HPMAX] * 150;
						MPBar = (float)StatusMainChar[MP] / StatusMainChar[MPMAX] * 150;
						HPBarWidth = HPBar;
						MPBarWidth = MPBar;

						if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(213 - 97, 466, White, FontMain, "%s", Name.c_str());
						else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(213 - 97, 466, Yellow, FontMain, "%s", Name.c_str());
						else if (HPBarWidth == 0) { DrawFormatStringToHandle(213 - 97, 466, Red, FontMain, "%s", Name.c_str()); DrawGraph(372 - 97, 463, IconGraph[1], TRUE); }
						DrawRectGraph(462 - 97, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
						DrawRectGraph(642 - 97, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
						DrawRectGraph(462 - 97, 490, 0, 0, HPBarWidth, 7, HPBarGraph, TRUE, FALSE);
						DrawRectGraph(642 - 97, 490, 0, 0, MPBarWidth, 7, MPBarGraph, TRUE, FALSE);
						DrawStringToHandle(461 - 97, 467, "HP", Blue, FontMain);
						DrawStringToHandle(641 - 97, 467, "MP", Blue, FontMain);
						if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(554 - 97, 467, White, FontMain, "%4d", StatusMainChar[HP]);
						else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(554 - 97, 467, Yellow, FontMain, "%4d", StatusMainChar[HP]);
						else if (HPBarWidth == 0) DrawFormatStringToHandle(554 - 97, 467, Red, FontMain, "%4d", StatusMainChar[HP]);
						if (MPBarWidth <= 186 && MPBarWidth > 56) DrawFormatStringToHandle(733 - 97, 467, White, FontMain, "%4d", StatusMainChar[MP]);
						else if (MPBarWidth <= 56 && MPBarWidth > 0) DrawFormatStringToHandle(733 - 97, 467, Yellow, FontMain, "%4d", StatusMainChar[MP]);
						else if (MPBarWidth == 0) DrawFormatStringToHandle(733 - 97, 467, Red, FontMain, "%4d", StatusMainChar[MP]);

						ScreenFlip();
						i = i - 2;
					} while (i >= 0);
					WaitTimer(500);
					PlaySoundMem(SE[HIT2], DX_PLAYTYPE_BACK);
					WaitTimer(1000);
					i = 0;
					do {
						ClearDrawScreen();
						StatusMainChar[HP] = StatusMainChar[HP] - 1;
						BattleAssist();
						ScreenFlip();
						i++;
						if (StatusMainChar[HP] <= 0) { StatusMainChar[HP] = 0; break; }
					} while (i <= BattleDamage);
					if (StatusMainChar[HP] == 0) GameOver = TRUE;
					if (GameOver == FALSE) {
						WaitTimer(500);
						do {
							ClearDrawScreen();
							DrawGraph(0, 0, EncountScreen, FALSE);
							DrawModiGraph(193 - MsgBoxX, 444, 816 - MsgBoxX, 444, 816 - MsgBoxX, 624, 193 - MsgBoxX, 624, BattleGraph[1], TRUE);

							HPBar = (float)StatusMainChar[HP] / StatusMainChar[HPMAX] * 150;
							MPBar = (float)StatusMainChar[MP] / StatusMainChar[MPMAX] * 150;
							HPBarWidth = HPBar;
							MPBarWidth = MPBar;

							if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(213 - MsgBoxX, 466, White, FontMain, "%s", Name.c_str());
							else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(213 - MsgBoxX, 466, Yellow, FontMain, "%s", Name.c_str());
							else if (HPBarWidth == 0) { DrawFormatStringToHandle(213 - MsgBoxX, 466, Red, FontMain, "%s", Name.c_str()); DrawGraph(372, 463, IconGraph[1], TRUE); }
							DrawRectGraph(462 - MsgBoxX, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
							DrawRectGraph(642 - MsgBoxX, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
							DrawRectGraph(462 - MsgBoxX, 490, 0, 0, HPBarWidth, 7, HPBarGraph, TRUE, FALSE);
							DrawRectGraph(642 - MsgBoxX, 490, 0, 0, MPBarWidth, 7, MPBarGraph, TRUE, FALSE);
							DrawStringToHandle(461 - MsgBoxX, 467, "HP", Blue, FontMain);
							DrawStringToHandle(641 - MsgBoxX, 467, "MP", Blue, FontMain);
							if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(554 - MsgBoxX, 467, White, FontMain, "%4d", StatusMainChar[HP]);
							else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(554 - MsgBoxX, 467, Yellow, FontMain, "%4d", StatusMainChar[HP]);
							else if (HPBarWidth == 0) DrawFormatStringToHandle(554 - MsgBoxX, 467, Red, FontMain, "%4d", StatusMainChar[HP]);
							if (MPBarWidth <= 186 && MPBarWidth > 56) DrawFormatStringToHandle(733 - MsgBoxX, 467, White, FontMain, "%4d", StatusMainChar[MP]);
							else if (MPBarWidth <= 56 && MPBarWidth > 0) DrawFormatStringToHandle(733 - MsgBoxX, 467, Yellow, FontMain, "%4d", StatusMainChar[MP]);
							else if (MPBarWidth == 0) DrawFormatStringToHandle(733 - MsgBoxX, 467, Red, FontMain, "%4d", StatusMainChar[MP]);

							ScreenFlip();
							MsgBoxX = MsgBoxX - 16;
						} while (MsgBoxX >= 0);
						MsgBoxX = 0;
						do {
							ClearDrawScreen();
							DrawGraph(0, 0, EncountScreen, FALSE);
							DrawModiGraph(0, 532 - MsgBoxY, 192, 532 - MsgBoxY, 192, 536 + MsgBoxY, 0, 536 + MsgBoxY, BattleGraph[0], TRUE);
							DrawModiGraph(193, 444, 816, 444, 816, 624, 193, 624, BattleGraph[1], TRUE);

							HPBar = (float)StatusMainChar[HP] / StatusMainChar[HPMAX] * 150;
							MPBar = (float)StatusMainChar[MP] / StatusMainChar[MPMAX] * 150;
							HPBarWidth = HPBar;
							MPBarWidth = MPBar;

							if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(213, 466, White, FontMain, "%s", Name.c_str());
							else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(213, 466, Yellow, FontMain, "%s", Name.c_str());
							else if (HPBarWidth == 0) { DrawFormatStringToHandle(213, 466, Red, FontMain, "%s", Name.c_str()); DrawGraph(372, 463, IconGraph[1], TRUE); }
							DrawRectGraph(462, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
							DrawRectGraph(642, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
							DrawRectGraph(462, 490, 0, 0, HPBarWidth, 7, HPBarGraph, TRUE, FALSE);
							DrawRectGraph(642, 490, 0, 0, MPBarWidth, 7, MPBarGraph, TRUE, FALSE);
							DrawStringToHandle(461, 467, "HP", Blue, FontMain);
							DrawStringToHandle(641, 467, "MP", Blue, FontMain);
							if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(554, 467, White, FontMain, "%4d", StatusMainChar[HP]);
							else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(554, 467, Yellow, FontMain, "%4d", StatusMainChar[HP]);
							else if (HPBarWidth == 0) DrawFormatStringToHandle(554, 467, Red, FontMain, "%4d", StatusMainChar[HP]);
							if (MPBarWidth <= 186 && MPBarWidth > 56) DrawFormatStringToHandle(733, 467, White, FontMain, "%4d", StatusMainChar[MP]);
							else if (MPBarWidth <= 56 && MPBarWidth > 0) DrawFormatStringToHandle(733, 467, Yellow, FontMain, "%4d", StatusMainChar[MP]);
							else if (MPBarWidth == 0) DrawFormatStringToHandle(733, 467, Red, FontMain, "%4d", StatusMainChar[MP]);

							ScreenFlip();
							MsgBoxY = MsgBoxY + 11;
						} while (MsgBoxY <= 88);
						MsgBoxY = 88;
					}
				}
					else if (BattleEnd == TRUE) {
						Money = Money + MobMoney[SLIME];
						StatusMainChar[EXP] = StatusMainChar[EXP] + MobExp[SLIME];
						if (StatusMainChar[EXP] < StatusMainChar[LV] * 50) StatusMainChar[NEXTLV] = StatusMainChar[LV] * 50 - StatusMainChar[EXP];
						else if (StatusMainChar[EXP] >= StatusMainChar[LV] * 50) {
							LVUP = 0;
							do {
								StatusMainChar[NEXTLV] = StatusMainChar[EXP] - StatusMainChar[LV] * 50;
								StatusMainChar[LV] = StatusMainChar[LV] + 1;
								LVUP++;
							} while (StatusMainChar[EXP] >= StatusMainChar[LV] * 50);
						}
						Light = 0, Pal = 255;
						do {
							ClearDrawScreen();
							DrawGraph(0, 0, BattleBackGraph[GRASS], FALSE);
							DrawGraph(0, 0, BattleBackOverGraph[GRASSOVER], TRUE);
							GraphFilterBlt(MobGraph[SLIME], FilterMob[SLIME], DX_GRAPH_FILTER_HSB, 0, 0, 0, Light);
							SetDrawBlendMode(DX_BLENDMODE_ALPHA, Pal);
							DrawGraph(344, 330, FilterMob[SLIME], TRUE);
							SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
							DrawModiGraph(193 - 97, 444, 816 - 97, 444, 816 - 97, 624, 193 - 97, 624, BattleGraph[1], TRUE);

							HPBar = (float)StatusMainChar[HP] / StatusMainChar[HPMAX] * 150;
							MPBar = (float)StatusMainChar[MP] / StatusMainChar[MPMAX] * 150;
							HPBarWidth = HPBar;
							MPBarWidth = MPBar;

							if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(213 - 97, 466, White, FontMain, "%s", Name.c_str());
							else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(213 - 97, 466, Yellow, FontMain, "%s", Name.c_str());
							else if (HPBarWidth == 0) { DrawFormatStringToHandle(213 - 97, 466, Red, FontMain, "%s", Name.c_str()); DrawGraph(372 - 97, 463, IconGraph[1], TRUE); }
							DrawRectGraph(462 - 97, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
							DrawRectGraph(642 - 97, 490, 0, 0, 150, 7, BarBaseGraph, TRUE, FALSE);
							DrawRectGraph(462 - 97, 490, 0, 0, HPBarWidth, 7, HPBarGraph, TRUE, FALSE);
							DrawRectGraph(642 - 97, 490, 0, 0, MPBarWidth, 7, MPBarGraph, TRUE, FALSE);
							DrawStringToHandle(461 - 97, 467, "HP", Blue, FontMain);
							DrawStringToHandle(641 - 97, 467, "MP", Blue, FontMain);
							if (HPBarWidth <= 186 && HPBarWidth > 56) DrawFormatStringToHandle(554 - 97, 467, White, FontMain, "%4d", StatusMainChar[HP]);
							else if (HPBarWidth <= 56 && HPBarWidth > 0) DrawFormatStringToHandle(554 - 97, 467, Yellow, FontMain, "%4d", StatusMainChar[HP]);
							else if (HPBarWidth == 0) DrawFormatStringToHandle(554 - 97, 467, Red, FontMain, "%4d", StatusMainChar[HP]);
							if (MPBarWidth <= 186 && MPBarWidth > 56) DrawFormatStringToHandle(733 - 97, 467, White, FontMain, "%4d", StatusMainChar[MP]);
							else if (MPBarWidth <= 56 && MPBarWidth > 0) DrawFormatStringToHandle(733 - 97, 467, Yellow, FontMain, "%4d", StatusMainChar[MP]);
							else if (MPBarWidth == 0) DrawFormatStringToHandle(733 - 97, 467, Red, FontMain, "%4d", StatusMainChar[MP]);

							ScreenFlip();
							if (Light != 255) Light = Light + 5;
							if (Pal != 0) Pal = Pal - 5;
						} while (Pal > 0);
						MsgBoxY = 88;
						do {
							ClearDrawScreen();
							DrawGraph(0, 0, BattleBackGraph[GRASS], FALSE);
							DrawGraph(0, 0, BattleBackOverGraph[GRASSOVER], TRUE);
							DrawModiGraph(193 - 97, 532 - MsgBoxY, 816 - 97, 532 - MsgBoxY, 816 - 97, 536 + MsgBoxY, 193 - 97, 536 + MsgBoxY, BattleGraph[1], TRUE);
							ScreenFlip();
							MsgBoxY = MsgBoxY - 11;
						} while (MsgBoxY >= 0);
						MsgBoxY = 0;
						do {
							ClearDrawScreen();
							DrawGraph(0, 0, BattleBackGraph[GRASS], FALSE);
							DrawGraph(0, 0, BattleBackOverGraph[GRASSOVER], TRUE);
							DrawModiGraph(0, 532 - MsgBoxY, 816, 532 - MsgBoxY, 816, 536 + MsgBoxY, 0, 536 + MsgBoxY, MsgGraph, TRUE);
							ScreenFlip();
							MsgBoxY = MsgBoxY + 11;
						} while (MsgBoxY <= 88);
						MsgBoxY = 88;
						int i = 0;
						do {
							DrawFormatStringToHandle(20 + (i * 14), 465, White, FontMain, "%c%c", VSMsg4[i], VSMsg4[i + 1]);
							ScreenFlip();
							WaitTimer(15);
							i = i + 2;
						} while (i + 1 <= 20);
						int j = 0;
						while (1) {
							ClearDrawScreen();
							DrawGraph(0, 0, BattleBackGraph[GRASS], FALSE);
							DrawGraph(0, 0, BattleBackOverGraph[GRASSOVER], TRUE);
							DrawGraph(0, 444, MsgGraph, TRUE);
							DrawFormatStringToHandle(20, 465, White, FontMain, "%s", VSMsg[3].c_str());
							if (j <= 15) DrawGraph(396, 600, CursorGraph[0], TRUE);
							else if (j > 15 && j <= 30) DrawGraph(396, 600, CursorGraph[1], TRUE);
							else if (j > 30 && j <= 45) DrawGraph(396, 600, CursorGraph[2], TRUE);
							else if (j > 45) { DrawGraph(396, 600, CursorGraph[3], TRUE); j = 0; }
							ScreenFlip();
							j++;
							UpdateKey();
							if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) break;
						}
						if (LVUP > 0) {
							StatusMainChar[HPMAX] = StatusMainChar[HPMAX] + (LVUP * 10);
							StatusMainChar[HP] = StatusMainChar[HPMAX];
							StatusMainChar[MPMAX] = StatusMainChar[MPMAX] + (LVUP * 10);
							StatusMainChar[MP] = StatusMainChar[MPMAX];
							StatusMainChar[ATK] = StatusMainChar[ATK] + (LVUP * 5);
							StatusMainChar[DEF] = StatusMainChar[DEF] + (LVUP * 5);
							StatusMainChar[MATK] = StatusMainChar[MATK] + (LVUP * 5);
							StatusMainChar[MDEF] = StatusMainChar[MDEF] + (LVUP * 5);
							StatusMainChar[AGI] = StatusMainChar[AGI] + (LVUP * 5);
							StatusMainChar[LUCK] = StatusMainChar[LUCK] + LVUP;

							ClearDrawScreen();
							DrawGraph(0, 0, BattleBackGraph[GRASS], FALSE);
							DrawGraph(0, 0, BattleBackOverGraph[GRASSOVER], TRUE);
							DrawModiGraph(0, 532 - 88, 816, 532 - 88, 816, 536 + 88, 0, 536 + 88, MsgGraph, TRUE);
							ScreenFlip();
							i = 0;
							do {
								DrawFormatStringToHandle(20 + (i * 14), 465, White, FontMain, "%c%c", VSMsg5[i], VSMsg5[i + 1]);
								ScreenFlip();
								WaitTimer(15);
								i = i + 2;
							} while (i + 1 <= 8);
							DrawFormatStringToHandle(20 + (i * 14), 465, White, FontMain, "%d", LVUP);
							ScreenFlip();
							WaitTimer(15);
							i++;
							do {
								DrawFormatStringToHandle(20 + (i * 14), 465, White, FontMain, "%c%c", VSMsg6[i], VSMsg6[i + 1]);
								ScreenFlip();
								WaitTimer(15);
								i = i + 2;
							} while (i + 1 <= 12);
							j = 0;
							while (1) {
								ClearDrawScreen();
								DrawGraph(0, 0, BattleBackGraph[GRASS], FALSE);
								DrawGraph(0, 0, BattleBackOverGraph[GRASSOVER], TRUE);
								DrawGraph(0, 444, MsgGraph, TRUE);
								DrawFormatStringToHandle(20, 465, White, FontMain, "%s%d%s", VSMsg[4].c_str(), LVUP, VSMsg[5].c_str());
								if (j <= 15) DrawGraph(396, 600, CursorGraph[0], TRUE);
								else if (j > 15 && j <= 30) DrawGraph(396, 600, CursorGraph[1], TRUE);
								else if (j > 30 && j <= 45) DrawGraph(396, 600, CursorGraph[2], TRUE);
								else if (j > 45) { DrawGraph(396, 600, CursorGraph[3], TRUE); j = 0; }
								ScreenFlip();
								j++;
								UpdateKey();
								if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) break;
							}
							LVUP = 0;
						}
						do {
							ClearDrawScreen();
							DrawGraph(0, 0, BattleBackGraph[GRASS], FALSE);
							DrawGraph(0, 0, BattleBackOverGraph[GRASSOVER], TRUE);
							DrawModiGraph(0, 532 - MsgBoxY, 816, 532 - MsgBoxY, 816, 536 + MsgBoxY, 0, 536 + MsgBoxY, MsgGraph, TRUE);
							ScreenFlip();
							MsgBoxY = MsgBoxY - 11;
						} while (MsgBoxY >= 0);
						MsgBoxY = 0;
						DrawGraph(0, 0, BattleBackGraph[GRASS], FALSE);
						DrawGraph(0, 0, BattleBackOverGraph[GRASSOVER], TRUE);
						GetDrawScreenGraph(0, 0, 816, 624, EncountScreen);
						Bright = 255;
						float Vol = 1.0;
						do {
							ClearDrawScreen();
							ChangeVolumeSoundMem((float)BGMVolume * Vol, BGM[BATTLE]);
							SetDrawBright(Bright, Bright, Bright);
							DrawGraph(0, 0, EncountScreen, FALSE);
							ScreenFlip();
							if (Vol != 0) Vol = Vol - 0.04;
							Bright = Bright - 10;
						} while (Bright >= 0);
						StopSoundMem(BGM[BATTLE]);
						ChangeVolumeSoundMem(BGMVolume, BGM[BATTLE]);
						Bright = 0;
						SetDrawBright(255, 255, 255);
						PlaySoundMem(BGM[FIELD], DX_PLAYTYPE_LOOP);
						break;
					}
					if (GameOver == TRUE) {
						WaitTimer(2000);
						GetDrawScreenGraph(0, 0, 816, 624, EncountScreen);
						Bright = 255;
						float Vol = 1.0;
						do {
						ClearDrawScreen();
						SetDrawBright(Bright, Bright, Bright);
						ChangeVolumeSoundMem((float)BGMVolume * Vol, BGM[BATTLE]);
						if (Vol != 0.00) Vol = Vol - 0.04;
						DrawGraph(0, 0, EncountScreen, FALSE);
						ScreenFlip();
						Bright = Bright - 10;
					} while (Bright >= 0);
						StopSoundMem(BGM[BATTLE]);
						ChangeVolumeSoundMem(BGMVolume, BGM[BATTLE]);
						PlaySoundMem(BGM[GAMEOVER], DX_PLAYTYPE_LOOP);
						do {
						ClearDrawScreen();
						SetDrawBright(Bright, Bright, Bright);
						DrawGraph(0, 0, GameOverGraph, FALSE);
						ScreenFlip();
						Bright = Bright + 10;
					} while (Bright <= 255);
						SetDrawBright(255, 255, 255);
						WaitTimer(2000);
						while (1) {
							ClearDrawScreen();
							DrawGraph(0, 0, GameOverGraph, FALSE);
							ScreenFlip();
							UpdateKey();
							if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) {
								float Vol = 1.00;
								Bright = 255;
								GetDrawScreenGraph(0, 0, 816, 624, EncountScreen);
								do {
									SetDrawBright(Bright, Bright, Bright);
									ChangeVolumeSoundMem((float)BGMVolume * Vol, BGM[GAMEOVER]);
									if (Vol != 0.00) Vol = Vol - 0.04;
									DrawGraph(0, 0, EncountScreen, FALSE);
									ScreenFlip();
									Bright = Bright - 10;
								} while (Bright >= 0);
								SetDrawBright(255, 255, 255);
								StopSoundMem(BGM[GAMEOVER]);
								ChangeVolumeSoundMem(BGMVolume, BGM[GAMEOVER]);
								break;
							}
						}
					}
				}
			}
		}
	}
}