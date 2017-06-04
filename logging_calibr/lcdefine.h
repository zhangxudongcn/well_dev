#pragma once
class LCMainWindow;
class aiDataWellGroup;
class LCENV {
public:
    enum DataChangeFlag { CurrentWellChanged = 0x1,SyntheticChanged = 0x2 };
	static int PixelPerCm;
	static LCMainWindow *MW;
	static aiDataWellGroup *WellData;
	static double DefaultTitleHeightCM;
};