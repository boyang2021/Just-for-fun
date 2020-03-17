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
	while (ptr != nullptr && ptr->loc != pos)
	{
		ptr = ptr->next;
	}
	ptr->num += val;
}

void displayList(Node* &head)
{
	Node* ptr = head;

	while (ptr != nullptr)
	{
		cout << ptr->num;
		ptr = ptr->next;
	}
	cout << endl;
}