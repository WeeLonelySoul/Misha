#include "../../libraries/bikka/ordered_array_algorithm.h"
#include "../../libraries/bikka/memory.h"

/* 

Courtesy of James Molloy
-> http://www.jamesmolloy.co.uk/tutorial_html/7.-The%20Heap.html

*/

s8 standard_lessthan_predicate(type_t a, type_t b){
    return (a<b)?1:0; /* Return either 1 or 0 */
}


ordered_array_t create_ordered_array(u32 max_size, lessthan_predicate_t less_than){
    ordered_array_t to_ret;
    to_ret.array = (void*)kmalloc(max_size*sizeof(type_t));
    memset(to_ret.array, 0, max_size*sizeof(type_t));
    to_ret.size = 0;
    to_ret.max_size = max_size;
    to_ret.less_than = less_than;

    return to_ret;
}

ordered_array_t place_ordered_array(void *Addr, u32 MaxSize, lessthan_predicate_t LessThan){
    ordered_array_t ToRet;
    ToRet.array = (type_t*)Addr;
    memset(ToRet.array, 0, MaxSize*sizeof(type_t));
    ToRet.size = 0;
    ToRet.max_size = MaxSize;
    ToRet.less_than = LessThan;
    return ToRet;
}

void destroy_ordered_array(ordered_array_t *array){
    //kfree(array->array); /* Doesn't exist */
}

void insert_ordered_array(type_t item, ordered_array_t *array){
    ASSERT(array->less_than);
    u32 iterator = 0;
    while (iterator < array->size && array->less_than(array->array[iterator], item)){ iterator++; }
    
    if (iterator == array->size){ array->array[array->size++] = item; }
    else{
        type_t tmp = array->array[iterator];
        array->array[iterator] = item;
        while(iterator < array->size){
            iterator++;
            type_t tmp2 = array->array[iterator];
            array->array[iterator] = tmp;
            tmp = tmp2;
        }
        array->size++;
    }
}

type_t lookup_ordered_array(u32 i, ordered_array_t *array){
    ASSERT(i < array->size);
    return array->array[i];
}

void remove_ordered_array(u32 i, ordered_array_t *array){
    while(i < array->size){
        array->array[i] = array->array[i+1];
        i++;
    }
    array->size--;
}