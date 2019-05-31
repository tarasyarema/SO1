#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"

p_meta_data first_element = NULL;
p_meta_data last_element  = NULL;

#define ALIGN8(x) (((((x)-1)>>3)<<3)+8)
#define MAGIC     0x12345678

p_meta_data search_available_space(size_t size_bytes) {
    p_meta_data current = first_element;

    while (current && !(current->available && current->size_bytes >= size_bytes)) 
        current = current->next;

    return current;
}

p_meta_data request_space(size_t size_bytes) 
{
    p_meta_data meta_data;

    meta_data = (void *) sbrk(0);

    if (sbrk(SIZE_META_DATA + size_bytes) == (void *) -1)
        return (NULL);

    meta_data->size_bytes = size_bytes;
    meta_data->available = 0;
    meta_data->magic = MAGIC;
    meta_data->next = NULL;
    meta_data->previous = NULL;

    return meta_data;
}


void *malloc(size_t size_bytes) 
{
    void *p;
    p_meta_data meta_data;

    if (size_bytes <= 0) {
        return NULL;
    }

    // We allocate a size of bytes multiple of 8
    size_bytes = ALIGN8(size_bytes);
    eprint("Malloc %zu bytes\n", size_bytes);

    meta_data = search_available_space(size_bytes);

    if (meta_data) { // free block found 
      meta_data->available = 0;
    } else {     // no free block found 
      meta_data = request_space(size_bytes);
      if (!meta_data)
        return (NULL);

      if (last_element)
          last_element->next = meta_data;
      meta_data->previous = last_element;
      last_element = meta_data;

      if (first_element == NULL) // Is this the first element ?
        first_element = meta_data;
    }

    p = (void *) meta_data;

    // We return the user a pointer to the space
    // that can be used to store data

    return (p + SIZE_META_DATA); 
}

void free(void *ptr)
{
    if (ptr == NULL)
        return;

    p_meta_data meta = ptr - SIZE_META_DATA;

    // First we check the magic attribute 
    if (meta->magic != MAGIC) {
        eprint("Magic number not equal (%d).\n", meta->magic);
        exit(1);
    }

    // Make available the pointer bytes
    meta->available = 1;
    eprint("%zu bytes freed.\n", meta->size_bytes);
}

void *calloc(size_t nelem, size_t elsize)
{
    void *ptr;
    size_t total = nelem * elsize;

    // Allocate and init to zeros
    ptr = malloc(total);
    memset(ptr, 0, total);

    return ptr;
}

void *realloc(void *ptr, size_t size_bytes)
{
    void *tptr;
    p_meta_data meta;

    // If ptr is NULL make a normal malloc
    if (ptr == NULL)
        return malloc(size_bytes);

    meta = ptr - SIZE_META_DATA;

    // Check if the realloc is needed
    if (meta->size_bytes >= size_bytes)
        return ptr;

    // Allocate a new pointer and copy the ptr contents to it
    tptr = malloc(size_bytes);
    memcpy(tptr, ptr, meta->size_bytes);
    free(ptr);

    return tptr;
}