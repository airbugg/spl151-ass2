#pragma once

#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
//#include "PreProcess.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct PreProcess
{
	static bool pre_process_test(const std::string road_map_location, const std::string events_location, const std::string commands_location, const std::string configuration_location);
	static bool test_events(const std::string events_location);
	static bool test_commands(const std::string commands_location);
	static bool test_roadMap(const std::string road_map_location);
	static bool test_configuration(const std::string configuration_location);

	static bool check_int_validation(const std::string& property_value);
	static void check_roadPlan(const std::string& property_value);
	static void print_error_massage(const std::string& section, const std::string& property_type);
	static bool check_existence(const std::string& property_type, const std::string& property_value);
};
