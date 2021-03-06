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

void register_comparison_callback(dll_t *dll, int (*comparison_fn)(void*, void*)){
  dll->comparison_fn = comparison_fn;
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
  if(!dll->head){
    dll->head = dll_new_node;
    return 0;
  }

  dll_node_t *first_node = dll->head;
  dll_new_node->right = first_node;
  first_node->left = dll_new_node;
  dll->head = dll_new_node;
  return 0;
}

int dll_priority_insert_data(dll_t *dll, void *data){
    if(!dll) return -1;

    /*if DLL is empty*/
    if(!dll->head){
        add_data_to_dll(dll, data);
        return 0;
    }

    dll_node_t *data_node = calloc(1, sizeof(dll_node_t));
    data_node->data = data;
    data_node->left = NULL;
    data_node->right = NULL;

    /* if there is only one node in DLL*/
    if(dll->head && !dll->head->right){
        if(dll->comparison_fn(dll->head->data, data) == -1){
            dll->head->right = data_node;
            data_node->left = dll->head;
        }
        else{
            dll->head->left = data_node;
            data_node->right = dll->head;
            dll->head = data_node;
        }
        return 0;
    }

    /*if More than one node in DLL*/
    if(dll->comparison_fn(data, dll->head->data) == -1){
        data_node->right = dll->head;
        dll->head->left = data_node;
        dll->head = data_node;
        return 0;
    }

    dll_node_t *prev = NULL, *current = NULL;
    current = dll->head;

    while(current){
        if(dll->comparison_fn(data, current->data) != -1){
            prev = current;
            current = current->right;
            continue;
        }

        prev->right = data_node;
        data_node->left = prev;
        data_node->right = current;
        current->left = data_node;
        return 0;
    }

    /*Add in the end*/
    prev->right = data_node;
    data_node->left = prev;
    return 0;
}
