#include <stdio.h>
#include <stdlib.h>

typedef struct NODE {int data; struct NODE* next;} NODE; // nodes of the linked list
typedef struct LINKED_LIST {struct NODE *head;} LINKED_LIST; // struct to act as the head of the list

LINKED_LIST Create_List(void) {LINKED_LIST list = {NULL}; return list;}

void Verify_Malloc(NODE *node) {if (node == NULL) {printf("Malloc Failed\n"); exit(1);} return;}

// this function prints out all of the nodes in the linked list
void Print_List(FILE *out, LINKED_LIST list) {
    if (list.head == NULL) {printf("\n"); return;} //empty list
    NODE *current = list.head;
    while (current->next != NULL) {
        fprintf(out, "%d -> ",current->data);
        current = current->next;
    }
    fprintf(out, "%d\n",current->data);
    return;
}

// this function returns the number 
// of elements in the linked list
int Size(LINKED_LIST list){
    if (list.head == NULL){
        return 0;
    }
    NODE *current = list.head;
    int size = 0;
    while(current->next != NULL){
        size++;
        current = current->next;
    }
    size++;
    return size;
}

// this function adds an element to
// the front of the list
void Push_Front(LINKED_LIST *list, int data){
    NODE *newNode = malloc(sizeof(NODE));
    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;
    return;
}

// this function adds an element 
// to the end of the linked list 
void Push_Back(LINKED_LIST *list, int data) {
    if (list->head == NULL){
        Push_Front(list, data);
    } 
    else{
        NODE *current = list->head;
        while(current->next != NULL){
            printf("%d\n", current->next->data);
            current = current->next;
        }
        NODE *newNode = malloc(sizeof(NODE));
        newNode->data = data;
        newNode->next = NULL;
        current->next = newNode;
    }
    return;
}


// if the list is not empty
// the value of the first element of the list is returned by reference in the parameter data
// the first element of the list is deleted
// returns 0 if the list is empty otherwise returns 1
// remember to free the deleted node
int Pop_Front(LINKED_LIST *list, int *data) {
    if(list->head == NULL){
        return 0;
    }    
    
    //only one element in list
    if(list->head->next == NULL){
        data = list->head->data;
        free(list->head);
        list->head = NULL;
        return 1;
    } 
    NODE *prevHead = list->head;
    data = prevHead->data;
    list->head = list->head->next;
    free(prevHead);
    return 1;
}


// if the list is not empty
// the value of the last element of the list is returned by reference in the parameter data
// the last element of the list is deleted
// returns 0 if the list is empty otherwise returns 1
// remember to free the deleted node
int Pop_Back(LINKED_LIST *list, int *data) {
    if(list->head == NULL){
        return 0;
    }
    NODE *previous = list->head;
    NODE *current = previous->next;

    //only one element in list
    if(list->head->next == NULL){
        free(list->head);
        list->head = NULL;
        return 1;
    }

    //more than one element in list
    while(current->next != NULL){
        current = current->next;
    }
    free(current->next);
    current->next = NULL;
    return 1;
}

// this function returns the number 
// of times that the value of the parameter 
// data appears in the list
int Count_If(LINKED_LIST list, int data) {
    int occurances = 0;
    NODE current = *list.head;
    while(current.next != NULL){
        current = *current.next;
        if (current.data == data){
            occurances++;
        }
    }
    return occurances;
}

// delete the first node containing the data value
// return 1 if something was deleted otherwise 0
// remember to free the deleted node
int Delete(LINKED_LIST *list, int data) {
    if(Count_If(*list, data) > 0){

        // if list only contains one value
        if(Size(*list) == 1){
            free(list->head);
            list->head = NULL;
            return 1;
        }

        NODE *previous = list->head;
        NODE *current = previous->next;
        while(current->data != data){
            previous = current;
            current = current->next;
        }

        //if node is end of list
        if (current->next == NULL){
            free(current);
            current = NULL;
            return 1;
        }
        else{
            previous->next = current->next;
            free(current);
            current = NULL;
            return 1;
        }
    }
    return 0;
}

// return 1 if the list is empty otherwise returns 0
int Is_Empty(LINKED_LIST list) {
    if(Size(list) == 0){
        return 1;
    }
    return 0;
}

// delete all elements of the list
// remember to free the nodes
void Clear(LINKED_LIST *list) {

    if(Size(*list) == 1){
        free(list->head);
        list->head = NULL;
        return;
    }

    NODE *previous = list->head;
    NODE *current = previous->next;
    while(current->next != NULL){
        previous = current;
        free(previous);
        previous = NULL;
        current = current->next;
    }
    free(list->head);
    list->head = NULL;
    free(current);
    current = NULL;

    return;
}


// if an element appears in the list 
// retain the first occurance but
// remove all other nodes with the same 
// data value
void Remove_Duplicates(LINKED_LIST *list) {
    return;
}

// modify main to completely test your functions 
int main() {
    // create a linked list
    printf("creating linked list\n");
    LINKED_LIST list = Create_List();
   
    // add some data (hardcoded for testing)
    printf("hardcoding some data\n");
    NODE *first  = malloc(sizeof(NODE)); Verify_Malloc(first);
    NODE *second = malloc(sizeof(NODE)); Verify_Malloc(second);
    first->data  = 1;
    second->data = 2;
    list.head = first;
    first->next = second;
    second->next = NULL;

    // print the list
    printf("Testing Print_List\n");
    Print_List(stdout, list);

    //test for Size
    printf("Testing Size\n");
    printf("size = %d\n",Size(list));

    //test for Push_Front
    printf("Testing Push_Front\n");
    Push_Front(&list, 0);
    Print_List(stdout, list);
    
    //test for Push_Back
    printf("Testing Push_Back\n");
    Push_Back(&list, 3);
    Print_List(stdout, list);

    //test for Pop_Front
    printf("Testing Pop_Front\n");
    {
        int x; 
        int not_empty = Pop_Front(&list, &x);
        if (not_empty) {
            printf("Element popped was %d\n",x);
            Print_List(stdout,list);
            printf("size = %d\n",Size(list));
        }
        else 
            printf("List was empty\n");
    }

    //test for Pop_Back
    printf("Testing Pop_Back\n");
    {
        int x; 
        int not_empty = Pop_Back(&list, &x);
        if (not_empty) {
            printf("Element popped was %d\n",x);
            Print_List(stdout,list);
            printf("size = %d\n",Size(list));
        }
        else 
            printf("List was empty\n");
    }

    //test for Count_If
    Push_Front(&list, 5);
    Push_Front(&list, 5);
    Print_List(stdout, list);
    printf("5 count = %d\n",Count_If(list, 5));
    
    //test for Delete 
    printf("Testing Delete\n");
    Print_List(stdout, list);
    Delete(&list, 1); 
    Print_List(stdout, list);

    //test for Is_Empty
    printf("Testing Is_Empty\n");
    if (Is_Empty(list)) printf("List is Empty\n"); else printf("List is not empty\n");
    
    //test for Clear
    Clear(&list);
    if (Is_Empty(list)) printf("List is Empty\n"); else printf("List is not empty\n");

    //test for Remove_Duplicates
    Push_Back(&list, 1);
    Push_Back(&list, 1);
    Push_Back(&list, 1);
    Push_Back(&list, 2);
    Push_Back(&list, 2);
    Push_Back(&list, 3);
    Push_Back(&list, 3);
    Push_Back(&list, 3);
    
    //Remove_Duplicates(&list);
    Print_List(stdout, list);
    return 0;
}
