#include <iostream>
#include <algorithm>

int Partition(int* array, int left, int right)
{
	//�ǹ� ����
	int first = left;
	int pivot = array[first];

	// ���� ��ġ�� �̵�.
	++left;

	//�� �ε����� ���� ������ ������ ����.
	while (left <= right)
	{
		//left pivot���� ū �� �˻�
		while (array[left] <= pivot)
		{
			++left;
		}

		//right pivot���� ���� �� �˻�
		// left�� right�� �������� ���� ���� �� ��ȯ.
		while (array[right] > pivot)
		{
			--right;
		}

		//if (left >= right)
		//{
		//	break;
		//}

		//std::swap(array[left], array[right]);

		//left�� right�� �������� ���� ���� �� ��ȯ.
		if (left < right)
		{
			std::swap(array[left], array[right]);
		}
		else {
			break;
		}
	}
	std::swap(array[first], array[right]);

	return right;
}

void QuickSort(int* array, int left, int right)
{
	if (left >= right)
	{
		return;
	}

	// ����
	int partition = Partition(array, left, right);

	//���� �迭 �� ����.
	QuickSort(array, left, partition - 1);

	QuickSort(array, partition, right);
}

void PrintArray(int array[], int length)
{
	for (int ix = 0; ix < length; ++ix)
	{
		if (ix < length - 1)
		{
			std::cout << array[ix] << (ix < length - 1 ? ", " : "");
		}
	}

	std::cout << "\n";
}

int main()
{
	int array[] = { 18, 19, 21, 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16, 11, 25 };

	//int length = sizeof(array) / sizeof(int);
	int length = _countof(array);

	std::cout << "���� �� : ";
	PrintArray(array, length);

	QuickSort(array, 0, length - 1);

	std::cout << "���� �� : ";
	PrintArray(array, length);


	std::cin.get();
}
