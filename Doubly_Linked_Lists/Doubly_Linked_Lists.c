#include <stddef.h> // required for NULL
#include <stdlib.h>
#include <stdio.h>


struct list_node
{
    struct list_node *prev;
    struct list_node *next;
};

struct list_node *list_append (struct list_node **head, struct list_node *item)
{
    struct list_node *tail = list_get_tail (head);
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