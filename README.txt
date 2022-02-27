CS_214_Mymalloc
Kyle Lin & Pranav Tripuraneni

Test Plan:
The code has to be able to allocate memory from a global memory array of a declared size, and return a pointer to the start of the payload.
  The metadata will be contained in a linked list struct, and the returned pointer will not be pointing to this metadata. This will be accounted for in malloc by returning a char* pointer with a +1 offset, and in free by checking the pointer with a -1 offset.
  
The code should also be able to free a chunk in the memory array if given a pointer.
  If a pointer that was not created through malloc is given, then the program should return an error stating that the pointer is not in the memory array. This will be checked by checking the location of the pointer through pointer arithmetic, and an error is returned if the pointer is outside of the global memory array.

The code will also check for an uninitialized memory array by looking at the first node. In the event that no malloc has been called prior to free, the default size of the first node would be 0 bytes, and thus the program would return an error stating that the memory array hasn't been initialized.

  If a pointer is given that points to an already freed chunk of memory, then the program should return an error stating that that chunk has already been freed. This will be checked by looking at the metadata's free variable, it is 0 if it is free and 1 if it is being used. If a pointer put into free has a 0 free variable then the program will return an error stating that this chunk has already been freed.
  
  If a pointer is given that does not point to the start of a chunk, then the program should return an error stating that the pointer does not point to the start of a chunk. This will be done by iterating through the linked list and comparing it to the provided pointer after accounting for the -1 offset. If the end of the list is reached without finding a match, then it can be concluded that the given pointer does not point to the start of a chunk of memory.
  If a chunk of memory has been freed, and there is an adjacent block of memory that is also free, then they should coalesce into a single, larger free block of memory.

Custom Stress Test #1: allocate and free the entire memory array 120 times.
Custom Stress Test #2: allocate 100 randomly sized chunks and then free them all.
