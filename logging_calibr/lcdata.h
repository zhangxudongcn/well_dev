#pragma once
#include <QVector>
#include <QString>
#include <QMap>
#include <QStringList>
class aiDataWell {
public:
	aiDataWell( const QString &name );
	~aiDataWell();
	QString wellName() const { return _well_name; }
	QVector<float> GetCurve(const QString& sName) const;
	QVector<float> GetCurve( int index ) const;
	QStringList GetCurveNames() const;
	double nullValue() const { return -999.2500; }
private:
	QString _well_name;
	QStringList _curve_names;
	QVector<QVector<float>> _curves;
};
class aiDataWellGroup {
public:
	aiDataWellGroup();
	aiDataWell* GetWell(const QString& sName, bool bAutoCreate = false);
private:
	aiDataWell *_data_well;
};
class aiDataSeismic {
public:
	aiDataSeismic() {};
	~aiDataSeismic() {};
};