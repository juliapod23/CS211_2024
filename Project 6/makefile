build:
	rm -f program.out
	g++ -I includes -Wall -fconcepts -std=c++2a project_utils.cpp celestial.cpp solarsystem.cpp star.cpp planet.cpp satellite.cpp flightpath.cpp interstellar.cpp -o program.out

test:
	rm -f tests.exe
	g++ -I includes -Wall -fconcepts -std=c++2a project_utils.cpp celestial.cpp solarsystem.cpp star.cpp planet.cpp satellite.cpp flightpath.cpp tests.cpp -o tests.out

run:
	clear;./program.out -splash

runno:
	clear;./program.out -hidemenu

runtest:
	./tests.out

clean:
	rm -f program.out
	rm -f tests.out

buildvalgrind:
	rm -f program.out
	g++ -g -I includes -Wall -fconcepts -std=c++2a project_utils.cpp celestial.cpp solarsystem.cpp star.cpp planet.cpp satellite.cpp flightpath.cpp interstellar.cpp -o program.out

runvalgrind:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes  ./program.out

solution:
	chmod u+x ./solution.out
	clear;./solution.out -splash
