#include <iostream>
/////////// Setareh Tavakoli 39913161032

using namespace std;

void controller();

void storeNumberInArray(string infix);

bool checkIfOperator(string ifOperator);

int priority(string op);

string infixToPostfix();

string postfixToInfix();

//global variables inorder to be able to use in multiple functions
string numberStorage[100];
string postfixArr[100];
int opFlag = 0;

void controller() {
    string infixExp, postfixExp;

    cout << "Enter the arithmetic (INFIX) expression :  " << "\n";
    getline(cin, infixExp);

    //call for the parser function
    storeNumberInArray(infixExp);
    infixToPostfix();
    cout << "Infix form Postfix :" << "   " << postfixToInfix() << "\n";
}

//parsing function
void storeNumberInArray(string infix) {

    //an index for global arr to traverse the infix exp from
    //left to right and parse it getting help from tempStore
    int storeNumberindex = 0;
    string tempStore;

    //traverse from left to right
    for (int i = 0; i < infix.length(); i++) {

        //clean tempStore everytime
        //change the type of char to string using append function
        tempStore.clear();
        string temp;
        temp.append(1, infix[i]);

        //if the element was operator or parenthesis
        if (temp == "(" || temp == ")" || temp == "+" || temp == "-"
            || temp == "*" || temp == "/" || temp == "%" || temp == "^") {

            //looks for the unary - operator in three situations
            if ((checkIfOperator(numberStorage[storeNumberindex - 1]) && checkIfOperator(temp) && temp == "-") ||
                (temp == "-" && i == 0) || (numberStorage[storeNumberindex - 1] == "(" && temp == "-")) {
                opFlag = 1;
                continue;
            } else {
                numberStorage[storeNumberindex] = temp;
                storeNumberindex++;
                continue;
            }
        }

            //if the element is an alphabet, next home is probably a trigonometric or log function
        else if ((infix[i] >= 'a' && infix[i] <= 'z') || (infix[i] >= 'A' && infix[i] <= 'Z')) {

            //the first element is already pre-checked in the condition
            tempStore += temp;

            int j = 1;
            while ((infix[i + j] >= 'a' && infix[i + j] <= 'z') || (infix[i + j] >= 'A' && infix[i + j] <= 'Z')) {
                tempStore += infix[i + j];
                j++;
            }

            //checks if the unary - is behind trigonometric functions if so store the - int array
            if (infix[i - 1] == '-') {
                numberStorage[storeNumberindex] = "-";
                i += (numberStorage[storeNumberindex].length() - 1);
                storeNumberindex++;
                opFlag = 5;
            }
            numberStorage[storeNumberindex] = tempStore;
            i += (numberStorage[storeNumberindex].length() - 1);
            storeNumberindex++;
        }

            //if the element is a number
        else if (infix[i] >= '0' && infix[i] <= '9' || infix[i] == '.') {

            //if the flag is 1 we probably have a unary - >>>line59
            if (opFlag == 1) {
                tempStore += "(";
                tempStore += "-";
                opFlag = 3;
            }
            tempStore += temp;

            int j = 1;
            while (infix[i + j] >= '0' && infix[i + j] <= '9' || infix[i + j] == '.') {
                tempStore += infix[i + j];
                j++;
            }

            //if the flag is 3 we had a unary - behind number, so we have to end it with ")" >> line 97
            if (opFlag == 3) {
                tempStore += ")";
                numberStorage[storeNumberindex] = tempStore;
                i += (numberStorage[storeNumberindex].length() - 4);
                storeNumberindex++;
                opFlag = 0;
            } else {
                numberStorage[storeNumberindex] = tempStore;
                i += (numberStorage[storeNumberindex].length() - 1);
                storeNumberindex++;
            }
        }
    }
}

bool checkIfOperator(string op) {

    if (op == "sec" || op == "csc" || op == "cos" || op == "sin" || op == "tan" || op == "cot"
        || op == "log" || op == "+" || op == "-" || op == "*"
        || op == "/" || op == "%" || op == "^") {
        return true;
    } else {
        return false;
    }
}

int priority(string op) {

    if (opFlag == 6 && op == "-") {
        opFlag = 8;
        return 5;
    } else if (op == "-") {
        return 1;
    }
    if (op == "cos" || op == "sin" || op == "tan" || op == "cot" || op == "log" || op == "sec" || op == "csc") return 4;
    if (op == "^") return 3;
    if (op == "*" || op == "/" || op == "%") return 2;
    if (op == "+") return 1;
    if (op == "(" || op == ")") return 0;
    else return -1;
}

//takes the global arr that was used in parser function
// and stores the postfix in another global arr
string infixToPostfix() {

    int index = 0;

    //makes a new stack object to use for infix to postfix
    MyArrayStack *myStack = new MyArrayStack(100);

    //traverse the global array
    for (int i = 0; i < 100; i++) {

        string temp;
        temp = numberStorage[i];

        //if the elements in array are finished come out of the loop
        if (temp == "") { break; }

        if (temp == " ") {
            continue;

            //rule of parenthesis
        } else if (temp == "(") {
            myStack->push(temp);

        } else if (temp == ")") {

            while ((myStack->topOperator() != "(") && (!myStack->stackIsEmpty())) {

                postfixArr[index] = myStack->topOperator();
                index++;
                myStack->pop();

            }
            if (myStack->topOperator() == "(") {
                myStack->pop();
            }
        }

            //rule of operators
        else if (checkIfOperator(temp)) {

            //checks if a unary - is before trigonometric functions
            if (priority(numberStorage[i + 1]) == 4 && numberStorage[i] == "-") {

                //if the flag is 6, the priority of - changes to the unary and to the most
                opFlag = 6;
            }

            //rule number one when facing an operator with an empty stack
            if (myStack->stackIsEmpty()) {
                myStack->push(temp);
            }

                //if first rule was false now check the second rule >> The Priority <<
            else {

                if (priority(temp) > priority(myStack->topOperator())) {
                    myStack->push(temp);

                }

                    //check for two or more ^
                else if (priority(temp) == priority(myStack->topOperator()) && (temp == "^")) {
                    myStack->push(temp);

                } else {
                    //when this conditions happen we face different situations
                    while ((!myStack->stackIsEmpty()) && priority(temp) <= priority(myStack->topOperator())) {

                        //1) we faced a unary -
                        if (priority(myStack->topOperator()) == 6) {
                            myStack->push(temp);
                        }

                        //2) trigonometric have the less priority than unary -
                        if (priority(myStack->topOperator()) == 4 && temp == "-") {
                            postfixArr[index] = myStack->topOperator();
                            index++;
                            myStack->pop();
                        }
                        postfixArr[index] = myStack->topOperator();
                        index++;
                        myStack->pop();

                        //3) / * % ^ have the less priority than unary -
                        if ((priority(temp) == 2 || priority(temp) == 3) && priority(postfixArr[index - 1]) == 4) {
                            opFlag = 6;
                        }
                    }
                    myStack->push(temp);
                }
            }
        } else {
            postfixArr[index] = temp;
            index++;
        }
    }
    //the last rule and step
    while (!myStack->stackIsEmpty()) {
        postfixArr[index] = myStack->topOperator();
        index++;
        myStack->pop();
    }
}


string postfixToInfix() {

    string infix;
    MyArrayStack *myStack2 = new MyArrayStack(100);

    for (int i = 0; i < 100; i++) {

        string temp;
        temp = postfixArr[i];

        if (temp == "") { break; }

        //in the postfix expression checks if it is an operator or not
        if (checkIfOperator(temp)) {

            //if my operator is trigonometric
            if (priority(temp) == 4) {
                string copy1 = myStack2->topOperator();
                myStack2->pop();
                myStack2->push("(" + temp + "(" + copy1 + ")" + ")");

            }

                //if my operator is unary - and behind the trigonometric function in the infix mode,
                // in postfix they are near each other >> E.g 45sin- <<
            else if (priority(postfixArr[i - 1]) == 4 && temp == "-") {
                string copy1 = myStack2->topOperator();
                myStack2->pop();
                myStack2->push("(" + temp + copy1 + ")");

            }

                //if non, check the regular rule of conversion of postfix to infix using stack
            else {
                string copy1 = myStack2->topOperator();
                myStack2->pop();
                string copy2 = myStack2->topOperator();
                myStack2->pop();
                myStack2->push("(" + copy2 + temp + copy1 + ")");
            }
        } else {
            myStack2->push(postfixArr[i]);
        }
    }
    return myStack2->topOperator();
}