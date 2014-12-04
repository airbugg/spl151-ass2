#pragma once

#include "Report.h"
#include "Simulator.h"

#include <iostream>
#include <fstream>

class Containers;

class CarReport :
	public Report
{
public:
	CarReport();
	~CarReport();
	CarReport(int report_serial_num, int time_slice, const std::string& report_id, const std::string& car_id);

	// methods
	void writeReport();
	void toString();

private:
	std::string _car_id;
};
