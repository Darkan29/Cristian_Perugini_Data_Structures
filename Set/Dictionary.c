#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "../DataStructures.h"

typedef struct aiv_dictionary_item
{
    const char *key;
    int value;
    size_t key_len;
}aiv_dictionary_item;

typedef struct aiv_dictionary
{
    struct aiv_dictionary_item hashmap[HASHMAP_SIZE][HASHMAP_SIZE_LIST];
}aiv_dictionary;

size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;

    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }

    return hash;
}

void aiv_dictionary_insert(aiv_dictionary *set, const char *key, const int value)
{
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    for (size_t i = 0; i < HASHMAP_SIZE; i++)  //CHECKS FOR UNIQUE KEY/VALUE PAIR
    {
        if (set->hashmap[index][i].key == key && set->hashmap[index][i].value == value)   //if current iteration's key/value inside the hashmap is equal to the given key/value
        {
            printf("There is already a %s element with %d value\n\n", key, value);  
            return;
        }
    }

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if (set->hashmap[index][i].key_len == 0)
        {
            set->hashmap[index][i].key = key;
            set->hashmap[index][i].value = value;
            set->hashmap[index][i].key_len = key_len;
            printf("hash of %s = %llu (index: %llu)\n", key, hash, index);
            printf("added %s with %d value at index %llu slot %llu\n", key, value, index, i);
            
            return;
        }
    }

    printf("COLLISION! for %s with %d value (index %llu)\n", key, value, index);
}

void aiv_dictionary_find(aiv_dictionary *set, const char *key, const int value)
{
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if (set->hashmap[index][i].key_len > 0)
        {
            if (set->hashmap[index][i].key == key && set->hashmap[index][i].value == value && !memcmp(set->hashmap[index][i].key, key, key_len))
            {
                printf("hash of %s = %llu (index: %llu)\n", key, hash, index);
                printf("FOUND %s with %d value at index %llu slot %llu\n", key, value, index, i);
                return;
            }
        }
    }

    printf("ERROR: No Key/Value pair found with Key=%s and Value=%d", key, value);
}

int main(int argc, char **argv)
{
    struct aiv_dictionary myset;
    memset(&myset, 0, sizeof(aiv_dictionary));

    aiv_dictionary_insert(&myset, "Uno", 1);
    aiv_dictionary_insert(&myset, "Due", 2);
    aiv_dictionary_insert(&myset, "Tre", 3);
    aiv_dictionary_insert(&myset, "Quattro", 4);
    aiv_dictionary_insert(&myset, "Cinque", 5);
    aiv_dictionary_insert(&myset, "Sei", 6);

    aiv_dictionary_insert(&myset, "Due", 2);  //WILL NOT ADD THIS

    aiv_dictionary_find(&myset, "Due", 2);    //WILL FIND THIS
    aiv_dictionary_find(&myset, "Due", 89);   //WILL NOT FIND THIS



    return 0;
}
