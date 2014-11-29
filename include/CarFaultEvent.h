#pragma once

#include "Event.h"
#include "Simulator.h"
//#include "Containers.h"

class Containers;

class CarFaultEvent :
	public Event
{
public:
	CarFaultEvent();
	~CarFaultEvent();
	CarFaultEvent(int event_serial_num, std::string event_id, int time_slice, std::string car_Id, int fault_time);
	void performEvent();
	void toString();

private:
	int _fault_time;
};
