#pragma once
#include "lcdefine.h"
#include <QVector>
#include <QString>
#include <QMap>
#include <QStringList>
#include <QRgb>
#include <QPointF>
#include <QPair>
#include <QPolygonF>
class aiDataProject;
class aiDataWellGroup;
class aiDataWell;
class aiDataSeismic;
class aiDataSurvey;
class LCData {
public:
	LCData();
	virtual ~LCData();
	bool setWorkData(const QString &pname, const QString &well_group_name, const QString &well_name, 
		const QString &survey_name, const QString &seis_name, float replace_velocity );
	aiDataProject *project() const { return _project; }
	aiDataWellGroup *wellGroup() const { return _well_group; }
	aiDataWell *wellData() const { return _well_data; }
	aiDataSurvey *survey() const { return _survey; }
	aiDataSeismic *seismicData() const { return _seis_data; }
	float replaceVelocity() const { return _replace_velocity; }

	LCTimeDepthCurve currentTimeDepthCurve() const;
	int currentTimeDepthCurveIndex() const { return _current_time_depth_curve_index; }
	void setCurrentTimeDepthCurveIndex(int index);
	const QVector<LCTimeDepthCurve> &timeDepthCurveArray() const { return _time_depth_curve_array; }
	void addTimeDepthCurve( const LCTimeDepthCurve &curve);
	void setCurrentTimeDepthCurve(const LCTimeDepthCurve &curve);

	LCWavelet currentWavelet() const;
	int currentWaveletIndex() const { return _current_wavelet_index; }
	void setCurrentWaveletIndex(int index);
	const QVector<LCWavelet> &waveletArray() const { return _wavelet_array; }
	void addWavelet(const LCWavelet &wavelet);
	void setCurrentWavelet(const LCWavelet &wavelet);

	float getTime(float depth) const;
	float getDepth(float time) const;
	float timeMin() const { return _time_min; }
	float timeMax() const { return _time_max; }
	QVector<LCTrace> wellSeismic(int il_num, int xl_num);
protected:
	void reset();
private:
	aiDataProject *_project;
	aiDataWellGroup *_well_group;
	aiDataWell *_well_data;
	aiDataSurvey *_survey;
	aiDataSeismic *_seis_data;
	float _replace_velocity;
	QVector<LCTimeDepthCurve> _time_depth_curve_array; /* s, m*/
	int _current_time_depth_curve_index;
	QVector<LCWavelet> _wavelet_array;
	int _current_wavelet_index;
	float _time_min, _time_max;
};