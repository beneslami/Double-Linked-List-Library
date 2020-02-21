/*header file for double linked list */
#ifndef __DLLH__
#define __DLLH__

typedef struct dll_node_{
  void *data;
  struct dll_node_ *left;
  struct dll_node_ *right;
} dll_node_t;

typedef struct dll_{
  dll_node_t *head;
  int (*key_match)(void*, void*); //Function pointer for searching the element
  int (*comparison_fn)(void*, void*); //Function pointer for comparing the elements
}dll_t;

void register_key_match_callback(dll_t *dll, int (*key_match)(void*, void*));
void register_comparison_callback(dll_t *dll, int (*comparison_fn)(void*, void*));
void *dll_search_by_key(dll_t *dll, void *key); //generic search function

/*Public function decleration to create and return a new empty dll*/
dll_t *get_new_dll();

/*Public function decleration to add the application data to the dll*/
int add_data_to_dll(dll_t *dll, void *app_data);

/*0 on success, -1 on failure*/
int dll_priority_insert_data(dll_t *dll, void *data);

/*Macro to iterate over a DLL*/
#define ITERATE_LIST_BEGIN(list_ptr, node_ptr)                              \
{                                                                           \
    dll_node_t *_node_ptr = NULL;                                           \
    node_ptr = list_ptr->head;                                              \
    for(; node_ptr!= NULL; node_ptr = _node_ptr){                           \
        if(!node_ptr) break;                                                \
        _node_ptr = node_ptr->right;
#define ITERATE_LIST_END  }}

#endif __DLLH__
