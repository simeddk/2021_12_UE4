#pragma once

/*
# Basic Rule
��Ģ1. ��� ���� Red�̰ų� Black�̾�� ��
��Ģ2. root ���� �׻� Black
��Ģ3. leaf(nil)���� �׻� Black
��Ģ4. ��� nil��忡�� ����ϴ�, root���� ���� Black�� ������ �����ؾ� ��
��Ģ5. Red�� �ڽĿ��� �׻� Black�� ���� �� ����
*/

template<typename T>
class RBTree
{
public:
	struct Node;
	enum class Color { Red, Black };

public:
	RBTree()
	{
		nil = CreateNode(0);
	}

	Node* Search(Node* node, T data)
	{
		if (node == nullptr) return nullptr;

		if (node->Data > data)
			return Search(node->Left, data);
		else if (node->Data < data)
			return Search(node->Right, data);

		return node;
	}

	Node* SearchMinNode(Node* node)
	{
		if (node == nullptr) return nullptr;

		if (node->Left == nil)
			return node;

		return SearchMinNode(node->Left);
	}

private:
	void InsertInternal(Node** node, Node* newNode)
	{
		if (*node == nullptr)
			*node = newNode;

		if ((*node)->Data < newNode->Data)
		{
			if ((*node)->Right == nil)
			{
				(*node)->Right = newNode;
				newNode->Parent = *node;
			}
			else
				InsertInternal(&(*node)->Right, newNode);
		}
		else if ((*node)->Data > newNode->Data)
		{
			if ((*node)->Left == nil)
			{
				(*node)->Left = newNode;
				newNode->Parent = *node;
			}
			else
				InsertInternal(&(*node)->Left, newNode);
		}
	}

	void RebuildInsert(Node** root, Node* node)
	{
		while (node != (*root) && node->Parent->Color == Color::Red)
		{
			//���ݳ���� �θ� Left�� ���
			if (node->Parent == node->Parent->Parent->Left)
			{
				Node* uncle = node->Parent->Parent->Right;

				//���� ��Ģ1.(������ Red�� ��� -> �θ�� ������ Black, �Ҿƹ����� Red��)
				if (uncle->Color == Color::Red)
				{
					node->Parent->Color = Color::Black;
					uncle->Color = Color::Black;
					node->Parent->Parent->Color = Color::Red;

					node = node->Parent->Parent;
				}
				else //������ Black�� ���
				{
					//���Ա�Ģ2.(������ Black, node�� Right�� ���� ���)
					if (node == node->Parent->Right)
					{
						node = node->Parent;
						RotateLeft(root, node);
					}
					
					//���Ա�Ģ3.(������ Black, node�� Left�� ���� ���)
					node->Parent->Color = Color::Black;
					node->Parent->Parent->Color = Color::Red;
					RotateRight(root, node->Parent->Parent);
				}
			} 
			//���ݳ���� �θ� Right�� ���
			else
			{
				Node* uncle = node->Parent->Parent->Left;

				//���� ��Ģ1.(������ Red�� ��� -> �θ�� ������ Black, �Ҿƹ����� Red��)
				if (uncle->Color == Color::Red)
				{
					node->Parent->Color = Color::Black;
					uncle->Color = Color::Black;
					node->Parent->Parent->Color = Color::Red;

					node = node->Parent->Parent;
				}
				else //������ Black�� ���
				{
					//���Ա�Ģ2.(������ Black, node�� Right�� ���� ���)
					if (node == node->Parent->Left)
					{
						node = node->Parent;
						RotateRight(root, node);
					}

					//���Ա�Ģ3.(������ Black, node�� Left�� ���� ���)
					node->Parent->Color = Color::Black;
					node->Parent->Parent->Color = Color::Red;
					RotateLeft(root, node->Parent->Parent);
				}
			}
		}

		(*root)->Color = Color::Black;
	}

public:
	void Insert(Node** node, Node* newNode)
	{
		InsertInternal(node, newNode);

		/*
		���� ��Ģ�� newNode�� �θ� Red�� ��쿡�� ����(Red�ؿ� Red�� �ٴ� ��Ȳ)
		���� ��Ģ1. Uncle�� Red�� ���, Parent->Black, Uncle->Black, Grand->Red
		���� ��Ģ2. Uncle�� Black�̰�, newNode�� Right�� ��� -> Parent�� �������� ��ȸ��
		���� ��Ģ3. Uncle�� Black�̰�, newNode�� Left�� ��� 
			-> Parent->Balck, Grand->Red, Grand�� �������� ��ȸ��
		*/

		newNode->Color = Color::Red;
		newNode->Left = nil;
		newNode->Right = nil;

		RebuildInsert(node, newNode);
	}

	//���� ��Ģ(5����)
	//(1) ������ Red�� ��� -> �θ� Red��, ������ Black -> ���ʿ� �־��ٸ� �θ� ���� ��ȸ��, �����ʿ� �־��ٸ� �θ� ���� ��ȸ��
	//(2) ������ Black�� ��� -> �Ʒ� �������� �Ļ�
	//(2-1) ������ ���� �ڽ��� ��� Black�� ��� -> ������ Red��
	//(2-2) ������ ���� �ڽĸ� Red -> ������ ���� �ڽ��� Black, ������ Red, ������ �������� ��ȸ��
	//(2-3) ������ ������ �ڽĸ� Red -> �θ� Black����, ������ �������� Black����, �θ� ���� ��ȸ��


	void RotateRight(Node** root, Node* pivot)
	{
		Node* left = pivot->Left;
		pivot->Left = left->Right;

		if (left->Right != nil)
			left->Right->Parent = pivot;

		left->Parent = pivot->Parent;

		if (pivot->Parent != nullptr)
		{
			if (pivot == pivot->Parent->Left)
				pivot->Parent->Left = left;
			else
				pivot->Parent->Right = left;
		}
		else
			*root = left;

		left->Right = pivot;

		pivot->Parent = left;
	}

	void RotateLeft(Node** root, Node* pivot)
	{
		Node* right = pivot->Right;
		pivot->Right = right->Left;

		if (right->Left != nil)
			right->Left->Parent = pivot;

		right->Parent = pivot->Parent;

		if (pivot->Parent != nullptr)
		{
			if (pivot == pivot->Parent->Left)
				pivot->Parent->Left = right;
			else
				pivot->Parent->Right = right;
		}
		else
			*root = right;

		right->Left = pivot;

		pivot->Parent = right;
	}

	void Print(Node* node, int depth)
	{
		if (node == nullptr || node == nil) return;

		if (node->Color == Color::Red)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
		else 
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

		T parent = -1;
		char d = 'X';
		if (node->Parent != nullptr)
		{
			parent = node->Parent->Data;

			if (node->Parent->Left == node)
				d = 'L';
			else
				d = 'R';
		}

		string depthBar = "";

		for (int i = 0; i < depth; i++)
			depthBar += " - ";

		printf("%s %d [%c,%d]\n", depthBar.c_str(), node->Data, d, parent);

		Print(node->Left, depth + 1);
		Print(node->Right, depth + 1);
	}

public:
	static Node* CreateNode(T data)
	{
		Node* node = new Node();
		node->Parent = nullptr;
		node->Left = node->Right = nullptr;
		node->Color = Color::Black;
		node->Data = data;

		return node;
	}

	static void DestroyNode(Node* node)
	{
		delete node;
		node = nullptr;
	}

public:
	struct Node
	{
		Node* Parent;
		Node* Left;
		Node* Right;
		Color Color;

		T Data;
	};

private:
	Node* nil;
};