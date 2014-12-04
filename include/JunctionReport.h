#pragma once

#include "Report.h"
#include "Simulator.h"

#include <iostream>
#include <fstream>

class Containers;

class JunctionReport :
	public Report
{
public:
	JunctionReport();
	JunctionReport(int report_serial_num, int timeSlice, const std::string& repID, const std::string& junc_id);
	~JunctionReport();
	void writeReport();
	void toString();

private:
	std::string _junc_id;
};
