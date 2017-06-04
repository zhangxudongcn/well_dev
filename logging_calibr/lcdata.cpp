#include "lcdata.h"
#include "lcdefine.h"
#include <QFile>
#include <QTextStream>

aiDataWell::aiDataWell( const QString &name ) : _well_name(name)
{
	_curve_names << "DEPTH" << "RHOB" << "DT" << "GR.API" << "AI" << "AI_rel" << "PHIE";

	_curves.resize(_curve_names.size());

	QFile log_file("H:\\workspace\\well_data.txt");
	log_file.open(QIODevice::ReadOnly);
	QTextStream t_out(&log_file);
	for (;;) {
		QString line = t_out.readLine();
		if (line.isNull()) {
			break;
		}
		QStringList s_list = line.split(' ', QString::SkipEmptyParts);
		for (int i = 0; i < _curve_names.size(); i++) {
			_curves[i].push_back(s_list[i].toFloat());
		}
	}
	log_file.close();
}
aiDataWell::~aiDataWell()
{

}
QVector<float> aiDataWell::GetCurve(const QString& sName) const
{
	int index = _curve_names.indexOf(sName);
	return GetCurve(index);
}


QVector<float> aiDataWell::GetCurve(int index) const
{
	return _curves[index];
}
QStringList aiDataWell::GetCurveNames() const
{
	QStringList result;
	result << "DEPTH" << "RHOB" << "DT" << "GR.API" << "AI" << "AI_rel" << "PHIE";
	return result;
}

aiDataWellGroup::aiDataWellGroup() : _data_well(nullptr)
{
	LCENV::WellData = this;
	_data_well = new aiDataWell( "F0" );
}
aiDataWell* aiDataWellGroup::GetWell(const QString& sName, bool bAutoCreate )
{
	return _data_well;
}
