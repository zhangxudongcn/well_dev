#pragma once
class LCUpdateNotifier {
public:
	LCUpdateNotifier() : _changed_flag(0) {};
	virtual ~LCUpdateNotifier() {};
	long dataChangedFlag() const { return _changed_flag; }
	void setDataChangedFlag(long flag) { _changed_flag = flag; }
private:
	long _changed_flag;
};