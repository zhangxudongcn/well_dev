#include "stdafx.h"
#include "lcalgorithm.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "cwp.h"
#include "par.h"


QVector<float> fillInvalid(const QVector<float> ori_vector)
{
	QVector<float> out_vector = ori_vector;

	float first_valid_value = ori_vector.first();
	for (const auto &item : ori_vector) {
		if (isnan(item) == false) {
			first_valid_value = item;
			break;
		}
	}
	for (auto &item : out_vector) {
		if (isnan(item) == true) {
			item = first_valid_value;
		}
		else {
			break;
		}
	}
	float last_valid_value = ori_vector.back();
	for (auto iter = ori_vector.rbegin(); iter != ori_vector.rend(); iter++) {
		if (isnan(*iter) == false) {
			last_valid_value = *iter;
			break;
		}
	}
	for (auto iter = out_vector.rbegin(); iter != out_vector.rend(); iter++) {
		if (isnan(*iter) == true) {
			*iter = last_valid_value;
		}
		else {
			break;
		}
	}
	return out_vector;
}

/* using gardner */
/* sonic: us / m 
   return: g/cm3
   */
QVector<float> VpToRHOB(const QVector<float> &sonic )
{
	QVector<float> rhob;
	rhob = sonic;
	for (auto &item : rhob) {
		item = 0.31f * powf(item, 0.25f);
	}
	return rhob;
}

/*
depth: m
sonic: us / m
replace_velocity: m / s
return time: s  depth: m
*/
QPair<QVector<float>, QVector<float>> depthToTime(const QVector<float> &depth, const QVector<float> &sonic, float replace_velocity)
{
	QVector<float> time, new_depth;
	float prev_depth = 0.f;
	float prev_vel = replace_velocity;
	float prev_time = 0.f;
	for (int index = 0; index < depth.size(); index++) {
		float t = prev_time + (depth[index] - prev_depth) / ( 1000000.f / prev_vel );
		time.push_back(t);
		prev_depth = depth[index];
		prev_vel = 1000000.f / sonic[index];
		prev_time = t;
	}
	return QPair<QVector<float>, QVector<float>>( time, depth );
}

/*
sonic: us/m
rhob: g/cm3
*/
QVector<float> impedance(const QVector<float> &sonic, const QVector<float> &rhob )
{
	QVector<float> imp(sonic.size());
	for (int index = 0; index < imp.size(); index++) {
		if (isnan( rhob[index] ) == false ) {
			imp[index] = (1000000.f / sonic[index]) * rhob[index];
		}
		else {
			imp[index] = (1000000.f / sonic[index]) * 0.31f * powf( 1000000.f / sonic[index], 0.25f);
		}
	}
	return imp;
}

QVector<float> reflectivities(const QVector<float> &impedance)
{
	QVector<float> result(impedance.size() - 1);
	for (int index = 0; index < result.size(); index++) {
		result[index] = (impedance[index + 1] - impedance[index]) / (impedance[index + 1] + impedance[index]);
	}
	result.push_back(result.back());
	return result;
}

QVector<float> rickerWavelet(int nt, float dt, float fpeak)
{
	QVector<float> wavelet( nt );
	ricker1_wavelet( nt,  dt,  fpeak, wavelet.data());
	return wavelet;
}

/*
ori_times: X: times(m), Y: value
dt: resampling interval(s)
*/
QPair<QVector<float>, QVector<float>> uniformResampleTimes(const QVector<float> &input_times, const QVector<float> &input_values, float dt)
{
	QVector<float> output_times;
	QVector<float> output_values;

	output_times.push_back(input_times.first());
	output_values.push_back(input_values.first());

	int result_index = 1;
	int prev_ori_index = 0;
	for  ( int ori_index = 1; ori_index < input_times.size(); ori_index++ ) {
		float time = result_index * dt;
		if ( input_times[ori_index] >= time ) {
			float scale = (time - input_times[ori_index - 1]) / (input_times[ori_index] - input_times[ori_index-1]);
			float value = input_values[ori_index - 1] + scale * (input_values[ori_index] - input_values[ori_index - 1]);
			output_times.push_back(time);
			output_values.push_back(value);
			result_index++;
			prev_ori_index = ori_index;
		}
	}
	if (prev_ori_index < input_times.size() - 1) {
		output_times.push_back(output_times.back() + dt );
		output_values.push_back(output_values.back());
	}
	return QPair<QVector<float>, QVector<float>>(output_times, output_values);
}
QVector<float> nonUniformResampleValues(const QVector<float> &input_uniform_times, const QVector<float> &input_uniform_values, float dt, const QVector<float> input_nonuniform_times)
{
	QVector<float> resample_values;
	float start_time = input_uniform_values.first();
	for (const auto &t : input_nonuniform_times) {
		int index = int((t - start_time) / dt );
		float scale = (t - input_uniform_times[index]) / (input_uniform_times[index+1] - input_uniform_times[index]);
		float value = input_uniform_values[index] + scale * (input_uniform_values[index + 1] - input_uniform_values[index]);
		resample_values.push_back(value);
	}
	return resample_values;
}

/* Automatic Gain Control--standard box */
void do_agc(float *data, int iwagc, int nt)
{
	static cwp_Bool first = cwp_true;
	static float *agcdata;
	register int i;
	register float val;
	register float sum;
	register int nwin;
	register float rms;


	/* allocate room for agc'd data */
	if (first) {
		first = cwp_false;
		agcdata = ealloc1float(nt);
	}


	/* compute initial window for first datum */
	sum = 0.0;
	for (i = 0; i < iwagc + 1; ++i) {
		val = data[i];
		sum += val*val;
	}
	nwin = 2 * iwagc + 1;
	rms = sum / nwin;
	agcdata[0] = (rms <= 0.0) ? 0.0 : data[0] / sqrt(rms);

	/* ramping on */
	for (i = 1; i <= iwagc; ++i) {
		val = data[i + iwagc];
		sum += val*val;
		++nwin;
		rms = sum / nwin;
		agcdata[i] = (rms <= 0.0) ? 0.0 : data[i] / sqrt(rms);
	}

	/* middle range -- full rms window */
	for (i = iwagc + 1; i <= nt - 1 - iwagc; ++i) {
		val = data[i + iwagc];
		sum += val*val;
		val = data[i - iwagc];
		sum -= val*val; /* rounding could make sum negative! */
		rms = sum / nwin;
		agcdata[i] = (rms <= 0.0) ? 0.0 : data[i] / sqrt(rms);
	}

	/* ramping off */
	for (i = nt - iwagc; i <= nt - 1; ++i) {
		val = data[i - iwagc];
		sum -= val*val; /* rounding could make sum negative! */
		--nwin;
		rms = sum / nwin;
		agcdata[i] = (rms <= 0.0) ? 0.0 : data[i] / sqrt(rms);
	}

	/* copy data back into trace */
	memcpy((void *)data, (const void *)agcdata, nt*FSIZE);

	return;
}