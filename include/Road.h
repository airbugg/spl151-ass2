#pragma once

#include <string>
#include <list>
#include <math.h>
#include <boost/ref.hpp>
#include <boost/lexical_cast.hpp>
#include "Car.h"
#include "Containers.h"
#include "ActorComparator.h"

class Car; //forward declaration of Car to avoid circular dependencies and whatnot.

class Road
{
	friend RoadQueue;

	typedef std::list<boost::reference_wrapper<Car> >::iterator road_iterator;
	typedef std::list<boost::reference_wrapper<Car> >::reverse_iterator r_road_iterator;

public:
	// constructors
	Road();
	Road(std::string road_id, std::string start_junc, std::string end_junc, int length);
	~Road();

	// getters, setters..
	int length();
	std::string road_id();
	std::string start_junc();
	std::string end_junc();
	bool junction_release_candidate();
	road_iterator last_car_in_junction();

	// methods
	void addCar(Car& car);
	void advanceCars();
	void generateReport(const std::string& report_id); //implement (ok. check)

private:
	// fields
	std::list<boost::reference_wrapper<Car> > _cars;
	road_iterator _last_car_in_junction;
	std::string _road_id;
	std::string _start_junc;
	std::string _end_junc;
	int _length;
	int _curr_speed;
	int _location_of_last_faulty_car;
	bool _junction_release_candidate;

	// private methods
	void calcRoadSpeed();
	std::string carsOnRoad();
};
