//マップ読み込み
//マップ1
void MAP001(void) {
	DrawGraph(map001X * -48 + 48, map001Y * -48 + 48, map001Graph, FALSE);
}
void MAP001Overlay(void) {
	DrawGraph(map001X * -48 + 48, map001Y * -48 + 48, map001OverlayGraph, TRUE);
}


//当たり判定処理
int wall(int place, int x, int y) {
	int RED, GREEN, BLUE, APPEARENCE;
	GetPixelSoftImage(place, x, y, &RED, &GREEN, &BLUE, &APPEARENCE);
	if (RED == 0 && GREEN == 0 && BLUE ==0) return 1; //黒･進行不可
	else if (RED == 255 && GREEN == 255 && BLUE == 255) return 0; //白･全方向進行可
	else if (RED == 255 && GREEN == 0 && BLUE == 0) return 2; //赤･上のみ進行不可
	else if (RED == 0 && GREEN == 255 && BLUE == 0) return 3; //青･下のみ進行不可
	else if (RED == 0 && GREEN == 0 && BLUE == 255) return 4; //緑･左のみ進行不可
	else if (RED == 64 && GREEN == 0 && BLUE == 0) return 5; //赤2･右のみ進行不可
	else if (RED == 0 && GREEN == 64 && BLUE == 0) return 6; //青2･上,右のみ進行不可
	else if (RED == 0 && GREEN == 0 && BLUE == 64) return 7; //緑2･上下のみ進行不可
	else if (RED == 128 && GREEN == 0 && BLUE == 0) return 8; //赤3･上,左のみ進行不可
	else if (RED == 0 && GREEN == 128 && BLUE == 0) return 9; //青3･右,下のみ進行不可
	else if (RED == 0 && GREEN == 0 && BLUE == 128) return 10; //緑3･左右のみ進行不可
	else if (RED == 192 && GREEN == 0 && BLUE == 0) return 11; //赤4･下,左のみ進行不可
	else if (RED == 0 && GREEN == 192 && BLUE == 0) return 12; //青4･上のみ進行可
	else if (RED == 0 && GREEN == 0 && BLUE == 192) return 13; //緑4･下のみ進行可
	else if (RED == 255 && GREEN == 255 && BLUE == 0) return 14; //黄･左のみ進行可
	else if (RED == 128 && GREEN == 0 && BLUE == 128) return 15; //紫･右のみ進行可
	else return -1;
}

int attackup(int MAP, int x, int y) {
	if (wall(MAP, (CharMainX + map001X - 1) * 48 - 48 + x, (CharMainY + map001Y - 1) * 48 - 48 + y) == 1 || wall(MAP, (CharMainX + map001X - 1) * 48 - 48 + x, (CharMainY + map001Y - 1) * 48 - 48 + y) == 2 || wall(MAP, (CharMainX + map001X - 1) * 48 - 48 + x, (CharMainY + map001Y - 1) * 48 - 48 + y) == 6 || wall(MAP, (CharMainX + map001X - 1) * 48 - 48 + x, (CharMainY + map001Y - 1) * 48 - 48 + y) == 7 || wall(MAP, (CharMainX + map001X - 1) * 48 - 48 + x, (CharMainY + map001Y - 1) * 48 - 48 + y) == 8) return 1;
	else if (wall(MAP, (CharMainX + map001X - 1) * 48 - 48 + x, (CharMainY + map001Y - 1) * 48 - 48 + y) == 1 || wall(MAP, (CharMainX + map001X - 1) * 48 - 48 + x, (CharMainY + map001Y - 1) * 48 - 48 + y) == 3 || wall(MAP, (CharMainX + map001X - 1) * 48 - 48 + x, (CharMainY + map001Y - 1) * 48 - 48 + y) == 7 || wall(MAP, (CharMainX + map001X - 1) * 48 - 48 + x, (CharMainY + map001Y - 1) * 48 - 48 + y) == 9 || wall(MAP, (CharMainX + map001X - 1) * 48 - 48 + x, (CharMainY + map001Y - 1) * 48 - 48 + y) == 11) return 1;
	else if (wall(MAP, (CharMainX + map001X - 1) * 48 - 48 + x, (CharMainY + map001Y - 1) * 48 - 48 + y) == 1 || wall(MAP, (CharMainX + map001X - 1) * 48 - 48 + x, (CharMainY + map001Y - 1) * 48 - 48 + y) == 4 || wall(MAP, (CharMainX + map001X - 1) * 48 - 48 + x, (CharMainY + map001Y - 1) * 48 - 48 + y) == 8 || wall(MAP, (CharMainX + map001X - 1) * 48 - 48 + x, (CharMainY + map001Y - 1) * 48 - 48 + y) == 10 || wall(MAP, (CharMainX + map001X - 1) * 48 - 48 + x, (CharMainY + map001Y - 1) * 48 - 48 + y) == 11) return 1;
	else if (wall(MAP, (CharMainX + map001X - 1) * 48 - 48 + x, (CharMainY + map001Y - 1) * 48 - 48 + y) == 1 || wall(MAP, (CharMainX + map001X - 1) * 48 - 48 + x, (CharMainY + map001Y - 1) * 48 - 48 + y) == 5 || wall(MAP, (CharMainX + map001X - 1) * 48 - 48 + x, (CharMainY + map001Y - 1) * 48 - 48 + y) == 6 || wall(MAP, (CharMainX + map001X - 1) * 48 - 48 + x, (CharMainY + map001Y - 1) * 48 - 48 + y) == 9 || wall(MAP, (CharMainX + map001X - 1) * 48 - 48 + x, (CharMainY + map001Y - 1) * 48 - 48 + y) == 10) return 1;
	else return 0;
}

int attackup2(int MAP, int x, int y) {
	if (wall(MAP, map001X * 48 - 48 + x, map001Y * 48 - 48 + y) == 1 || wall(MAP, map001X * 48 - 48 + x, map001Y * 48 - 48 + y) == 2 || wall(MAP, map001X * 48 - 48 + x, map001Y * 48 - 48 + y) == 6 || wall(MAP, map001X * 48 - 48 + x, map001Y * 48 - 48 + y) == 7 || wall(MAP, map001X * 48 - 48 + x, map001Y * 48 - 48 + y) == 8) return 1;
	else if (wall(MAP, map001X * 48 - 48 + x, map001Y * 48 - 48 + y) == 1 || wall(MAP, map001X * 48 - 48 + x, map001Y * 48 - 48 + y) == 3 || wall(MAP, map001X * 48 - 48 + x, map001Y * 48 - 48 + y) == 7 || wall(MAP, map001X * 48 - 48 + x, map001Y * 48 - 48 + y) == 9 || wall(MAP, map001X * 48 - 48 + x, map001Y * 48 - 48 + y) == 11) return 1;
	else if (wall(MAP, map001X * 48 - 48 + x, map001Y * 48 - 48 + y) == 1 || wall(MAP, map001X * 48 - 48 + x, map001Y * 48 - 48 + y) == 4 || wall(MAP, map001X * 48 - 48 + x, map001Y * 48 - 48 + y) == 8 || wall(MAP, map001X * 48 - 48 + x, map001Y * 48 - 48 + y) == 10 || wall(MAP, map001X * 48 - 48 + x, map001Y * 48 - 48 + y) == 11) return 1;
	else if (wall(MAP, map001X * 48 - 48 + x, map001Y * 48 - 48 + y) == 1 || wall(MAP, map001X * 48 - 48 + x, map001Y * 48 - 48 + y) == 5 || wall(MAP, map001X * 48 - 48 + x, map001Y * 48 - 48 + y) == 6 || wall(MAP, map001X * 48 - 48 + x, map001Y * 48 - 48 + y) == 9 || wall(MAP, map001X * 48 - 48 + x, map001Y * 48 - 48 + y) == 10) return 1;
	else return 0;
}