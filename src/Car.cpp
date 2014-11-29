#include "Car.h"

Car::Car()
	:_car_id(""), _location(0), _history(""), _fault_time(0), _curr_road_index(0), _done(false), _halt_history(false), _road_plan(), _max_road_index(0), _at_junc(false)
{
	// Why the fuck would you use this?
}

Car::Car(std::string car_id, std::string road_plan)
	: _car_id(car_id), _location(0), _history(""), _fault_time(0), _curr_road_index(0), _done(false), _halt_history(false), _road_plan(), _max_road_index(0), _at_junc(false)
{
	// populates _road_plan with references to Road objects.
	createRoadPlan(road_plan);
	_max_road_index = _road_plan.size() - 1;

	// add car to first road in _road_plan.
	_road_plan[_curr_road_index].get().addCar(*this);

	// add road to active_road_container, for it has at least this car on it.
	Containers::active_road_container[_road_plan[_curr_road_index].get().road_id()] = Containers::road_container[_road_plan[_curr_road_index].get().road_id()];
}

Car::~Car()
{
}

// getters, setters..
std::string Car::car_id() { return _car_id; }

bool Car::at_junc() { return _at_junc; }

int Car::location() { return _location; }

int Car::fault_time() { return _fault_time; }

// methods
void Car::generateReport(const std::string& report_id)
{
	Containers::report_tree.add(report_id + ".carId", _car_id);
	Containers::report_tree.add(report_id + ".history", _history);
	Containers::report_tree.add(report_id + ".faultyTimeLeft", _fault_time);

	//std::string report;

	//report += "carId=" + _car_id + "\n";
	//report += "history=" + _history + "\n";
	//report += "faultyTimeLeft=" + boost::lexical_cast<std::string>(_fault_time) + "\n";
}

void Car::move(int speed) //TODO complete move
{
	if (_location + speed >= _road_plan[_curr_road_index].get().length()) // this means we're at current road's end
	{
		_location = _road_plan[_curr_road_index].get().length();

		_at_junc = true;
	}
	else
		_location += speed;

	reduceFaultTime();
}

void Car::sabotageCar(int faultTime) { _fault_time += faultTime; }

void Car::reduceFaultTime()
{
	if (_fault_time > 0)
		_fault_time--;
}

void Car::advanceCar() //TODO advance iterator current road
{
	if (_curr_road_index < _max_road_index)
	{
		++_curr_road_index;

		_road_plan[_curr_road_index].get().addCar(*this);
		_location = 0;
		_at_junc = false;

		Containers::active_road_container[_road_plan[_curr_road_index].get().road_id()] = Containers::road_container[_road_plan[_curr_road_index].get().road_id()];
	}
	else
	{
		_done = true;
	}
}

void Car::exitJunction()
{
	advanceCar(); // advance to next road
}

void Car::createRoadPlan(std::string road_plan)
{
	size_t begin = 0;
	size_t mid = road_plan.find(',');
	size_t end = road_plan.find(',', mid + 1);

	while (mid != std::string::npos)
	{
		_road_plan.push_back(boost::ref(*Containers::road_container[road_plan.substr(begin, end - begin)])); // make sure this adds a reference to _road_plan. god forbid we get duplicates..

		begin = mid + 1;
		mid = end;
		end = road_plan.find(',', mid + 1);
	}
}

void Car::updateHistory()
{
	if (!_halt_history) // don't update history if trip is over
	{
		std::string history_update;
		history_update += "(";
		history_update += boost::lexical_cast<std::string>(Containers::time());
		history_update += ",";
		history_update += _road_plan[_curr_road_index].get().road_id();
		history_update += ",";
		history_update += boost::lexical_cast<std::string>(_location);
		history_update += ")";
		_history.append(history_update);
	}

	if (_done && _fault_time == 0)
		_halt_history = true;
}

std::string Car::toString()
{
	return "fu";
}