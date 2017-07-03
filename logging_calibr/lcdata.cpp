#include "stdafx.h"

#include "lcdata.h"
#include "lcdefine.h"
#include "lcalgorithm.h"
#include "lcmainwindow.h"
#include "lcupdatenotifier.h"
#include <QFile>
#include <QTextStream>
#include "ai_data_include.h"

LCData::LCData() : _project(nullptr), _well_group(nullptr), _well_data(nullptr), _survey(nullptr), _seis_data(nullptr), _replace_velocity(-1), _current_time_depth_curve_index(-1)
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

	addTimeDepthCurve( depthToTime(depth_vector, sonic_vector, replace_velocity) );

	QSettings &options = LCENV::MW->lcOptions();
	float time_ext = options.value("TimeAxisExt").toFloat();
	_time_min = 0.0f;
	_time_max = currentTimeDepthCurve().first.back() + time_ext;

	// set default wavelet: 20Hz ricker wavelet
	LCWavelet wavelet = rickerWavelet(400, 0.001, 20);
	addWavelet(wavelet);
	return true;
}	
LCTimeDepthCurve LCData::currentTimeDepthCurve() const
{
	LCTimeDepthCurve time_depth_curve;
	if (currentTimeDepthCurveIndex() >= 0) {
		time_depth_curve = _time_depth_curve_array[currentTimeDepthCurveIndex()];
	}
	return time_depth_curve;
}

void LCData::setCurrentTimeDepthCurveIndex(int index)
{
	if (_current_time_depth_curve_index != index) {
		_current_time_depth_curve_index = index;
		LCUpdateNotifier notifier;
		notifier.setDataChangedFlag(LCENV::TimeDepthCurveChanged);
		LCENV::MW->onUpdate(notifier);
	}
}

void LCData::addTimeDepthCurve( const LCTimeDepthCurve &time_depth_curve) 
{ 
	_time_depth_curve_array.push_back( time_depth_curve );
	_current_time_depth_curve_index = _time_depth_curve_array.size() - 1;
	LCUpdateNotifier notifier;
	notifier.setDataChangedFlag(LCENV::TimeDepthCurveChanged);
	LCENV::MW->onUpdate(notifier);
}

void LCData::setCurrentTimeDepthCurve(const LCTimeDepthCurve &curve)
{
	_time_depth_curve_array[_current_time_depth_curve_index] = curve;
	LCUpdateNotifier notifier;
	notifier.setDataChangedFlag(LCENV::TimeDepthCurveChanged);
	LCENV::MW->onUpdate(notifier);
}

LCWavelet LCData::currentWavelet() const
{
	LCWavelet wavelet;
	if (_current_wavelet_index >= 0) {
		wavelet = _wavelet_array[_current_wavelet_index];
	}
	return wavelet;
}

void LCData::setCurrentWaveletIndex(int index)
{
	_current_wavelet_index = index;
}

void LCData::addWavelet(const LCWavelet &wavelet)
{
	_wavelet_array.push_back(wavelet);
	_current_wavelet_index = _wavelet_array.size() - 1;
	LCUpdateNotifier notifier;
	notifier.setDataChangedFlag(LCENV::WaveletChanged);
	LCENV::MW->onUpdate(notifier);
}
void LCData::setCurrentWavelet(const LCWavelet &wavelet)
{
	_wavelet_array[_current_wavelet_index] = wavelet;
	LCUpdateNotifier notifier;
	notifier.setDataChangedFlag(LCENV::WaveletChanged);
	LCENV::MW->onUpdate(notifier);
}

float LCData::getTime(float depth) const
{
	QVector<float> time_vector = currentTimeDepthCurve().first;
	QVector<float> depth_vector = currentTimeDepthCurve().second;

	float time = LCENV::InvalidTime;
	for (int index = 0; index < depth_vector.size(); index++) {
		if (depth_vector[index] >= depth) {
			if (index > 0) {
				float scale = (depth - depth_vector[index - 1]) / (depth_vector[index] - depth_vector[index - 1]);
				time = time_vector[index - 1] + scale * (time_vector[index] - time_vector[index - 1]);
			}
			else {
				time = 0.f;
			}
			break;
		}
	}
	return time;
}
float LCData::getDepth(float time) const
{
	QVector<float> time_vector = currentTimeDepthCurve().first;
	QVector<float> depth_vector = currentTimeDepthCurve().second;
	float depth = LCENV::InvalidTime;
	for (int index = 0; index < time_vector.size(); index++) {
		if (time_vector[index] >= time) {
			if (index > 0) {
				float scale = (time - time_vector[index - 1]) / (time_vector[index] - time_vector[index - 1]);
				depth = depth_vector[index - 1] + scale * (depth_vector[index] - depth_vector[index - 1]);
			}
			else {
				depth = 0.f;
			}
			break;
		}
	}
	return depth;
}

QVector<QPair<QVector<float>, QVector<float>>> LCData::wellSeismic(int il_num, int xl_num)
{
	aiDataWell *well_data = LCENV::MW->lcData()->wellData();
	aiGridCrd well_coord = LCENV::MW->lcData()->survey()->Convert(well_data->GetPos());
	aiDataSeismic *seis_data = LCENV::MW->lcData()->seismicData();
	aiSampleRange sample_range = seis_data->GetSampleRange();
	QVector<float> trace_buffer(sample_range.GetCount());
	QVector<float> average_buffer(sample_range.GetCount());
	std::fill(average_buffer.begin(), average_buffer.end(), 0);
	QVector<QPair<QVector<float>, QVector<float>>> all_trace_data; /* inline + current + xline + average */

	for (int cmp = well_coord.cmp - xl_num / 2; cmp <= well_coord.cmp + xl_num / 2; cmp++) {
		if (cmp != well_coord.cmp) {
			QPair<QVector<float>, QVector<float>> trace_data;
			trace_data.first.resize(sample_range.GetCount());
			trace_data.second.resize(sample_range.GetCount());
			seis_data->ReadSample(aiGridCrd(well_coord.line, cmp), trace_data.second.data());
			for (int sample_index = 0; sample_index < trace_data.second.size(); sample_index++) {
				if (isnan(trace_data.second[sample_index])) {
					trace_data.second[sample_index] = 0.f;
				}
				trace_data.first[sample_index] = sample_range.GetStart() + sample_range.GetStep() * sample_index;
				average_buffer[sample_index] += trace_data.second[sample_index];
			}
			all_trace_data.push_back(trace_data);
		}
	}
	{
		QPair<QVector<float>, QVector<float>> trace_data;
		trace_data.first.resize(sample_range.GetCount());
		trace_data.second.resize(sample_range.GetCount());
		seis_data->ReadSample(well_coord, trace_data.second.data());
		for (int sample_index = 0; sample_index < trace_data.second.size(); sample_index++) {
			if (isnan(trace_data.second[sample_index])) {
				trace_data.second[sample_index] = 0.f;
			}				
			trace_data.first[sample_index] = sample_range.GetStart() + sample_range.GetStep() * sample_index;
			average_buffer[sample_index] += trace_data.second[sample_index];
		}
		all_trace_data.push_back(trace_data);
	}
	for (int line = well_coord.line - il_num / 2; line <= well_coord.line + il_num / 2; line++) {
		if (line != well_coord.line) {
			QPair<QVector<float>, QVector<float>> trace_data;
			trace_data.first.resize(sample_range.GetCount());
			trace_data.second.resize(sample_range.GetCount());			
			seis_data->ReadSample(aiGridCrd(line, well_coord.cmp), trace_data.second.data());
			for (int sample_index = 0; sample_index < trace_data.second.size(); sample_index++) {
				if (isnan(trace_data.second[sample_index])) {
					trace_data.second[sample_index] = 0.f;
				}
				trace_data.first[sample_index] = sample_range.GetStart() + sample_range.GetStep() * sample_index;
				average_buffer[sample_index] += trace_data.second[sample_index];;
			}
			all_trace_data.push_back(trace_data);
		}
	}
	{
		QPair<QVector<float>, QVector<float>> trace_data;
		trace_data.first = all_trace_data.first().first;
		trace_data.second.resize(sample_range.GetCount());
		int trace_num = il_num + xl_num - 1;
		for (int sample_index = 0; sample_index < average_buffer.size(); sample_index++) {
			trace_data.second[sample_index] = average_buffer[sample_index] / trace_num;
		}

		all_trace_data.push_back(trace_data);
	}
	return all_trace_data;
}