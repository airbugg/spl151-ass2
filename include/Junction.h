#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <boost/ref.hpp>
#include <boost/lexical_cast.hpp>
#include "Road.h"
#include "RoadQueue.h"

class RoadQueue;

class Junction
{
public:
	// constructors
	Junction();
	Junction(std::string junc_id, int DEFAULT_TIME_SLICE, std::string incoming_roads);
	~Junction();

	// getters, setters...
	std::string junc_id();
	void set_junc_id(std::string junc_id);

	// methods..
	void buildRoadRobin(std::string incoming_roads);
	void advance();
	void rotate();
	void calcTimeSlice();
	void generateReport(const std::string& report_id); // implement

private:
	std::string _junc_id;
	int _def_time_slice;
	int _curr_road_location;
	std::vector<RoadQueue> _road_robin;

	// private methods
	std::string timeSlices();
	void queueReport(const std::string& report_id);
};
