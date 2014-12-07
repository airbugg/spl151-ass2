#include <iostream>
#include <string>
#include "Containers.h"
#include "Car.h"
#include "Road.h"
#include "Simulator.h"
#include "Junction.h"


int main(int argc, char** argv)
{
	Simulator sim("RoadMap.ini", "Events.ini", "Commands.ini", "Configuration.ini", "Report.ini");
	sim.init();
	sim.tick();

	std::cin.get();

	return 0;
}
