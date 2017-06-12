#pragma once
class LCMainWindow;
class aiDataWellGroup;
#define LCITEM 65537
class LCENV {
public:
    enum DataChangeFlag { CurrentWellChanged = 0x1,SyntheticChanged = 0x2 };
	enum FillWiggle { FillNone = 0, FillPositive = 1, FillNegative = 2 };
	enum ItemType { TopItem = LCITEM, TraceItem = LCITEM + 1, CurveItem = LCITEM + 2, TraceItemGroup = LCITEM + 4, SyntheticItemGroup = LCITEM + 4, 
		AverageTraceItemGroup = LCITEM + 5, WellSeismicItem = LCITEM + 6, AverageTraceItem = LCITEM + 7, LayerItemGroup = LCITEM + 8 };
	static int PixelPerCM;
	static LCMainWindow *MW;
	static float InvalidTime;
	static float InvalidDepth;
};