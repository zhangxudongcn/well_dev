#include "lcsyntheticcontainer.h"
#include "lcupdatenotifier.h"
#include "lcsynthetictitle.h"
#include "lcsyntheticwidget.h"
#include "lcdefine.h"
#include "lcmainwindow.h"
#include <QLabel>
#include <QVBoxLayout>
LCSyntheticContainer::LCSyntheticContainer(QWidget *parent)
	: QWidget(parent)
{
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	setFixedWidth(widthCM() * LCENV::PixelPerCM);

	_synthetic_title = new LCSyntheticTitle(this);
	_synthetic_widget = new LCSyntheticWidget(this);
	QLabel *_name_widget = new QLabel("Synthetic", this);
	_name_widget->setAlignment(Qt::AlignCenter);

	QVBoxLayout *layout = new QVBoxLayout();
	layout->setContentsMargins(QMargins());
	layout->setSpacing(0);
	layout->addWidget(_synthetic_title);
	layout->addWidget(_synthetic_widget);
	layout->addWidget(_name_widget);
	setLayout(layout);
}
LCSyntheticContainer::~LCSyntheticContainer()
{}

float LCSyntheticContainer::widthCM() const 
{
	QSettings &options = LCENV::MW->lcOptions();
	float width_one_trace = 1 / options.value("Seismic/TracesPerCM").toFloat();
	int trace_num = options.value("Synthetic/TraceNum").toInt();
	float gap = options.value("Synthetic/Gap").toFloat();
	float margin = options.value("Synthetic/Margin").toFloat();
	float container_width_cm = width_one_trace * trace_num * 2 + gap + margin * 2;
	return container_width_cm;
}

void LCSyntheticContainer::onUpdate(const LCUpdateNotifier &update_notifier)
{
	_synthetic_title->onUpdate(update_notifier);
	_synthetic_widget->onUpdate(update_notifier);
}
void LCSyntheticContainer::optionsChanged()
{}