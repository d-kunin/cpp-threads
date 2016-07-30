all:
	g++ -o allocator allocator.cpp
	g++ -o leak leak.cpp -ldmalloc
	g++ -o mass_alloc mass_alloc.cpp
	g++ -std=c++11 -g -o small_alloc small_allocator.cpp
clean:
	-rm allocator leak mass_alloc small_alloc
