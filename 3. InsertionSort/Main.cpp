#include <iostream>

// 삽입 정렬 함수.
void InsertionSort(int* array, int length)
{
    // 배열 순회.
    for (int ix = 1; ix < length; ++ix)
    {
        // 키 뽑기.
        int keyValue = array[ix];
        int jx = ix - 1;

        // 셔플링(교환).
        while (jx >= 0 && array[jx] > keyValue)
        {
            array[jx + 1] = array[jx];
            --jx;
        }

        // 값 끼우기.
        array[jx + 1] = keyValue;
    }
}

// 배열 출력 함수.
void PrintArray(int* array, int length)
{
    for (int ix = 0; ix < length; ++ix)
    {
        std::cout << array[ix] << (ix < length - 1 ? ", " : "");
    }

    std::cout << "\n";
}


int main()
{
	int array[] = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };

	int length = sizeof(array) / sizeof(int);

	std::cout << "정렬 전: ";
	PrintArray(array, length);

	InsertionSort(array, length);

	std::cout << "정렬 후: ";
	PrintArray(array, length);

	std::cin.get();
}