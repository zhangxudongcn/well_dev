#pragma once
#include <QVector>
#include <QPolygonF>
#include <QPair>

extern QVector<float> fillInvalid(const QVector<float> ori_vector);
extern QVector<float> VpToRHOB(const QVector<float> &sonic);

extern QPair<QVector<float>, QVector<float>> depthToTime(const QVector<float> &depth, const QVector<float> &sonic, float replace_velocity);

extern QVector<float> impedance(const QVector<float> &sonic, const QVector<float> &rhob );

extern QVector<float> rickerWavelet(int nt, float dt, float fpeak);

extern QVector<float> reflectivities(const QVector<float> &impedance);

extern QPair<QVector<float>,QVector<float>> uniformResampleTimes(  const QVector<float> &input_nonuniform_times, const QVector<float> &input_nonuniform_values, float dt);

extern QVector<float> nonUniformResampleValues(const QVector<float> &input_uniform_times, const QVector<float> &input_uniform_values, float dt, const QVector<float> input_nonuniform_times );

void do_agc(float *data, int iwagc, int nt);