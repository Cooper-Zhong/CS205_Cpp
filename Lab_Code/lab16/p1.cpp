#include <iostream>
#include <stdexcept>

using namespace std;
class OutOfRangeException : public std::exception
{
private:
    string errorMsg;

public:
    OutOfRangeException(const string &msg) : errorMsg(msg) {}

    const char* what() const noexcept override 
    {
        return errorMsg.c_str();
    }
};

float calculateAverage(int mark1, int mark2, int mark3, int mark4)
{
    if (mark1 < 0 || mark1 > 100)
    {
        throw OutOfRangeException("Mark 1 out of range (0-100)");
    }
    if (mark2 < 0 || mark2 > 100)
    {
        throw OutOfRangeException("Mark 2 out of range (0-100)");
    }
    if (mark3 < 0 || mark3 > 100)
    {
        throw OutOfRangeException("Mark 3 out of range (0-100)");
    }
    if (mark4 < 0 || mark4 > 100)
    {
        throw OutOfRangeException("Mark 4 out of range (0-100)");
    }

    return static_cast<float>(mark1 + mark2 + mark3 + mark4) / 4.0f;
}

int main()
{
    while (true)
    {
        try
        {
            cout << "Please enter 4 marks: ";
            int m1, m2, m3, m4;
            cin >> m1 >> m2 >> m3 >> m4;

            float avg = calculateAverage(m1, m2, m3, m4);
            cout << "Average: " << avg << endl;

            char c;
            cout << "Would you like to continue? (y/n): ";
            cin >> c;
            if (c != 'y')
            {
                break;
            }
        }
        catch (const OutOfRangeException &e)
        {
            std::cout << "Exception: " << e.what() << std::endl;
            // Clear the input buffer to prevent the infinite loop
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    return 0;
}
