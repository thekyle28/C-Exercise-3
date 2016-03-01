#include <string>
#include <iostream>

using namespace std;

#include "evalobj.h"

int main(int argc, const char *argv[])
{
    ExpList *l = nullptr;
    l = new ExpList(new Constant(23), l);
    l = new ExpList(new Constant(42), l);
    l = new ExpList(new Constant(666), l);
    
    Exp *e1 = new Constant(1);
    Exp *e = new OpApp(plusop, l);
    cout << e->eval(nullptr) << endl;
}
