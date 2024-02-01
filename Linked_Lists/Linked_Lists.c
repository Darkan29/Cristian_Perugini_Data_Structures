#include <stddef.h> // required for NULL
#include <stdlib.h>
#include <stdio.h>

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

int main()
{
    // struct string_item *my_linked_list = NULL;
    // list_append((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("Hello World"));
    // list_append((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("Test001"));
    // list_append((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("Test002"));
    // list_append((struct list_node **)&my_linked_list, (struct list_node *)string_item_new("Last Item of the Linked List"));
    // struct string_item *string_item = my_linked_list;

    int_item *my_linked_list = NULL;

    list_append((list_node**)&my_linked_list, (list_node*)int_item_new(21));
    list_append((list_node**)&my_linked_list, (list_node*)int_item_new(12));
    list_append((list_node**)&my_linked_list, (list_node*)int_item_new(69));

    int_item *int_item = my_linked_list;
    printf("%d\n",list_lenght((list_node*)int_item));

    while (int_item)
    {
        printf("%d\n", int_item->value);
        int_item = (struct int_item*)int_item->node.next;
    }

    
    return 0;
}