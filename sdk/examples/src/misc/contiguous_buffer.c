#include <stdio.h>
#include <stdlib.h>
#include <electronetsoft/arithmos/adt/list.h>

int main(void) {
    // STEP 1) Initialize
    int myData[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 99};
    list_element buffer_slots[11];
    list_function_table operations; // P.S : I don't like this
    list buffer;
    buffer.type = CONTIGUOUS_BUFFER;
    buffer.function_table = &operations; // P.S : I don't like this
    buffer.limit = 16;

    // STEP 2) Allocate
    buffer.elements = malloc(buffer.limit * sizeof(*buffer.elements));
    if (buffer.elements == NULL) 
    {
        printf("Could not allocate the buffer");
        return -1;
    }
    for (size_t i = 0; i < buffer.limit; i++) // Remove garbage memory
    {
        buffer.elements[i] = NULL;
    }

    // STEP 3) Initialize correct operations (of contiguous buffer)
    status_code init_operations = init_list_function_table(&buffer, buffer.elements, &operations, NULL);
    if (init_operations != PASS) 
    {
        printf("Could not initialize the buffer\n");
        free(buffer.elements);
        return -1;
    }

    // Add ten integers to the buffer.
    for (size_t i = 0; i < 10; i++) 
    {
        buffer_slots[i].data = &myData[i];
        buffer_slots[i].size = sizeof(myData[i]);
        buffer_slots[i].type = ELEMENT_LIST;

        if (buffer.function_table->add(&buffer, &buffer_slots[i]) != PASS) 
        {
            printf("Could not add an item\n");
            free(buffer.elements);
            return -1;
        }
    }

    // Add 99 at the end.
    buffer_slots[10].data = &myData[10];
    buffer_slots[10].size = sizeof(myData[10]);
    buffer_slots[10].type = ELEMENT_LIST;
    if (buffer.function_table->add(&buffer, &buffer_slots[10]) != PASS) 
    {
        printf("Could not add 99\n");
        free(buffer.elements);
        return -1;
    }

    // Shift items right to insert 99 in the middle.
    for (size_t i = buffer.position - 1; i > 5; i--) 
    {
        buffer.elements[i] = buffer.elements[i - 1];
    }
    buffer.elements[5] = &buffer_slots[10];

    // Delete the second item (index 1).
    if (buffer.function_table->remove_by_index(&buffer, 1) != PASS) 
    {
        printf("Could not remove the second item\n");
        free(buffer.elements);
        return -1;
    }

    // Print the final buffer.
    for (size_t i = 0; i < buffer.position; i++) 
    {
        printf("%d ", *(int *) buffer.elements[i]->data); // Cast pointer to dereference it
    }
    printf("\n");

    free(buffer.elements);
    return 0;
}
