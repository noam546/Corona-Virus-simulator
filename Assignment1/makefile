# All Targets
all: bin/cTrace

# Tool invocations
# Executable "cTrace" depends on the files main.o Agent.o Graph.o Tree.o Session.o
bin/cTrace: bin/main.o bin/Agent.o bin/Graph.o bin/Tree.o bin/Session.o
	@echo 'Building target: cTrace'
	@echo 'Invoking: C++ Linker'
	g++ -o bin/cTrace bin/main.o bin/Agent.o bin/Graph.o bin/Tree.o bin/Session.o
	@echo 'Finished building target: cTrace'
	@echo ' '

#main.o Depends on the source and header files src/main.cpp include/Session.h
bin/main.o: src/main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/main.o src/main.cpp 

#Session.o Depends on the source and header files src/Session.cpp include/Session.h include/Agent.h include/json.hpp
bin/Session.o: src/Session.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Session.o src/Session.cpp

#Agent.o Depends on the source and header files src/Agent.cpp include/Agent.h
bin/Agent.o: src/Agent.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Agent.o src/Agent.cpp

#Graph.o Depends on the source and header files src/Graph.cpp include/Graph.h
bin/Graph.o: src/Graph.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Graph.o src/Graph.cpp
	
#Tree.o Depends on the source and header files src/Tree.cpp include/Tree.h include/Session.h
bin/Tree.o: src/Tree.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Tree.o src/Tree.cpp
	

#Clean the build directory
clean: 
	rm -f bin/*
