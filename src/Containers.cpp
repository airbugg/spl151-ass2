#include "Containers.h"

int Containers::_min_time_slice;
int Containers::_max_time_slice;
int Containers::_default_time_slice;
int Containers::_max_speed;
int Containers::_time = 1;
int Containers::_termination = 0;

std::map<std::string, Road*> Containers::road_container;
std::map<std::string, Road*> Containers::active_road_container;
std::map<std::string, Car*> Containers::car_container;
std::map<std::string, Junction*> Containers::junction_container;

std::priority_queue<Event*, std::vector<Event*>, EventComparator> Containers::event_queue;
std::priority_queue<Report*, std::vector<Report*>, EventComparator> Containers::report_queue;

boost::property_tree::ptree Containers::report_tree;

Containers::Containers() {}

Containers::~Containers()
{
}

// getters, setters..
int Containers::time() { return _time; }

int Containers::max_time_slice() { return _max_time_slice; }

int Containers::min_time_slice() { return _min_time_slice; }

int Containers::default_time_slice() { return _default_time_slice; }

int Containers::max_speed() { return _max_speed; }

int Containers::termination() { return _termination; }

void Containers::set_max_time_slice(int max_time_slice) { _max_time_slice = max_time_slice; }

void Containers::set_min_time_slice(int min_time_slice) { _min_time_slice = min_time_slice; }

void Containers::set_default_time_slice(int default_time_slice) { _default_time_slice = default_time_slice; }

void Containers::set_max_speed(int max_speed) { _max_speed = max_speed; }

void Containers::advanceTime() { _time++; }

void Containers::set_termination(int termination) { _termination = termination; }
