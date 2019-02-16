#include "../name/first.hpp"
#include "../name/last.hpp"
#include "../name/name.hpp"
#include "../hellothere/hello.hpp"
#include "../hellothere/there.hpp"
#include "../hellothere/hellothere.hpp"
#include <iostream>

using namespace std;

int main()
{
    First *first = new First("kashish");
    Last *last = new Last("khullar");
    Name *name = new Name(*first, *last);
    Hello *hello = new Hello();
    There *there = new There();
    Hellothere *hellothere = new Hellothere(*hello, *there);

    cout << hellothere->hellothere << " "
         << name->name << endl;
    ;
}