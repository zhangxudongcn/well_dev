#pragma once
class LCModelPri;
class LCWellData;
class LCModel {
public:
	LCModel();
	virtual ~LCModel();
	void addWell(LCWellData *well_data);
	LCWellData *wellData(int index) const;

	virtual void modelChanged();
private:
	LCModelPri *_pri_data;
};