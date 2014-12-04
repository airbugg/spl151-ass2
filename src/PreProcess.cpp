#include "PreProcess.h"

using namespace std;

bool PreProcess::pre_process_test(const std::string road_map_location, const std::string events_location, const std::string commands_location, const std::string configuration_location)
{
	return (PreProcess::test_events(events_location) && PreProcess::test_commands(commands_location) && PreProcess::test_roadMap(road_map_location) && PreProcess::test_configuration(configuration_location));
}

bool PreProcess::test_events(const std::string events_location) //read Event.ini and check's fields validility
{
	bool ITSALLGOOD = true;
	boost::property_tree::ptree pt;
	boost::property_tree::ini_parser::read_ini(events_location, pt);
	for (boost::property_tree::ptree::const_iterator section = pt.begin(); section != pt.end(); ++section)
	{
		for (boost::property_tree::ptree::const_iterator property = section->second.begin(); property != section->second.end(); ++property)
		{
			string property_type = property->first;
			string property_value = property->second.data();
			if (property_type == "type")
			{
				if (property_value != "car_arrival" && property_value != "car_fault")
				{
					PreProcess::print_error_massage(section->first, property_type);
					ITSALLGOOD = false;
				}
			}
			else if (property_type == "time")
			{
				if (!check_int_validation(property_value)) //should be int
				{
					PreProcess::print_error_massage(section->first, property_type);
					ITSALLGOOD = false;
				}
			}
			else if (property_type == "timeOfFault") //should be int
			{
				if (!check_int_validation(property_value))
				{
					PreProcess::print_error_massage(section->first, property_type);
					ITSALLGOOD = false;
				}
			}
			else if (property_type == "carId")
			{
				if (property_value == "") // should not be empty
				{
					PreProcess::print_error_massage(section->first, property_type);
					ITSALLGOOD = false;
				}
			}
			else if (property_type == "roadPlan")
			{
				if (property_value == "")
				{
					PreProcess::print_error_massage(section->first, property_type);
					ITSALLGOOD = false;
				}
			}
		}
	}
	return ITSALLGOOD;
}

bool PreProcess::test_commands(const std::string commands_location) //reads Commands.ini and check's fields validility
{
	bool ITSALLGOOD = true;
	boost::property_tree::ptree pt;
	boost::property_tree::ini_parser::read_ini(commands_location, pt);
	for (boost::property_tree::ptree::const_iterator section = pt.begin(); section != pt.end(); section++)
	{
		for (boost::property_tree::ptree::const_iterator property = section->second.begin(); property != section->second.end(); property++)
		{
			string property_type = property->first;
			string property_value = property->second.data();
			if (property_type == "type")
			{
				if (property_value != "termination" && property_value != "car_report" && property_value != "road_report" && property_value != "junction_report")
				{
					PreProcess::print_error_massage(section->first, property_type);
					ITSALLGOOD = false;
				}
			}

			else if (property_type == "time") // supose to be an int
			{
				if (!check_int_validation(property_value))
				{
					PreProcess::print_error_massage(section->first, property_type);
					ITSALLGOOD = false;
				}
			}
			else if (property_type == "id") // should'nt be empty
			{
				if (property_value == "")
				{
					PreProcess::print_error_massage(section->first, property_type);
					ITSALLGOOD = false;
				}
			}
			else if (property_type == "carId" || property_type == "junctionId" || property_type == "startJunction" || property_type == "endJunction")
			{
				if (property_value == "") // should'nt be empty, existence will be checked later
				{
					PreProcess::print_error_massage(section->first, property_type);
					ITSALLGOOD = false;
				}
			}
		}
	}
	return ITSALLGOOD;
}

bool PreProcess::test_roadMap(const std::string road_map_location)
{
	return true;
}

bool PreProcess::test_configuration(const std::string configuration_location) // reads Configuration.ini file and checks that all fields are valid (supose to be all int's)
{
	bool ITSALLGOOD = true;
	boost::property_tree::ptree pt;
	boost::property_tree::ini_parser::read_ini(configuration_location, pt);
	for (boost::property_tree::ptree::const_iterator section = pt.begin(); section != pt.end(); section++)
	{
		for (boost::property_tree::ptree::const_iterator property = section->second.begin(); property != section->second.end(); property++)
		{
			string property_type = property->first;
			string property_value = property->second.data();
			if (!check_int_validation(property_value))
			{
				PreProcess::print_error_massage(section->first, property_type);
				ITSALLGOOD = false;
			}
		}
	}
	return ITSALLGOOD;
}

bool PreProcess::check_int_validation(const std::string& property_value) // checks that every charachter in is a digit
{
	bool isAdigit = true;
	if (!property_value.empty() && property_value[0] != '-')
	{
		for (size_t i = 1; i < property_value.size(); ++i)
		{
			if (!isdigit(property_value[i]))
			{
				isAdigit = false;
			}
		}
	}
	else
	{
		isAdigit = false;
	}
	return isAdigit;
}

void PreProcess::print_error_massage(const std::string& section, const std::string& property_type) // prints an error message if invalid input identified
{
	std::cout << "property " << property_type << " is not valid in the section " << section << endl;
}
