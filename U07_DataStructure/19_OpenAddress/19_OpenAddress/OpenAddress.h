#pragma once

template<typename T>
class OpenAddress
{
public:
	struct Element;

public:
	OpenAddress(int size)
		: tableSize(size)
	{
		table = new Element[tableSize];
		memset(table, 0, sizeof(Element) * tableSize);
	}

	~OpenAddress()
	{
		delete[] table;
	}

	int Hash(char* key, int keyLength)
	{
		int hash = 0;

		for (int i = 0; i < keyLength; i++)
			hash = (hash << 3) + key[i];

		return hash % tableSize;
	}

	int Hash2(char* key, int keyLength)
	{
		int hash = 0;

		for (int i = 0; i < keyLength; i++)
			hash = (hash << 4) + key[i];

		return hash % (tableSize - 3);
	}

	void ReHash()
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("\n70%% �̻� ����. Index ������ Ȯ���մϴ�.\n\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

		int oldSize = tableSize;
		tableSize *= 2;

		Element* oldTable = table;
		table = new Element[tableSize];

		for (int i = 0; i < oldSize; i++)
		{
			if (oldTable[i].Occupied == true)
				Set(oldTable[i].Key, strlen(oldTable[i].Key), oldTable[i].Value);
		}

		delete[] oldTable;
	}

	void Set(char* key, int keyLength, T value)
	{
		float usage = (float)occupiedCount / (float)tableSize;
		if (usage >= 0.7f)
			ReHash();

		int index = Hash(key, keyLength);
		int spare = Hash2(key, keyLength);

		while (table[index].Occupied == true && strcmp(table[index].Key, key) != 0)
		{
			printf("\n [!] %sŰ ���� �� [%d]�� �̹� %s�� �����մϴ�."
				, key, index, table[index].Key);

			index = (index + spare) % tableSize;

			printf(" -> �ٸ� �ε��� [%d]�� �̵��մϴ�\n", index);
		}

		table[index].Key = new char[keyLength + 1];
		strcpy_s(table[index].Key, sizeof(key) * strlen(key + 1), key);
		table[index].Value = value;

		table[index].Occupied = true;
		occupiedCount++;

		printf("key(%s)�� [%d]�ε����� �����\n", key, index);
	}

	T Get(char* key, int keyLength)
	{
		int index = Hash(key, keyLength);
		int spare = Hash2(key, keyLength);

		while (table[index].Occupied == true && strcmp(table[index].Key, key) != 0)
			index = (index + spare) % tableSize;

		return table[index].Value;
	}

private:
	struct Element
	{
		char* Key;
		T Value;

		bool Occupied;
	};

private:
	int occupiedCount = 0;
	int tableSize;

	Element* table;
};