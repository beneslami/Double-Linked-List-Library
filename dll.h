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
  int (*key_match)(*void, *void); //Function pointer for searching the element
}dll_t;

void register_key_match_callback(dll_t *dll, int (*key_match)(void*, void*));
void *dll_search_by_key(dll_t *dll, void *key); //generic search function

/*Public function decleration to create and return a new empty dll*/
dll_t *get_new_dll();

/*Public function decleration to add the application data to the dll*/
int add_data_to_dll(dll_t *dll, void *app_data);


#endif __DLLH__
