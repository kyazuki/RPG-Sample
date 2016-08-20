typedef struct {
	int config1;
	int config2;
	int config3;
	int config4;
	int config5;
	int config6;
}Config_t;

FILE *cfp;

void ConfigSave(void) {
	Config_t Data = { Dash, Cheat, BGMVolume, MEVolume, BGSVolume, SEVolume };
	//Config_t Data = { 1, 1, 0, 0, 0, 0 };
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