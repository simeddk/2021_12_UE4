#include <stdio.h>
#include <Windows.h>
#include <string>
using namespace std;

#include "PQueue.h"

void Print(PQueue<string>::Node* nodes, int size)
{
	for (int i = 0; i < size; i++)
	printf("�켱����(%d) : %s\n", nodes[i].Priority, nodes[i].Data.c_str());
}

int main()
{
	PQueue<string> queue(16);
	queue.Enqueue(PQueue<string>::Node(66, "�� ���� �ϱ�"));
	queue.Enqueue(PQueue<string>::Node(34, "��Ʈ������ �ϼ��ϱ�"));
	queue.Enqueue(PQueue<string>::Node(12, "�˰��� ����Ǯ��"));
	queue.Enqueue(PQueue<string>::Node(45, "�� û���ϱ�"));
	queue.Enqueue(PQueue<string>::Node(35, "�İ� ���� �����ϱ�"));
	queue.Enqueue(PQueue<string>::Node(87, "���ڱ�"));
	Print(queue.Nodes(), queue.Size());

	PQueue<string>::Node node = queue.Dequeue();
	printf("-> %d : %s\n\n", node.Priority, node.Data.c_str());
	Print(queue.Nodes(), queue.Size());

	node = queue.Dequeue();
	printf("-> %d : %s\n\n", node.Priority, node.Data.c_str());
	Print(queue.Nodes(), queue.Size());

	node = queue.Dequeue();
	printf("-> %d : %s\n\n", node.Priority, node.Data.c_str());
	Print(queue.Nodes(), queue.Size());

	node = queue.Dequeue();
	printf("-> %d : %s\n\n", node.Priority, node.Data.c_str());
	Print(queue.Nodes(), queue.Size());

	node = queue.Dequeue();
	printf("-> %d : %s\n\n", node.Priority, node.Data.c_str());
	Print(queue.Nodes(), queue.Size());

	system("pause");
	return 0;
}