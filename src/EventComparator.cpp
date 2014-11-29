#include "EventComparator.h"

EventComparator::EventComparator()
{
}

EventComparator::~EventComparator()
{
}

bool EventComparator::operator()(Event* e1, Event* e2)
{
	return (e1->time_slice() > e2->time_slice() || (e1->time_slice() == e2->time_slice() && e1->event_serial_num() > e2->event_serial_num()));
}

bool EventComparator::operator()(Report* rep1, Report* rep2)
{
	return (rep1->time_slice() > rep2->time_slice() || (rep1->time_slice() == rep2->time_slice() && rep1->report_serial_num() > rep2->report_serial_num())); // maybe >=, i dunno
}

// check if priority queue is stable