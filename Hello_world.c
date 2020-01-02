#include "string.c"

int main ()
{
    string_t *string;

    string = creatString("Hello world\n");
    printString(string);

    return 0;
}
