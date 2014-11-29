#pragma once

#include "Road.h"
#include "Car.h"
#include <string>
#include <boost/lexical_cast.hpp>
#include <algorithm>    // std::min,max
#include "Junction.h"

class Car;
class Road;
class Junction;

class RoadQueue
{
	typedef std::list< boost::reference_wrapper<Car> >::iterator car_iterator;
	typedef std::list< boost::reference_wrapper<Car> >::reverse_iterator r_car_iterator;

public:
	// constructors
	RoadQueue();
	RoadQueue(Road& incoming_road, int def_time_slice);
	~RoadQueue();

	// getters, setters..
	int curr_time_slice();
	int remaining_time();
	int passed_cars();
	void set_remaining_time(int remaining_time);

	// methods
	void advance();
	void calcNewTimeSlice();
	void queueReport(const std::string& report_id);

private:
	// fields
	int _curr_time_slice;
	int _remaining_time;
	int _passed_cars;
	boost::reference_wrapper<Road> _incoming_road;

	// private methods
	std::string carsInQueue();
};
