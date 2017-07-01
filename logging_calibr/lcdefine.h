#pragma once
class LCMainWindow;
class aiDataWellGroup;
#define LCITEM 65537
class LCENV {
public:
	enum DataChangeFlag { CurrentWellChanged = 0x1, TimeDepthCurveChanged = 0x2, TopChanged = 0x4, WaveletChanged = 0x8 };
	enum FillWiggle { FillNone = 0, FillPositive = 1, FillNegative = 2 };
	enum ItemType { TopItem = LCITEM, CurveItem = LCITEM + 1, TraceItem = LCITEM + 2, TraceItemGroup = LCITEM + 3, SyntheticItem = LCITEM + 4, SyntheticItemGroup = LCITEM + 5,
		AverageTraceItem = LCITEM + 6, AverageTraceItemGroup = LCITEM + 7, WellSeismicItem = LCITEM +8, WellSeismicItemGroup = LCITEM + 9, LayerItemGroup = LCITEM + 10 };
	static int PixelPerCM;
	static LCMainWindow *MW;
	static float InvalidTime;
	static float InvalidDepth;
};