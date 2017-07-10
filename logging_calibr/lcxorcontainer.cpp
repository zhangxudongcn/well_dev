#include "stdafx.h"
#include "lcxorcontainer.h"
#include "lcupdatenotifier.h"
#include "lcdefine.h"
#include "lcmainwindow.h"
#include "lcdata.h"
#include "lcalgorithm.h"
#include "ai_data_include.h"
extern "C" void convolve_cwp(int lx, int ifx, float *x, int ly, int ify, float *y, int lz, int ifz, float *z);
extern "C" void xcor(int lx, int ifx, float *x, int ly, int ify, float *y,	int lz, int ifz, float *z);
LCXorContainer::LCXorContainer( QWidget *parent, Qt::WindowFlags f ) : QWidget( parent, f )
{
	ui.setupUi(this);
	ui._lag_xor_chartview->setChart(new QChart());
}

LCXorContainer::~LCXorContainer()
{}

void LCXorContainer::onUpdate(const LCUpdateNotifier &update_notifier)
{
	if (update_notifier.dataChangedFlag() & LCENV::CurrentWellChanged || update_notifier.dataChangedFlag() & LCENV::TimeDepthCurveChanged) {
		setLagXorChart();
	}
}
void LCXorContainer::optionsChanged()
{

}

void LCXorContainer::lagApplaySlot()
{
	setLagXorChart();
}

void LCXorContainer::setLagXorChart()
{
	ui._lag_xor_chartview->chart()->removeAllSeries();
	QSettings &options = LCENV::MW->lcOptions();

	int il_num = options.value("WellSeismic/ILTraceNum").toInt();
	int xl_num = options.value("WellSeismic/XLTraceNum").toInt();
	QVector<LCTrace> all_trace_data = LCENV::MW->lcData()->wellSeismic(il_num, xl_num);

	aiDataWell *well_data = LCENV::MW->lcData()->wellData();

	QVector<float> imped = fillInvalid(well_data->GetImpedance());
	if (imped.size() == 0) {
		QVector<float> sonic = fillInvalid(well_data->GetSonic());
		QVector<float> rhob = well_data->GetDensity(); /* kg/m3 */
		for (auto &item : rhob) {
			if (isnan(item) == false) {
				item /= 1000.f;
			}
		}
		imped = impedance(sonic, rhob);
	}
	/* get wavelet */
	LCWavelet wavelet = LCENV::MW->lcData()->currentWavelet();
	aiDataSeismic *seis_data = LCENV::MW->lcData()->seismicData();
	aiSampleRange sample_range = seis_data->GetSampleRange();
	float sample_interval = sample_range.GetStep() / 1000.f; /* ms->s */
	LCTimeDepthCurve time_depth_curve = LCENV::MW->lcData()->currentTimeDepthCurve();

	LCTrace resample_imped = uniformResampleTimes(time_depth_curve.first, imped, sample_interval);
	LCTrace resample_wavelet = uniformResampleTimes(wavelet.first, wavelet.second, sample_interval);

	QVector<float> resample_refl = reflectivities(resample_imped.second);

	int start_index = ui._lag_start_time_spinbox->value() / sample_range.GetStep();
	int end_index = ui._lag_end_time_spinbox->value() / sample_range.GetStep();
	int half_lag_num = ui._lag_range_spinbox->value() / sample_range.GetStep();
	QVector<float> ext_resample_refl(resample_refl.size() + half_lag_num * 2);
	ext_resample_refl.fill(0.f);

	memcpy(&ext_resample_refl[half_lag_num], &resample_refl[0], resample_refl.size() * sizeof(float));
	QVector<float> trace_out(resample_refl.size());
	QVector<float> xor_result(end_index - start_index + 1);
	QVector<float> max_xor_array(half_lag_num * 2 + 1);
	for (int index = 0; index < half_lag_num * 2 + 1; index++) {
		convolve_cwp(resample_refl.size(), index, ext_resample_refl.data(), resample_wavelet.second.size(), 0, resample_wavelet.second.data(), trace_out.size(), 0, trace_out.data());
		xcor(end_index - start_index + 1, start_index, trace_out.data(), end_index - start_index + 1, start_index, all_trace_data.back().second.data(),
			end_index - start_index + 1, 0, xor_result.data());
		std::sort(xor_result.begin(), xor_result.end() );
		max_xor_array[index] = xor_result.back();
	}
	QLineSeries *series = new QLineSeries();

	for (int value = -ui._lag_range_spinbox->value(), index = 0; value <= ui._lag_range_spinbox->value(); value += sample_range.GetStep()) {
		series->append(value, max_xor_array[index++]);
	}
	ui._lag_xor_chartview->chart()->addSeries(series);
	ui._lag_xor_chartview->chart()->createDefaultAxes();
}