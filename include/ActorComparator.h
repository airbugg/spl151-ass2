#pragma once

#include "Car.h"
#include "Road.h"
#include "Junction.h"

class Car;
class Road;
class Junction;

class ActorComparator
{
public:
	ActorComparator();
	~ActorComparator();

	bool operator()(Car& e1, Car& e2);
};
