/*******************************************************************************

Project : CMP-5015Y - Programming 2, Assignment 1:
                      Off-line Movie Database in C (OMDB).

File    : film.c

Date    : Sunday 03rd November 2019

Author  : Martin Siddons

Desc.   : This contains the code for defining the film struct which holds the
          necessary information for each film listed in films.txt.

History : 03/11/2019 - v1.0 - Defined constructor, getters + toString.
          11/11/2019 - v1.1 - Added fromString but it's not working right(?)

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "film.h"

// Struct Constructors:
Film* film_new(char* title, int year, char* cert,
                char* genre, int duration, double rating){

    Film *f = (Film*)malloc(sizeof(Film)); // Allocate memory for film

    f->title    = title;
    f->year     = year;
    f->cert     = cert;
    f->genre    = genre;
    f->duration = duration;
    f->rating   = rating;

    return f;
}

Film* film_fromString(char* string){
    char *title, *cert, *genre, *charPtr;
    int year, duration;
    double rating;

    charPtr = strtok(string, "\"");
    title = charPtr;
    charPtr = strtok(NULL, "\",");
    year = atoi(charPtr); // convert given sting to int
    charPtr = strtok(NULL, "\"");
    cert = charPtr;
    charPtr = strtok(NULL, "\",");
    genre = charPtr;
    charPtr = strtok(NULL, ",");
    duration = atoi(charPtr); // convert given string to int again
    charPtr = strtok(NULL, "\n");
    rating = atof(charPtr); // convert given string to double.
    Film* f = film_new(title, year, cert, genre, duration, rating);
    return f;
}

// Accessor Functions:
char* film_getTitle(const Film *f){
    return f->title;
}

int film_getYear(const Film *f){
    return f->year;
}

char* film_getCert(Film *f){
    return f->cert;
}

char* film_getGenre(const Film *f){
    return f->genre;
}

int film_getDuration(const Film *f){
    return f->duration;
}

double film_getRating(const Film *f){
    return f->rating;
}

// toString Function:
char* film_toString(Film *f) {
    static char buffer[150]; // buffer to store an entry longer than expected

    sprintf(buffer, "\"%s\",%d,\"%s\",\"%s\",%d,%2.2f",
            f->title, f->year, f->cert, f->genre, f->duration, f->rating);

    return buffer;
}

// Free memory from malloc:
void film_free(Film *f){
    free(f);
}

// Test harness for Film.
//int main(){
//    Film *f1 = film_new("Some Title", 2019, "12A", "Horror", 420, 0 );
//    printf("Year of f1 = %i\n", film_getYear(f1));
//    printf("f1 is = %s\n", film_toString(f1));
//
//    return EXIT_SUCCESS;
//}