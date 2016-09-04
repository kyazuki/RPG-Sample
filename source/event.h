//イベントセリフ
char EVMsg1[24 + 1];

void MsgLoad(void) {
	EVMsg[0] = "何してるの？早くしなさい";
	strncpy_s(EVMsg1, EVMsg[0].c_str(), 24);
}

//イベント処理
void Event(void) {
	if (MapNumber == 0) {
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
					if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) { PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK); break; }
				} while (i + 1 <= 24);
			int j = 0;
			while(1) {
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
				if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) { PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK); break; }
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
				if (Key[KEY_INPUT_RETURN] == 1 || Key[KEY_INPUT_Z] == 1) { PlaySoundMem(SE[DECISION], DX_PLAYTYPE_BACK); break; }
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
	else if (MapNumber == 1) {
		if (MapX == 1 && MapY == 4) {
			if (CharMainX == 6 && CharMainY == 7 && Direction == FACEUP) {

			}
		}
	}
}