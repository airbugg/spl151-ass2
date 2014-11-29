#include <iostream>
#include <string>
#include "Containers.h"
#include "Car.h"
#include "Road.h"
#include "Simulator.h"
#include "Junction.h"


int main(int argc, char** argv)
{
	Simulator sim("input/RoadMap.ini", "input/Events.ini", "input/Commands.ini", "input/Configuration.ini", "output/Report.ini");
	sim.init();
	sim.tick();

	std::cin.get();

	return 0;
}
