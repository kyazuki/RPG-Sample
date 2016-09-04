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
	int savestatus1;
	int savestatus2;
	int savestatus3;
	int savestatus4;
	int savestatus5;
	int savestatus6;
	int savestatus7;
	int savestatus8;
	int savestatus9;
	int savestatus10;
	int savestatus11;
	int savestatus12;
	int savestatus13;
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
	SaveData_t Data = { CharMainX, CharMainY, MapX, MapY, MapNumber, StatusMainChar[0], StatusMainChar[1], StatusMainChar[2], StatusMainChar[3], StatusMainChar[4], StatusMainChar[5], StatusMainChar[6], StatusMainChar[7], StatusMainChar[8], StatusMainChar[9], StatusMainChar[10], StatusMainChar[11], StatusMainChar[12] };
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
			StatusMainChar[0] = Data.savestatus1;
			StatusMainChar[1] = Data.savestatus2;
			StatusMainChar[2] = Data.savestatus3;
			StatusMainChar[3] = Data.savestatus4;
			StatusMainChar[4] = Data.savestatus5;
			StatusMainChar[5] = Data.savestatus6;
			StatusMainChar[6] = Data.savestatus7;
			StatusMainChar[7] = Data.savestatus8;
			StatusMainChar[8] = Data.savestatus9;
			StatusMainChar[9] = Data.savestatus10;
			StatusMainChar[10] = Data.savestatus11;
			StatusMainChar[11] = Data.savestatus12;
			StatusMainChar[12] = Data.savestatus13;
		}
	CharMainRightX = CharMainX * 48 - 48;
	CharMainRightY = CharMainY * 48 - 48;
	MapRightX = MapX * -48 + 48;
	MapRightY = MapY * -48 + 48;
	Direction = FACEDOWN;
}