#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    uint8_t *data;  // Symbols of string 
    uint8_t size;   // Size of string
} string_t;

static uint8_t sizeVal (const char *val);

// Creates a new string
static string_t *newString (uint8_t length)
{
    string_t *string;

    string = (string_t *) malloc(sizeof(string_t));
    string -> data = (uint8_t *) malloc(length);
    string -> size = length;

    return string;
}

// Writes text to a new string
string_t *creatString (const char *val)
{
    uint8_t size;
    string_t *string;

    size = sizeVal(val);
    string = newString(size);
    memcpy(string -> data, val, string -> size);

    return string;
}

// Clears a string
void freeString (string_t *string)
{
    free(string);
    free(string -> data);
    string -> size = 0;
}

// Clears a string with a given letter
void freenString (string_t *string, unsigned n)
{
    string -> data = (uint8_t *) realloc(string -> data, n);
    string -> size = n;
}

// Prints a string
void printString (string_t *string)
{
    fwrite(string -> data, sizeof(uint8_t), string -> size, stdout);
}

// Returns size of a string
uint8_t lenString (string_t *string)
{
    return string -> size;
}

// Lexicographic string comparison 1, 0, -1  -  s1 > s2, s1 = s2, s1 < s2
int cmpString (string_t *string1, string_t *string2)
{
    while (*string1 -> data++ == *string2 -> data++)
    {
        if (*string2 -> data == '\0')
        {
            return 0;
        }
    }

    return (*string1 -> data > *string2 -> data) ? 1 : -1;
}

// Lexicographic comparison of the first n bytes of strings
int cmpnString (string_t *string1, string_t *string2, unsigned n)
{
    for (unsigned i = 0; i < n && *string1 -> data++ == *string2 -> data++; i++)
    {
        if (i + 1 >= n)
        {
            return 0;
        }
    }

    return (*string1 -> data > *string2 -> data) ? 1 : -1;
}

// Copies from_string to to_string
void cpyString (string_t *to_string, string_t *from_string)
{
    freeString(to_string);

    to_string -> size = from_string -> size;
    to_string = newString(from_string -> size);
    memcpy(to_string -> data, from_string -> data, to_string -> size);
}

// Copies the first n bytes from from_string to to_string
void cpynString (string_t *to_string, string_t *from_string, unsigned n)
{
    n = (n > from_string -> size) ? from_string -> size : n;
    
    freeString(to_string);

    to_string -> size = n;
    to_string = newString(n);
    memcpy(to_string -> data, from_string -> data, n);
}

// Copies from from_string from sn bytes to fn bytes in to_string
void cpynnString (string_t *to_string, string_t *from_string, unsigned sn, unsigned fn)
{
    fn = (fn > from_string -> size) ? from_string -> size : fn;

    freeString(to_string);

    to_string -> size = fn - sn;
    to_string = newString(fn - sn);
    memcpy(to_string -> data, from_string -> data + sn, fn - sn);
}

// Appends the string to the end of to_string
void catString (string_t *to_string, string_t *string)
{
    to_string -> data = (uint8_t *) realloc(to_string -> data, to_string -> size + string -> size);
    memcpy(to_string -> data + to_string -> size, string -> data, string -> size);

    to_string -> size += string -> size;
}

// Appends no more than n initial characters of the string to the end of to_string
void catnString (string_t *to_string, string_t *string, unsigned n)
{
    n = (n > string -> size) ? string -> size : n;
    
    to_string -> data = (uint8_t *) realloc(to_string -> data, to_string -> size + n);
    memcpy(to_string -> data + to_string -> size, string -> data, n);

    to_string -> size += n;
}

// Appends sn - fn from from_string to to_string
void catnnString (string_t *to_string, string_t *from_string, unsigned sn, unsigned fn)
{
    fn = (fn > from_string -> size) ? from_string -> size : fn;
    
    to_string -> data = (uint8_t *) realloc(to_string -> data, to_string -> size + (fn - sn));
    memcpy(to_string -> data + to_string -> size, from_string -> data + sn, fn - sn);

    to_string -> size += (fn - sn);
}

// Appends the val to the end of string
void scatString (string_t *string, const char *val)
{
    uint8_t valsize = sizeVal(val);

    string -> data = (uint8_t *) realloc(string -> data, string -> size + valsize);
    memcpy(string -> data + string -> size, val, valsize);

    string -> size += valsize;
}

// Compare two strings by number of characters
int lengthString (string_t *string1, string_t *string2)
{
    int dif = lenString(string1) - lenString(string2);

    if (dif == 0)
    {
        return dif;
    }

    return (dif < 0) ? -1 : 1;
}

// Finds the length of a string constant
static uint8_t sizeVal (const char *val)
{
    uint8_t size;

    for (; *val != '\0'; val++)
    {
        size++;
    }

    return size;
}
