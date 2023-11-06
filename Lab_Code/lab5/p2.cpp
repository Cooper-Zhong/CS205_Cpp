#include <iostream>
#include <cctype> // for isalpha

int main()
{
    char input;
    int vowelsCount = 0;
    int consonantsCount = 0;
    int otherCount = 0;

    std::cout << "Enter words, one at a time. Enter 'q' to finish.\n";

    while (true)
    {
        std::string word;
        std::cin >> word;

        if (word == "q")
            break;
        if (!word.empty())
        {
            char firstChar = word[0];
            if (isalpha(firstChar))
            {
                if (tolower(firstChar) == 'a' || tolower(firstChar) == 'e' || tolower(firstChar) == 'i' || tolower(firstChar) == 'o' || tolower(firstChar) == 'u')
                {
                    vowelsCount++;
                }
                else
                {
                    consonantsCount++;
                }
            }
            else
            {
                otherCount++;
            }
        }
    }

    std::cout << "Words beginning with vowels: " << vowelsCount << std::endl;
    std::cout << "Words beginning with consonants: " << consonantsCount << std::endl;
    std::cout << "Words that don't fit either category: " << otherCount << std::endl;

    return 0;
}
