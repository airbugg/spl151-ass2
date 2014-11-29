#pragma once

#include <string>

class Simulator;
class Containers;
//class EventComparator;

class Event
{
public:
	Event();
	virtual ~Event();
	virtual void performEvent() = 0;

	std::string event_id();
	int time_slice();
	int event_serial_num();
	void set_time_slice(int time_slice);
	void set_event_serial_num(int event_serial_num);
	void set_event_id(std::string event_id);
	void set_car_id(std::string car_id);

protected:
	int _time_slice;
	int _event_serial_num;
	std::string _car_id;
	std::string _event_id;
};
