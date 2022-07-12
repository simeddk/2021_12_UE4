#include <stdio.h>
#include <Windows.h>

int CountCoins(int amount, int coinUnit)
{
	int count = 0;
	int currAmount = amount;

	while (currAmount >= coinUnit)
	{
		count++;
		currAmount -= coinUnit;
	}

	return count;
}

void GetChange(int price, int pay, int coinUnit[], int change[], int unitCount)
{
	int amount = pay - price;

	for (int i = 0; i < unitCount; i++)
	{
		change[i] = CountCoins(amount, coinUnit[i]);

		amount = amount - (change[i] * coinUnit[i]);
	}
}

void PrintChange(int coinUnit[], int change[], int unitCount)
{
	printf("�Ž����� : \n");
	for (int i = 0; i < unitCount; i++)
		printf("%d�� : %d��\n", coinUnit[i], change[i]);
}

int Compare(const void* a, const void* b)
{
	int A = *(int*)a;
	int B = *(int*)b;

	return A < B ? 1 : -1;
}

int main()
{
	int unitCount; //������ ���� ����

	printf("������ ����(������) �Է� : ");
	scanf_s("%d", &unitCount);

	int* coinUnit = new int[unitCount];
	int* change = new int[unitCount];

	for (int i = 0; i < unitCount; i++)
	{
		printf("[%d]��° ���� ���� : ", i);
		scanf_s("%d", &coinUnit[i]);
	}

	qsort(coinUnit, unitCount, sizeof(int), Compare);

	int price = 0;
	printf("���� ���� : ");
	scanf_s("%d", &price);

	int pay = 0;
	printf("������ �� : ");
	scanf_s("%d", &pay);

	GetChange(price, pay, coinUnit, change, unitCount);
	printf("\n");
	PrintChange(coinUnit, change, unitCount);

	system("pause");
	return 0;
}