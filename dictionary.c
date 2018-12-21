// Implements a dictionary's functionality

#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

// Here we define a custom data type based on a custom data structure: the node.
// The node will consist of 45+1=46 characters in memory (the longest word in English plus room for that null).
// node * declares a variable that points to a node.
typedef struct node
{
     char word[LENGTH+1];
     struct node *next;
}
node;

// We will be using a hash table to organize and store our data.
// A hash table consists of an array of linked lists. Each element of this array is a node*, or a node pointer pointing to the very first node of a linked list.
// Creating a hash table is as easy as creating an array of any other variable type:
node *hashtable[AZSIZE];

// Here we have our hash function named hashFn. This little guy will calculate the index of the hashtable by taking the modulus (or remainder)...
// ... of the integer value of the first character of a word and 27 (every character in the alphabet plus an apostrophe).
// To search a linked list, hash(word) should be a pointer to a linked list:
int hash(char* key)
{
    int index = 0;
    index = key[0] % AZSIZE;
    return index;
}


// This function returns true if word is in dictionary else false.
// This function is case insensitive.
// This function assumes only strings with alphabetical characters and/or apostrophes will be passed.
bool check(const char *word)
{
    // For this function to not be case sensitive, we will convert all characters in word to lower case to jive with our exclusively lower-case dictionary.
    char lower[strlen(word)+1];
    for (int i = 0; i < strlen(word); i++)
    {
        lower[i] = tolower(word[i]);
    }
    lower[strlen(word)] = '\0';

    // Now that we've neutered the CaSe SiTuAtIoN, it's time to dig into our hash table.
    // For starters, we need to determine which index of our hash function we're going to follow to a trail of linked lists.
    // Remember, a hash table is simply an array of linked lists where each element of the array is a pointer to the first node of a list.
    // One big question: which bucket will this word be in? One answer:
    int index = hash(lower);

    // Now we initialize the head, or the first node in our hash table:
    node* head = hashtable[index];

    // If the word exists, it should be found in the hash table.
    // How do we search the bucket? That is, how do we traverse a linked list?
    // traversing linked lists:
    node *cursor = head;
    while (cursor != NULL)
    {
        // do something.
        if (strcmp(word, cursor->word) == 0)
        {
            return true;
        }

        //Note that we didn't malloc any space. The cursor is simply a pointer, not a node!
        cursor = cursor->next;
    }
    return false;
}


// Now we have a new node with a value we scanned from the dictionary. Let's insert that into a linked list!
// IMPORTANT! MAINTAIN LINKS IN LINKED LIST!!!
// Reiterate: Take word from dictionary. Take that word and put it into node. Take that node and put it into linked list.
// Next: Which word do we put into which linked list?
// Time to use a hash function!! hash function: 1. takes a string 2. returns an index (index < # buckets) 3. deterministic (the same value needs to map to the same bucket every time)
// Once you've made your hash function, you can hash your words.
// hash the word: 1. new_node->word has the word from the dictionary 2. hashing new_node->word will give us the index of a bucket in the hash table 3. insert into the linked list
// REMEMBER: A HASH TABLE IS AN ARRAY OF LINKED LISTS, AND EACH ELEMENT OF ARRAY IS A NODE * (POINTER POINTING TO THE VERY FIRST NODE IN THAT LINKED LIST)

// As we will want to show the size of our loaded dictionary in the function size(), we will initialize an integer to count during load().
int nowords = 0;

// This function loads dictionary into memory, returning true if successful else false
// We are going to load a dictionary into a hash table! REMEMBER: A HASH TABLE IS AN ARRAY OF LINKED LISTS, AND EACH ELEMENT OF ARRAY IS A NODE *
bool load(const char *dictionary)
{
    // Our first step to loading a dictionary is, of course, to load the source file.
    FILE* dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return false;
    }

    // We need to set aside space for the words we are scanning from dict!
    char word[LENGTH + 1];

    // make a new word: scan dictionary word by word
    while (fscanf(dict, "%s", word) != EOF)
    {
        // We need to make sure the last character in our extracted string is the null terminator '\0'.
        word[strlen(word)] = '\0';

        // Here we allocate enough memory to store our node using the malloc() function.
        // malloc() returns a pointer to the memory which stores our node char and pointer.
        // Whenever we're creating a node, we actually just want to malloc a node pointer.
        // make a new word: malloc a node * for each new word
        node *new_node = malloc(sizeof(node));

        // (always need to check to make sure you don't run out of memory)
        if (new_node == NULL)
        {
            unload();
            return false;
        }

        // To set the value for new_node, we'll use the arrow notation in order to access the word variable, and strcpy() to set word equal to a particular string.
        // make a new word: copy word into node
        strcpy(new_node->word, word);

        // Now how do we correctly insert into a linked list?
        // Point our new node to the pointer the head's pointing to so that..
        // ... we can THEN point the head to new_node.
        node* head = NULL;

        new_node->next = head;
        head = new_node;

        int index = hash(word);
        // new_node->next = hashtable[index];

        // hash the word:
        // new_node->word has the word from the dictionary
        // hashing new_node->word will give us the index of a bucket in the hash table
        // insert into the linked list

        // Our word count just went up by 1!
        nowords++;
    }
    return false;


    // Reiterate: Take word from dictionary. Take that word and put it into node. Take that node and put it into linked list.
    // Next: Which word do we put into which linked list?
    // Time to use a hash function!! hash function: 1. takes a string 2. returns an index (index < # buckets) 3. deterministic (the same value needs to map to the same bucket every time)
    // Once you've made your hash function, you can hash your words.

    // hash the word: 1. new_node->word has the word from the dictionary 2. hashing new_node->word will give us the index of a bucket in the hash table 3. insert into the linked list
    // REMEMBER: A HASH TABLE IS AN ARRAY OF LINKED LISTS, AND EACH ELEMENT OF ARRAY IS A NODE * (POINTER POINTING TO THE VERY FIRST NODE IN THAT LINKED LIST)

}

// Returns number of words in dictionary if loaded else 0 if not yet loaded.
unsigned int size(void)
{
    // The good news is that we counted the number of words in our loaded dictionary in size().
    return nowords;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}
