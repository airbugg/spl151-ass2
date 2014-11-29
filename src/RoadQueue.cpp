#include "RoadQueue.h"

RoadQueue::RoadQueue(Road& incomingRoad, int default_time_slice)
	: _incoming_road(incomingRoad), _curr_time_slice(default_time_slice), _remaining_time(default_time_slice), _passed_cars(0) {}

RoadQueue::~RoadQueue()
{
}

void RoadQueue::calcNewTimeSlice()
{
	if (_curr_time_slice == _passed_cars)
		_curr_time_slice = std::min(Containers::max_time_slice(), _curr_time_slice + 1);
	else if (_passed_cars == 0)
		_curr_time_slice = std::max(Containers::min_time_slice(), _curr_time_slice - 1);

	_remaining_time = _curr_time_slice;
	_passed_cars = 0;
}

void RoadQueue::advance() // disgusting hack (using friendship. ugh.)
{
	if (_incoming_road.get().junction_release_candidate() && _incoming_road.get()._cars.size() != 0)
	{
		_incoming_road.get().last_car_in_junction()->get().exitJunction();
		_incoming_road.get()._cars.erase(_incoming_road.get().last_car_in_junction());

		if (_incoming_road.get()._cars.size() == 0)
		{
			std::map<std::string, Road*>::iterator road = Containers::active_road_container.find(_incoming_road.get().road_id());
			Containers::active_road_container.erase(road);
		}

		_passed_cars++;
	}
	_remaining_time--;
}

int RoadQueue::curr_time_slice() { return _curr_time_slice; }

int RoadQueue::remaining_time() { return _remaining_time; }

int RoadQueue::passed_cars() { return _passed_cars; }

void RoadQueue::set_remaining_time(int remaining_time) { _remaining_time = remaining_time; }

void RoadQueue::queueReport(const std::string& report_id)
{
	Containers::report_tree.add(report_id + "." + _incoming_road.get().start_junc(), carsInQueue());
}

std::string RoadQueue::carsInQueue()
{
	std::string cars_in_queue = "";

	r_car_iterator r_car_iterator = _incoming_road.get()._cars.rbegin();

	while (r_car_iterator != _incoming_road.get()._cars.rend() && r_car_iterator->get().at_junc())
	{
		cars_in_queue += "(";
		cars_in_queue += r_car_iterator->get().car_id();
		cars_in_queue += ")";
	}

	return cars_in_queue;
}