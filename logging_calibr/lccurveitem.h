#pragma once
#include "lcbaseitem.h"
class LCWellItem;
class LCUpdateNotifier;
class LCCurveItem :	public LCBaseItem
{
public:
	LCCurveItem( LCWellItem *well_item, Qt::WindowFlags wFlags = Qt::WindowFlags());
	virtual ~LCCurveItem();
	void onUpdate( const LCUpdateNotifier &update_notifier ) override;
};

