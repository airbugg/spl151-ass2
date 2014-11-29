#pragma once

#include "Event.h"
#include "Report.h"
//#include <queue>
//#include "Simulator.h"

class EventComparator
{
public:
	EventComparator();
	~EventComparator();

	bool operator()(Event* e1, Event* e2);
	bool operator()(Report* rep1, Report* rep2);
};
