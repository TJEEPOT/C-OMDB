/*******************************************************************************

Project : CMP-5015Y - Programming 2, Assignment 1:
                      Off-line Movie Database in C (OMDB).

File    : moviedatabase.c

Date    : Sunday 03rd November 2019

Author  : Martin Siddons

Desc.   : Main function for calling moviedatabase functions to complete tasks.

History : 12/11/2019 - v1.0 - Giving up after several days trying to get
                              list_fill to actually work properly. :-(
          13/11/2019 - v1.1 - Finished writing tasks to best of my ability,
                              but unable to test them.

*******************************************************************************/


#include <stdio.h>
#include <stdlib.h>

#include "moviedatabase.h"


int main(int argc, char** argv) {
    // Note - These tasks won't actually complete as I can't get the movies to
    // load correctly from films.txt (see note in moviedatabase.c). I've
    // written these mostly blind, I think they'd work if I could actually
    // test them, but I can't be certain.

    // Initialise and fill the list:
    List* movieList = list_new(); // initialise the list.
    list_fill(movieList, "films.txt"); // populate the list with
        // entries from films.txt (if it was working correctly).

    // Task #1:
    list_sort(byYear, movieList); // Sort list by year.
    list_print(movieList); // print list of movies to console.

    // Task #2:
    List* filmNoir = list_clone(movieList); // make a copy of the list.
    // I should probably locate and clone the individual nodes I want from the
    // main list but I really don't want to re-write this right now...
    list_remove_genre(filmNoir, "Film-Noir", 'n');
    list_sort(byDuration, filmNoir); // fp to sort list by longest duration.
    Film* thirdLongest = list_peek(filmNoir, 2); // third entry in list.
    printf("The third longest Film-Noir is: %s\n",
            film_toString(thirdLongest));
    list_free(filmNoir); // dispose of this list.

    // Task #3:
    list_sort(byTitleLength, movieList); // sort the main list by title length.
    Film* shortestTitle = list_peek(movieList, 0); // return a pointer.
    printf("The movie with shortest title is: %s\n",
            film_toString(shortestTitle));

    // Task #4:
    list_remove_cert(movieList, "R", 'y'); // must exactly match.
    printf("After removing all Cert-R movies, the list has %d entries",
            list_length(movieList));

    list_clear(movieList); // remove all nodes, and films stored within them.
    list_free(movieList); // delete the list.

    return EXIT_SUCCESS;
}