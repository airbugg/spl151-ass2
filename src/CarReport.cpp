#include "CarReport.h"

CarReport::CarReport()
	:_car_id("")
{
}

CarReport::~CarReport()
{
}

CarReport::CarReport(int report_serial_num, int time_slice, const std::string& report_id, const std::string& car_id)
	:_car_id(car_id)
{
	Report::set_report_serial_num(report_serial_num);
	Report::set_time_slice(time_slice);
	Report::set_report_id(report_id);
}

void CarReport::writeReport()
{
	if (Containers::car_container.find(_car_id) != Containers::car_container.end())
		Containers::car_container[_car_id]->generateReport(_report_id);
	else
		std::cout << "are you trying to produce a report of a non-existant car?\n";
}

void CarReport::toString()
{
}
