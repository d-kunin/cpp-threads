#include <iostream>
#include <cstring>

#define DK_MAX 1048576
typedef unsigned int stp_size;
typedef unsigned char byte;

class SmallAllocator {
private:
        byte memory[DK_MAX];
		stp_size allocated;
		stp_size num_blocks;
		
		void dump() {
			std::cout << "allocated: " << allocated << " blocks: " << num_blocks << std::endl;
		}
public:
        void *Alloc(stp_size size) {
			num_blocks++;
			stp_size total_allocation_size = size + sizeof(stp_size);
			// writing size of the block as fist bytes
			stp_size* next_block_size_ptr = (stp_size*)&memory[allocated];
			*next_block_size_ptr = size;
			// memory block right after size
			void* next_block_memory_ptr = &memory[allocated] + sizeof(stp_size);

			allocated += total_allocation_size;			
			
			dump();
			return next_block_memory_ptr;
        };
		
        void *ReAlloc(void *ptr, stp_size size) {
			stp_size* old_size = (stp_size*)((byte*)ptr - sizeof(stp_size));
			void* new_ptr = Alloc(size);
			
			std::memcpy(new_ptr, ptr, *old_size);
			
			Free(ptr);
			
			dump();
        	return new_ptr;
        };
		
        void Free(void *ptr) {
			num_blocks--;
        	stp_size* sz = (stp_size*)((byte*)ptr - sizeof(stp_size));
			*sz = 0;
			dump();
        };
		
		SmallAllocator(): allocated(0), num_blocks(0) {};
};

// make && gdb -ex run ./small_alloc

int main(int argc, char** argv) {
	
	SmallAllocator A1;
	int * A1_P1 = (int *) A1.Alloc(sizeof(int));
	A1_P1 = (int *) A1.ReAlloc(A1_P1, 2 * sizeof(int));
	A1.Free(A1_P1);
	SmallAllocator A2;
	int * A2_P1 = (int *) A2.Alloc(10 * sizeof(int));
	for(unsigned int i = 0; i < 10; i++) A2_P1[i] = i;
	for(unsigned int i = 0; i < 10; i++) if(A2_P1[i] != i) std::cout << "ERROR 1" << std::endl;
	int * A2_P2 = (int *) A2.Alloc(10 * sizeof(int));
	for(unsigned int i = 0; i < 10; i++) A2_P2[i] = -1;
	for(unsigned int i = 0; i < 10; i++) if(A2_P1[i] != i) std::cout << "ERROR 2" << std::endl;
	for(unsigned int i = 0; i < 10; i++) if(A2_P2[i] != -1) std::cout << "ERROR 3" << std::endl;
	A2_P1 = (int *) A2.ReAlloc(A2_P1, 20 * sizeof(int));
	for(unsigned int i = 10; i < 20; i++) A2_P1[i] = i;
	for(unsigned int i = 0; i < 20; i++) if(A2_P1[i] != i) std::cout << "ERROR 4" << std::endl;
	for(unsigned int i = 0; i < 10; i++) if(A2_P2[i] != -1) std::cout << "ERROR 5" << std::endl;
	A2_P1 = (int *) A2.ReAlloc(A2_P1, 5 * sizeof(int));
	for(unsigned int i = 0; i < 5; i++) if(A2_P1[i] != i) std::cout << "ERROR 6" << std::endl;
	for(unsigned int i = 0; i < 10; i++) if(A2_P2[i] != -1) std::cout << "ERROR 7" << std::endl;
	A2.Free(A2_P1);
	A2.Free(A2_P2);
	
	return 0;
}