#include "CarFaultEvent.h"

CarFaultEvent::CarFaultEvent()
	:_fault_time(0)
{}

CarFaultEvent::~CarFaultEvent() {}

CarFaultEvent::CarFaultEvent(int event_serial_num, std::string event_id, int time_slice, std::string car_id, int fault_time)
	: _fault_time(fault_time)
{
	Event::set_event_id(event_id);
	Event::set_event_serial_num(event_serial_num);
	Event::set_time_slice(time_slice);
	Event::set_car_id(car_id);
}

void CarFaultEvent::toString() {}

void CarFaultEvent::performEvent()
{
	Containers::car_container[_car_id]->sabotageCar(_fault_time);
}