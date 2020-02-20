#include "dll.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*Application specific data structures*/
typedef struct student_{
    char name[32];
    int age;
    int weight;
    unsigned int rollno;
} student_t;

/*Application specific data structures*/
typedef struct employee_{
    char name[32];
    char designation[32];
    unsigned int salary;
    unsigned int emp_id;
} employee_t;

static void print_student_db(dll_t *student_db) {
    if(!student_db || !student_db->head) return;

    dll_node_t *head = student_db->head;
    student_t *data = NULL;

    while(head){
        data = head->data;
        printf("Name = %s\n",   data->name);
        printf("Age = %d\n",    data->age);
        printf("weight = %d\n", data->weight);
        printf("rollno = %u\n", data->rollno);
        head = head->right;
    }
}

static void print_employee_db(dll_t *employee_db) {
    if(!employee_db || !employee_db->head) return;

    dll_node_t *head = employee_db->head;
    employee_t *data = NULL;

    while(head){
        data = head->data;
        printf("Name = %s\n", data->name);
        printf("Designation = %s\n", data->designation);
        printf("salary = %u\n", data->salary);
        printf("emp_id = %u\n", data->emp_id);
        head = head->right;
    }
}

student_t *search_student_by_rollno(dll_t *student_db, unsigned int rollno/*search key*/){
    if(!student_db || !student_db->head) return NULL;

    dll_node_t *head = student_db->head;
    student_t *data = NULL;

    while(head){
        data = head->data;
        if(data->rollno == rollno)
            return data;
        head = head->right;
    }
}

/*Search function*/

employee_t *search_employee_by_emp_id(dll_t *employee_db, unsigned int emp_id/*search key*/){
    if(!employee_db || !employee_db->head) return NULL;

    dll_node_t *head = employee_db->head;
    employee_t *data = NULL;

    while(head){
        data = head->data;
        if(data->emp_id == emp_id)
            return data;
        head = head->right;
    }
}

/*Search callbacks*/
static int search_student_db_by_key(void *data, void *key){  /*return 0 if matches, return -1 if do not match*/
    student_t *student = (student_t *)data;
    unsigned int rollno = (unsigned int)key;
    if(student->rollno == rollno)
        return 0;
    return -1;
}

/*Search callbacks*/
static int search_employee_db_by_key(void *data, void *key){ /*return 0 if matches, return -1 if do not match*/
    employee_t *emp = (employee_t *)data;
    unsigned int emp_id = (unsigned int)key;
    if(emp->emp_id == emp_id)
        return 0;
    return -1;
}
int main(int argc, char **argv){
    /*Student database*/
    student_t *student1 = calloc(1, sizeof(student_t));
    strncpy(student1->name, "Ben", strlen("Eslami"));
    student1->age = 26;
    student1->weight = 75;
    student1->rollno = 810196101;

    student_t *student2 = calloc(1, sizeof(student_t));
    strncpy(student2->name, "Mehrnaz", strlen("Niazi"));
    student2->age = 26;
    student2->weight = 55;
    student2->rollno = 810196102;

    student_t *student3 = calloc(1, sizeof(student_t));
    strncpy(student3->name, "Fatemeh", strlen("Eslami"));
    student3->age = 16;
    student3->weight = 40;
    student3->rollno = 12345678;

    /*Create a new Linked List*/
    dll_t *student_db = get_new_dll();
    register_key_match_callback(student_db, search_student_db_by_key);
    add_data_to_dll(student_db, student1);
    add_data_to_dll(student_db, student2);
    add_data_to_dll(student_db, student3);

    student_t *student = dll_search_by_key(student_db, (void *)810196101);
    if(!student){
        printf("Student record not found\n");
    }
    else{
        print_student_db(student);
    }

  return 0;
}
