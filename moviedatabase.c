/*******************************************************************************

Project : CMP-5015Y - Programming 2, Assignment 1:
                      Off-line Movie Database in C (OMDB).

File    : moviedatabase.c

Date    : Sunday 03rd November 2019

Author  : Martin Siddons

Desc.   : Functions for loading data from films.txt into a LinkedList of Film
          structs and performing the tasks required via generic queries.

History : 05/11/2019 - v1.0 - Set up and tested all required LinkList functions.
          07/11/2019 - v1.1 - Rewrote get(head/tail) functions as peek.
          08/11/2019 - v1.2 - Defined sort functions.
          12/11/2019 - v1.3 - Giving up after several days trying to get
                              list_fill to actually work properly. :-(

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "moviedatabase.h"

List* list_new(){
    List* list = (List*)malloc(sizeof(List));

    if (list == NULL){
        fprintf(stderr, "Error: Unable to allocate memory for new list\n");
        exit(EXIT_FAILURE);
    }

    list->first = NULL;
    list->last  = NULL;

    return list;
}

void list_add(List* list, Film* new){
    Node* node = (Node*)malloc(sizeof(Node));

    if (node == NULL){
        fprintf(stderr, "Error: Unable to allocate memory to add to list\n");
        exit(EXIT_FAILURE);
    }

    node->thisFilm = new;
    node->next  = NULL;

    if (list->last == NULL){ // if LinkedList is currently empty.
        list->first = list->last = node;
    }
    else{
        // set the value of next on the current last node to point to this new
        // node and point the value for list-> to also point there.
        list->last = list->last->next = node;
    }
}

int list_length(List* list){
    int length = 0;
    if (list->first == NULL){ // if list is empty, return 0.
        return length;
    }
    for (Node* node = list->first; node != NULL; node = node->next){
        length++;
    }

    return length;
}

Film* list_peek(List* list, int position){
    if (list->first == NULL){
        fprintf(stderr, "Error: Unable to peek at an empty list.");
        exit(EXIT_FAILURE);
    }

    if (list_length(list) < (position)){
        fprintf(stderr, "Error: Given position is outside given list.");
        exit(EXIT_FAILURE);
    }

    // Iterate through the LinkedList until defined position is reached.
    // Assuming that 0 = first position, 1 = second, etc.
    Node* node;
    for (node = list->first; position != 0; node = node->next) {
        position--;
    }
    return node->thisFilm;
}

void list_remove(List* list, int position, char deleteFilms){
    if (list->first == NULL){
        fprintf(stderr, "Error: Unable to remove from an empty list.");
        exit(EXIT_FAILURE);
    }

    if (list_length(list) < position){
        fprintf(stderr, "Error: Given position is outside given list.");
        exit(EXIT_FAILURE);
    }

    Node* node = list->first;
    if (node == list->last){ // if there's only one node, clear the list.
        list->first = list->last = NULL;
    }
    else if (position == 0) { // if we're removing the head
        list->first = list->first->next;
    }
    else{ // find the node before the current one
        position = position - 1; // find the node before the one we're removing.
        while(position > 0){
            position--;
            node = node->next; // move to next node
        }
        // check if the node we're removing is the last and if so, make this one
        // the tail by pointing it at NULL and setting it as last.
        if(node->next->next == NULL){
            Node* nodeNext = node->next; // save the address for the next node.
            node->next = NULL;
            list->last = node;
            node = nodeNext; // move to the node we're removing.
        }
        else { // move the pointer for the next node one down the LinkedList.
            node->next = node->next->next;
            node->next; // move to the node we want to remove.
        }
    }
    if (deleteFilms == 'y') {
        film_free(node->thisFilm); // remove the film from memory.
    }
    free(node); // free the memory allocated to this node.
}

// yeah I know it sucks sorry just want to finish this at this point.
void list_remove_genre(List* list, char* remove, char deleteFilms){
    int pos = 0;

    for (Node* node = list->first; node != NULL; node = node->next) {
        // check if genre of this film contains the string given in 'remove'.
        if (strstr(film_getGenre(node->thisFilm), remove)){
            list_remove(list, pos, deleteFilms); // if so, remove it from the list.
        }
        pos++;
    }

}

// This sucks too, I know. It's too specific. I can't think of anything rn.
void list_remove_cert(List* list, char* remove, char deleteFilms){
    int pos = 0;

    for (Node* node = list->first; node != NULL; node = node->next) {
        // check if given string is present as the cert and if so, remove it.
        if (film_getCert(node->thisFilm) == remove){
            list_remove(list, pos, deleteFilms);
        }
        pos++;
    }
}

void list_clear(List *list){
    while (list->first != NULL){
        Node* node = list->first;
        list->first = node->next; // set the next node as the new start.
        film_free(node->thisFilm); // delete the film strut in this node.
        free(node); // then delete this node.
    }
    list->last = NULL;
}

void list_print(List* list){
    for (Node *node = list->first; node != NULL; node = node->next){
        printf("%s\n", film_toString(node->thisFilm));
    }
    printf("\n");
}

void list_free(List* list){
    free(list);
}

// Sort Functions:

int byYear(Film* a, Film* b){
    if (film_getYear(a) > film_getYear(b)){
        return -1; // looking for oldest first, so these two need switching.
    }
    return 0; // if Films are from the same year, or in correct order, return 0.
}

int byDuration(Film* a, Film* b){
    if (film_getDuration(a) < film_getDuration(b)){
        return -1; // looking for longest first, so these need to be swapped.
    }
    return 0; // if equal or in correct order, nothing needs to be done.
}

int byTitleLength(Film* a, Film* b){
    unsigned int len_a = strlen(film_getTitle(a));
    unsigned int len_b = strlen(film_getTitle(b));

    if (len_a > len_b){
        return -1; // looking for shortest first, so these need swapping.
    }
    return 0; // if the lengths are equal or in correct order, return 0.
}

// Main sort operation (calling a function pointer).
void list_sort(list_sort_operation op, List* list){
    if (list->first != list->last){   // If list contains two or more Films:
        int sorted;
        do{
            sorted = 1;
            // this loop iterates through all nodes in LinkedList.
            for (Node* node = list->first; node->next != NULL;
            node = node->next){
                // call the requested sort operation via function pointer.
                int comparison = op(node->thisFilm, node->next->thisFilm);
                if (comparison == -1){ // Film struts will need swapping.
                    Film* temp              = node->thisFilm;
                    node->thisFilm          = node->next->thisFilm;
                    node->next->thisFilm    = temp;
                    sorted                  = 0;
                }
            }
        }
        while (!sorted);
    }
}

// File functions

void list_fill(List* list, char* filename){
    FILE *input = fopen(filename, "r");
    if (input == NULL){ // Test if data can be loaded from file
        fprintf(stderr, "Error: Unable to open file '%s'.", filename);
        exit(EXIT_FAILURE);
    }


    char* curLine = "";// Initialise line as an empty string.

    while (fgets(curLine, 150, input) != NULL){
        // we have the film as a string, now split it into parts for film_new,
        // create the Film strut and add the strut to the list.
        list_add(list, film_fromString(curLine));
    }

    fclose(input);
}

List* list_clone(List* list){
    List* newList = list_new(); // create the list;

    // iterate through the list and call film_toString on each node.
    for (Node *node = list->first; node != NULL; node = node->next){
        char* filmString = film_toString(node->thisFilm);
        list_add(newList, film_fromString(filmString)); // create film strut
            // and add it to the list.
    }

    return newList;
}


//char* loadList(List* list){
//
//}

//List* list_add_string(char* string, List* list){
//
//}

// Test Harness
//main(){
//    Film* f1 = film_new("Some Title", 2019, "12A", "Horror", 420, 0 );
//    Film* f2 = film_new("Another title", 2016, "18", "Comedy", 69, 7.8);
//
//    List *movieList = list_new();
//    list_add(movieList, f1);
//    list_add(movieList, f2);
//    list_print(movieList);
//
//    printf("The list contains %d elements.\n", list_length(movieList));
//
//    Film *head = list_peekFirst(movieList);
//    printf("The first element is %s.\n", film_toString(head));
//    printf("The last element is %s.\n", film_toString(list_peekLast(movieList)));
//
//    printf("Sorting the list by year:\n");
//    list_sort(byYear, movieList);
//    list_print(movieList);
//
//    Film *second = list_peek(movieList, 1); // Assuming list starts at 0.
//    printf("The second film is: %s\n", film_toString(second));
//
//    printf("Removing the second film leaves:\n");
//    list_remove(movieList, 1); // remove the second (last) entry.
//    list_print(movieList);
//    printf("Once you remove the first entry too:\n");
//    list_remove(movieList, 0); // remove the first entry.
//    printf("The list contains %d elements.\n\n", list_length(movieList));
//
//    list_clear(movieList);
//    list_free(movieList);
//
//    List* list = list_new();
//    char* line = "";
//    line = "\"Indiana Jones and the Last Crusade\",1989,\"PG-13\",\"Action/Adventure/Fantasy\","
//           "127,0";
//    Film* f3 = film_fromString(line);
//    list_add(list, f3);
//    line = "\"The Great Dictator\",1940,\"APPROVED\",\"Comedy/Drama/War\",125,0";
//    Film* f4 = film_fromString(line);
//    list_add(list, f4);
//    list_fill(list, "films.txt");
//    list_print(list);
//}