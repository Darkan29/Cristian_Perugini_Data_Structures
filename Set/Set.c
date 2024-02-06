#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "../DataStructures.h"

typedef struct aiv_set_item
{
    const char *key;
    size_t key_len;
}aiv_set_item;

typedef struct aiv_set
{
    struct aiv_set_item hashmap[HASHMAP_SIZE][HASHMAP_SIZE_LIST];
}aiv_set;

size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;

    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }

    return hash;
}

void aiv_set_insert(aiv_set *set, const char *key)
{
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    for (size_t i = 0; i < HASHMAP_SIZE; i++)  //CHECK FOR UNIQUE KEYS
    {
        if (set->hashmap[index][i].key == key)
        {
            printf("There is already a %s element\n", key);
            return;
        }
    }

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if (set->hashmap[index][i].key_len == 0)
        {
            set->hashmap[index][i].key = key;
            set->hashmap[index][i].key_len = key_len;
            printf("hash of %s = %llu (index: %llu)\n", key, hash, index);
            printf("added %s at index %llu slot %llu\n", key, index, i);
            
            return;
        }
    }

    printf("COLLISION! for %s (index %llu)\n", key, index);
}

void aiv_set_find(struct aiv_set *set, const char *key)
{
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    printf("hash of %s = %llu (index: %llu)\n", key, hash, index);

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if (set->hashmap[index][i].key_len > 0)
        {
            if (set->hashmap[index][i].key_len == key_len && !memcmp(set->hashmap[index][i].key, key, key_len))
            {
                printf("FOUND %s at index %llu slot %llu\n", key, index, i);
                return;
            }
        }
    }
}

int main(int argc, char **argv)
{
    struct aiv_set myset;
    memset(&myset, 0, sizeof(struct aiv_set));

    aiv_set_insert(&myset, "Hello");
    aiv_set_insert(&myset, "Hello2");
    aiv_set_insert(&myset, "Test");
    aiv_set_insert(&myset, "Foobar");
    aiv_set_insert(&myset, "XYZ");
    aiv_set_insert(&myset, "AAAAAA");
    aiv_set_insert(&myset, "AAAAAa");

    aiv_set_find(&myset, "XYZ");

    aiv_set_insert(&myset, "AAAAAa"); //THIS KEY IS ALREADY IN THE SET
    aiv_set_insert(&myset, "Hello2"); //THIS KEY IS ALREADY IN THE SET
    aiv_set_insert(&myset, "NotInSet"); 

    aiv_set_insert(&myset, "NotInSet"); //IN SET

    return 0;
}
