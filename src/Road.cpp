#include "Road.h"

Road::Road()
	:_road_id(""), _start_junc(""), _end_junc(""), _length(0), _junction_release_candidate(false), _curr_speed(0), _last_car_in_junction(), _location_of_last_faulty_car(0), _cars()
{
}

Road::Road(std::string roadID, std::string startJunc, std::string endJunc, int length)
	: _road_id(roadID), _start_junc(startJunc), _end_junc(endJunc), _length(length), _junction_release_candidate(false), _curr_speed(0), _last_car_in_junction(), _location_of_last_faulty_car(0), _cars()
{
}

Road::~Road()
{
}

// getters, setters...

int Road::length() { return _length; }

std::string Road::road_id() { return _road_id; }

std::string Road::start_junc() { return _start_junc; }

std::string Road::end_junc() { return _end_junc; }

bool Road::junction_release_candidate() { return _junction_release_candidate; }

Road::road_iterator Road::last_car_in_junction() { return _last_car_in_junction; }

// methods

void Road::calcRoadSpeed()
{
	if (_cars.size() == 0)
		_curr_speed = _length;
	else
		_curr_speed = ceil(_length / _cars.size());
}

void Road::advanceCars()
{
	_junction_release_candidate = false;
	int _num_of_faulty_cars = 0;
	calcRoadSpeed();

	for (r_road_iterator r_car_iterator = _cars.rbegin(); r_car_iterator != _cars.rend(); ++r_car_iterator)
	{
		if (r_car_iterator->get().fault_time() == 0)
		{
			if (r_car_iterator->get().location() == _location_of_last_faulty_car || _num_of_faulty_cars == 0)
				r_car_iterator->get().move(std::min(Containers::max_speed(), _curr_speed));
			else
			{
				r_car_iterator->get().move(std::min(Containers::max_speed(), (int)ceil(_curr_speed / std::pow(2, _num_of_faulty_cars))));
			}

			if (!_junction_release_candidate && r_car_iterator->get().at_junc()) // assign iterator to first operational car set to leave junction
			{
				_last_car_in_junction = --(r_car_iterator.base());
				_junction_release_candidate = true;
			}
		}
		else
		{
			r_car_iterator->get().move(0); // moving anyway, to update fault time. maybe make it automatic once sim starts working.
			_num_of_faulty_cars++; // this field should maybe probably belong only to this function.
			_location_of_last_faulty_car = r_car_iterator->get().location(); // revisit
		}
	}

	_cars.sort(ActorComparator()); // stable sort, NlogN ( where N is list.size() )
}

void Road::generateReport(const std::string& report_id)
{
	Containers::report_tree.add(report_id + ".startJunction", _start_junc);
	Containers::report_tree.add(report_id + ".endJunction", _end_junc);
	Containers::report_tree.add(report_id + ".cars", carsOnRoad());
}

void Road::addCar(Car &car)
{
	_cars.push_front(boost::ref(car));
}

std::string Road::carsOnRoad()
{
	std::string cars_on_road = "";

	for (road_iterator car_iterator = _cars.begin(); car_iterator != _cars.end(); ++car_iterator)
	{
		cars_on_road += "(" + car_iterator->get().car_id();
		cars_on_road += ",";
		cars_on_road += boost::lexical_cast<std::string>(car_iterator->get().location());
		cars_on_road += ")";
	}

	return cars_on_road;
}