#pragma once

#include "EventComparator.h"
#include "Event.h"
#include "Report.h"

#include "Road.h"
#include "Car.h"
#include "Junction.h"
#include "RoadQueue.h"

#include <string>
#include <map>
#include <queue>
#include <vector>

#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>

class EventComparator;
class Event;
class Report;

class Containers
{
public:

	typedef std::map<std::string, Road* >::iterator road_container_iterator;
	typedef std::map<std::string, Car* >::iterator car_container_iterator;
	typedef std::map<std::string, Junction* >::iterator junction_container_iterator;

	// constructors
	Containers();
	~Containers();

	// getters, setters...
	static int min_time_slice();
	static int max_time_slice();
	static int default_time_slice();
	static int max_speed();
	static int time();
	static int termination();
	static void set_min_time_slice(int min_time_slice);
	static void set_max_time_slice(int max_time_slice);
	static void set_default_time_slice(int default_time_slice);
	static void set_max_speed(int max_speed);
	static void advanceTime();
	static void set_termination(int termination);

	// actor containers..
	static std::map<std::string, Road*> road_container;
	static std::map<std::string, Road*> active_road_container;
	static std::map<std::string, Car*> car_container;
	static std::map<std::string, Junction*> junction_container;

	// event and command queue..
	static std::priority_queue<Event*, std::vector<Event*>, EventComparator> event_queue;
	static std::priority_queue<Report*, std::vector<Report*>, EventComparator> report_queue;

	// boost property tree for report output
	static boost::property_tree::ptree report_tree;

private:
	// private members
	static int _min_time_slice;
	static int _max_time_slice;
	static int _default_time_slice;
	static int _max_speed;
	static int _time;
	static int _termination;
};
