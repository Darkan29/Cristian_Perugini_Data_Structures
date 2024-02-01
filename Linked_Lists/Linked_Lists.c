#include <stddef.h> // required for NULL
#include <stdlib.h>
#include <stdio.h>

struct list_node
{
    struct list_node *next;
};

struct list_node *list_get_tail(struct list_node **head)
{
    if (!head)
    {
        return NULL;
    }

    struct list_node *current_node = *head;
    struct list_node *last_node = NULL;
    while (current_node)
    {
        last_node = current_node;
        current_node = current_node->next;
    }
    return last_node;
}

struct list_node *list_append(struct list_node **head, struct list_node *item)
{
    struct list_node *tail = list_get_tail(head);
    if (!tail)
    {
        *head = item;
    }
    else
    {
        tail->next = item;
    }
    item->next = NULL;
    return item;
}
struct list_node *list_pop(struct list_node **head)
{
    struct list_node *current_head = *head;
    if (!current_head)
    {
        return NULL;
    }
    *head = (*head)->next;
    current_head->next = NULL;
    return current_head;
}

struct string_item
{
    struct list_node node;
    const char *string;
};

typedef struct int_item
{
    struct list_node node;
    int value;
}int_item;

struct string_item *string_item_new(const char *string)
{
    struct string_item *item = malloc(sizeof(struct string_item));
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

    list_append((struct list_node**)&my_linked_list, (struct list_node*)int_item_new(21));
    list_append((struct list_node**)&my_linked_list, (struct list_node*)int_item_new(12));
    list_append((struct list_node**)&my_linked_list, (struct list_node*)int_item_new(69));

    int_item *int_item = my_linked_list;

    while (int_item)
    {
        printf("%d\n", int_item->value);
        int_item = (struct int_item*)int_item->node.next;
    }
    return 0;
}