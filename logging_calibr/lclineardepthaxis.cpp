#include "stdafx.h"
#include "lclineardepthaxis.h"
#include "lcmainwindow.h"
#include "lcdefine.h"
#include "lcdata.h"
double LCLinearDepthAxis::tickValue(int index) const
{
	double tick_value = LCLinearAxis::tickValue(index);
	return LCENV::MW->lcData()->getTime(tick_value) * 1000;
}
