#pragma once

#include <string>

class Simulator;
class Containers;
//class EventComparator;

class Report
{
public:
	Report();
	virtual ~Report();

	virtual void writeReport() = 0;

	int time_slice();
	std::string report_id();
	int report_serial_num();
	void set_report_serial_num(int report_serial_num);
	void set_time_slice(int time_slice);
	void set_report_id(const std::string report_id);

protected:
	int _time_slice;
	int _report_serial_num;
	std::string _report_id;
};
