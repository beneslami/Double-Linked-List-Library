#include <memory.h>
#include <stdlib.h>
#include "dll.h"

/*Public function implementation to create and return a new empty double linked list*/
dll_t *get_new_dll(){
  dll_t *dll = calloc(1, sizeof(dll_t));
  dll-> head = NULL;
  dll->key_match = NULL;
  return dll;
}

void register_key_match_callback(dll_t *dll, int (*key_match)(void *, void *)){
  dll->key_match = key_match;
}

/*Generic search function*/
void *dll_search_by_key(dll_t *dll, void *key){
  if(!dll || !dll->head) return NULL;
  dll_node_t *head = dll->head;
  while(head){
    if(dll->key_match(head->data, key) == 0)
      return (void *)head->data;
    head = head->right;
  }
  return NULL;
}

/*Public function implementation to add a new application data to dll*/
int add_data_to_dll(dll_t *dll, void *app_data){

  if( !dll || !app_data) return -1;

  dll_node_t *dll_new_node = calloc(1, sizeof(dll_node_t));
  dll_new_node->left = NULL;
  dll_new_node->right = NULL;
  dll_new_node->data = app_data;

  /*add the data to the end of dll*/
  if(!dll_head){
    dll->head = dll_new_node;
    return 0;
  }

  dll_node_t *first_node = dll->head;
  dll_new_node->right = first_node;
  first_node->left = dll_new_node;
  dll_head = dll_new_node;
  return 0;
}
