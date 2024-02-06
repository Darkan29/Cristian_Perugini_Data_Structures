#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "../DataStructures.h"

typedef struct list_node
{
    struct list_node *next;
    unsigned int count;
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

list_node *list_append(list_node **head, list_node *item)
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

// void list_remove(list_node **head, list_node* item_to_remove)  
// {
//     list_node *head_ref = *head; 

//     if (!head_ref)
//     {
//         return;
//     }

//     while (head_ref)
//     {
//         if (head_ref == item_to_remove)        COMPARISON IS PROBABLY NOT ALLOWED
//         {
//             printf("Removed\n");               NEVER ENTERS HERE
//         }
         
//         head_ref = head_ref->next;
//     }
    
//     free(head_ref);
// }

void list_reverse(list_node** head)      //REVERSE LIST (FROM 1,2,3,4 ---> 4,3,2,1)
{
    list_node* previous_node = NULL;     //Starts at NULL as there are no Nodes before the Current one
    list_node* current = *head;          //The current node we are at
    list_node* next_node = NULL;         //Starts at NULL, will be changed to the node after Current

    while (current!=NULL)
    {
        next_node = current->next;       //next_node become the node after current
        current->next = previous_node;   //Change current's next item to its previous one, reversing the list step by step
        previous_node = current;         //Moves previous node to Current position
        current=next_node;               //Moves current node to Next node position
    }                                    //At the end of the loop, previous_node is the last item of the list

    *head = previous_node;               //Head is moved to the last item of the list, that is now the first. 
}

void print_list(int_item * head) 
{
    int_item * current = head;

    while (current != NULL) {
        printf("%d\n", current->value);
        current = (int_item*)current->node.next;
    }
}

int main()
{
    // struct string_item *my_linked_list = NULL;
    // list_append((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("Hello World"));
    // list_append((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("Test001"));
    // list_append((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("Test002"));
    // list_append((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("Last Item of the Linked List"));
    // struct string_item *string_item = my_linked_list;

    int_item *my_linked_list = NULL;

    list_append(LISTPP(my_linked_list), LIST(int_item_new(21)));
    list_append(LISTPP(my_linked_list), LIST(int_item_new(61)));
    list_append(LISTPP(my_linked_list), LIST(int_item_new(69)));
    list_append(LISTPP(my_linked_list), LIST(int_item_new(3)));
    list_append(LISTPP(my_linked_list), LIST(int_item_new(55555)));
    list_append(LISTPP(my_linked_list), LIST(int_item_new(777)));

    list_pop(LISTPP(my_linked_list));
    
    //list_remove(LISTPP(my_linked_list), LIST(int_item_new(3)));

    int_item *int_item = my_linked_list;
    print_list(int_item);

    list_reverse(LISTPP(int_item));

    print_list(int_item);
    
    return 0;
}