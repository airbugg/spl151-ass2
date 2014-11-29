#include "ActorComparator.h"

ActorComparator::ActorComparator()
{
}

ActorComparator::~ActorComparator()
{
}

bool ActorComparator::operator()(Car& car1, Car& car2)
{
	return (car1.location() < car2.location()); // maybe >=, i dunno
}