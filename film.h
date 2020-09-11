/*******************************************************************************

Project : CMP-5015Y - Programming 2, Assignment 1:
                      Off-line Movie Database in C (OMDB).

File    : film.h

Date    : Sunday 03rd November 2019

Author  : Martin Siddons

Desc.   : Definitions for functions found in film.c.

History : 03/11/2019 - v1.0 - Listed constructor, getters + toString.

*******************************************************************************/

#ifndef OMDB_FILM_H
#define OMDB_FILM_H

#endif

// Struct definition
typedef struct FilmStruct{
    char *title, *cert, *genre;
    int year, duration;
    double rating;
} Film;

// Constructors
Film* film_new(char* title, int year, char* cert,
        char* genre, int duration, double rating);

// Takes a given string and uses the above to create a Film strut.
Film* film_fromString(char* string);

// Getters
char* film_getTitle(const Film *f);

int film_getYear(const Film *f);

char* film_getCert(Film *f);

char* film_getGenre(const Film *f);

int film_getDuration(const Film *f);

double film_getRating(const Film *f);

// toString - Outputs film title as a string as it's listed.
char* film_toString(Film *f);

// Destructor
void film_free(Film *f);