CS_214_Mymalloc
Kyle Lin & Pranav Tripuraneni

Test Plan:

malloc():
If a malloc with size 0 is called, then a NULL pointer will be returned, because it would be a request to allocate no memory. This is done with a simple if statement at the beginning of malloc.

The code will then create a ListNode* pointer to the beginning of the memory array, and if the size variable is 0, it means that the linked list is uninitialized, and this is checked through an if statement. If true, the code will create the head node with the size of the memory array and set the free variable to 0, meaning the memory is unused, 1 would mean that the memory is being used.

When malloc is called, the code will iterate through the linked list until it finds a free chunk of memory that has enough space. This is done through checking the pointer's aforementioned free and size variables. If a suitable chunk is found, then it will create a new node to split unnecessary memory from the amount allocated, and updates the parameters of the pointer node, then it returns a char* pointer with a +1 offset so that the pointer given is to the payload, not the header metadata.

In the event that the list is iterated through and no suitable chunk of memory is found, then it will return NULL and an error stating that there is not enough memory remaining in the array.

free():
The code has to be able to allocate memory from a global memory array of a declared size, and return a pointer to the start of the payload.
  The metadata will be contained in a linked list struct, and the returned pointer will not be pointing to this metadata. This will be accounted for in malloc by returning a char* pointer with a +1 offset, and in free by checking the pointer with a -1 offset.
  
The code should also be able to free a chunk in the memory array if given a pointer.
  If a pointer that was not created through malloc is given, then the program should return an error stating that the pointer is not in the memory array. This will be checked by checking the location of the pointer through pointer arithmetic, and an error is returned if the pointer is outside of the global memory array.

The code will also check for an uninitialized memory array by looking at the first node. In the event that no malloc has been called prior to free, the default size of the first node would be 0 bytes, and thus the program would return an error stating that the memory array hasn't been initialized.

  If a pointer is given that points to an already freed chunk of memory, then the program should return an error stating that that chunk has already been freed. This will be checked by looking at the metadata's free variable, it is 0 if it is free and 1 if it is being used. If a pointer put into free has a 0 free variable then the program will return an error stating that this chunk has already been freed.
  
  If a pointer is given that does not point to the start of a chunk, then the program should return an error stating that the pointer does not point to the start of a chunk. This will be done by iterating through the linked list and comparing it to the provided pointer after accounting for the -1 offset. If the end of the list is reached without finding a match, then it can be concluded that the given pointer does not point to the start of a chunk of memory.
  
  If a chunk of memory has been freed, and there is an adjacent block of memory that is also free, then they should coalesce into a single, larger free block of memory. This will be achieved by iterating through the list and checking the current and next node's free variable, if they are both 0 then the current node will have the next node's size added to it.

memgrind.c:
Custom Stress Test #1: allocate and free the entire memory array 120 times.
Custom Stress Test #2: allocate 100 randomly sized chunks and then free them all.

The average time taken for each of the stress tests were recorded with the clock() function from the time.h library. The average time taken for 50 runs of each stress test are:

Stress Test #1: 0.000002 seconds
Stress Test #2: 0.000073 seconds
Stress Test #3: 0.000021 seconds
Custom Test #1: 0.000003 seconds
Custom Test #2: 0.000062 seconds
