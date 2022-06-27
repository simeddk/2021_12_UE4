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
	}

	void RotateRight(Node** root, Node* pivot)
	{
		Node* left = pivot->Left;
		pivot->Left = left->Right;

		if (left->Right != nil)
			left->Right->Parent = pivot;

		if (parent->Parent != nullptr)
		{
			if (parent == parent->Parent->Left)
				parent->Parent->Left = left;
			else
				parent->Parent->Right = left;
		}
		else
			*pivot = left;
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