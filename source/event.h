//ÉCÉxÉìÉgèàóù
void Event(void) {
	if (MapNumber == STARTMAP) {
		if (MapX == 3 && MapY == 3 && CharMainX == 14 && CharMainY == 7 && Direction == FACEUP) {
			ClearDrawScreen();
			DrawGraph(0, 0, MapEVGraphDOWN[STARTMAPEV1], FALSE);
			CharMain(10);
			GetDrawScreenGraph(0, 0, 48 * 17, 48 * 13, MsgScreen);
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
			DrawGraph(16, 462, FaceGraph[1], TRUE);
			ScreenFlip();
			int i = 0;
			do {
				DrawFormatStringToHandle(185 + (i * 14), 465, White, FontMain, "%c%c", EVMsg1[i], EVMsg1[i + 1]);
				ScreenFlip();
				WaitTimer(15);
				i = i + 2;
				if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) break;
			} while (i + 1 <= 24);
			int j = 0;
			while (1) {
				ClearDrawScreen();
				DrawGraph(0, 0, MsgScreen, FALSE);
				DrawGraph(0, 444, MsgGraph, TRUE);
				DrawGraph(16, 462, FaceGraph[1], TRUE);
				DrawFormatStringToHandle(185, 465, White, FontMain, "%s", EVMsg[0].c_str());
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
				DrawGraph(0, 0, MsgScreen, FALSE);
				DrawModiGraph(0, 532 - MsgBoxY, 816, 532 - MsgBoxY, 816, 536 + MsgBoxY, 0, 536 + MsgBoxY, MsgGraph, TRUE);
				ScreenFlip();
				MsgBoxY = MsgBoxY - 8;
			} while (MsgBoxY >= 0);
		}
		else if (MapX == 3 && MapY == 2 && CharMainX == 13 && CharMainY == 7 && Direction == FACERIGHT) {
			ClearDrawScreen();
			DrawGraph(0, 0, MapEVGraphLEFT[STARTMAPEV1], FALSE);
			CharMain(7);
			GetDrawScreenGraph(0, 0, 48 * 17, 48 * 13, MsgScreen);
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
			DrawGraph(16, 462, FaceGraph[1], TRUE);
			ScreenFlip();
			int i = 0;
			do {
				DrawFormatStringToHandle(185 + (i * 14), 465, White, FontMain, "%c%c", EVMsg1[i], EVMsg1[i + 1]);
				ScreenFlip();
				WaitTimer(15);
				i = i + 2;
				if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) break;
			} while (i + 1 <= 24);
			int j = 0;
			while (1) {
				ClearDrawScreen();
				DrawGraph(0, 0, MsgScreen, FALSE);
				DrawGraph(0, 444, MsgGraph, TRUE);
				DrawGraph(16, 462, FaceGraph[1], TRUE);
				DrawFormatStringToHandle(185, 465, White, FontMain, "%s", EVMsg[0].c_str());
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
				DrawGraph(0, 0, MsgScreen, FALSE);
				DrawModiGraph(0, 532 - MsgBoxY, 816, 532 - MsgBoxY, 816, 536 + MsgBoxY, 0, 536 + MsgBoxY, MsgGraph, TRUE);
				ScreenFlip();
				MsgBoxY = MsgBoxY - 8;
			} while (MsgBoxY >= 0);
		}
		else if (MapX == 3 && MapY == 2 && CharMainX == 15 && CharMainY == 7 && Direction == FACELEFT) {
			ClearDrawScreen();
			DrawGraph(0, 0, MapEVGraphRIGHT[STARTMAPEV1], FALSE);
			CharMain(4);
			GetDrawScreenGraph(0, 0, 48 * 17, 48 * 13, MsgScreen);
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
			DrawGraph(16, 462, FaceGraph[1], TRUE);
			ScreenFlip();
			int i = 0;
			do {
				DrawFormatStringToHandle(185 + (i * 14), 465, White, FontMain, "%c%c", EVMsg1[i], EVMsg1[i + 1]);
				ScreenFlip();
				WaitTimer(15);
				i = i + 2;
				if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) break;
			} while (i + 1 <= 24);
			int j = 0;
			while (1) {
				ClearDrawScreen();
				DrawGraph(0, 0, MsgScreen, FALSE);
				DrawGraph(0, 444, MsgGraph, TRUE);
				DrawGraph(16, 462, FaceGraph[1], TRUE);
				DrawFormatStringToHandle(185, 465, White, FontMain, "%s", EVMsg[0].c_str());
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
				DrawGraph(0, 0, MsgScreen, FALSE);
				DrawModiGraph(0, 532 - MsgBoxY, 816, 532 - MsgBoxY, 816, 536 + MsgBoxY, 0, 536 + MsgBoxY, MsgGraph, TRUE);
				ScreenFlip();
				MsgBoxY = MsgBoxY - 8;
			} while (MsgBoxY >= 0);
		}
	}
	else if (MapNumber == TOWN1INN1FMAP) {
		if (MapX == 3 && MapY == 7 && CharMainX == 9 && CharMainY == 7 && Direction == FACEUP) {
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
				DrawFormatStringToHandle(20 + (i * 14), 465, White, FontMain, "%c%c", EVMsg2[i], EVMsg2[i + 1]);
				ScreenFlip();
				WaitTimer(15);
				i = i + 2;
			} while (i + 1 <= 6);
			do {
				DrawFormatStringToHandle(22 + (i * 14), 465, White, FontMain, "%c%c", EVMsg2[i], EVMsg2[i + 1]);
				ScreenFlip();
				WaitTimer(15);
				i = i + 2;
			} while (i + 1 <= 8);
			do {
				DrawFormatStringToHandle(24 + (i * 14), 465, White, FontMain, "%c%c", EVMsg2[i], EVMsg2[i + 1]);
				ScreenFlip();
				WaitTimer(15);
				i = i + 2;
				if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) break;
			} while (i + 1 <= 30);
			int YesNoBoxY = 0;
			do {
				ClearDrawScreen();
				DrawGraph(0, 0, MsgScreen, FALSE);
				DrawGraph(0, 444, MsgGraph, TRUE);
				DrawFormatStringToHandle(20, 465, White, FontMain, "%s", EVMsg[1].c_str());
				DrawModiGraph(684, 382 - YesNoBoxY, 816, 382 - YesNoBoxY, 816, 392 + YesNoBoxY, 684, 392 + YesNoBoxY, YesNoGraph, TRUE);
				ScreenFlip();
				YesNoBoxY = YesNoBoxY + 4;
			} while (YesNoBoxY <= 52);
			int Pal = 255, SelectY = 354, Flag = TRUE;
			while (1) {
				ClearDrawScreen();
				DrawGraph(0, 0, MsgScreen, FALSE);
				DrawGraph(0, 444, MsgGraph, TRUE);
				DrawFormatStringToHandle(20, 465, White, FontMain, "%s", EVMsg[1].c_str());
				DrawGraph(684, 336, YesNoGraph, TRUE);

				SetDrawBlendMode(DX_BLENDMODE_ALPHA, Pal);
				DrawModiGraph(702, SelectY, 797, SelectY, 797, SelectY + 36, 702, SelectY + 36, SelectGraph, TRUE);
				if (Pal == 255) Flag = 1;
				else if (Pal == 129) Flag = 0;

				if (Flag == 1) Pal = Pal - 6;
				else if (Flag == 0) Pal = Pal + 6;

				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
				DrawStringToHandle(707, 358, "ÇÕÇ¢", White, FontMain);
				DrawStringToHandle(707, 395, "Ç¢Ç¢Ç¶", White, FontMain);
				ScreenFlip();

				UpdateKey();
				if (Key[KEY_INPUT_UP] == 1 && SelectY == 390) { PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); SelectY = 354; }
				else if (Key[KEY_INPUT_DOWN] == 1 && SelectY == 354) { PlaySoundMem(SE[SELECT], DX_PLAYTYPE_BACK); SelectY = 390; }
				else if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) {
					if (SelectY == 354) {
						PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK);
						do {
							ClearDrawScreen();
							DrawGraph(0, 0, MsgScreen, FALSE);
							if (YesNoBoxY >= 0) DrawModiGraph(0, 532 - MsgBoxY, 816, 532 - MsgBoxY, 816, 536 + MsgBoxY, 0, 536 + MsgBoxY, MsgGraph, TRUE);
							if (MsgBoxY >= 0)DrawModiGraph(684, 382 - YesNoBoxY, 816, 382 - YesNoBoxY, 816, 392 + YesNoBoxY, 684, 392 + YesNoBoxY, YesNoGraph, TRUE);
							ScreenFlip();
							YesNoBoxY = YesNoBoxY - 4;
							MsgBoxY = MsgBoxY - 8;
						} while (YesNoBoxY >= 0 || MsgBoxY >= 0);
						int Bright = 255;
						do {
							ClearDrawScreen();
							SetDrawBright(Bright, Bright, Bright);
							DrawGraph(0, 0, MsgScreen, FALSE);
							ScreenFlip();
							Bright = Bright - 5;
						} while (Bright > 0);
						Money = Money - 100;
						StatusMainChar[HP] = StatusMainChar[HPMAX];
						StatusMainChar[MP] = StatusMainChar[MPMAX];
						WaitTimer(1500);
						do {
							ClearDrawScreen();
							SetDrawBright(Bright, Bright, Bright);
							DrawGraph(0, 0, MsgScreen, FALSE);
							ScreenFlip();
							Bright = Bright + 5;
						} while (Bright < 255);
						break;
					}
					else if (SelectY == 390) {
						PlaySoundMem(SE[CANCEL], DX_PLAYTYPE_BACK);
						do {
							ClearDrawScreen();
							DrawGraph(0, 0, MsgScreen, FALSE);
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
						DrawGraph(0, 0, MsgScreen, FALSE);
						if (YesNoBoxY >= 0) DrawModiGraph(0, 532 - MsgBoxY, 816, 532 - MsgBoxY, 816, 536 + MsgBoxY, 0, 536 + MsgBoxY, MsgGraph, TRUE);
						if (MsgBoxY >= 0)DrawModiGraph(684, 382 - YesNoBoxY, 816, 382 - YesNoBoxY, 816, 392 + YesNoBoxY, 684, 392 + YesNoBoxY, YesNoGraph, TRUE);
						ScreenFlip();
						YesNoBoxY = YesNoBoxY - 4;
						MsgBoxY = MsgBoxY - 8;
					} while (YesNoBoxY >= 0 || MsgBoxY >= 0);
					break;
				}
			}
		}
		else if (MapX == 1 && MapY == 1 && CharMainX == 8 && CharMainY == 7 && Direction == FACEUP) {
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
				DrawFormatStringToHandle(20 + (i * 14), 465, White, FontMain, "%c%c", EVMsg3[i], EVMsg3[i + 1]);
				ScreenFlip();
				WaitTimer(15);
				i = i + 2;
				if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) break;
			} while (i + 1 <= 32);
			int j = 0;
			while (1) {
				ClearDrawScreen();
				DrawGraph(0, 0, MsgScreen, FALSE);
				DrawGraph(0, 444, MsgGraph, TRUE);
				DrawFormatStringToHandle(20, 465, White, FontMain, "%s", EVMsg[2].c_str());
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
		}
		else if (MapX == 5 && MapY == 1 && CharMainX == 11 && CharMainY == 6 && Direction == FACEUP) {
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
				DrawFormatStringToHandle(20 + (i * 14), 465, White, FontMain, "%c%c", EVMsg4[i], EVMsg4[i + 1]);
				ScreenFlip();
				WaitTimer(15);
				i = i + 2;
				if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) break;
			} while (i + 1 <= 16);
			int j = 0;
			while (1) {
				ClearDrawScreen();
				DrawGraph(0, 0, MsgScreen, FALSE);
				DrawGraph(0, 444, MsgGraph, TRUE);
				DrawFormatStringToHandle(20, 465, White, FontMain, "%s", EVMsg[3].c_str());
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
		}
		else if (MapX == 5 && MapY == 1 && CharMainX == 10 && CharMainY == 5 && Direction == FACERIGHT) {
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
				DrawFormatStringToHandle(20 + (i * 14), 465, White, FontMain, "%c%c", EVMsg4[i], EVMsg4[i + 1]);
				ScreenFlip();
				WaitTimer(15);
				i = i + 2;
				if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) break;
			} while (i + 1 <= 16);
			int j = 0;
			while (1) {
				ClearDrawScreen();
				DrawGraph(0, 0, MsgScreen, FALSE);
				DrawGraph(0, 444, MsgGraph, TRUE);
				DrawFormatStringToHandle(20, 465, White, FontMain, "%s", EVMsg[3].c_str());
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
		}
	}
	else if (MapNumber == FIELDMAP) {
		if (MapX == 24 && MapY == 20 && CharMainX == 9 && CharMainY == 7 && Direction == FACEDOWN) {
			if (StatusMainChar[LV] < 20) {
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
					DrawFormatStringToHandle(20 + (i * 14), 465, White, FontMain, "%c%c", EVMsg5[i], EVMsg5[i + 1]);
					ScreenFlip();
					WaitTimer(15);
					i = i + 2;
					if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) break;
				} while (i + 1 <= 16);
				WaitTimer(500);
				do {
					DrawFormatStringToHandle(20 + (i * 14), 501, White, FontMain, "%c%c", EVMsg6[i], EVMsg6[i + 1]);
					ScreenFlip();
					WaitTimer(15);
					i = i + 2;
					if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) break;
				} while (i + 1 <= 28);
				int j = 0;
				while (1) {
					ClearDrawScreen();
					DrawGraph(0, 0, MsgScreen, FALSE);
					DrawGraph(0, 444, MsgGraph, TRUE);
					DrawFormatStringToHandle(20, 465, White, FontMain, "%s", EVMsg[4].c_str());
					DrawFormatStringToHandle(20, 501, White, FontMain, "%s", EVMsg[5].c_str());
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
			}
		}
		if (MapX == 25 && MapY == 20 && CharMainX == 9 && CharMainY == 7 && Direction == FACEDOWN) {
			if (StatusMainChar[LV] < 20) {
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
					DrawFormatStringToHandle(20 + (i * 14), 465, White, FontMain, "%c%c", EVMsg5[i], EVMsg5[i + 1]);
					ScreenFlip();
					WaitTimer(15);
					i = i + 2;
					if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) break;
				} while (i + 1 <= 16);
				WaitTimer(500);
				do {
					DrawFormatStringToHandle(20 + (i * 14), 501, White, FontMain, "%c%c", EVMsg6[i], EVMsg6[i + 1]);
					ScreenFlip();
					WaitTimer(15);
					i = i + 2;
					if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) break;
				} while (i + 1 <= 28);
				int j = 0;
				while (1) {
					ClearDrawScreen();
					DrawGraph(0, 0, MsgScreen, FALSE);
					DrawGraph(0, 444, MsgGraph, TRUE);
					DrawFormatStringToHandle(20, 465, White, FontMain, "%s", EVMsg[4].c_str());
					DrawFormatStringToHandle(20, 501, White, FontMain, "%s", EVMsg[5].c_str());
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
			}
		}
	}
}