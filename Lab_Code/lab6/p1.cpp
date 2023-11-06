#include <iostream>
using namespace std;
void displayMenu();
int add(int a, int b);
int sub(int a, int b);
int mul(int a, int b);
int divide(int a, int b);
int mod(int a, int b);
int main()
{
    displayMenu();
    int yourChoice;
    int a, b;
    char confirm;
    do
    {
        cout << "Enter your choice: ";
        cin >> yourChoice;
        cout << "Enter two integers: ";
        cin >> a >> b;
        cout << "\n";
        switch (yourChoice)
        {
        case 1:
            cout << "Result: " << add(a, b) << endl;
            break;
        case 2:
            cout << "Result: " << sub(a, b) << endl;
            break;
        case 3:
            cout << "Result: " << mul(a, b) << endl;
            break;
        case 4:
            cout << "Result: " << divide(a, b) << endl;
            break;
        case 5:
            cout << "Result: " << mod(a, b) << endl;
            break;
        default:
            cout << "Invalid choice!\n";
        }
        cout << "press y or Y to continue: ";
        cin >> confirm;


    } while (confirm == 'y' || confirm == 'Y');
    cout << "Bye!\n";
    return 0;
}

void displayMenu()
{
    cout << "1. Add\n";
    cout << "2. Subtract\n";
    cout << "3. Multiply\n";
    cout << "4. Divide\n";
    cout << "5. Modulus\n";
}

int add(int a, int b)
{
    return a + b;
}

int sub(int a, int b)
{
    return a - b;
}

int mul(int a, int b)
{
    return a * b;
}

int divide(int a, int b)
{
    return a / b;
}

int mod(int a, int b)
{
    return a % b;
}
