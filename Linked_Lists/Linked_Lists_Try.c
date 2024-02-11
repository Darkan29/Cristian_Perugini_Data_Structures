#include <stddef.h> 
#include <stdlib.h>
#include <stdio.h>
#include "../DataStructures.h"

typedef struct list_node
{
    struct list_node *next;
    unsigned int count;
    int value;
}list_node;

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

list_node *list_append(list_node **head, list_node *item, int value)
{
    list_node *tail = list_get_tail(head);
    if (!tail)
    {
        *head = item;
        (*head)->count=1;
    }
    else
    {
        tail->next = item;
        (*head)->count++;
    }

    item->next = NULL;
    item->value = value;
    return item;
}

list_node *list_pop(list_node **head)
{
    if (!*head)
    {
        return NULL;
    }
    
    list_node *current_head = *head;

    const unsigned int current_count = current_head->count;
    *head = (*head)->next;
    
    if (*head)
    {
        (*head)->count = current_count-1;
    }
    

    current_head->next = NULL;
    return current_head;
}

unsigned list_lenght(list_node* head)
{
    return head-> count;
}

typedef struct string_item
{
    struct list_node node;
    const char *string;
}string_item;

typedef struct int_item
{
    struct list_node node;
    int value;
}int_item;

string_item *string_item_new(const char *string)
{
    string_item *item = malloc(sizeof(string_item));
    if (!item)
    {
        return NULL;
    }
    item->string = string;
    return item;
}

int_item *int_item_new(int value)
{
    int_item *item = malloc(sizeof(int_item));
    if (!item)
    {
        return NULL;
    }
    item->value = value;
    return item;
}

void list_remove(list_node **head, int value_to_remove)  //NOT WORKING
{
    list_node *head_ref = *head; 
    list_node *prev = NULL;

    if (head_ref->value == value_to_remove) 
    {
        *head = head_ref->next;
        return;
    }

    while (head_ref != NULL)
    {
        prev = head_ref;    
        head_ref = head_ref->next;
    }
    
    if (!head_ref)
    {
        return;
    }

    prev->next = head_ref->next;

    free(head_ref);
}

int main()
{
    list_node *my_linked_list = NULL;

    list_node first_element;
    list_node second_element;
    list_node third_element;

    list_append(&my_linked_list, &first_element, 21);
    list_append(&my_linked_list, &second_element, 66);
    list_append(&my_linked_list, &third_element, 1111);
    

    list_pop(&my_linked_list);
    
    list_remove(&my_linked_list, 21); //ONLY WORKS IF ELEMENT TO REMOVE IS THE FIRST OF THE LIST

    //printf("%d\n\n\n",list_lenght(my_linked_list));

    while (my_linked_list)
    {
        printf("%d\n", my_linked_list->value);
        my_linked_list = my_linked_list->next;
    }
    

    return 0;
}