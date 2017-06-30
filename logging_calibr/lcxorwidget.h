#pragma once
#include <QScrollArea>
#include <QWidget>
#include <QtCharts>
using namespace QtCharts;
class LCXorWidget : pulic QWidget {
public:
    LCXorWidget( QWidget *parent = Q_NULLPTR, Qt::windowFlags f = Qt::windowFlags());
    ~LCXorWidget();
private:
    QChartView *_lag_xor_widget;
    QChartView *_rotation_xor_widget;
};