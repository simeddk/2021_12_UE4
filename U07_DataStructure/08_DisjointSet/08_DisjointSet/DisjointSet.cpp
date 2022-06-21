#include <iostream>
#include <Windows.h>
using namespace std;

#include "DisjointSet.h"

#define Group DisjointSet<string>

int main()
{
	Group::Set* mcu = Group::CreateSet("MCU");
	Group::Set* spiderMan = Group::CreateSet("�����̴���");
	Group::Set* ironMan = Group::CreateSet("���̾��");
	Group::Set* hulk = Group::CreateSet("��ũ");
	Group::Set* batMan = Group::CreateSet("��Ʈ��");

	Group::UinionSet(mcu, spiderMan);
	cout << Group::IsSameGroup(mcu, spiderMan) << endl;

	Group::UinionSet(spiderMan, ironMan);
	cout << Group::IsSameGroup(mcu, ironMan) << endl;
	cout << Group::IsSameGroup(spiderMan, ironMan) << endl;
	
	Group::UinionSet(mcu, hulk);
	cout << Group::IsSameGroup(ironMan, hulk) << endl;

	cout << Group::IsSameGroup(mcu, batMan) << endl;

	system("pause");
	return 0;
}