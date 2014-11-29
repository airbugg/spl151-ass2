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
	Containers::car_container[_car_id]->generateReport(_report_id);

	//std::ofstream report_file;
	//report_file.open(Simulator::_output_file, std::ios_base::app);
	//report_file << "[" << _report_id << "]" << "\n";
	//report_file << Containers::car_container[_car_id]->generateReport();

	//report_file.close();
}

void CarReport::toString()
{
}