#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "../DataStructures.h"

typedef struct list_node
{
    struct list_node *prev;
    struct list_node *next;
}list_node;

typedef struct int_list_node
{
    struct list_node node;
    int value;
}int_list_node;

list_node *list_get_tail(list_node **head)
{
    if (!head)
    {
        return NULL;
    }

    list_node *current_node = *head;
    list_node *last_node = NULL;

    while (current_node)
    {
        last_node = current_node;
        current_node = current_node->next;
    }

    return last_node;
}

list_node *list_append (list_node **head, list_node *item)
{
    list_node *tail = list_get_tail (head);
    if (!tail)
    {
        *head = item;
    }
    else
    {
        tail->next = item;
    }
    item->prev = tail;
    item->next = NULL;
    return item;
}

void print_list(int_list_node* head) 
{
    int_list_node* current = head;

    while (current != NULL) {
        printf("%d\n", current->value);
        current = (int_list_node*)current->node.next;
    }
}

void insert_After(list_node* prev_node, list_node* new_node)
{
    if (prev_node == NULL)                            //Checks if the considered node is NULL
    {
        printf("ERROR: prev_node cannot be NULL");
        return;
    }

    new_node->next = prev_node->next;                 //The new_node's next item is now the prev_node's next item

    prev_node->next = new_node;                       //The prev_node's next item is now the new_node

    new_node->prev = prev_node;                       //The new_node's previous item is now the prev_node

    if (new_node->next != NULL)                       //if new_node is not last item of list
    {
        new_node->next->prev = new_node;              //the previous item of new_node->next is new_node
    }
}

void insert_Before(list_node* next_node, list_node* new_node)
{
    if (next_node == NULL)                            //Checks if the considered node is NULL
    {
        printf("ERROR: next_node cannot be NULL");   
        return;
    }

    new_node->prev = next_node->prev;                 //The new_node's prev item is now the next_node's prev item

    next_node->prev = new_node;                       //The next_node's prev item is now the new_node 

    new_node->next = next_node;                       //The new_node's next item is now the considered item

    if (new_node->prev != NULL)                       //if new_node is not first item of list
    {
        new_node->prev->next = new_node;             //The next item of new_node->prev is new_node
    }
}

// void list_remove(list_node** head_ref, list_node* item_to_remove) //I GUESS REMOVE IS NOT MY STRONG SUIT
// {
//     if (*head_ref == NULL || item_to_remove == NULL) 
//     {
//         return; 
//     }

//     if (*head_ref == item_to_remove)
//     { 
//         *head_ref = item_to_remove->next; 
//     }

//     if (item_to_remove->next != NULL) 
//     {
//         item_to_remove->next->prev = item_to_remove->prev; 
//     }

//     if (item_to_remove->prev != NULL) 
//     {
//         item_to_remove->prev->next = item_to_remove->next; 
//     }

//     free(item_to_remove);
// } 

int main()
{
    int_list_node* my_doubly_linked_list = NULL;

    int_list_node item1;
    item1.value = 1;
    int_list_node item2;
    item2.value = 2;
    int_list_node item3;
    item3.value = 3;
    int_list_node item5;
    item5.value = 5;
    int_list_node item7;
    item7.value = 7;

    list_append((list_node**)&my_doubly_linked_list, (list_node*)&item1);
    list_append((list_node**)&my_doubly_linked_list, (list_node*)&item2);
    list_append((list_node**)&my_doubly_linked_list, (list_node*)&item3);
    list_append((list_node**)&my_doubly_linked_list, (list_node*)&item5);
    list_append((list_node**)&my_doubly_linked_list, (list_node*)&item7);

    int_list_node *int_list = my_doubly_linked_list;

    print_list(int_list);

    int_list_node item4;
    item4.value = 4;
    int_list_node item6;
    item6.value = 6;

    insert_After((list_node*)&item3, (list_node*)&item4);
    insert_Before((list_node*)&item7, (list_node*)&item6);
    //list_remove((list_node**)&int_list, (list_node*)&item2.node.next); //DOESN'T DO ANYTHING, STOPS OTHER FUNCTIONS TOO

    print_list(int_list);

    return 0;
}