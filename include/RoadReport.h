#pragma once

#include "Report.h"
#include "Simulator.h"
//#include "Containers.h"

#include <iostream>
#include <fstream>

class Containers;

class RoadReport :
	public Report
{
public:
	RoadReport();
	~RoadReport();
	RoadReport(int report_serial_num, int time, const std::string& report_id, const std::string& start_Junction, const std::string& end_Junction);

	void writeReport();
	void toString();

private:
	std::string _start_junction;
	std::string _end_junction;
};
