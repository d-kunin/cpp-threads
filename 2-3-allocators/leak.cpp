#include <stdlib.h>

#include <dmalloc.h>

void leak(unsigned int n) {
	malloc(n);
}

// how to find memory leaks:
// 1. eval `dmalloc -d 0 -l leak.log -p log-non-free`
// 2. sudo ldconfig -p | grep dmalloc 
// 3. find libdmalloc.so and libdmalloccxx.so
// 4. add #include <dmalloc.h>
// 5. run LD_PRELOAD="ldmalloccxx.so ./leak"
// 6. check leak.log file

int main(int argc, char** argv) {
	leak(1);
	leak(2);
	leak(3);
	
	void *m = malloc(1024);
	free(m);
	
	return 0;
}
