#include <stdio.h>
#include <Windows.h>
#include <set>
#include <map>
#include <unordered_map>
#include <string>
using namespace std;

int main()
{
	//unordered
	map<string, int> m;
	m["���� ��ġ"] = 100; //insert? create? push???
	m["���� ��ġ"] = 0;
	m["�츮�� ��ġ"] = 999;
	m["������ ��ġ"] = -999;
	m["������ ��ġ"] = 77777777;

	for (map<string, int>::iterator it = m.begin(); it != m.end(); ++it)
		printf("%s, %d\n", it->first.c_str(), it->second);

	system("pause");
	return 0;
}