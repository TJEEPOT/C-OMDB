/*******************************************************************************

Project : CMP-5015Y - Programming 2, Assignment 1:
                      Off-line Movie Database in C (OMDB).

File    : moviedatabase.h

Date    : Sunday 03rd November 2019

Author  : Martin Siddons

Desc.   : Definitions for functions found in moviedatabase.c.

*******************************************************************************/

#ifndef OMDB_MOVIEDATABASE_H
#define OMDB_MOVIEDATABASE_H

#include "film.h"

// Define the Elements of the LinkedList.
typedef struct _Node
{
    Film* thisFilm;

    struct _Node* next;
}
Node;

// Define the first and last nodes of the LinkedList.
typedef struct _List
{
    Node* first;

    Node* last;
}
List;

// LinkedList Functions:
// Create a new LinkedList by allocating the memory and initialising it.
List* list_new();

// Add a new node to the last position in the LinkedList.
void list_add(List* list, Film* new);

// Count how many nodes are in the LinkedList.
int list_length(List* list);

// Peek at the specified node in the LinkedList and return the Film strut there.
Film* list_peek(List* list, int position);

// Delete all nodes in the LinkedList.
void list_clear(List* list);

// Delete a specific node in the LinkedList and the film if specified.
void list_remove(List* list, int position, char deleteFilms);

// Use list_remove to remove certain entries in a genre.
void list_remove_genre(List* list, char* remove, char deleteFilms);

// Use list_remove to remove certain entries in a cert.
void list_remove_cert(List* list, char* remove, char deleteFilms);

// Print each member of the list to stdout using film_toString.
void list_print(List* list);

// Free memory for the list:
void list_free(List* list);

// Sorting Functions:
// Define the pointer function for selecting sort function operation.
typedef int (*list_sort_operation)(Film* a, Film* b);

// Sort function, which sorts list by given operation (fp) using bubble sort.
void list_sort(list_sort_operation op, List* list);

// Compare the year value of two Film struts (earliest first).
int byYear(Film* a, Film* b);

// Compare the Duration of two film struts (longest first).
int byDuration(Film* a, Film* b);

// Compare the Title Length of  two film struts (shortest first).
int byTitleLength(Film* a, Film* b);

// Data Handling Functions:
// Load a given list with entries from a given file.
void list_fill(List* list, char* filename);

// Make a duplicate of the given list and return it.
List* list_clone(List* list);

#endif