all:
	g++ -o allocator allocator.cpp
	g++ -o leak leak.cpp -ldmalloc
	g++ -o mass_alloc mass_alloc.cpp
clean:
	-rm allocator leak mass_alloc
