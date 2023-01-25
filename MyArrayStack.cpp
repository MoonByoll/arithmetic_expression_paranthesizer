#include "MyArrayStack.h"
#include <iostream>
/////////// Setareh Tavakoli 39913161032
using namespace std;

MyArrayStack::MyArrayStack(int size) {
    this->size = size;
    this->arr = new string[this->size];
    for (int i = 0; i < size; i++) {
        arr[i] = "0";
    }
    stackTop = -1;
}

bool MyArrayStack::stackIsFull() {
    if (this->stackTop == this->size - 1) return true;
    else return false;
}

bool MyArrayStack::stackIsEmpty() {
    if (this->stackTop == (-1)) return true;
    else return false;
}

void MyArrayStack::push(string operators) {
    if (stackIsFull()) {
        cout << "The Stack is Full" << "\n";
    } else {
        this->stackTop++;
        this->arr[this->stackTop] = operators;
    }
}

string MyArrayStack::pop() {
    if (stackIsEmpty()) {
        cout << "The Stack is Empty" << "\n";
        return NULL;
    } else {
        string k = this->arr[this->stackTop];
        this->arr[this->stackTop] = "0";
        this->stackTop--;
        return k;
    }
}

string MyArrayStack::topOperator() {
    if (stackIsEmpty()) {
        cout << " Nothing to show " << "\n";
        return NULL;
    } else {
        return this->arr[this->stackTop];
    }
}

void MyArrayStack::show() {
    for (int i = size - 1; i >= 0; i--) {
        cout << arr[i] << "\n";
    }
}
