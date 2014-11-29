#include "JunctionReport.h"

std::string Simulator::_output_file;
using namespace std;

JunctionReport::JunctionReport()
	:_junc_id("")
{
}

JunctionReport::JunctionReport(int report_serial_num, int time_slice, const std::string& report_id, const std::string& junction_id)
	: _junc_id(junction_id)
{
	Report::set_report_serial_num(report_serial_num);
	Report::set_report_id(report_id);
	Report::set_time_slice(time_slice);
}

JunctionReport::~JunctionReport()
{
}

void JunctionReport::writeReport()
{
	if (Containers::junction_container.find(_junc_id) != Containers::junction_container.end())
		Containers::junction_container[_junc_id]->generateReport(_report_id);
	else
		std::cout << "are you trying to access a non-existant junction? \n";

}

void JunctionReport::toString()
{
}
