#ifndef ORDERED_ARRAY_ALGORITHM_H
#define ORDERED_ARRAY_ALGORITHM_H 1

/* 

Courtesy of James Molloy
-> http://www.jamesmolloy.co.uk/tutorial_html/7.-The%20Heap.html

*/

#include "../common.h"

typedef void* type_t;


typedef s8 (*lessthan_predicate_t)(type_t, type_t);

typedef struct{
    type_t *array;
    u32 size;
    u32 max_size;
    lessthan_predicate_t less_than;
} ordered_array_t;

s8 standard_lessthan_predicate(type_t a, type_t b);

ordered_array_t create_ordered_array(u32 max_size, lessthan_predicate_t less_than);
ordered_array_t place_ordered_array(void *addr, u32 max_size, lessthan_predicate_t less_than);
void destroy_ordered_array(ordered_array_t *array);
void insert_ordered_array(type_t item, ordered_array_t *array);
type_t lookup_ordered_array(u32 i, ordered_array_t *array);
void remove_ordered_array(u32 i, ordered_array_t *array);


#endif