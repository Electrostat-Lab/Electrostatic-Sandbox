/*

Simple example code for: Usage of customizable lists of type "CONTIGUOUS_BUFFER"
A simple program that makes a list, add data to it in different places and delete
data in some place. A simple test of the list capabilities

>>> Design Philosophy: This list - abstractly - is a dynamic contiguous 
    buffer of pointers that point to user data wherever this data was stored
    (On Stack or Heap .. User's choice). The list just handles pointers order 

This list implementation is built (by pavl-g) for hashmaps to work with hashing function
(also the naming is done according to that) so don't use it like an std::vector 
(although in some cases it can work as a vector)
Also note that this list is basically a contiguous buffer of pointers 
to list_element pointers (I think this needs to change)
To know the operations you can do on this list check out "list_function_table"
in "list.h" header file

>>> Notes:
1) List accepts only elements of type: (list_element *)
    (pointers to struct list_element) so before any operation
    put your data inside "list_element"s
2) You still can't initialize the list directly with more than one element
    (you have to add them one by one)
3) After declaring a list, you first have to specify a type 
    (only CONTIGUOUS_BUFFER for now)
    Secondly, initialize its "list_function_table" with a function_table of your own
    Third, Specify a limit (deal with "limit" as an initial size of new list)
    Lastly, initialize the function_table with correct (CONTIGUOUS_BUFFER)
    functions using init_list_function_table() after allocating memory
    (Yeah its a bit ridiculous but in order to be generic and work with hashing)   
5) The list you declared itself (and as a result the first element) is held
    by a pointer to the list_element pointer called elements (elements **)
    This enables moving between elements by using
    pointer arithmetics or array indexing on this pointer
5) You have to allocate the memory for the list elements yourself
    and return the address to (elements **)
6) You can't insert an element in a place in the middle without overwriting
    the original element at that place (for hashmap reasons) so you have
    to shift the elements yourself, empty that place and then insert
7) All operations return a status code to check for errors (separated from main() return)
    (WORK IN PROGRESS !)
8) Position is the index of the element (((to-be-added)))
    (last added element + 1)
9) You can use Position as the size of elements containing actual data at any time
11) Compiling using electrostatic-sandbox command is down below
12) list_info is a struct used solely (for now) for iteartion on the list
13) You should NOT modify limit (after first initialization) or position
    (This is not intended because they are private data .. Should be "encapsulated")

*/

#include <stdio.h>
#include <stdlib.h>

#include <electronetsoft/arithmos/adt/list.h>

static void printListValues(list userList) // for debugging
{
    for (int i = 0; i < userList.position; i++)
    {
        // In order to get the data: dereference (list_elements **) by array index
        //                         -> dereference (list_element *) by using "->"
        //                         -> cast (data) generic pointer to (int *)
        //                         -> dereference (data)
        printf("Element %d : %d\n", i, *(int *)(userList.elements[i]->data));
    }

    printf("========================================\n");
}

int main(void)
{
    printf("\n========================================\n");

    int myData[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // Initial data

    // Put data into "list_element"s because list only takes pointers to this type
    list_element myElements[10];
    for (int i = 0; i < 10; i++)
    {
        myElements[i].data = &myData[i];
    }

    // STEP 1) Declare the list and initialize its function table
    list_function_table operations = {0};
    list myList = {0};
    myList.type = CONTIGUOUS_BUFFER; // Only initialize, Don't modify after this
    myList.function_table = &operations; // Only initialize, Don't modify after this
    myList.limit = 10; // Only initialize, Don't modify after this

    // STEP 2 - option A) Allocate memory buffer for the list on Heap
    myList.elements = malloc(myList.limit * sizeof(list_element*));
    if (myList.elements == NULL) 
    {
        printf("Could not allocate the buffer\n");
        return -1;
    }

    for (int i = 0; i < myList.limit; i++) // Nullify list pointers
    {
        myList.elements[i] = NULL;
    }

    // STEP 2 - option B) Use the allocated myElements array on Stack
    // WORK IN PROGRESS!

    // STEP 3) Initialize your contiguous buffer with its operations
    status_code init_operations = init_list_function_table(&myList, myList.elements, &operations, NULL);
    if (init_operations != PASS) 
    {
        printf("Could not initialize the buffer\n");
        free(myList.elements);
        return -1;
    }


    // Add myData (in form of myElements) to the allocated list buffer
    for (int i = 0; i < myList.limit; i++)
    {
        if (myList.function_table->add(&myList, &myElements[i]) != PASS)
        {
            printf("Could not add an item\n");
            free(myList.elements);
            return -1;
        }
    }

    printf("List initialized with data!\n");
    printf("Index of next element to be added : [%lu]\n", myList.position);
    printListValues(myList);

    // Add 99 at the end of the list
    int newLast_int = 99;
    list_element newLast_element = {0};
    newLast_element.data = &newLast_int;

    if (myList.function_table->add(&myList, &newLast_element) != PASS)
    {
        printf("Could not add an item\n");
        free(myList.elements);
        return -1;
    }

    printf("Added 99 at the end!\n");
    printf("Index of next element to be added : [%lu]\n", myList.position);
    printListValues(myList);

    // Insert 99 in the middle
    int newMid_int = 67;
    list_element newMid_element = {0};
    newMid_element.data = &newMid_int;

    if (myList.function_table->insert_overwrite(&myList, &newMid_element, 5) != PASS)
    {
        printf("Could not insert an item\n");
        free(myList.elements);
        return -1;
    }

    printf("Inserted 67 in the middle!\n");
    printf("Index of next element to be added : [%lu]\n", myList.position);
    printListValues(myList);

    // Delete the second element
    if (myList.function_table->remove_by_index(&myList, 1) != PASS)
    {
        printf("Could not delete an item\n");
        free(myList.elements);
        return -1;
    }

    printf("Deleted the second element!\n");
    printf("Index of next element to be added : [%lu]\n", myList.position);
    printListValues(myList);

    free(myList.elements);
    return 0;
}

/*

>>> Compiling:
Go to (cd to) root directory of SDK before compiling
Copy this line and paste in your terminal:
./helper-scripts/ci-cd/test-electrostatic.sh "misc/hello_customizable_list.c" "list"

*/