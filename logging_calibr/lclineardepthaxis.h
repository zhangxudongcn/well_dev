#pragma once
#include "lclinearaxis.h"
class LCLinearDepthAxis : public LCLinearAxis {
public:
	LCLinearDepthAxis(Qt::Alignment align) : LCLinearAxis(align) {}
	~LCLinearDepthAxis() {};
	double tickValue(int index) const override;
};