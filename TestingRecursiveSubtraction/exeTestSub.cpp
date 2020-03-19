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

void input(string& num1, string& num2) {
    //fstream readfile;
    //string filename;
    cout << "Enter two overflowed number\n" << endl;
    //getline(cin, filename);
    //readfile.open(filename, ios::in | ios::binary);
    getline(cin, num1);
    //readfile.ignore();
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

    nodeForNum1 = modifyNodeNums(length1);
    nodeForNum2 = modifyNodeNums(length2);
    cout << "The first number is splited into " << nodeForNum1 << " nodes" << endl;
    cout << "The second number is splited into " << nodeForNum2 << " nodes" << endl;

    Node* ptr = head1;
    int i, j = 0;
    for (i = length1 - 3; i >= 0; i = i - 3) {
        //cout << num1.substr(i, 3) << endl;
        addNode(head1, stoi(num1.substr(i, 3)), j);
        j++;
        if (i < 3)
            break;
    }
    if (i != 0)
        addNode(head1, stoi(num1.substr(0, i)), j);

    ptr = head2;
    j = 0;
    for (i = length2 - 3; i >= 0; i = i - 3) {
        //cout << num1.substr(i, 3) << endl;
        addNode(head2, stoi(num2.substr(i, 3)), j);
        j++;
        if (i < 3)
            break;
    }
    if (i != 0)
        addNode(head2, stoi(num2.substr(0, i)), j);


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
    int sum;
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
        if (getListValue(head1, m - 1) >= getListValue(head2, n - 1))
        {
            return true;
        }
        else
        {
            return false;
        }
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


int main()
{
    string num1, num2;
    Node* head1 = nullptr, * head2 = nullptr, * head3 = nullptr;
    int m, n, totalNode;
    input(num1, num2);
    cutString(num1, num2, head1, head2, m, n);
    /*
    //addition
    totalNode = nodeNumAddition(m, n);
    initializeResult(head1, head3, totalNode);

    overflowAddition(head2, head3, n);
    */
    totalNode = nodeNumSub(m, n);
    cout << "The result is: ";
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

    displayList(head3);
    cout << endl;
    return 0;
}

