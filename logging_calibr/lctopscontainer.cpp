#include "lctopscontainer.h"
#include "lctopstitle.h"
#include "lctopswidget.h"
#include "lcupdatenotifier.h"
#include "lcdefine.h"
#include "lcmainwindow.h"
#include <QLabel>
#include <QVBoxLayout>
LCTopsContainer::LCTopsContainer(QWidget *parent)	: QWidget(parent)
{
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	_tops_title = new LCTopsTitle(this);
	_tops_widget = new LCTopsWidget(this);
	_name_widget = new QLabel("Tops", this);
	_name_widget->setAlignment(Qt::AlignCenter);

	QSettings &options = LCENV::MW->lcOptions();
	int tops_width_pixel = options.value("Tops/TopsWidth").toFloat() * LCENV::PixelPerCM;
	setFixedWidth(tops_width_pixel);

	QVBoxLayout *layout = new QVBoxLayout();
	layout->setContentsMargins(QMargins());
	layout->setSpacing(0);
	layout->addWidget(_tops_title);
	layout->addWidget(_tops_widget);
	layout->addWidget(_name_widget);
	setLayout(layout);
}
LCTopsContainer::~LCTopsContainer()
{

}
float  LCTopsContainer::widthCM() const
{
	QSettings &options = LCENV::MW->lcOptions();
	return options.value("Tops/TopsWidth").toFloat();
}

void LCTopsContainer::onUpdate(const LCUpdateNotifier &update_notifier)
{
	_tops_title->onUpdate(update_notifier);
	_tops_widget->onUpdate(update_notifier);
}

void LCTopsContainer::optionsChanged()
{

}
