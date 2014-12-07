all:RoadSimulator

CC = g++
CFLAGS = -g -c -Linclude -Iinclude -Weffc++ -o
LFLAGS = -o



RoadSimulator: Compile
	
	@echo 'Linking Source files...'
	$(CC) $(LFLAGS) bin/RoadSimulator bin/Main.o bin/ActorComparator.o bin/AddCarEvent.o  bin/CarFaultEvent.o bin/Car.o bin/CarReport.o bin/Containers.o bin/Event.o bin/EventComparator.o bin/JunctionReport.o bin/PreProcess.o bin/Report.o bin/Road.o bin/RoadQueue.o bin/Junction.o bin/RoadReport.o bin/Simulator.o 
	@echo 'Done.'

Compile:
	
	@echo 'Compiling source files...'
	$(CC) $(CFLAGS)  bin/ActorComparator.o src/ActorComparator.cpp
	$(CC) $(CFLAGS)  bin/AddCarEvent.o src/AddCarEvent.cpp
	$(CC) $(CFLAGS)  bin/CarFaultEvent.o src/CarFaultEvent.cpp
	$(CC) $(CFLAGS)  bin/Car.o src/Car.cpp
	$(CC) $(CFLAGS)  bin/Junction.o src/Junction.cpp
	$(CC) $(CFLAGS)  bin/RoadQueue.o src/RoadQueue.cpp
	$(CC) $(CFLAGS)  bin/CarReport.o src/CarReport.cpp
	$(CC) $(CFLAGS)  bin/Containers.o src/Containers.cpp
	$(CC) $(CFLAGS)  bin/Event.o src/Event.cpp
	$(CC) $(CFLAGS)  bin/EventComparator.o src/EventComparator.cpp
	$(CC) $(CFLAGS)  bin/JunctionReport.o src/JunctionReport.cpp
	$(CC) $(CFLAGS)  bin/PreProcess.o src/PreProcess.cpp
	$(CC) $(CFLAGS)  bin/Report.o src/Report.cpp
	$(CC) $(CFLAGS)  bin/Road.o src/Road.cpp
	$(CC) $(CFLAGS)  bin/RoadReport.o src/RoadReport.cpp
	$(CC) $(CFLAGS)  bin/Simulator.o src/Simulator.cpp
	$(CC) $(CFLAGS)  bin/Main.o src/Main.cpp

clean:
	rm -rf bin/*
