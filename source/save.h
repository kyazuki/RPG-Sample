typedef struct {
	int config1;
	int config2;
	int config3;
	int config4;
	int config5;
	int config6;
}Config_t;

typedef struct {
	int saveCharX;
	int saveCharY;
	int saveMapX;
	int saveMapY;
	int saveMapNum;
	int saveBattleMap;
	int saveMoney;
	int savestatus[13];
}SaveData_t;

FILE *cfp, *sdp;

void ConfigSave(void) {
	Config_t Data = { Dash, Cheat, BGMVolume, MEVolume, BGSVolume, SEVolume };
	if (errno_t errorcs = fopen_s(&cfp, "config.dat", "wb") == 0) {
		fwrite(&Data, sizeof(Data), 1, cfp);
		fclose(cfp);
	}
}

void ConfigLoad(void) {
	Config_t Data;
	if (errno_t errorcl = fopen_s(&cfp, "config.dat", "rb") == 0) {
		fread(&Data, sizeof(Data), 1, cfp);
		fclose(cfp);
		Dash = Data.config1;
		Cheat = Data.config2;
		BGMVolume = Data.config3;
		MEVolume = Data.config4;
		BGSVolume = Data.config5;
		SEVolume = Data.config6;
	}
}

void Save(void) {
	SaveData_t Data;
	Data.saveCharX = CharMainX;
	Data.saveCharY = CharMainY;
	Data.saveMapX = MapX;
	Data.saveMapY = MapY;
	Data.saveMapNum = MapNumber;
	Data.saveBattleMap = BattleMap;
	Data.saveMoney = Money;
	int i = 0;
	do {
		Data.savestatus[i] = StatusMainChar[i];
		i++;
	} while (i <= 13 - 1);
	if (errno_t errorcs = fopen_s(&sdp, "save.dat", "wb") == 0) {
			fwrite(&Data, sizeof(Data), 1, sdp);
			fclose(sdp);
		}
}

void Load(void) {
	SaveData_t Data;
	if (errno_t errorcl = fopen_s(&sdp, "save.dat", "rb") == 0) {
			fread(&Data, sizeof(Data), 1, sdp);
			fclose(sdp);
			CharMainX = Data.saveCharX;
			CharMainY = Data.saveCharY;
			MapX = Data.saveMapX;
			MapY = Data.saveMapY;
			MapNumber = Data.saveMapNum;
			BattleMap = Data.saveBattleMap;
			Money = Data.saveMoney;
			int i = 0;
			do {
				StatusMainChar[i] = Data.savestatus[i];
				i++;
			} while (i <= 13 - 1);
	}
	CharMainRightX = CharMainX * 48 - 48;
	CharMainRightY = CharMainY * 48 - 48;
	MapRightX = MapX * -48 + 48;
	MapRightY = MapY * -48 + 48;
	Direction = FACEDOWN;
}