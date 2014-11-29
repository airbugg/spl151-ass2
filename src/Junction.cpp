#include "Junction.h"

Junction::Junction()
	:_junc_id(""), _def_time_slice(0), _curr_road_location(0), _road_robin()
{
}

Junction::Junction(std::string junc_id, int default_time_slice, std::string incomingRoads)
	: _junc_id(junc_id), _def_time_slice(default_time_slice), _curr_road_location(0), _road_robin()
{
	buildRoadRobin(incomingRoads);
	_curr_road_location = 0;
}

Junction::~Junction()
{
}

void Junction::buildRoadRobin(std::string incomingRoads)
{
	std::stringstream ss(incomingRoads);

	while (ss.good())
	{
		std::string substr;
		getline(ss, substr, ',');
		_road_robin.push_back(RoadQueue(*Containers::road_container[substr + "," + _junc_id], _def_time_slice));
	}
}

void Junction::rotate()
{
	_road_robin[_curr_road_location].calcNewTimeSlice();
	if (_road_robin.size() != 1)
		_curr_road_location = (_curr_road_location + 1) % _road_robin.size();
}

void Junction::advance()
{
	if (_road_robin[_curr_road_location].remaining_time() == 0)
		rotate();

	_road_robin[_curr_road_location].advance();
}

void Junction::generateReport(const std::string& report_id)
{
	Containers::report_tree.add(report_id + ".junctionId", _junc_id);
	Containers::report_tree.add(report_id + ".timeSlices", timeSlices());

	queueReport(report_id);
}

std::string Junction::timeSlices()
{
	std::string timeSlices;

	for (size_t i = 0; i < _road_robin.size(); i++)
	{
		timeSlices += "(";
		timeSlices += boost::lexical_cast<std::string>(_road_robin[i].curr_time_slice());
		timeSlices += ",";

		if (i != _curr_road_location)
		{
			timeSlices += "-1";
			timeSlices += ")";
		}
		else
		{
			timeSlices += boost::lexical_cast<std::string>(_road_robin[i].remaining_time());
			timeSlices += ")";
		}
	}

	return timeSlices;
}

void Junction::queueReport(const std::string& report_id)
{
	for (size_t i = 0; i < _road_robin.size(); i++)
		_road_robin[i].queueReport(report_id);
}

std::string Junction::junc_id() { return _junc_id; }

void Junction::set_junc_id(std::string junc_id) { _junc_id = junc_id; }