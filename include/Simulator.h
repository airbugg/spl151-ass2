#pragma once

#include "Car.h"
#include "Report.h"
#include "Event.h"
#include "Containers.h"
#include "Road.h"
#include "AddCarEvent.h"
#include "CarFaultEvent.h"
#include "CarReport.h"
#include "RoadReport.h"
#include "JunctionReport.h"
#include "PreProcess.h"
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/lexical_cast.hpp>

#include <iostream>
#include <map>
#include <string>

using namespace std;

class EventComparator;
class Road;
class Car;
class Junction;


class Simulator
{
	typedef std::map<std::string, Road* >::iterator road_container_iterator;
	typedef std::map<std::string, Car* >::iterator car_container_iterator;
	typedef std::map<std::string, Junction* >::iterator junction_container_iterator;

public:
	Simulator();
	~Simulator();
	Simulator(const std::string road_map_location, const std::string events_location, const std::string commands_location, const std::string configuration_location, const std::string output_file_location);

	// methods
	void init();
	void tick();

	static std::string _output_file;

private:

	// fields
	int _time_slice;
	int fTerminationTime;
	std::string _road_map_file;
	std::string _events_file;
	std::string _commands_file;
	std::string _config_file;

	//private methods
	void buildRoads(const std::string& file_location);
	void buildEventsPriorityQueue(const std::string& file_location);
	void buildReportsPriorityQueue(const std::string& file_location);
	void setAttributes(const std::string& file_location);
	void updateCarHistory();
	void executeEvents();
	void executeCommands();
	void advanceCarsInRoads();
	void advanceCarsInJunctions();
	void outputReport();
};
