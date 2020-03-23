/**/
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include<cctype>
#include<cstring>
#include<cmath>
using namespace std;

struct Node
{
    int loc;
    int num;
    Node* next;
};

void overflowMulti(Node*& head1, Node*& head2, Node*& head3, int m, int n);
int getListValue(Node*& head, int pos);
void setValue(Node*& head, int pos, int val);
void incrementValue(Node*& head, int pos, int val);
void displayList(Node*& head);
void menu();
void input(string& num1, string& num2);
void cutString(string& num1, string& num2, Node*& head1, Node*& head2, int& nodeForNum1, int& nodeForNum2);
void addNode(Node*& head, int num, int pos);
int modifyNodeNums(int num);
void initializeResult(Node*& head, int totalNode);
void initializeResult(Node*& head1, Node*& head2, int totalNode);
void sequentialFlow(Node*& head, int val, int pos);
void sequentialUnder(Node*& head, int val, int pos);
int sequentialDivi(Node*& head1, Node*& head2, Node*& r, int m, int n, int val1, int val2, int val2Ceil);
void overflowAddition(Node*& head2, Node*& head3, int n);
void underflowSub(Node*& head2, Node*& head3, int n);
int divisionFor(Node*& head1, Node*& head2, Node*& head3, int n, int loc, int place);
bool numCompare(Node*& head1, Node*& head2, int m, int n);
int nodeNumAddition(int m, int n);
int nodeNumSub(int m, int n);
int nodeNumMulti(int m, int n);
void displayEveryDigit(Node*& head, int intsize);   //since subscript 0 with decimal point
void displayEveryDigit(Node*& head);                //since subscript 0 without decimal point
void displayList(Node*& head);                      //recursive, since subscript n
bool digit(string number);
void addition(Node*& head1, Node*& head2, Node*& head3, int m, int n, int totalNode);
void subtraction(Node*& head1, Node*& head2, Node*& head3, int m, int n, int totalNode);
void multiplication(Node*& head1, Node*& head2, Node*& head3, int m, int n, int totalNode);
int division(Node*& head1, Node*& head2, Node*& head3, int m, int n, int totalNode);
void stepNextNode(int& pos, int& place);
int getNextDigit(Node*& head, int pos, int sub);
bool compareValue(Node*& head1, Node*& head2, Node*& testHead1, Node*& testHead2, int m, int n, int lower, int upper);
int getNodeNum(Node*& head);
int getFirstTwoDigit(Node*& head, int m, int& ceiling);
int getFirstThreeDigit(Node*& head, int m, int num2);
Node* getFirstDiviNum(Node*& head1, Node*& head2, int m, int n, int& offsetNode, int& place);
Node* currentNode(Node*& head, int pos);
bool isfloor(Node*& head, int pos, int look);
bool isfloor(Node*& head, int pos);
int modifyLowerBound(int num, int secondary);
int countNodeDigit(Node*& head, int m);
Node* allocDecimalNode(int totalDec, int totalDecNode);
Node* newNodeInt(int place);
Node* cutNodes(Node*& head, int pos, int totalNode);
int numDigitNode(int num);
int nodeNumDivision(int m, int n);
int isNegative(Node*& head1, Node*& head2, int m, int n);
void negateNode(Node*& head, int m);
void clearTopZero(Node*& head);
int numberDigits(Node*& head);
int getUpmostDigit(int num);
int divisionCeiling(int num, int d);


int main() 
{
    Node* head1, * head2, * head3;
    Node* temp = nullptr;
    string num1, num2;
    int m, n, totalNode = 0, flag, size = 0;
    string choice;
    do 
    {
        menu();
        getline(cin, choice);
        while (!digit(choice))    //input validation
        {
            cout << "Entering a number from the list in order to continue\n";
            getline(cin, choice);
        }

        //if the choice is to exit, exit the program
        if (choice != "1" && choice != "2" && choice != "3" && choice != "4")
        {
            exit(EXIT_SUCCESS);
        }

        //else, continue the calculation
        head1 = nullptr, head2 = nullptr, head3 = nullptr;
        input(num1, num2);
        cutString(num1, num2, head1, head2, m, n);

        //pre-display the context
        temp = head1;
        cout << "The first number is: \t";
        displayList(temp);
        cout << endl;
        temp = head2;
        cout << "The second number is: \t";
        displayList(temp);
        cout << endl;
        flag = isNegative(head1, head2, m, n);
        switch (stoi(choice))
        {
        case 1: //+
            if (flag == 2)      //==> NUM1 + NUM2
            {
                addition(head1, head2, head3, m, n, totalNode);
            }
            else if (flag == 1) //==> NUM1 - NUM2
            {
                negateNode(head2, n);
                subtraction(head1, head2, head3, m, n, totalNode);
            }
            else if (flag == -1)//==> NUM2 - NUM1
            {
                negateNode(head1, m);
                subtraction(head2, head1, head3, n, m, totalNode);
            }
            else                //==> -(NUM1 + NUM2)
            {
                negateNode(head1, m);
                negateNode(head2, n);
                addition(head1, head2, head3, m, n, totalNode);
                cout << "-";
                //or
                //negateNode(head3, totalNode - 1);
            }
            //END ADDITION
            break;
        case 2: //-
            if (flag == 2)      //==> NUM1 - NUM2
            {
                subtraction(head1, head2, head3, m, n, totalNode);
            }
            else if (flag == 1) //==> NUM1 - (-NUM2)
            {
                negateNode(head2, n);
                addition(head1, head2, head3, m, n, totalNode);
            }
            else if (flag == -1)//==> -NUM1 - NUM2 == -(NUM1 + NUM2)
            {
                negateNode(head1, m);
                addition(head1, head2, head3, m, n, totalNode);
                cout << "-";
                //or
                //negateNode(head3, totalNode - 1);
            }
            else                //==> -NUM1 - (-NUM2) == NUM2 - NUM1
            {
                negateNode(head1, m);
                negateNode(head2, n);
                subtraction(head2, head1, head3, n, m, totalNode);
            }
            //END SUBTRACTION
            break;
        case 3: //*
            if (flag == 2)      //==> NUM1 * NUM2
            {
                multiplication(head1, head2, head3, m, n, totalNode);
            }
            else if (flag == 1) //==> - (NUM1 * NUM2)
            {
                negateNode(head2, n);
                multiplication(head1, head2, head3, m, n, totalNode);
                cout << "-";
                //or
                //negateNode(head3, totalNode - 1);
            }
            else if (flag == -1)//==> - (NUM1 * NUM2)
            {
                negateNode(head1, m);
                multiplication(head1, head2, head3, m, n, totalNode);
                cout << "-";
                //or
                //negateNode(head3, totalNode - 1);
            }
            else                //==> NUM1 * NUM2
            {
                negateNode(head1, m);
                negateNode(head2, n);
                multiplication(head1, head2, head3, m, n, totalNode);
            }
            //END MULTIPLICATION
            break;
        case 4: //division
            size = division(head1, head2, head3, m, n, totalNode);
            break;
        }

        if (choice != "4")
        {
            //display the result
            temp = head3;
            displayList(temp);
            cout << endl;

        }
        
    } while (choice >= "1" && choice <= "4");

    return 0;
}


int division(Node*& head1, Node*& head2, Node*& head3, int m, int n, int totalNode)
{
    int totalDec, totalDecNode = 0, integerSize = 0, pos = 0, place = 3;
    Node* aux10 = nullptr, * temp = nullptr, * aux = nullptr;
    cout << "Result in how many decimal places: ";
    cin >> totalDec;
    cin.ignore();
    ////////////////////////////////
    //need a validation
    ////////////////////////////////
    cout << "Performing division\n";
    //do normal division with result >= 1
    //augumented the number if the result contains decimals
    temp = head1;
    if (totalDec != 0)
    {
        temp = nullptr;
        if (totalDec % 3 == 0)
        {
            initializeResult(aux, totalDec / 3 + 1);
            setValue(aux, totalDec / 3, 1);
        }
        else if (totalDec % 3 == 1)
        {
            initializeResult(aux, totalDec / 3 + 1);
            setValue(aux, totalDec / 3, 10);
        }
        else
        {
            initializeResult(aux, totalDec / 3 + 1);
            setValue(aux, totalDec / 3, 100);
        }
        multiplication(head1, aux, temp, m, getNodeNum(aux), 0);
        clearTopZero(temp);
        //set the position
        pos = totalDec / 3;
        place = 3 - (totalDec % 3);
    }

    /////////////////////////////////////////////
    integerSize = divisionFor(temp, head2, head3, n, pos, place);
    /////////////////////////////////////////////

    cout << "The result is: \t\t";

    if (!numCompare(head1, head2, getNodeNum(head1), n))
    {
        cout << "0.";
        displayEveryDigit(head3);
        cout << endl;
    }
    else
    {
        displayEveryDigit(head3, integerSize);
        cout << endl;
    }

    return integerSize;
}


int divisionFor(Node*& head1, Node*& head2, Node*& head3, int n, int loc, int place)
{
    int i, k = 0, totalNode = 0;
    int ceiling = 0, a = 0;
    int sub, next, offset;
    bool flag = true;
    Node* r = nullptr;
    Node* aux10 = nullptr;
    addNode(aux10, 10, 0);
    Node* R = nullptr;

    Node* firstNum = getFirstDiviNum(head1, head2, getNodeNum(head1), n, offset, sub);
    clearTopZero(firstNum);
    offset = getNodeNum(head1) - offset - 1;
    if (offset == 0 && sub == 3)
        flag = false;
    int currNode = getNodeNum(firstNum);
    int first3List1 = getFirstThreeDigit(firstNum, currNode, numberDigits(head2));
    int first2List2 = getFirstTwoDigit(head2, n, ceiling);
    int digit = sequentialDivi(firstNum, head2, r, getNodeNum(firstNum), n, first3List1, first2List2, ceiling);
    if (digit != 0)
        a++;
    addNode(head3, digit, k);
    k++;
    multiplication(r, aux10, R, getNodeNum(r), 1, totalNode);
    stepNextNode(offset, sub);
    next = getNextDigit(head1, offset, sub);
    incrementValue(R, 0, next);
    clearTopZero(R);

    if (!flag)
        return 1;

    while (offset != 0 || sub != 3)
    {
        if (offset > loc || offset == loc && sub < place)
            a++;
        r = nullptr;
        if (numCompare(R, head2, getNodeNum(R), n))
        {
            //have enough number to be divided
            currNode = getNodeNum(R);
            first3List1 = getFirstThreeDigit(R, currNode, numberDigits(head2));
            digit = sequentialDivi(R, head2, r, getNodeNum(R), n, first3List1, first2List2, ceiling);
            addNode(head3, digit, k);
            k++;
            R = nullptr;
            stepNextNode(offset, sub);
            multiplication(r, aux10, R, getNodeNum(r), 1, totalNode);
            next = getNextDigit(head1, offset, sub);
            incrementValue(R, 0, next);
        }
        else
        {
            addNode(head3, 0, k);
            k++;
            stepNextNode(offset, sub);
            multiplication(R, aux10, r, getNodeNum(R), 1, totalNode);
            R = r;
            next = getNextDigit(head1, offset, sub);
            incrementValue(R, 0, next);
        }
        clearTopZero(R);
    }
    a++;

    if (numCompare(R, head2, getNodeNum(R), n))
    {
        //have enough number to be divided
        currNode = getNodeNum(R);
        first3List1 = getFirstThreeDigit(R, currNode, numberDigits(head2));
        digit = sequentialDivi(R, head2, r, getNodeNum(R), n, first3List1, first2List2, ceiling);
        addNode(head3, digit, k);
        k++;
        R = r;
        /*
        stepNextNode(offset, sub);
        multiplication(r, aux10, R, getNodeNum(r), 1, totalNode);
        next = getNextDigit(head1, offset, sub);
        incrementValue(R, 0, next);
        */
    }
    else
    {
        addNode(head3, 0, k);
        k++;
        /*
        stepNextNode(offset, sub);
        multiplication(R, aux10, r, getNodeNum(R), 1, totalNode);
        R = r;
        next = getNextDigit(head1, offset, sub);
        incrementValue(R, 0, next);
        */
    }
    clearTopZero(R);

    return a;
}


int divisionCeiling(int num, int d)
{
    double result = num / static_cast<double>(d);
    if (result != static_cast<double>(num / d))
    {
        return num / d + 1;
    }
    else
        return num / d;
}


void clearTopZero(Node*& head)
{
    Node* temp = currentNode(head, getNodeNum(head) - 1);
    while (temp != nullptr && temp->num == 0)
    {
        temp = currentNode(head, getNodeNum(head) - 2);
        if(temp != nullptr)
            temp->next = nullptr;
    }
}


int numberDigits(Node*& head)
{
    int firstNode;
    if (getListValue(head, getNodeNum(head) - 1) / 100 != 0)
    {
        firstNode = 3;
    }
    else if (getListValue(head, getNodeNum(head) - 1) / 10 != 0)
    {
        firstNode = 2;
    }
    else
    {
        firstNode = 1;
    }
    return firstNode + (getNodeNum(head) - 1) * 3;
}


void stepNextNode(int &pos, int& place)
{
    if (place >= 3)
    {
        pos--;
        place = 1;
    }
    else
    {
        place++;
    }
}

int getNextDigit(Node*& head, int pos, int sub)
{
    int i, num;
    num = getListValue(head, pos);
    for (i = 0; i < sub; i++)
    {
        num %= static_cast<int>(pow(10, 3 - i));
    }
    return num / static_cast<int>(pow(10, 3 - i));;
    
}


int sequentialDivi(Node*& head1, Node*& head2, Node*& r, int m , int n, int val1, int val2, int val2Ceil)
{
    Node* testHead1 = nullptr, * testHead2 = nullptr;
    int lower = val1 / val2Ceil;
    int upper = val1 / val2;
    if (lower != upper)
    {
        for (int i = lower; i < upper; i++)
        {
            if (!compareValue(head1, head2, testHead1, testHead2, m, n, i, i + 1))
            {
                subtraction(head1, testHead1, r, m, getNodeNum(testHead1), 0);
                return i;
            }
        }
        subtraction(head1, testHead2, r, m, getNodeNum(testHead2), 0);
        return upper;
    }
    else
    {
        compareValue(head1, head2, testHead1, testHead2, m, n, lower, upper);
        subtraction(head1, testHead1, r, m, getNodeNum(testHead1), 0);
        return lower;
    }
}


bool compareValue(Node*& head1, Node*& head2, Node*& testHead1, Node*& testHead2, int m, int n, int lower, int upper)
{
    Node* tempLow = nullptr, * tempUp = nullptr, * h = nullptr, * head = head1;
    testHead1 = testHead2 = nullptr;
    addNode(tempLow, lower, 0);
    addNode(tempUp, upper, 0);
    multiplication(head2, tempLow, testHead1, n, 1, 0);
    multiplication(head2, tempUp, testHead2, n, 1, 0);
    clearTopZero(testHead1);
    clearTopZero(testHead2);
    if (numCompare(head, testHead2, m, getNodeNum(testHead2)) && numCompare(head, testHead1, m, getNodeNum(testHead1)))
    {
        //subtraction(head1, testHead2, r, m, getNodeNum(testHead2), totalNodeR);
        return true;    //have the ceiling value;
    }
    else
    {
        //subtraction(head1, testHead1, r, m, getNodeNum(testHead1), totalNodeR);
        return false;   //the ceiling value exceeds NUM1, therefore have the floor value
    }
}




int getNodeNum(Node*& head)
{
    int i = 0;
    Node* ptr = head;
    while (ptr != nullptr)
    {
        ptr = ptr->next;
        i++;
    }
    return i;
}


int getFirstTwoDigit(Node*& head, int m, int &ceiling)
{
    int num;
    if (countNodeDigit(head, m) == 1)
    {
        ceiling = num = getListValue(head, m - 1) * 10 + getListValue(head, m - 2) / 100;
        if (!isfloor(head, m - 2, 100))
            ceiling++;
        return num;
    }
    else if (countNodeDigit(head, m) == 2)
    {
        ceiling = num = getListValue(head, m - 1);
        if (!isfloor(head, m - 2))
            ceiling++;
        return num;
    }
    else
    {
        ceiling = num = getListValue(head, m - 1) / 10;
        if (!isfloor(head, m - 2))
            ceiling++;
        return num;
    }
}


int getFirstThreeDigit(Node*& head, int m, int num2)
{
    int numDigits = numberDigits(head);
    if (numDigits > num2)
    {
        if (countNodeDigit(head, m) == 1)
        {
            return getListValue(head, m - 1) * 100 + getListValue(head, m - 2) / 10;
        }
        else if (countNodeDigit(head, m) == 2)
        {
            return getListValue(head, m - 1) * 10 + getListValue(head, m - 2) / 100;
        }
        else
        {
            return getListValue(head, m - 1);
        }
    }
    
    if (countNodeDigit(head, m) == 1)
    {
        //place = 1;
        //pos = m - 2;
        return getListValue(head, m - 1) * 10 + getListValue(head, m - 2) / 100;
    }
    else if (countNodeDigit(head, m) == 2)
    {
        //place = 3;
        //pos = m - 2;
        return getListValue(head, m - 1);
    }
    else
    {
        //place = 2;
        //pos = m - 1;
        return getListValue(head, m - 1) / 10;
    }
}


Node* currentNode(Node*& head, int pos)
{
    Node* ptr = head;
    while (ptr != nullptr && ptr->loc != pos)
    {
        ptr = ptr->next;
    }
    return ptr;
}


bool isfloor(Node*& head, int pos, int look)
{
    int i;
    if (getListValue(head, pos) % look != 0)
        return false;
    for (i = pos - 1; i >= 0; i--)
    {
        if (getListValue(head, i) != 0)
            return false;
    }
    return true;
}


bool isfloor(Node*& head, int pos)
{
    int i;
    for (i = pos; i >= 0; i--)
    {
        if (getListValue(head, i) != 0)
            return false;
    }
    return true;
}


int getUpmostDigit(int num)
{
    if (num >= 100)
        return num / 100;
    else if (num >= 10)
        return num / 10;
    else if (num >= 1)
        return num;
    else
        return 0;
}


Node* getFirstDiviNum(Node*& head1, Node*& head2, int m, int n, int &offsetNode, int &place)
{
    Node* temp = nullptr, * h = nullptr, * multi = nullptr, * lowNode = nullptr, * aux = nullptr;

    int pos;
    int list1NodeLow;
    int secondary = (n - 1) * 3 + countNodeDigit(head2, n) - countNodeDigit(head1, m);
    int list1High = getListValue(head1, m - 1);
    list1High = getUpmostDigit(list1High);
    int list2High = getListValue(head2, n - 1);
    list2High = getUpmostDigit(list2High);
    if (list1High < list2High)  //the part of list1 with the same length of list2 cannot divide list2
    {
        secondary++;    //move to the next digit on the right
    }

    offsetNode = secondary / 3;
    place = secondary % 3;
    if (place != 0)
    {
        offsetNode++;
        pos = m - 1 - offsetNode;
        list1NodeLow = getListValue(head1, pos);
        list1NodeLow = modifyLowerBound(list1NodeLow, secondary);
    }
    else
    {
        place = 3;
        pos = m - 1 - offsetNode;
        list1NodeLow = getListValue(head1, pos);
        list1NodeLow = modifyLowerBound(list1NodeLow, secondary);
    }
    aux = newNodeInt(place);
    addNode(lowNode, list1NodeLow, 0);
    h = cutNodes(head1, pos + 1, m);
    multiplication(h, aux, multi, getNodeNum(h), getNodeNum(aux), 0);
    addition(multi, lowNode, temp, getNodeNum(multi), getNodeNum(lowNode), 0);
    clearTopZero(temp);
    return temp;
}


Node* cutNodes(Node*& head, int pos, int totalNode)
{
    int i, j;
    Node* temp = nullptr;
    j = pos;
    for (i = 0; i < totalNode - pos && j < totalNode; i++, j++)
    {
        addNode(temp, getListValue(head, j), i);
    }
    return temp;
}


Node* newNodeInt(int place)
{
    Node* head = nullptr;
    if (place != 0)
        addNode(head, pow(10, place), 0);
    else
    {
        addNode(head, 0, 0);
        addNode(head, 1, 1);
    }
    return head;
}


int numDigitNode(int num)
{
    if (num / 100 != 0)
        return 3;
    else if (num / 10 != 0)
        return 2;
    else if (num / 1 != 0)
        return 1;
    else
        return 0;
}


int modifyLowerBound(int num, int secondary)
{
    if (secondary % 3 == 1)
    {
        return num / 100;
    }
    else if (secondary % 3 == 2)
    {
        return num / 10;
    }
    else
    {
        return num;
    }

}

int countNodeDigit(Node*& head, int m)
{
    if (getListValue(head, m - 1) < 10)
    {
        return 1;
    }
    else if (getListValue(head, m - 1) < 100)
    {
        return 2;
    }
    else
    {
        return 3;
    }
}



/*
This function allocates nodes for the decimal section and
set all the digits in the nodes to 0's
*/
Node* allocDecimalNode(int totalDec, int totalDecNode)
{
    totalDecNode = modifyNodeNums(totalDec);
    Node* head = nullptr;
    initializeResult(head, totalDecNode);
    return head;
}

int nodeNumDivision(int m, int n)
{
    if (m >= n) //the result has at least 1 digit or 0 (sometimes)
    {
        return m - n + 1;
    }
    else
    {
        return 0;   //the result is fully decimal (e.g. 0.xxx)
    }
}

int isNegative(Node*& head1, Node*& head2, int m, int n)
{
    if (getListValue(head1, m - 1) > 0 && getListValue(head2, n - 1) > 0)
    {
        return 2;   //2 numbers are all positive
    }
    else if (getListValue(head1, m - 1) > 0 && getListValue(head2, n - 1) < 0)
    {
        return 1;   //the first number is positive and the other is negative
    }
    else if (getListValue(head1, m - 1) < 0 && getListValue(head2, n - 1) > 0)
    {
        return -1;  //the second number is positive and the other is negative
    }
    else
    {
        return -2;  //2 numbers are all negative
    }
}


/*
This function negates the upmost 3 digits to either positive or negative
*/
void negateNode(Node*& head, int m)
{
    setValue(head, m - 1, -getListValue(head, m - 1));
}


void addition(Node*& head1, Node*& head2, Node*& head3, int m, int n, int totalNode)
{
    cout << "Performing addition\n";
    cout << "The result is: \t\t";
    totalNode = nodeNumAddition(m, n);
    initializeResult(head1, head3, totalNode);
    overflowAddition(head2, head3, n);

}

void subtraction(Node*& head1, Node*& head2, Node*& head3, int m, int n, int totalNode)
{
    cout << "Performing subtraction\n";
    cout << "The result is: \t\t";
    totalNode = nodeNumSub(m, n);
    if (!numCompare(head1, head2, m, n))
    {
        //a - b < 0, swap 2 numbers
        initializeResult(head2, head3, totalNode);
        underflowSub(head1, head3, m);
        cout << "-";
    }
    else
    {
        //a - b >= 0, do normal calculation
        initializeResult(head1, head3, totalNode);
        underflowSub(head2, head3, n);
    }

}

void multiplication(Node*& head1, Node*& head2, Node*& head3, int m, int n, int totalNode)
{
    cout << "Performing multiplication\n";
    cout << "The result is: \t\t";
    totalNode = nodeNumMulti(m, n);
    initializeResult(head3, totalNode); //initialize all digits to 0's
    overflowMulti(head1, head2, head3, m, n);

}



bool digit(string number)
{
    if (number == "")
        return false;
    if (number.length() != 1)
        return false;
    if (!isdigit(number[0]))
        return false;
    return true;
}


void overflowMulti(Node*& head1, Node*& head2, Node*& head3, int m, int n)
{
    int i, j, val;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            val = getListValue(head1, i) * getListValue(head2, j);
            sequentialFlow(head3, val, i + j);

        }
    }
}


void incrementValue(Node*& head, int pos, int val)
{
    Node* ptr = head;
    while (ptr != nullptr && ptr->loc != pos)
    {
        ptr = ptr->next;
    }
    ptr->num += val;
}


void menu() {
    cout << "Select from menu" << endl
        << "1. addition" << endl
        << "2. subtruction" << endl
        << "3. multiplication" << endl
        << "4. division " << endl;
    cout << "Or enter any other key to exit\n";

}


//new functions, re-arrange the functions
//subtraction
void input(string& num1, string& num2) {
    cout << "Enter two overflowed number\n";
    getline(cin, num1);
    getline(cin, num2);

}


int modifyNodeNums(int num)
{
    if (num % 3 == 0)
    {
        return num / 3;
    }
    else
    {
        return num / 3 + 1;
    }
}


void addNode(Node*& head, int num, int pos)
{
    Node* A = new Node, * ptr = head;
    A->num = num;
    A->loc = pos;
    A->next = nullptr;
    ptr = head;
    if (head == nullptr)
    {
        head = A;
        return;
    }
    else
    {
        while (ptr->next != nullptr) {
            ptr = ptr->next;
        }
        ptr->next = A;
    }
}


void cutString(string& num1, string& num2, Node*& head1, Node*& head2, int& nodeForNum1, int& nodeForNum2) {
    int length1 = static_cast<int>(num1.length());
    int length2 = static_cast<int>(num2.length());

    if(num1[0] == '-')
        nodeForNum1 = modifyNodeNums(length1 - 1);
    else
        nodeForNum1 = modifyNodeNums(length1);
    if (num2[0] == '-')
        nodeForNum2 = modifyNodeNums(length2 - 1);
    else
        nodeForNum2 = modifyNodeNums(length2);

    cout << "The first number is splited into " << nodeForNum1 << " nodes" << endl;
    cout << "The second number is splited into " << nodeForNum2 << " nodes" << endl;

    Node* ptr = head1;
    int i, j = 0;
    if (length1 <= 4 && num1[0] == '-')
    {
        addNode(head1, stoi(num1.substr(0, length1)), 0);
    }
    else
    {
        for (i = length1 - 3; i >= 0; i = i - 3) {
            //cout << num1.substr(i, 3) << endl;
            addNode(head1, stoi(num1.substr(i, 3)), j);
            j++;
            if ((i == 4 && num1[0] == '-') || i < 3)
                break;
        }
        if (i != 0)
            addNode(head1, stoi(num1.substr(0, i)), j);
    }

    ptr = head2;
    j = 0;
    if (length2 <= 4 && num2[0] == '-')
    {
        addNode(head2, stoi(num2.substr(0, length2)), 0);
    }
    else
    {
        for (i = length2 - 3; i >= 0; i = i - 3) {
            //cout << num1.substr(i, 3) << endl;
            addNode(head2, stoi(num2.substr(i, 3)), j);
            j++;
            if ((i == 4 && num2[0] == '-') || i < 3)
                break;
        }
        if (i != 0)
            addNode(head2, stoi(num2.substr(0, i)), j);
    }


}


//initalize the result linked list with 0's
void initializeResult(Node*& head, int totalNode)
{
    int i;
    for (i = 0; i < totalNode; i++)
    {
        addNode(head, 0, i);
    }
}


//initialize the result linked list with the first list's content
void initializeResult(Node*& head1, Node*& head3, int totalNode)
{
    Node* ptr1 = head1;
    initializeResult(head3, totalNode);
    Node* ptr2 = head3;
    while (ptr1 != nullptr)
    {
        ptr2->num = ptr1->num;
        ptr2->loc = ptr1->loc;
        ptr2 = ptr2->next;
        ptr1 = ptr1->next;
    }
}


int getListValue(Node*& head, int pos)
{
    Node* ptr = head;
    while (ptr != nullptr && ptr->loc != pos)
    {
        ptr = ptr->next;
    }
    if (!ptr)
        return -1;
    return ptr->num;
}


void setValue(Node*& head, int pos, int val)
{
    Node* ptr = head;
    while (ptr != nullptr && ptr->loc != pos)
    {
        ptr = ptr->next;
    }
    ptr->num = val;
}


void sequentialFlow(Node*& head, int val, int pos)
{
    //in case of carrying
    int sum = getListValue(head, pos) + val;
    if (sum > 999)
    {
        sequentialFlow(head, sum / 1000, pos + 1);
        setValue(head, pos, sum % 1000);
    }
    //if the addition does not exceed 3-digit size (<1000)
    else
    {
        setValue(head, pos, sum);
    }
}


void sequentialUnder(Node*& head, int val, int pos)
{
    int sub = getListValue(head, pos) - val;
    //in case of borrowing
    if (sub < 0)
    {
        sequentialUnder(head, 1, pos + 1);
        setValue(head, pos, 1000 + sub);
    }
    else
    {
        setValue(head, pos, sub);
    }
}


void overflowAddition(Node*& head2, Node*& head3, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        sequentialFlow(head3, getListValue(head2, i), i);
    }
}


void underflowSub(Node*& head2, Node*& head3, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        sequentialUnder(head3, getListValue(head2, i), i);
    }
}


bool numCompare(Node*& head1, Node*& head2, int m, int n)
{
    if (m > n)
    {
        return true;
    }
    else if (m < n)
    {
        return false;
    }
    else
    {
        //if they are equal
        int i;
        //check every node(3 digits)
        for (i = m - 1; i >= 0; i--)
        {
            if (getListValue(head1, i) > getListValue(head2, i))
            {
                return true;
            }
            else if(getListValue(head1, i) < getListValue(head2, i))
            {
                return false;
            }
        }
        return true;
    }
}


int nodeNumAddition(int m, int n)
{
    if (m > n)
    {
        return m + 1;
    }
    else
    {
        return n + 1;
    }
}


int nodeNumSub(int m, int n)
{
    if (m > n)
    {
        return m;
    }
    else
    {
        return n;
    }

}


int nodeNumMulti(int m, int n)
{
    return m + n;
}


void displayEveryDigit(Node*& head, int intsize)
{
    Node* ptr = head;
    int i = 0;
    while (ptr != nullptr)
    {
        if (i == intsize)
            cout << ".";
        cout << ptr->num;
        ptr = ptr->next;
        i++;
    }
}

void displayEveryDigit(Node*& head)
{
    Node* ptr = head;
    while (ptr != nullptr)
    {
        cout << ptr->num;
        ptr = ptr->next;
    }
}



void displayList(Node*& head)
{
    if (head->next != nullptr)
    {
        displayList(head->next);
        if (head->num >= 0 && head->num < 10)
            cout << "00" << head->num;
        else if (head->num > 10 && head->num < 100)
            cout << "0" << head->num;
        else
            cout << head->num;
    }
    else
    {
        if (head->num != 0)
            cout << head->num;
    }
}

