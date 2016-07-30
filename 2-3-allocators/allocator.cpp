#include <vector>

int main() {
	// setting an allocator for a vector
	std::vector<int, std::allocator<int> > v(16);
		
	return 0;
}