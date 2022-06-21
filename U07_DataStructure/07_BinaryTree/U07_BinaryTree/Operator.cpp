#include <iostream>
#include <string>
using namespace std;

#include "BinaryTree.h"

#define Order

void MakeTree(const char* postfix, BinaryTree<char>::Node** node)
{
	char* str = (char*)postfix;

	size_t length = strlen(str);
	
	char token = str[length - 1];
	str[length - 1] = '\0';

	switch (token)
	{
		case '+': case '-': case '*': case '/': case '%':
		{
			*node = BinaryTree<char>::CreateNode(token);
			MakeTree(postfix, &(*node)->Right);
			MakeTree(postfix, &(*node)->Left);
		}
		break;

		default:
		{
			*node = BinaryTree<char>::CreateNode(token);
		}
		break;
	}
}

float Calc(BinaryTree<char>::Node* node)
{
	if (node == nullptr) return 0.0f;

	switch (node->Data)
	{
		case '+': case '-': case '*': case '/': case '%':
		{
			float left = Calc(node->Left);
			float right = Calc(node->Right);

			//Todo. ���� ��� �ڵ�
		}
		break;

		default:
		{
			char temp[4];
			memset(temp, '\0', sizeof(temp));

			temp[0] = node->Data;


			return atof(temp);
		}
		break;
	}

}

int main()
{
	BinaryTree<char>::Node* root = nullptr;
	
	string postfix = "12*34*-";
	MakeTree(postfix.c_str(), &root);

#ifndef Order
	BinaryTree<char> tree;
	tree.Root(root);

	tree.PreOrder(root);
	cout << endl;

	tree.InOrder(root);
	cout << endl;

	tree.PostOrder(root);
	cout << endl;
#endif

	cout << Calc(root) << endl;


	system("pause");
	return 0;
}