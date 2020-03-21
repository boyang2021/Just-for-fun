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
void overflowAddition(Node*& head2, Node*& head3, int n);
void underflowSub(Node*& head2, Node*& head3, int n);
bool numCompare(Node*& head1, Node*& head2, int m, int n);
int nodeNumAddition(int m, int n);
int nodeNumSub(int m, int n);
int nodeNumMulti(int m, int n);
void displayList(Node*& head);
bool digit(string number);
void addition(Node*& head1, Node*& head2, Node*& head3, int m, int n, int totalNode);
void subtraction(Node*& head1, Node*& head2, Node*& head3, int m, int n, int totalNode);
void multiplication(Node*& head1, Node*& head2, Node*& head3, int m, int n, int totalNode);
int isNegative(Node*& head1, Node*& head2, int m, int n);
void negateNode(Node*& head, int m);


int main() 
{
    Node* head1, * head2, * head3;
    Node* temp = nullptr;
    string num1, num2;
    int m, n, totalNode = 0, flag;
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


            //need implementation
            break;
        }

        //display the result
        temp = head3;
        displayList(temp);
        cout << endl;

    } while (choice >= "1" && choice <= "4");

    return 0;
}


void division(Node*& head1, Node*& head2, Node*& head3, int m, int n, int totalNode)
{
    int totalDec, totalDecNode = 0;
    cout << "Result in how many decimal places: ";
    cin >> totalDec;
    cin.ignore();
    ////////////////////////////////
    //need a validation
    ////////////////////////////////
    //allocate memory
    Node* headDec = allocDecimalNode(totalDec, totalDecNode);
    cout << "Performing division\n";
    cout << "The result is: \t\t";
    if (numCompare(head1, head2, m, n))
    {
        //num1 >= num2
        totalNode = nodeNumDivision(m, n);
        //initializeResult(head3, totalNode);
    }
    else
    {
        //num1 < num2 ==> 0.xxx
        totalNode = 0;
    }

    if (totalNode != 0)
    {
        //do normal division with result >= 1
        /////////////////////////////////////////////

        /////////////////////////////////////////////

    }

    if (totalDecNode != 0)
    {
        //do decimal calculation
        /////////////////////////////////////////////

        /////////////////////////////////////////////
    }
    

    

}


void divisionFor(Node*& head1, Node*& head2, Node*& head3, int m, int n, int val, int pos)
{
    int ceiling = 0;
    Node* firstNum = getFirstDiviNum(head1, head2, m, n);
    int currNode = getNodeNum(firstNum);
    int first3List1 = getFirstThreeDigit(firstNum, currNode);
    int first2List2 = getFirstTwoDigit(head2, n, ceiling);
    int digit = sequentialDivi(head1, head2, m, n, first3List1, first2List2, ceiling);
    addNode(head3, digit, 0);

}


int sequentialDivi(Node*& head1, Node*& head2, int m , int n, int val1, int val2, int val2Ceil)
{
    int lower = val1 / val2Ceil;
    int upper = val1 / val2;
    if (lower != upper)
    {
        if (compareValue(head1, head2, m, n, lower, upper))
            return upper;
        else
            return lower;
    }
    else
    {
        return lower;
    }
}


bool compareValue(Node*& head1, Node*& head2, int m, int n, int lower, int upper)
{
    Node* tempLow = nullptr, * tempUp = nullptr, * testHead1 = nullptr, * testHead2 = nullptr;
    int totalNode1 = 0, totalNode2 = 0;
    addNode(tempLow, lower, 0);
    addNode(tempUp, upper, 0);
    multiplication(head2, tempLow, testHead1, n, 1, totalNode1);
    multiplication(head2, tempUp, testHead2, n, 1, totalNode2);

    if (numCompare(head1, testHead2, m, getNodeNum(testHead2)) && numCompare(head1, testHead1, m, getNodeNum(testHead1)))
    {
        return true;    //have the ceiling value;
    }
    else
    {
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


int getFirstThreeDigit(Node*& head, int m)
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


Node* getFirstDiviNum(Node*& head1, Node*& head2, int m, int n)
{
    Node* temp = nullptr;
    int i, j = 1;
    int list1NodeLow, offsetNode;
    int secondary = (n - 1) * 3 + countNodeDigit(head2, n) - countNodeDigit(head1, m);
    int list1High = getListValue(head1, m - 1);
    int list2High = getListValue(head2, n - 1);
    if (list1High < list2High)  //the part of list1 with the same length of list2 cannot divide list2
    {
        secondary++;    //move to the next digit on the right
    }

    offsetNode = secondary / 3;
    if (secondary % 3 != 0)
    {
        offsetNode++;
        list1NodeLow = getListValue(head1, m - 1 - offsetNode);
        list1NodeLow = modifyLowerBound(list1NodeLow, secondary);
    }
    else
    {
        list1NodeLow = getListValue(head1, m - 1 - offsetNode);
    }

    //add the lowest node to the list
    addNode(temp, list1NodeLow, 0);
    //add the rest of the nodes
    for (i = m - offsetNode; i < m; i++)
    {
        addNode(temp, getListValue(head1, i), j);
        j++;
    }
    return temp;
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
    if (length1 <= 4)
    {
        addNode(head1, stoi(num1.substr(0, length1)), 0);
    }
    else
    {
        for (i = length1 - 3; i >= 0; i = i - 3) {
            //cout << num1.substr(i, 3) << endl;
            addNode(head1, stoi(num1.substr(i, 3)), j);
            j++;
            if (i == 4 && num1[0] == '-' || i < 3)
                break;
        }
        if (i != 0)
            addNode(head1, stoi(num1.substr(0, i)), j);
    }

    ptr = head2;
    j = 0;
    if (length2 <= 4)
    {
        addNode(head2, stoi(num2.substr(0, length2)), 0);
    }
    else
    {
        for (i = length2 - 3; i >= 0; i = i - 3) {
            //cout << num1.substr(i, 3) << endl;
            addNode(head2, stoi(num2.substr(i, 3)), j);
            j++;
            if (i == 4 && num2[0] == '-' || i < 3)
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

