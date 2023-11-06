#include <iostream>
#include <string>

int main()
{
    int wordCount = 0;
    std::string word;

    std::cout << "Enter words, one at a time. Enter 'done' to finish.\n";

    while (true)
    {
        std::cin >> word;

        if (word == "done")
        {
            break; // Exit the loop when "done" is entered
        }

        wordCount++;
    }

    std::cout << "You entered " << wordCount << " word(s) before 'done'." << std::endl;

    return 0;
}
