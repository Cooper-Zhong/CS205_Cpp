#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

int main()
{
    // Get user input
    std::cout << "Enter a string: ";
    std::string input;
    std::getline(std::cin, input);

    // Save the letters and blanks to f1.txt
    std::ofstream file1("f1.txt");
    for (char c : input)
    {
        if (std::isalpha(c) || std::isspace(c))
            file1.put(c);
    }
    file1.close();

    // Convert lowercase letters to uppercase and save to f2.txt
    std::ofstream file2("f2.txt");
    for (char c : input)
    {
        if (std::isalpha(c) || std::isspace(c))
        {

            file2.put(std::toupper(c));
        }
    }
    file2.close();

    // Display the contents of f1.txt
    std::ifstream readFile1("f1.txt");
    std::string content1;
    if (readFile1.is_open())
    {
        std::cout << "Contents of f1.txt:" << std::endl;
        char ch;
        while (readFile1.get(ch))
            std::cout << ch;
        readFile1.close();
    }
    else
    {
        std::cerr << "Error opening f1.txt." << std::endl;
    }

    // Display the contents of f2.txt
    std::ifstream readFile2("f2.txt");
    std::string content2;
    if (readFile2.is_open())
    {
        std::cout << "\nContents of f2.txt (Uppercase):" << std::endl;
        char ch;
        while (readFile2.get(ch))
        {
            std::cout << ch;
        }
        readFile2.close();
    }
    else
    {
        std::cerr << "Error opening f2.txt." << std::endl;
    }

    return 0;
}
