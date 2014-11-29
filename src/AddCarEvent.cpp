#include "AddCarEvent.h"

using namespace std;

AddCarEvent::AddCarEvent()
	:_road_plan("")
{
}

AddCarEvent::~AddCarEvent()
{
}

AddCarEvent::AddCarEvent(int event_serial_num, std::string event_id, int time_slice, const std::string& car_id, const std::string& road_Plan)
	:_road_plan(road_Plan)
{
	Event::set_event_id(event_id);
	Event::set_event_serial_num(event_serial_num);
	Event::set_time_slice(time_slice);
	Event::set_car_id(car_id);
}

void AddCarEvent::toString()
{
}

void AddCarEvent::performEvent()
{ //check_existence
	Containers::car_container[_car_id] = new Car(_car_id, _road_plan);
}