#include "Report.h"
#include <iostream>

Report::Report()
	:_time_slice(0), _report_id(""), _report_serial_num(0)
{
}

Report::~Report()
{
}

void Report::set_time_slice(int time_slice) { _time_slice = time_slice; }

void Report::set_report_serial_num(int report_serial_num) { _report_serial_num = report_serial_num; }

int Report::time_slice() { return _time_slice; }

void Report::set_report_id(const std::string report_id) { _report_id = report_id; }

std::string Report::report_id() { return _report_id; }

int Report::report_serial_num() { return _report_serial_num; }