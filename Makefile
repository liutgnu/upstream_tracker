all: main.cpp tracker.cpp upstream_tracker.cpp fedora_tracker.cpp string_splitor.cpp
	g++ -g -o main $^

.PHONY clean:
	rm -f main *.o