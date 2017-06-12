#include "lcseismiccontainer.h"
#include "lcupdatenotifier.h"
#include "lcseismictitle.h"
#include "lcseismicwidget.h"
#include "lcdefine.h"
#include "lcmainwindow.h"
#include <QLabel>
#include <QVBoxLayout>
LCSeismicContainer::LCSeismicContainer(QWidget *parent ) 
	: QWidget(parent)
{
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);


	setFixedWidth( widthCM() * LCENV::PixelPerCM);
	_seismic_title = new LCSeismicTitle(this);
	_seismic_widget = new LCSeismicWidget(this);
	_name_widget = new QLabel("Seismic", this);
	_name_widget->setAlignment(Qt::AlignCenter);

	QVBoxLayout *layout = new QVBoxLayout();
	layout->setContentsMargins(QMargins());
	layout->setSpacing(0);
	layout->addWidget(_seismic_title);
	layout->addWidget(_seismic_widget);
	layout->addWidget(_name_widget);
	setLayout(layout);
}
LCSeismicContainer::~LCSeismicContainer()
{}

float LCSeismicContainer::widthCM() const
{
	QSettings &options = LCENV::MW->lcOptions();
	float width_one_trace = 1 / options.value("Seismic/TracesPerCM").toFloat();
	int trace_num = options.value("WellSeismic/TraceNum").toInt();
	float margin = options.value("WellSeismic/Margin").toFloat();
	float container_width_cm = width_one_trace * ( trace_num + 1 ) + margin * 2;
	return container_width_cm;
}


void LCSeismicContainer::onUpdate(const LCUpdateNotifier &update_notifier)
{
	_seismic_title->onUpdate(update_notifier);
	_seismic_widget->onUpdate(update_notifier);
}

void LCSeismicContainer::optionsChanged()
{}