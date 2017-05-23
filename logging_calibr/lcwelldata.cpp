#include "stdafx.h"
#include "lcwelldata.h"
#include <QString>
#include <QList>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <algorithm>

void LCSubLogData::setMinMaxValue( double null_value )
{
	LCSubLogData tmp_data = *this;
	std::sort(tmp_data.begin(), tmp_data.end());
	for( auto &item : tmp_data ) {
		if( item == null_value ) {
			item = tmp_data.back();
		}
	}
	std::sort(tmp_data.begin(), tmp_data.end());
	_min_value = tmp_data.first();
	_max_value = tmp_data.back();
	qDebug( "range: %f, %f, %f", _min_value, _max_value, null_value );
}
class LCWellDataPri {
public:
	LCWellDataPri() {}
	void reset();
	bool loadFromLasFile(const QString &las_name);
	int readVerInfo(const QStringList &las_buffer, int index);
	int readWellInfo(const QStringList &las_buffer, int index);
	int readCurveInfo(const QStringList &las_buffer, int index);
	int readParaInfo( const QStringList &las_buffer, int index );
	int readOtherInfo( const QStringList &las_buffer, int index );
	int readLogData( const QStringList &las_buffer, int index );
public:
	double _vers;
	LC::WrapType _wrap_type;
	double _start_depth, _stop_depth, _step_depth;
	QString _depth_unit;
	double _null_value;
	QString _company;
	QString _well_name;
	QString _field_name;
	QString _location;
	QString _service_company;
	QString _log_date;
	QString _unique_well_id;

	QList<QString> _mnems;
	QList<QString> _units;
	QList<QString> _descs;
	QVector<LCSubLogData> _log_data;
};

bool LCWellDataPri::loadFromLasFile(const QString &las_name)
{
	reset();
	QFile las_file(las_name);
	if (las_file.open(QIODevice::ReadOnly) == false) {
		qDebug("can't open las file");
		return false;
	}
	QTextStream t_stream(&las_file);
	QString all_str = t_stream.readAll();
	QStringList str_list = all_str.split("\n");
	//qDebug("all_str is %s", all_str.toStdString().c_str());
	int index = readVerInfo( str_list, 0 );
	index = readWellInfo(str_list, index);
	index = readCurveInfo(str_list, index);
	index = readParaInfo(str_list, index);
	index = readOtherInfo(str_list, index);
	index = readLogData(str_list, index);
	return true;
}

void LCWellDataPri::reset()
{
	_mnems.clear();
	_units.clear();
	_descs.clear();
	_log_data.clear();
}
int LCWellDataPri::readVerInfo(const QStringList &las_buffer, int index)
{
	/* find version information */
	int old_index = index;
	while (index < las_buffer.size()) {
		if (las_buffer[index].toUpper().indexOf( "~VERSION" ) >= 0 ) {
			index++;
			break;
		}
		else {
			index++;
		}
	}
	/* read ver */
	while (index < las_buffer.size()) {
		if (las_buffer[index].toUpper().indexOf("VERS" ) >= 0) {
			_vers = las_buffer[index].split(":")[0].split(".")[1].toFloat();
			index++;
			break;
		}
	}
	/* read wrap type */
	_wrap_type = LC::OneLine;
	while (index < las_buffer.size()) {
		if (las_buffer[index].toUpper().indexOf("WRAP"  ) >= 0) {
			if (las_buffer[index].split(":")[0].split(".")[1].toUpper().indexOf("YES" ) ) {
				_wrap_type = LC::MultiLine;
			}
			index++;
			break;
		}
	}
	return index;
}
int LCWellDataPri::readWellInfo(const QStringList &las_buffer, int index)
{
	/* find well infomation */
	while (index < las_buffer.size()) {
		if (las_buffer[index].toUpper().indexOf("~WELL") >= 0) {
			index++;
			break;
		}
		else {
			index++;
		}
	}
	while (index < las_buffer.size() && las_buffer[index].toUpper().indexOf("~") < 0) {
		if (las_buffer[index].size() == 0 || las_buffer[index][0] == '#') {
			index++;
			continue;
		}
		QString mnem = las_buffer[index].split(":")[0].split(".")[0];
		QString mdata = las_buffer[index].split(":")[0].split(".")[1];
		QString desc = las_buffer[index].split(":")[1];
		if (mnem.toUpper().indexOf("STRT") >= 0) {
			_start_depth = mdata.split(" ", QString::SkipEmptyParts)[1].toDouble();
			_depth_unit = mdata.split(" ", QString::SkipEmptyParts)[0];
		}
		else if (mnem.toUpper().indexOf("STOP") >= 0) {
			_stop_depth = mdata.split(" ", QString::SkipEmptyParts)[1].toDouble();
		}
		else if (mnem.toUpper().indexOf("STEP") >= 0) {
			_step_depth = mdata.split(" ", QString::SkipEmptyParts)[1].toDouble();
		}
		else if (mnem.toUpper().indexOf("NULL") >= 0) {
			qDebug( "null: %s", mdata.toStdString().c_str( ) );
			_null_value = mdata.toDouble();
		}
		else if (mnem.toUpper().indexOf("COMP") >= 0) {
			_company = mdata;
		}
		else if (mnem.toUpper().indexOf("WELL") >= 0) {
			_well_name = mdata;
		}
		else if (mnem.toUpper().indexOf("FLD") >= 0) {
			_field_name = mdata;
		}
		else if (mnem.toUpper().indexOf("LOC") >= 0) {
			_location = mdata;
		}
		else if (mnem.toUpper().indexOf("PROV") >= 0) {
			
		}
		else if (mnem.toUpper().indexOf("SRVC") >= 0) {
			_service_company = mdata;
		}
		else if (mnem.toUpper().indexOf("DATE") >= 0) {
			_log_date = mdata;
		}
		else if (mnem.toUpper().indexOf("UWI") >= 0) {
			_unique_well_id = mdata;
		}
		else {

		}
		index++;
	}
	return index;
}
int LCWellDataPri::readCurveInfo(const QStringList &las_buffer, int index)
{
	/* find curve infomation */
	while (index < las_buffer.size()) {
		if (las_buffer[index].toUpper().indexOf("~CURVE") >= 0) {
			index++;
			break;
		}
		else {
			index++;
		}
	}
	while (index < las_buffer.size() && las_buffer[index].toUpper().indexOf("~") < 0) {
		if (las_buffer[index].size() == 0 || las_buffer[index][0] == '#') {
			index++;
			continue;
		}
		_mnems.push_back(las_buffer[index].split(":")[0].split(".")[0]);
		_units.push_back(las_buffer[index].split(":")[0].split(".")[1]);
		_descs.push_back(las_buffer[index].split(":")[1]);
		index++;
	}
	return index;
}
int LCWellDataPri::readParaInfo(const QStringList &las_buffer, int index)
{
	/* find para infomation */
	int old_index = index;
	while (index < las_buffer.size()) {
		if (las_buffer[index].toUpper().indexOf("~PARA") >= 0) {
			index++;
			break;
		}
		else {
			index++;
		}
	}
	/* 设置index为原始位置，因为PARA是可选的 */
	if (index == las_buffer.size()) {
		index = old_index;
	}
	while (index < las_buffer.size() && las_buffer[index].toUpper().indexOf("~") < 0) {
		if (las_buffer[index].size() == 0 || las_buffer[index][0] == '#') {
			index++;
			continue;
		}
		index++;
	}
	return index;
}
int LCWellDataPri::readOtherInfo(const QStringList &las_buffer, int index)
{
	/* find other infomation */
	int old_index = index;
	while (index < las_buffer.size()) {
		if (las_buffer[index].toUpper().indexOf("~OTHER") >= 0) {
			index++;
			break;
		}
		else {
			index++;
		}
	}
	/* 设置index为原始位置，因为OTHER是可选的 */
	if (index == las_buffer.size()) {
		index = old_index;
	}
	while (index < las_buffer.size() && las_buffer[index].toUpper().indexOf("~") < 0) {
		if (las_buffer[index].size() == 0 || las_buffer[index][0] == '#') {
			index++;
			continue;
		}
		index++;
	}
	return index;
}
int LCWellDataPri::readLogData(const QStringList &las_buffer, int index)
{
	/* find well data */
	while (index < las_buffer.size()) {
		if (las_buffer[index].toUpper().indexOf("~A") >= 0) {
			index++;
			break;
		}
		else {
			index++;
		}
	}
	_log_data.resize(_mnems.size());
	while (index < las_buffer.size() ) {
		if (las_buffer[index].size() == 0 || las_buffer[index][0] == '#') {
			index++;
			continue;
		}
		QStringList str_list = las_buffer[index].split(" ", QString::SkipEmptyParts);
		if (str_list.size() == _mnems.size()) {
			for (int str_index = 0; str_index < str_list.size(); str_index++ ) {
				_log_data[str_index].push_back(str_list[str_index].toDouble());
			}
		}
		index++;
	}
	for (auto &item : _log_data) {
		item.setMinMaxValue( -999.2500 );
	}
	return index;
}

LCWellData::LCWellData() : _pri_data(new LCWellDataPri())
{
}

LCWellData::LCWellData(const QString &las_name) : _pri_data(new LCWellDataPri())
{
	loadFromLasFile(las_name);
}
LCWellData::~LCWellData()
{
	_pri_data->reset();
	delete _pri_data;
}

double LCWellData::version() const
{
	return _pri_data->_vers;
}

LC::WrapType LCWellData::wrapType() const
{
	return _pri_data->_wrap_type;
}
double LCWellData::startDepth() const
{
	return _pri_data->_start_depth;
}
double LCWellData::stopDepth() const
{
	return _pri_data->_stop_depth;
}
double LCWellData::stepDepth() const
{
	return _pri_data->_step_depth;
}
double LCWellData::nullValue() const
{
	return _pri_data->_null_value;
}
const QString &LCWellData::company() const
{
	return _pri_data->_company;
}
const QString &LCWellData::wellName() const
{
	return _pri_data->_well_name;
}
const QString &LCWellData::fieldName() const
{
	return _pri_data->_field_name;
}
const QString &LCWellData::location() const
{
	return _pri_data->_location;
}
const QString &LCWellData::serviceCompany() const
{
	return _pri_data->_service_company;
}
const QString &LCWellData::logDate() const
{
	return _pri_data->_log_date;
}
const QString &LCWellData::uniqueWellId() const
{
	return _pri_data->_unique_well_id;
}
const QList<QString> &LCWellData::mnems() const
{
	return _pri_data->_mnems;
}
const QList<QString> &LCWellData::units() const
{
	return _pri_data->_units;
}
const QList<QString> &LCWellData::descs() const
{
	return _pri_data->_descs;
}
const QVector<LCSubLogData> &LCWellData::logData() const
{
	return _pri_data->_log_data;
}
bool LCWellData::loadFromLasFile(const QString &las_name)
{
	return _pri_data->loadFromLasFile(las_name);
}
