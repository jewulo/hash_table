// hash_table.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// https://www.youtube.com/watch?v=2Ti5yvumFTU


// continue at https://youtu.be/2Ti5yvumFTU?t=924

#include <iostream>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME    256
#define TABLE_SIZE  10

typedef struct {
    char name[MAX_NAME];
    int age;
} person;

unsigned int hash(const char* name)
{
    int length = strnlen(name, MAX_NAME);
    unsigned int hash_value = 0;
    for (int i = 0; i < length; ++i) {
        hash_value += name[i];
        hash_value = (hash_value * name[i]) % TABLE_SIZE;

    }
    return hash_value;
}

void test_hash_fn()
{
    printf("Jacob => %u\n", hash("Jacob"));
    printf("Natalie => %u\n", hash("Natalie"));
    printf("Sara => %u\n", hash("Sara"));
    printf("Mpho => %u\n", hash("Mpho"));
    printf("Tebogo => %u\n", hash("Tebogo"));
    printf("Ron => %u\n", hash("Ron"));
    printf("Jane => %u\n", hash("Jane"));
    printf("Maren => %u\n", hash("Maren"));
    printf("Bill => %u\n", hash("Bill"));

    printf("\n");
}

person* hash_table[TABLE_SIZE];

void init_hash_table()
{
    for (int i = 0; i < TABLE_SIZE; ++i) {
        hash_table[i] = NULL;
    }
    // table is empty
}

void print_table()
{
    printf("[hash table][start]\n");
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (hash_table[i] == NULL) {
            printf("\t%i\t---\n", i);
        }
        else {
            printf("\t%i\t%s\n", i, hash_table[i]->name);
        }
    }
    printf("[hash table][end]\n");
    printf("\n");
}

bool hash_table_insert(person *p)
{
    if (p == NULL) return false;
    int index = hash(p->name);
    if (hash_table[index] != NULL) {
        return false;
    }
    hash_table[index] = p;
    return true;
}

// find a person in the table by thier name
person *hash_table_lookup(const char *name)
{
    int index = hash(name);
    if (hash_table[index] != NULL &&
        strncmp(hash_table[index]->name, name, TABLE_SIZE) == 0) {
        return hash_table[index];
    } else {
        return NULL;
    }
}

// remove a person from the table. 
person* hash_table_delete(const char* name)
{
    int index = hash(name);
    if (hash_table[index] != NULL &&
        strncmp(hash_table[index]->name, name, TABLE_SIZE) == 0) {
        person* tmp = hash_table[index];
        hash_table[index] = NULL;
        return tmp;
    }
    else {
        return NULL;
    }
}

int main()
{
    test_hash_fn();

    init_hash_table();
    print_table();

    person jacob = { "Jacob", 256 };
    person kate = { "Kate", 27 };
    person mpho = { "Mpho", 14 };
    
    hash_table_insert(&jacob);
    hash_table_insert(&kate);
    hash_table_insert(&mpho);

    print_table();

    // lookup Mpho
    person* tmp = hash_table_lookup("Mpho");
    if (tmp == NULL) {
        printf("Mpho Not found!\n");
    }
    else {
        printf("Found %s.\n", tmp->name);
    }

    // lookup Geogre
    tmp = hash_table_lookup("George");
    if (tmp == NULL) {
        printf("George Not found!\n");
    }
    else {
        printf("Found %s.\n", tmp->name);
    }

    // delete Mpho
    person* del_tmp = hash_table_delete("Mpho");
    if (del_tmp == NULL) {
        printf("Not found!\n");
    }
    else {
        printf("Found %s. for deletion\n", del_tmp->name);
    }
    
    print_table();

    // dealing with collisions. add more entries
    // robert and jane will clash
    person sarah = { "Sarah", 54 };
    person edna = { "Edna", 15 };
    person maren = { "Maren", 25 };
    person eliza = { "Eliza", 34 };
    person robert = { "Robert", 1 };
    person jane = { "Jane", 75 };

    hash_table_insert(&sarah);
    hash_table_insert(&edna);
    hash_table_insert(&maren);
    hash_table_insert(&eliza);
    hash_table_insert(&robert);
    hash_table_insert(&jane);

    print_table();

    return 0;

    // continue at https://youtu.be/2Ti5yvumFTU?t=924
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
