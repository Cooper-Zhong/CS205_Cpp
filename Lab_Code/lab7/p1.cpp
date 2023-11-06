#include <iostream>
#include <cstring> // prototype for strlen()

struct stringy
{
    char *str; // points to a string
    int ct;    // length of string (not counting '\0')
};

// prototypes for set(), show(), and show() go here
void set(stringy &beany, const char *testing);
void show(const stringy &beany, int n = 1);
void show(const char *testing, int n = 1);

int main()
{
    stringy beany;
    char testing[] = "Reality isn't what it used to be.";
    set(beany, testing); // first argument is a reference,
                         // allocates space to hold copy of testing,
                         // sets str member of beany to point to the
                         // new block, copies testing to new block,
                         // and sets ct member of beany
    show(beany);         // prints member string once
    show(beany, 2);      // prints member string twice
    testing[0] = 'D';
    testing[1] = 'u';
    show(testing);    // prints testing string once
    show(testing, 3); // prints testing string thrice
    show(beany, 2);
    show("Done!");

    return 0;
}

void set(stringy &beany, const char *testing)
{
    beany.ct = strlen(testing);
    beany.str = new char[beany.ct + 1];
    strcpy(beany.str, testing);
}

void show(const stringy &beany, int n)
{
    for (int i = 0; i < n; i++)
        std::cout << beany.str << std::endl;
}

void show(const char *testing, int n)
{
    for (int i = 0; i < n; i++)
        std::cout << testing << std::endl;
}