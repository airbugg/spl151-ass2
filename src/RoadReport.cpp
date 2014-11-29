#include "RoadReport.h"

using namespace std;

RoadReport::RoadReport()
	:_start_junction(""), _end_junction("")
{
}

RoadReport::~RoadReport()
{
}

RoadReport::RoadReport(int report_serial_num, int time_slice, const std::string& report_id, const std::string& start_Junction, const std::string& end_junction)
	:_start_junction(start_Junction), _end_junction(end_junction)
{
	Report::set_report_serial_num(report_serial_num);
	Report::set_report_id(report_id);
	Report::set_time_slice(time_slice);
}

void RoadReport::writeReport()
{
	if (Containers::road_container.find(_start_junction + "," + _end_junction) != Containers::road_container.end())
		Containers::road_container[_start_junction + "," + _end_junction]->generateReport(_report_id);
	else
		std::cout << "are you trying to access a non-existant road?\n";
}

void RoadReport::toString()
{
}