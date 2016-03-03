


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

    Exp *e = new OpApp(plusop, l);
    Exp *e1 = new OpApp(plusop, l);
    Exp *e2 = new OpApp(plusop, l);
    Exp *e3 = new OpApp(plusop, l);
    Exp *e4 = new OpApp(plusop, l);
    Exp *e5 = new OpApp(plusop, l);
    Exp *e6 = new OpApp(plusop, l);
    Exp *e7 = new OpApp(plusop, l);
    cout << "Should print 731: ";
    cout << e->eval(nullptr) << endl; // 731

    l = nullptr;
    l = new ExpList(new Constant(2), l);
    l = new ExpList(new Constant(3), l);
    l = new ExpList(new Constant(5), l);

    e = new OpApp(plusop, l);

    ExpList *l2 = nullptr;
    l2 = new ExpList(new Var("x"), l2);
    l2 = new ExpList(new Var("x"), l2);
    l2 = new ExpList(new Constant(2), l2);

    Exp *xLet = new OpApp(timesop, l2);

    Exp *xVal = new Let("x", e, xLet);
    cout << "Should print 200: ";
    cout << xVal->eval(nullptr) << endl; // 200

    l = nullptr;
    l = new ExpList(new Constant(5), l);
    l = new ExpList(new Constant(3), l);
    l = new ExpList(new Constant(2), l);
    e = new OpApp(plusop, l);

    l = nullptr;
    l = new ExpList(new Var("x"), l);
    l = new ExpList(new Var("x"), l);
    l = new ExpList(new Var("x"), l);
    e2 = new OpApp(timesop, l);

    e1 = new Let("x", e, e2);

    cout << "Should print 1000: ";
    cout << e1->eval(nullptr) << endl; // should print  1000

    // (= x (+ 2 3 5) (* x x (+ x x))) = 2000

    e1 = nullptr;
    e2 = nullptr;

    l = nullptr;
    l = new ExpList(new Constant(2), l);
    l = new ExpList(new Constant(3), l);
    l = new ExpList(new Constant(5), l);
    e1 = new OpApp(plusop, l);

    l = nullptr;
    l = new ExpList(new Var("x"), l);
    l = new ExpList(new Var("x"), l);
    e2 = new OpApp(plusop, l);
    l = nullptr;
    l = new ExpList(e2, l);
    l = new ExpList(new Var("x"), l);
    l = new ExpList(new Var("x"), l);
    e3 = new OpApp(timesop, l);

    e4 = new Let("x", e1, e3);

    cout << "Should print 2000: ";
    cout << e4->eval(nullptr) << endl;

    // (= y 2 (+ y (= y 10 y) y)) = 14

    e1 = nullptr;
    e2 = nullptr;
    e3 = nullptr;
    e4 = nullptr;

    l = nullptr;
    l = new ExpList(new Var("y"), l);
    l = new ExpList(new Let("y", new Constant(10), new Var("y")), l);
    l = new ExpList(new Var("y"), l);
    e2 = new OpApp(plusop, l);

    e1 = new Let("y", new Constant(2), e2);

    cout << "Should print 14: ";
    cout << e1->eval(nullptr) << endl;

    // (= Z (40) (= Y (5) (= X (+ 2 3 5) (* z x y))))

    e1 = nullptr;
    e2 = nullptr;
    e3 = nullptr;
    e4 = nullptr;
    e5 = nullptr;

    l = nullptr;
    l = new ExpList(new Constant(5), l);
    l = new ExpList(new Constant(3), l);
    l = new ExpList(new Constant(2), l);
    e1 = new OpApp(plusop, l);

    l = nullptr;
    l = new ExpList(new Var("y"), l);
    l = new ExpList(new Var("x"), l);
    l = new ExpList(new Var("z"), l);
    e2 = new OpApp(timesop, l);

    e3 = new Let("x", e1, e2);
    e4 = new Let("y", new Constant(5), e3);
    e5 = new Let("z", new Constant(40), e4);
    cout << "Should print 2000: ";
    cout << e5->eval(nullptr) << endl; // should print 2000

    // (= x (1) (= y (x) (+ y))

    e1 = nullptr;
    e2 = nullptr;
    e3 = nullptr;

    l = nullptr;
    l = new ExpList(new Var("y"), l);
    e1 = new OpApp(plusop, l);
    e2 = new Let("y", new Var("x"), e1);
    e3 = new Let("x", new Constant(1), e2);

    cout << "Should print 1: ";
    cout << e3->eval(nullptr) << endl;

    // let x = (let x = 2 in x + 3) in x + (let x = 4 + x in x + 9) + x
    e = nullptr;
    e1 = nullptr;
    e2 = nullptr;
    e3 = nullptr;
    e4 = nullptr;
    e5 = nullptr;
    e6 = nullptr;
    e7 = nullptr;

    l = nullptr;
    l = new ExpList(new Constant(4), l);
    l = new ExpList(new Var("x"), l);
    e6 = new OpApp(plusop, l); // 4 + x
    l = nullptr;
    l = new ExpList(new Var("x"), l);
    l = new ExpList(new Constant(9), l);
    e5 = new OpApp(plusop, l); // x + 9
    e4 = new Let("x", e6, e5); // let x = 4 + x in x + 9

    l = nullptr;
    l = new ExpList(new Var("x"), l);
    l = new ExpList(e4, l);
    l = new ExpList(new Var("x"), l);
    e3 = new OpApp(plusop, l); // x + (let x = 4 + x in x + 9) + x

    l = nullptr;
    l = new ExpList(new Constant(3), l);
    l = new ExpList(new Var("x"), l);
    e2 = new OpApp(plusop, l); // x + 3
    e7 = new Let("x", new Constant(2), e2); // let x = 2 in x + 3

    e1 = new Let("x", e7, e3); // let x = (let x = 2 in x + 3) in x + (let x = 4 + x in x + 9) + x
    cout << "Should print 28: ";
    cout << e1->eval(nullptr) << endl;

    getchar();
}
