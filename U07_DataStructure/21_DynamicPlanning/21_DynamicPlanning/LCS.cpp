#include <stdio.h>
#include <Windows.h>

struct Table
{
	int** Data;
};

int LCS(char* x, char* y, int i, int j, Table* table)
{
	if (i == 0 || j == 0)
	{
		table->Data[i][j] = 0;
	}
	else if (x[i - 1] == y[j - 1])
	{
		table->Data[i][j] = LCS(x, y, i - 1, j - 1, table) + 1;
	}
	else
	{
		int a = LCS(x, y, i - 1, j, table);
		int b = LCS(x, y, i, j - 1, table);

		if (a > b)
			table->Data[i][j] = a;
		else
			table->Data[i][j] = b;
	}

	return table->Data[i][j];
}

int main()
{
	//char* a = (char*)"GOOD MORNING";
	//char* b = (char*)"GUTEN MORGEN";

	char* a = (char*)"AXYC";
	char* b = (char*)"ABCD";

	int lenA = strlen(a);
	int lenB = strlen(b);

	Table table;
	table.Data = new int*[lenA + 1];

	for (int i = 0; i < lenA + 1; i++)
	{
		table.Data[i] = new int[lenB + 1];
		memset(table.Data[i], 0, sizeof(int) * (lenB + 1));
	}

	int reuslt = LCS(a, b, lenA, lenB, &table);

	//���̺� ���
	printf("\n%-04s", " ");

	for (int i = 0; i <= lenB; i++)
		printf("%c ", b[i]);
	printf("\n");

	for (int i = 0; i <= lenA; i++)
	{
		printf("%c ", a[i - 1]);

		for (int j = 0; j <= lenB; j++)
			printf("%d ", table.Data[i][j]);

		printf("\n");
	}

	printf("\n\n�ߺ� ���� �� : %d\n", reuslt);

	system("pause");
	return 0;
}