#include <iostream>
#include <memory>
using namespace std;
int main()
{
    double *p = new double(5);
    shared_ptr<double> p_reg(p);
    
    // shared_ptr<double> p_reg = make_shared<double>(5);
    shared_ptr<double> pd = p_reg;
    // pd = p_reg; // wrong
    // pd.reset(p_reg);

    cout << "*pd = " << *pd << endl;
    // shared_ptr<double> pshared = p_reg; // wrong
    shared_ptr<double> pshared(p_reg);

    cout << "*pshred = " << *pshared << endl;

    // string str("Hello World!");
    // cout << &str << endl;
    // shared_ptr<string> pstr(&str)
    shared_ptr<string> pstr(new string("Hello World!"));
    // shared_ptr<string> pstr = make_shared<string>("Hello World!");
    cout << "*pstr = " << *pstr << endl;
    return 0;
}