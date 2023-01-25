#include <iostream>
/////////// Setareh Tavakoli 39913161032
using namespace std;

// Define of the stack class and it's methods
class MyArrayStack {
private:
    int stackTop;
    string *arr;
    int size;

public:
    MyArrayStack(int size);

    //checks if stack is Full
    bool stackIsFull();

    //checks if stack is Empty
    bool stackIsEmpty();
    void push(string operators);
    string pop();
    string topOperator();

    //methode to show the elements in the stack which are stored in arr of String pointer
    void show();
};