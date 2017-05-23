#include "stdafx.h"
#include "lcmodel.h"
#include "lcwelldata.h"
#include "lcapplication.h"
#include <ai_data_include.h>
#include <QVector>
class LCModelPri {
public:
	LCModelPri() {};
	~LCModelPri() {};
	void reset();
	QVector<LCWellData*> _wells;
};
void LCModelPri::reset()
{
	for (auto &ptr : _wells) {
		delete ptr;
	}
	_wells.clear();
}
LCModel::LCModel() : _pri_data( new LCModelPri() )
{

}

LCModel::~LCModel()
{
	_pri_data->reset();
	delete _pri_data;
}

void LCModel::addWell(LCWellData *well_data)
{
	_pri_data->_wells.push_back(well_data);
    modelChanged();
}

LCWellData *LCModel::wellData(int index) const
{
	if (index < 0 || index >= _pri_data->_wells.size()) {
		return nullptr;
	}
	return _pri_data->_wells[index];
}
void LCModel::modelChanged()
{
    lcApp()->modelChanged();
}