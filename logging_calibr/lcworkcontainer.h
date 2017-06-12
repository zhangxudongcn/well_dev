#pragma once
#include <QScrollArea>
#include <QWidget>
class LCTopsContainer;
class LCWellContainer;
class LCSyntheticContainer;
class LCSeismicContainer;
class LCUpdateNotifier;
class LCWorkContainer : public QScrollArea {
public:
	LCWorkContainer(QWidget *parent = Q_NULLPTR);
	~LCWorkContainer();
	float scrollWidthCM() const;
	virtual void onUpdate(const LCUpdateNotifier &update_notifier);
	virtual void optionsChanged();
public slots:
	virtual void setDeviceYValue(int value);
protected:
	void resizeEvent(QResizeEvent *event) override;
private:
	LCTopsContainer *_tops_container;
	LCWellContainer *_well_container;
	LCSyntheticContainer *_synthetic_container;
	LCSeismicContainer *_il_seismic_container, *_xl_seismic_container;
};
