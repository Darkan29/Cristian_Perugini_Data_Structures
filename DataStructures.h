#define LIST(x) (list_node*)x   //REMOVES CAST TO SINGLE POINTER list_node
#define LISTPP(x) (list_node**)&x //REMOVES CAST TO POINTER TO POINTER list_node
#define INT_LIST(x) (struct int_item*)x //REMOVES CAST TO POINTER int_item

#define HASHMAP_SIZE 16
#define HASHMAP_SIZE_LIST 5
