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

void multiplication(Node*& head1, Node*& head2, Node*& head3, int m, int n);
void overflow(Node*& head, int val, int strlen);
int getListValue(Node*& head, int pos);
void setListValue(Node*& head, int pos, int val);
void displayList(Node*& head);
void menu();
void input(string& num1, string& num2);
void cutString(string& num1, string& num2, Node*& head1, Node*& head2, int& nodeForNum1, int& nodeForNum2);
void addNode(Node*& head, int num, int pos);
void printlist(Node*& head1, Node*& head2);
int modifyNodeNums(int num);
void initializeResult(Node*& head, int totalNode);


int main() 
{
    Node* head1 = nullptr, * head2 = nullptr, * head3 = nullptr;
    string num1, num2;
    int m, n;
    input(num1, num2);
    cutString(num1, num2, head1, head2, m, n);
    initializeResult(head3, m + n);
    multiplication(head1, head2, head3, m, n);

    //display
    Node* temp = head1;
    cout << "The first number is: \t";
    displayList(temp);
    cout << endl;
    temp = head2;
    cout << "The second number is: \t";
    displayList(temp);
    cout << endl;
    temp = head3;
    cout << "The result is: \t\t";
    displayList(temp);


}

void initializeResult(Node*& head, int totalNode)
{
    int i;
    for (i = 0; i < totalNode; i++)
    {
        addNode(head, 0, i);
    }
}

void multiplication(Node*& head1, Node*& head2, Node*& head3, int m, int n)
{
    int i, j, val;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            val = getListValue(head1, i) * getListValue(head2, j);
            //if overflow
            //if not overflow(maximum 999)
            overflow(head3, val, i + j);
        }
    }
}

void overflow(Node*& head, int val, int strlen)
{
    if (val / static_cast<int>(pow(10, 3)) >= 1)
    {
        //split the part that overflows 10^3 to the next 3-digit node
        setListValue(head, strlen + 1, val / pow(10, 3));
        //set the base 3 digits
        setListValue(head, strlen, val % static_cast<int>(pow(10, 3)));
    }
    else
    {
        setListValue(head, strlen, val);
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

void setListValue(Node*& head, int pos, int val)
{
    Node* ptr = head;
    int sum;
    while (ptr != nullptr && ptr->loc != pos)
    {
        ptr = ptr->next;
    }
    if(ptr->num + val < static_cast<int>(pow(10, 3)))
        ptr->num += val;
    else
    {
        sum = val + ptr->num;
        ptr->num = sum % static_cast<int>(pow(10, 3));
        ptr = ptr->next;
        ptr->num += sum / static_cast<int>(pow(10, 3));
    }
}

void displayList(Node*& head)
{
    /*
    Node* ptr = head;

    while (ptr != nullptr)
    {
        cout << ptr->num;
        ptr = ptr->next;
    }
    cout << endl;
*/
    if (head->next != nullptr)
    {
        displayList(head->next);
        cout << head->num;
    }
    else
    {
        if (head->num != 0)
            cout << head->num;
    }
}



void menu() {
    cout << "Select from menu" << endl
        << "1. addition" << endl
        << "2. subtruction" << endl
        << "3. multiplication" << endl
        << "4. division " << endl;

}
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

void cutString(string& num1, string& num2, Node*& head1, Node*& head2, int &nodeForNum1, int &nodeForNum2) {
    int length1 = static_cast<int>(num1.length());
    int length2 = static_cast<int>(num2.length());
 
    nodeForNum1 = modifyNodeNums(length1);
    nodeForNum2 = modifyNodeNums(length2);
    cout << "The first number is splited into " << nodeForNum1 << " nodes" << endl;
    cout << "The first number is splited into " << nodeForNum2 << " nodes" << endl;

    Node *ptr = head1;
    int i, j = 0;
    for (i = length1 - 3; i >=0; i = i - 3) {
        //cout << num1.substr(i, 3) << endl;
        addNode(head1, stoi(num1.substr(i, 3)), j);
        j++;
        if (i < 3)
            break;
    }
    if(i != 0)
        addNode(head1, stoi(num1.substr(0, i)), j);

    ptr = head2;
    j = 0;
    for (i = length2 - 3; i >=0; i = i - 3) {
        //cout << num1.substr(i, 3) << endl;
        addNode(head2, stoi(num2.substr(i, 3)), j);
        j++;
        if (i < 3)
            break;
    }
    if (i != 0)
        addNode(head2, stoi(num2.substr(0, i)), j);


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

void printlist(Node*& head1, Node*& head2) {
    Node* ptr1 = nullptr, * ptr2 = nullptr;
    ptr1 = head1;
    ptr2 = head2;
    cout << ptr1->num;
    while (ptr1->next != nullptr) {
        ptr1 = ptr1->next;
        cout << ptr1->num;
    }
    cout << endl;
    cout << ptr2->num;
    while (ptr2->next != nullptr) {
        ptr2 = ptr2->next;
        cout << ptr2->num;
    }
}
