#include <iostream>
#include <thread>
#include <vector>
using namespace std;

void Sum(vector<int>::iterator start, vector<int>::iterator end, int* result)
{
	int sum = 0;
	for (auto it = start; it < end; ++it)
		sum += *it;

	*result = sum;

	thread::id id = this_thread::get_id();
	printf("Thread(%x)���� %d ~ %d���� ����� ��� : %d\n", id, *start, *end - 1, sum);
}

int main()
{
	//0~100 Data
	vector<int> data;
	for (int i = 0; i <= 100; i++)
		data.push_back(i);

	vector<int> results(4);

	//Thread ����
	vector<thread> threads;
	for (int i = 0; i < 4; i++)
	{
		threads.push_back(thread
		(
			Sum,
			data.begin() + i * 25,
			data.begin() + ((i + 1) * 25),
			&results[i]
		));
	}

	//Thread ����
	for (int i = 0; i < 4; i++)
		threads[i].join();


	//�����ջ�
	int sum = 0;
	for (int i = 0; i < 4; i++)
		sum += results[i];

	printf("%d\n", sum);

	system("pause");
	return 0;
}