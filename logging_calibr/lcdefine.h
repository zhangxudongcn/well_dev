#pragma once
#include <QPair>
#include <QVector>
class LCMainWindow;
class aiDataWellGroup;
#define LCITEM 65537
class LCTimeDepthCurve : public QPair<QVector<float>, QVector<float>> {
public:	
	LCTimeDepthCurve() : QPair<QVector<float>, QVector<float>>() {}
	LCTimeDepthCurve(const QVector<float> &time, const QVector<float> &depth) : QPair<QVector<float>, QVector<float>>(time, depth) {}
	const QString desc() const { return _desc; }
	void setDesc(const QString &desc) { _desc = desc; }
private:
	QString _desc;
};

typedef QPair<QVector<float>, QVector<float>> LCTrace;
class LCWavelet : public LCTrace {
public:
	LCWavelet() : QPair<QVector<float>, QVector<float>>() {}
	LCWavelet(const QVector<float> &time, const QVector<float> &value) : QPair<QVector<float>, QVector<float>>(time, value) {}
	const QString desc() const { return _desc; }
	float fPeak() const { return _fpeak; }
	void setFPeak(float peak) { _fpeak = peak; }
	void setDesc(const QString &desc) { _desc = desc; }
	float sampleInterval() const { return _sample_interval; }
	void setSampleInterval(float interval) { _sample_interval = interval; }
private:
	QString _desc;
	float _fpeak;
	float _sample_interval;
};
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