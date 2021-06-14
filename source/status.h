void StatusSet(void) {
	Name = "ƒ`ƒƒ‹";
	StatusMainChar[LV] = 1;
	StatusMainChar[EXP] = 0;
	StatusMainChar[HP] = 450;
	StatusMainChar[HPMAX] = 450;
	StatusMainChar[MP] = 90;
	StatusMainChar[MPMAX] = 90;
	StatusMainChar[ATK] = 26;
	StatusMainChar[DEF] = 46;
	StatusMainChar[MATK] = 16;
	StatusMainChar[MDEF] = 16;
	StatusMainChar[AGI] = 32;
	StatusMainChar[LUCK] = 32;
	StatusMainChar[NEXTLV] = StatusMainChar[LV] * 50 - StatusMainChar[EXP];
	Money = 0;
}