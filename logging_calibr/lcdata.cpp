#include "stdafx.h"

#include "lcdata.h"
#include "lcdefine.h"
#include "lcalgorithm.h"
#include "lcmainwindow.h"
#include <QFile>
#include <QTextStream>
#include "ai_data_include.h"

LCData::LCData() : _project(nullptr), _well_group(nullptr), _well_data(nullptr), _survey(nullptr), _seis_data(nullptr), _replace_velocity(-1)
{
}
LCData::~LCData()
{
}
void LCData::reset()
{
	if (_seis_data != nullptr) {
		_seis_data->UnUsed();
		delete _seis_data;
		_seis_data = nullptr;
	}
	if (_survey != nullptr) {
		_survey->UnUsed();
		delete _survey;
		_survey = nullptr;
	}
	if (_well_data != nullptr) {
		_well_data->UnUsed();
		delete _well_data;
		_well_data = nullptr;
	}
	if (_well_group != nullptr) {
		delete _well_group;
		_well_group = nullptr;
	}
	if ( _project != nullptr) {
		delete _project;
		_project = nullptr;
	}
}

bool LCData::setWorkData(const QString &pname, const QString &well_group_name, const QString &well_name, const QString &survey_name, const QString &seis_name, float replace_velocity)
{
	_project = aiDataServer::OpenProject( pname );
	if (_project == nullptr) { return false; }

	_well_group = (aiDataWellGroup*)(_project->GetItem(aiData::DT_WELL_GROUP, well_group_name));
	if (_well_group == nullptr) { return false; }

	_well_data = _well_group->GetWell( well_name );
	if (_well_data == nullptr) { return false; }
	_well_data->Use();

	_survey = (aiDataSurvey*)(_project->GetItem(aiData::DT_SURVEY, survey_name));
	if (_survey == nullptr) { return false;	}
	_survey->Use();

	_seis_data = (aiDataSeismic*)(_survey->GetItem(aiData::DT_SEISMIC, seis_name));
	if (_seis_data == nullptr) { return false; }
	_seis_data->Use();

	_replace_velocity = replace_velocity;
	/* get default time-depth curve */
	QVector<float> depth_vector = _well_data->GetDepth();
	QVector<float> sonic_vector = fillInvalid( _well_data->GetSonic() );

	setTimeDepthCurve( depthToTime(depth_vector, sonic_vector, replace_velocity) );

	QSettings &options = LCENV::MW->lcOptions();
	float time_ext = options.value("TimeAxisExt").toFloat();
	_time_min = 0.0f;
	_time_max = _time_depth_curve.first.back() + time_ext;
	return true;
}
void LCData::setTimeDepthCurve( const QPair<QVector<float>, QVector<float>> &curve) 
{ 
	_time_depth_curve = curve; 
}

float LCData::getTime(float depth) const
{
	QVector<float> time_vector = _time_depth_curve.first;
	QVector<float> depth_vector = _time_depth_curve.second;

	float time = LCENV::InvalidTime;
	for (int index = 0; index < depth_vector.size(); index++) {
		if (depth_vector[index] >= depth) {
			if (index > 0) {
				float scale = (depth - depth_vector[index - 1]) / (depth_vector[index] - depth_vector[index - 1]);
				time = time_vector[index - 1] + scale * (time_vector[index] - time_vector[index - 1]);
			}
			else {
				time = time_vector.first();
			}
			break;
		}
	}
	return time;
}
float LCData::getDepth(float time) const
{
	QVector<float> time_vector = _time_depth_curve.first;
	QVector<float> depth_vector = _time_depth_curve.second;
	float depth = LCENV::InvalidTime;
	for (int index = 0; index < time_vector.size(); index++) {
		if (time_vector[index] >= time) {
			if (index > 0) {
				float scale = (time - time_vector[index - 1]) / (time_vector[index] - time_vector[index - 1]);
				depth = depth_vector[index - 1] + scale * (depth_vector[index] - depth_vector[index - 1]);
			}
			else {
				depth = depth_vector.first();
			}
			break;
		}
	}
	return depth;
}