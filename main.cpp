// #include <iostream>
// #include <sstream>
// #include <string>
// #include <any>
// #include <functional>
#include "src/CLeyla/Algorithm/Linked_List.h"
#include "src/CLeyla/Algorithm/Array.h"
// #include "src/Parser/Parser.hpp"
// #include "src/Parser/Types.hpp"
// #include "src/Parser/Parsout.hpp"

//typedef struct{ Leyla_linked_node_int* next;int value; }Leyla_linked_node_int; typedef struct { Leyla_linked_node_int* front; unsigned int length; Leyla_linked_node_int* back; }Leyla_linked_list_int; Leyla_linked_node_int* new_linked_node_int(int value){ Leyla_linked_node_int *new_node = (Leyla_linked_node_int*)(malloc(sizeof(Leyla_linked_node_int))); new_node -> value = value; new_node -> next = __null; return new_node; } Leyla_linked_list_int* new_list_int(unsigned int l){ Leyla_linked_list_int linked { __null, l, __null }; Leyla_linked_node_int* current = new_linked_node_int(0); linked.front = current; for(int i{0}; i < l;++i){ current -> next = new_linked_node_int(0); current = current -> next; } linked.back = current; Leyla_linked_list_int* plinked = (Leyla_linked_list_int*)(malloc(sizeof(linked))); *plinked = linked; return plinked; } Leyla_linked_list_int* new_list_from_vectorint(int* vector,unsigned int l){ Leyla_linked_list_int linked { __null, l, __null }; Leyla_linked_node_int* current= new_linked_node_int(vector[0]); linked.front = current; for(int i{0}; i < l;++i){ current -> next = new_linked_node_int(vector[i]); current = current -> next; } linked.back = current; Leyla_linked_list_int* plinked = (Leyla_linked_list_int*)(malloc(sizeof(linked))); *plinked = linked; return plinked; } void linked_push_back_int(Leyla_linked_list_int* list,int element){ list -> back -> next = new_linked_node_int(element); list -> back = list-> back -> next; list -> length++; } void linked_push_front_int(Leyla_linked_list_int* list,int element){ Leyla_linked_node_int* new_element = new_linked_node_int(element); new_element -> next = list -> front; list -> front = new_element; list -> length ++; } void linked_remove_back_int(Leyla_linked_list_int* list){ if(list -> length < 2){ free(list -> front); list -> front = __null; list -> back = __null; return; } Leyla_linked_node_int* quasi_last = list -> front; while(quasi_last -> next -> next != __null){ quasi_last = quasi_last -> next; } free(list -> back); list -> back = quasi_last; list -> back -> next = __null; list -> length--; } void linked_remove_front_int(Leyla_linked_list_int* list){ Leyla_linked_node_int * second = list -> front -> next; free(list -> front); list -> front = second; list -> length --; } Leyla_linked_node_int* linked_get_at_int(Leyla_linked_list_int* list, unsigned int index){ if(index < 0 || index >= list -> length) return __null; Leyla_linked_node_int* current = list -> front; for(int i{0}; i < index;++i) current = current -> next; return current; } void linked_remove_at_int(Leyla_linked_list_int* list, unsigned int index){ if(index <= 0){ linked_remove_front_int(list); return; } if(index >= list -> length - 1){ linked_remove_back_int(list); return; } Leyla_linked_node_int* removed_node = linked_get_at_int(list, index); Leyla_linked_node_int* premoved_node = linked_get_at_int(list, index - 1); premoved_node -> next = removed_node -> next; free(removed_node); list -> length --; } void linked_push_at_int(Leyla_linked_list_int* list,int value, unsigned int index){ if(index <= 0){ linked_push_front_int(list, value); return; } if(index >= list -> length){ linked_push_back_int(list, value); return; } Leyla_linked_node_int* pre_node = linked_get_at_int(list, index - 1); Leyla_linked_node_int* new_node = new_linked_node_int(value); new_node -> next = pre_node -> next; pre_node -> next = new_node; list -> length++; } void linked_concat_int(Leyla_linked_list_int* l1, Leyla_linked_list_int* l2){ for(unsigned int i{0}; i < l2 -> length; ++i) linked_push_back_int(l1,linked_get_at_int(l2,i) -> value); }

Leyla_define_array(uint8_t)

int main()
{   

    Leyla_array_uint8_t* v = new_array_uint8_t(2);
    array_push_back_uint8_t(v, 100);
    printf("%d \n", array_get_at_uint8_t(v, 1));
    return 0;
}