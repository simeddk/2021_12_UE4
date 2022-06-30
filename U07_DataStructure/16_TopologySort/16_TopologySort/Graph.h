#pragma once

#include <list>

template<typename T>
class Graph
{
public:
	struct Edge;
	struct Node;

public:
	Graph() = default;
	~Graph() = default;

	void AddNode(Node* node)
	{
		Node* nodeList = nodes;
		if (nodeList != nullptr)
		{
			while (nodeList->Next != nullptr)
				nodeList = nodeList->Next;

			nodeList->Next = node;
		}
		else
			nodes = node;

		node->Index = count++;
	}

	void AddEdge(Node* node, Edge* edge)
	{
		if (node->Edge != nullptr)
		{
			Edge* edgeList = node->Edge;

			while (edgeList->Next != nullptr)
				edgeList = edgeList->Next;

			edgeList->Next = edge;
		}
		else
			node->Edge = edge;
	}

	void Print()
	{
		Node* node = nullptr;
		Edge* edge = nullptr;

		if ((node = nodes) == nullptr)
			return;

		while (node != nullptr)
		{
			printf("%c : ", node->Data);

			if ((edge = node->Edge) == nullptr)
			{
				node = node->Next;
				printf("\n");

				continue;
			}

			while (edge != nullptr)
			{
				printf("%c ", edge->Target->Data);
				edge = edge->Next;
			}

			printf("\n");

			node = node->Next;
		}

		printf("\n");
	}


private:
	void TopologyDfs(Node* node)
	{
		Edge* edge = nullptr;

		node->Visited = true;
		edge = node->Edge;

		while (edge != nullptr)
		{
			if (edge->Target != nullptr && edge->Target->Visited == false)
				TopologyDfs(edge->Target);

			edge = edge->Next;
		}

		printf("%c ", node->Data);

		linkedList.push_back(node);

	}

public:
	void TopologySort(Node* node)
	{
		while (node != nullptr && node->Visited == false)
		{
			TopologyDfs(node);

			node = node->Next;
		}
	}

public:
	static Node* CreateNode(T data)
	{
		Node* node = new Node();
		node->Data = data;
		return node;
	}

	static void DestroyNode(Node* node)
	{
		while (node->Edge != nullptr)
		{
			Edge* edge = node->Edge->Next;
			DestroyEdge(node->Edge);
			node->Edge = edge;
		}
	}

	void DestroyEdge(Edge* edge)
	{
		delete edge;
		edge = nullptr;
	}

	static Edge* CreateEdge(Node* start, Node* target, float weight = 0.0f)
	{
		Edge* edge = new Edge();
		edge->Start = start;
		edge->Target = target;
		edge->Next = nullptr;
		edge->Weight = weight;

		return edge;
	}

private:
	struct Edge
	{
		float Weight = 0.0f;
		Node* Start = nullptr;
		Node* Target = nullptr;
		Edge* Next = nullptr;
	};

	struct Node
	{
		T Data;
		bool Visited = false;
		int Index = -1;

		Node* Next = nullptr;
		Edge* Edge = nullptr;
	};

public:
	std::list<Node*> GetList() { return linkedList; }

private:
	Node* nodes = nullptr;
	int count = 0;

	std::list<Node*> linkedList;
};