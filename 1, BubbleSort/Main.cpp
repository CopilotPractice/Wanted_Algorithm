#include <iostream>


//두 값을 서로 교환
void Swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

//버블 정렬 함수
void BubbleSort(int* array, int length)
{
	//정렬
	for (int ix = 0; ix < length - 1; ++ix)
	{
		for (int jx = 0; jx < length - 1 -ix; ++jx)
		{
			if (array[jx] > array[jx + 1])
			{
				Swap(array[jx], array[jx + 1]);
			}
		}
	}
}

void PrintArray(int* array, int length)
{
	for (int ix = 0; ix < length; ++ix)
	{
		std::cout << array[ix] << " ";
	}

	std::cout << "\n";
}

int main()
{
	int array[] = { 4, 5, 6, 7, 8, 20, 3, 2, 50, 70, 40, 10 };
	int length = sizeof(array) / sizeof(int);

	std::cout << "정렬 전 : ";
	PrintArray(array, length);

	std::cout << "정렬 후 : ";
	BubbleSort(array, length);
	PrintArray(array, length);
}