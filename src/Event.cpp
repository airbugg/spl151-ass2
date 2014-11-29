#include "Event.h"

Event::Event()
	:_time_slice(0), _event_id(""), _event_serial_num(0), _car_id("")
{
}

Event::~Event()
{
}

void Event::set_time_slice(int time_slice) { _time_slice = time_slice; }

std::string Event::event_id() { return _event_id; }

int Event::time_slice()  { return _time_slice; }

int Event::event_serial_num() { return _event_serial_num; }

void Event::set_event_serial_num(int event_serial_num) { _event_serial_num = event_serial_num; }

void Event::set_event_id(std::string event_id) { _event_id = event_id; }

void Event::set_car_id(std::string car_id) { _car_id = car_id; }