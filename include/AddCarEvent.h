#pragma once

#include "Event.h"
#include "Simulator.h"

class Containers;

class AddCarEvent :
	public Event
{
public:
	AddCarEvent();
	~AddCarEvent();

	AddCarEvent(int event_serial_num, std::string event_id, int time_slice, const std::string& car_Id, const std::string& road_plan);
	void toString();
	void performEvent();

private:
	std::string _road_plan;
};
