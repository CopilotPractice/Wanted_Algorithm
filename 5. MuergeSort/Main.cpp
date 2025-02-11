#include <iostream>

// 병합 함수(Merge).
void Merge(int* array, int length,
	int* leftArray, int leftLength,
	int* rightArray, int rightLength)
{
	int leftIndex = 0;
	int rightIndex = 0;
	int mergedIndex = 0;

	while (leftIndex < leftLength && rightIndex < rightLength)
	{
		if (leftArray[leftIndex] <= rightArray[rightIndex]) {
			array[mergedIndex] = leftArray[leftIndex];
			++leftIndex;
		}
		else
		{
			array[mergedIndex] = rightArray[rightIndex];
			++rightIndex;
		}
		++mergedIndex;
	}

	while (leftIndex < leftLength)
	{
		array[mergedIndex] = leftArray[leftIndex];
		++mergedIndex;
		++leftIndex;
	}

	while (rightIndex < rightLength)
	{
		array[mergedIndex] = rightArray[rightIndex];
		++mergedIndex;
		++rightIndex;
	}
}
// 정렬 함수(MergeSort).
void MergeSort(int* array, int length)
{
	if (length <= 1) {
		return;
	}

	int mid = length / 2;
	int* leftArray = new int[mid];
	int* rightArray = new int[length-mid];
	
	memcpy(leftArray, array, sizeof(int) * mid);

	memcpy(rightArray, (array + mid), sizeof(int) * (length - mid));

	MergeSort(leftArray, mid);

	MergeSort(rightArray, length-mid);

	Merge(array, length, leftArray, mid, rightArray, (length - mid));

	delete[] leftArray;
	delete[] rightArray;
}

// 배열 출력 함수.
void PrintArray(int array[], int length)
{
	for (int ix = 0; ix < length; ++ix)
	{
		std::cout << array[ix] << (ix < length - 1 ? ", " : "");
	}

	std::cout << "\n";
}

int main()
{
	// 배열.
	int array[] = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };

	int length = _countof(array);

	std::cout << "정렬 전 : ";
	PrintArray(array, length);

	MergeSort(array, length);

	std::cout << "정렬 후 : ";
	PrintArray(array, length);

	std::cin.get();
}