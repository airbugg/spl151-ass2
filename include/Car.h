#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <boost/ref.hpp>
#include <boost/lexical_cast.hpp>
#include "Road.h"

class Road; //forward declaration of Road to avoid circular dependencies and whatnot.

class Car
{
public:
	// constructors
	Car();
	Car(std::string car_id, std::string road_plan);
	~Car();

	// getters, setters..
	std::string car_id();
	int location();
	int fault_time();
	bool at_junc();

	// methods
	void generateReport(const std::string& report_id); //implement (check)
	void move(int speed);
	void sabotageCar(int faultTime);
	void exitJunction();
	void updateHistory();

	std::string toString();

private:

	// fields
	std::string _car_id;
	std::vector< boost::reference_wrapper<Road> > _road_plan;
	int _curr_road_index;
	int _max_road_index;
	std::string _history;
	int _fault_time;
	int _location;
	bool _at_junc;
	bool _done;
	bool _halt_history;

	// private methods
	void advanceCar();
	void createRoadPlan(std::string road_plan);
	void reduceFaultTime();
};
