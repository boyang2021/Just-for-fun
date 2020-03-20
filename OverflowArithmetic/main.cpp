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
            cout << "Performing division\n";
            cout << "The result is: \t\t";
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

