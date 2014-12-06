#include "Simulator.h"

using namespace std;

Simulator::Simulator()
	:_time_slice(0), fTerminationTime(0), _road_map_file(""), _events_file(""), _commands_file(""), _config_file("")
{
}

Simulator::~Simulator()
{
	// destroy car_container
	for (Containers::car_container_iterator it = Containers::car_container.begin(); it != Containers::car_container.end(); ++it)
	{
		delete (it->second);
	}

	// destroy road_container
	for (Containers::road_container_iterator it = Containers::road_container.begin(); it != Containers::road_container.end(); ++it)
	{
		delete (it->second);
	}

	// destroy junction_container
	for (Containers::junction_container_iterator it = Containers::junction_container.begin(); it != Containers::junction_container.end(); ++it)
	{
		delete (it->second);
	}
}

Simulator::Simulator(const std::string road_map_location, const std::string events_location, const std::string commands_location, const std::string configuration_location, const std::string output_file_location)
	:_time_slice(0), fTerminationTime(0), _road_map_file(road_map_location), _events_file(events_location), _commands_file(commands_location), _config_file(configuration_location)
{
	_output_file = output_file_location;
}

void Simulator::init()// commiting syntax validation of .ini files and initializes all major data structors in the program (maps, queues)
{
	cout << "Simulator initializing: Running Pre-Proccessing..." << endl;
	if (PreProcess::pre_process_test(_road_map_file, _events_file, _commands_file, _config_file)) // the program will only run if all the .ini files pass intactness check
	{
		cout << "Finished Pre-Processing, reading configuration file..." << endl;
		setAttributes(_config_file);
		cout << "Done. Building roads and junctions..." << endl;
		buildRoads(_road_map_file);
		cout << "Done. Queuing-up events..." << endl;
		buildEventsPriorityQueue(_events_file);
		cout << "Done, queuing-up commands..." << endl;
		buildReportsPriorityQueue(_commands_file);
		cout << "Simulator Initialization: Complete." << endl;
	}
}

void Simulator::tick() // commit time-slice "tick"
{
	while (Containers::time() < Containers::termination())
	{
		cout << "\n\nSimulating time slice #: " << Containers::time() << std::endl;

		executeEvents();
		updateCarHistory();
		executeCommands();
		advanceCarsInRoads();
		advanceCarsInJunctions();

		Containers::advanceTime();
	}

	// write report
	outputReport();

	// notify user simulation ended
	cout << "\n\nSimulation Complete.";
}

void Simulator::buildRoads(const std::string& file_location) // constructing Containers::fRoadMap and Containers::fJunctionMap
{
	boost::property_tree::ptree pt;
	boost::property_tree::ini_parser::read_ini(file_location, pt);
	
	//for every section in "RoadMap.ini", create appropriate roads and junctions
	for (boost::property_tree::ptree::const_iterator section = pt.begin(); section != pt.end(); ++section)
	{
		std::string incoming_roads;

		for (boost::property_tree::ptree::const_iterator property = section->second.begin(); property != section->second.end(); ++property)
		{
			incoming_roads += property->first;
			incoming_roads += ",";

			std::string roadName = property->first;
			roadName += ",";
			roadName += section->first;
			Containers::road_container[roadName] = new Road(roadName, property->first, section->first, boost::lexical_cast<int>(property->second.data())); // insert new road to the map
		}

		incoming_roads = incoming_roads.substr(0, incoming_roads.size() - 1); // remove pesky trailing comma.
		Containers::junction_container[section->first] = new Junction(section->first, Containers::default_time_slice(), incoming_roads); //insert ne junction to the map
	}
}

void Simulator::buildEventsPriorityQueue(const std::string& file_location) // constructing Containers::fEventQueue
{
	boost::property_tree::ptree pt;
	boost::property_tree::ini_parser::read_ini(file_location, pt);
	
	//event_serial_number helps us positioning the event's in queue by their file apperiance order.
	int event_serial_num = 1;
	
	
	//for every event in "Events.ini", create an appropriate event and insert it to Containers::fEventQueue
	for (boost::property_tree::ptree::const_iterator section = pt.begin(); section != pt.end(); ++section)
	{
		std::string event_type;
		std::string carId;
		std::string roadPlan;
		int time;
		int timeOfFault;

		for (boost::property_tree::ptree::const_iterator property = section->second.begin(); property != section->second.end(); ++property)
		{
			string property_type = property->first;
			string property_value = property->second.data();
			if (property_type == "type")
			{
				event_type = property_value;
			}
			else if (property_type == "time")
			{
				time = boost::lexical_cast<int>(property->second.data());
			}
			else if (property_type == "timeOfFault")
			{
				timeOfFault = boost::lexical_cast<int>(property->second.data());
			}
			else if (property_type == "carId")
			{
				carId = property_value;
			}
			else if (property_type == "roadPlan")
			{
				roadPlan = property_value;
			}
		}
		if (event_type == "car_arrival")
		{
			Containers::event_queue.push(new AddCarEvent(event_serial_num, section->first, time, carId, roadPlan));
		}
		else
		{
			Containers::event_queue.push(new CarFaultEvent(event_serial_num, section->first, time, carId, timeOfFault));
		}

		event_serial_num++;
	}
}

void Simulator::buildReportsPriorityQueue(const std::string& file_location) // constructing Containers::fReportQueue
{
	boost::property_tree::ptree pt;
	boost::property_tree::ini_parser::read_ini(file_location, pt);

	//report_serial_number helps us positioning the reportss in queue by their file apperiance order.
	int report_serial_num = 1;

	//for every report in "Reports.ini", create an appropriate report and insert it to Containers::fReportQueue
	for (boost::property_tree::ptree::const_iterator section = pt.begin(); section != pt.end(); ++section)
	{
		std::string report_type;
		std::string report_id;
		std::string car_id;
		std::string start_junction;
		std::string end_junction;
		std::string junction_id;
		int time;
		
		for (boost::property_tree::ptree::const_iterator property = section->second.begin(); property != section->second.end(); ++property)
		{
			string property_type = property->first;
			string property_value = property->second.data();

			if (property_type == "type")
			{
				report_type = property_value;
			}
			else if (property_type == "time")
			{
				time = boost::lexical_cast<int>(property->second.data());
			}
			else if (property_type == "id")
			{
				report_id = property_value;
			}
			else if (property_type == "carId")
			{
				car_id = property_value;
			}
			else if (property_type == "startJunction")
			{
				start_junction = property_value;
			}
			else if (property_type == "endJunction")
			{
				end_junction = property_value;
			}
			else if (property_type == "junctionId")
			{
				junction_id = property_value;
			}
		}

		if (report_type == "car_report")
		{
			CarReport* car_report = new CarReport(report_serial_num, time, report_id, car_id);
			Containers::report_queue.push(car_report);
		}
		else if (report_type == "road_report")
		{
			RoadReport* road_report = new RoadReport(report_serial_num, time, report_id, start_junction, end_junction);
			Containers::report_queue.push(road_report);
		}
		else if (report_type == "junction_report")
		{
			JunctionReport* junction_report = new JunctionReport(report_serial_num, time, report_id, junction_id);
			Containers::report_queue.push(junction_report);
		}
		else if (time > Containers::termination())// if the report is non of the above, this means the report is a  "termination" report
			Containers::set_termination(time);

		report_serial_num++;
	}
}

void Simulator::setAttributes(const std::string& file_location)// sets program global attributes (DEFAULT_TIME_SLICE etc...)
{
	boost::property_tree::ptree pt;
	boost::property_tree::ini_parser::read_ini(file_location, pt);

	for (boost::property_tree::ptree::const_iterator section = pt.begin(); section != pt.end(); section++)
	{
		for (boost::property_tree::ptree::const_iterator property = section->second.begin(); property != section->second.end(); property++)
		{
			string property_type = property->first;
			string property_value = property->second.data();

			if (property_type == "MAX_SPEED")
			{
				Containers::set_max_speed(boost::lexical_cast<int>(property->second.data()));
			}
			else if (property_type == "DEFAULT_TIME_SLICE")
			{
				Containers::set_default_time_slice(boost::lexical_cast<int>(property->second.data()));
			}
			else if (property_type == "MAX_TIME_SLICE")
			{
				Containers::set_max_time_slice(boost::lexical_cast<int>(property->second.data()));
			}
			else if (property_type == "MIN_TIME_SLICE")
			{
				Containers::set_min_time_slice(boost::lexical_cast<int>(property->second.data()));
			}
		}
	}
}

void Simulator::executeEvents() // execute events thet match the current time slice, by thier appearance order in the file
{
	while (!Containers::event_queue.empty() && Containers::event_queue.top()->time_slice() == Containers::time())
	{
		std::cout << "perfoming event: " << Containers::event_queue.top()->event_id() + "\n";

		Event* e = Containers::event_queue.top();
		e->performEvent();

		Containers::event_queue.pop(); // release event from container

		delete e; // delete event from heap
	}
}

void Simulator::executeCommands() // execute reports thet match the current time slice, by thier appearance order in the file
{
	while (!Containers::report_queue.empty() && Containers::report_queue.top()->time_slice() == Containers::time())
	{
		std::cout << "perfoming command: " << Containers::report_queue.top()->report_id() + "\n";

		Report* rep = Containers::report_queue.top();
		rep->writeReport();

		Containers::report_queue.pop(); // release report from container

		delete rep; // delete report from heap
	}
}

void Simulator::advanceCarsInRoads()// for each road that has cars on it, advance all cars on road
{
	for (road_container_iterator it = Containers::active_road_container.begin(); it != Containers::active_road_container.end(); ++it)
	{
		std::cout << "advancing cars on road: " << it->second->road_id() << std::endl;
		it->second->advanceCars();
	}
}

void Simulator::advanceCarsInJunctions() // for each junction, advence cars on junction
{
	for (junction_container_iterator it = Containers::junction_container.begin(); it != Containers::junction_container.end(); ++it)
	{
		std::cout << "advancing cars in junction: " << it->second->junc_id() << std::endl;
		it->second->advance();
	}
}

void Simulator::updateCarHistory() // update car history for all cars in Containers::fCarMap
{
	for (car_container_iterator it = Containers::car_container.begin(); it != Containers::car_container.end(); ++it)
		it->second->updateHistory();
}

void Simulator::outputReport()// extract report from report_tree to output file
{
	boost::property_tree::write_ini(_output_file, Containers::report_tree);
	std::cout << "\n\nReport output file created in: " << _output_file << std::endl;
}
