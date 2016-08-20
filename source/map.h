//マップ読み込み
//マップ描画
void MAPDraw(int Map, int Roop) {
	if (Roop == 1) DrawGraph(MapRightX, MapRightY, MapGraph[Map], FALSE);
	if (Roop == 2) DrawGraph(MapRightX, MapRightY, MapGraph2[Map], FALSE);
	if (Roop == 3) DrawGraph(MapRightX, MapRightY, MapGraph3[Map], FALSE);
	if (Roop == 4) DrawGraph(MapRightX, MapRightY, MapGraph2[Map], FALSE);
}
void MAPOverlayDraw(int Map) {
	DrawGraph(MapRightX, MapRightY, MapOverlayGraph[Map], TRUE);
}

//当たり判定処理
int wall(int place, int x, int y) {
	int RED, GREEN, BLUE, APPEARENCE;
	GetPixelSoftImage(place, x, y, &RED, &GREEN, &BLUE, &APPEARENCE);
	if (RED == 0 && GREEN == 0 && BLUE == 0) return 1; //黒･進行不可
	else if (RED == 255 && GREEN == 255 && BLUE == 255) return 0; //白･全方向進行可
	else if (RED == 255 && GREEN == 0 && BLUE == 0) return 2; //赤･下のみ進行不可
	else if (RED == 0 && GREEN == 255 && BLUE == 0) return 3; //緑･上のみ進行不可
	else if (RED == 0 && GREEN == 0 && BLUE == 255) return 4; //青･右のみ進行不可
	else if (RED == 64 && GREEN == 0 && BLUE == 0) return 5; //赤2･左のみ進行不可
	else if (RED == 0 && GREEN == 64 && BLUE == 0) return 6; //緑2･下,左のみ進行不可
	else if (RED == 0 && GREEN == 0 && BLUE == 64) return 7; //青2･上下のみ進行不可
	else if (RED == 128 && GREEN == 0 && BLUE == 0) return 8; //赤3･下,右のみ進行不可
	else if (RED == 0 && GREEN == 128 && BLUE == 0) return 9; //緑3･上,左のみ進行不可
	else if (RED == 0 && GREEN == 0 && BLUE == 128) return 10; //青3･左右のみ進行不可
	else if (RED == 192 && GREEN == 0 && BLUE == 0) return 11; //赤4･上,右のみ進行不可
	else if (RED == 0 && GREEN == 192 && BLUE == 0) return 12; //緑4･下のみ進行可
	else if (RED == 0 && GREEN == 0 && BLUE == 192) return 13; //青4･上のみ進行可
	else if (RED == 255 && GREEN == 255 && BLUE == 0) return 14; //黄･右のみ進行可
	else if (RED == 128 && GREEN == 0 && BLUE == 128) return 15; //紫･左のみ進行可
	else return -1;
}

int attackup(int MAP, int x, int y) {
	if (wall(MAP, (CharMainX + MapX - 1) * 48 - 48 + x, (CharMainY + MapY - 1) * 48 - 48 + y) == 1 || wall(MAP, (CharMainX + MapX - 1) * 48 - 48 + x, (CharMainY + MapY - 1) * 48 - 48 + y) == 2 || wall(MAP, (CharMainX + MapX - 1) * 48 - 48 + x, (CharMainY + MapY - 1) * 48 - 48 + y) == 6 || wall(MAP, (CharMainX + MapX - 1) * 48 - 48 + x, (CharMainY + MapY - 1) * 48 - 48 + y) == 7 || wall(MAP, (CharMainX + MapX - 1) * 48 - 48 + x, (CharMainY + MapY - 1) * 48 - 48 + y) == 8) return 1;
	else return 0;
}
int attackdown(int MAP, int x, int y) {
	if (wall(MAP, (CharMainX + MapX - 1) * 48 - 48 + x, (CharMainY + MapY - 1) * 48 - 48 + y) == 1 || wall(MAP, (CharMainX + MapX - 1) * 48 - 48 + x, (CharMainY + MapY - 1) * 48 - 48 + y) == 3 || wall(MAP, (CharMainX + MapX - 1) * 48 - 48 + x, (CharMainY + MapY - 1) * 48 - 48 + y) == 7 || wall(MAP, (CharMainX + MapX - 1) * 48 - 48 + x, (CharMainY + MapY - 1) * 48 - 48 + y) == 9 || wall(MAP, (CharMainX + MapX - 1) * 48 - 48 + x, (CharMainY + MapY - 1) * 48 - 48 + y) == 11) return 1;
	else return 0;
}
int attackleft(int MAP, int x, int y) {
	if (wall(MAP, (CharMainX + MapX - 1) * 48 - 48 + x, (CharMainY + MapY - 1) * 48 - 48 + y) == 1 || wall(MAP, (CharMainX + MapX - 1) * 48 - 48 + x, (CharMainY + MapY - 1) * 48 - 48 + y) == 4 || wall(MAP, (CharMainX + MapX - 1) * 48 - 48 + x, (CharMainY + MapY - 1) * 48 - 48 + y) == 8 || wall(MAP, (CharMainX + MapX - 1) * 48 - 48 + x, (CharMainY + MapY - 1) * 48 - 48 + y) == 10 || wall(MAP, (CharMainX + MapX - 1) * 48 - 48 + x, (CharMainY + MapY - 1) * 48 - 48 + y) == 11) return 1;
	else return 0;
}
int attackright(int MAP, int x, int y) {
	if (wall(MAP, (CharMainX + MapX - 1) * 48 - 48 + x, (CharMainY + MapY - 1) * 48 - 48 + y) == 1 || wall(MAP, (CharMainX + MapX - 1) * 48 - 48 + x, (CharMainY + MapY - 1) * 48 - 48 + y) == 5 || wall(MAP, (CharMainX + MapX - 1) * 48 - 48 + x, (CharMainY + MapY - 1) * 48 - 48 + y) == 6 || wall(MAP, (CharMainX + MapX - 1) * 48 - 48 + x, (CharMainY + MapY - 1) * 48 - 48 + y) == 9 || wall(MAP, (CharMainX + MapX - 1) * 48 - 48 + x, (CharMainY + MapY - 1) * 48 - 48 + y) == 10) return 1;
	else return 0;
}