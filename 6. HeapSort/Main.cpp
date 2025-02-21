#include <iostream>
#include <vector>

// 힙 만들기 (Heapify) 함수.
void Heapify(std::vector<int>& array, int length, int ix)
{
    while (true)
    {
        int largest = ix; //root 인덱스 계산
        int left = 2 * ix + 1; // left 인덱스 계산
        int right = 2 * ix + 2; // right 인덱스 계산
        
        if (left < length && array[left] > array[largest])
        {//최대 heap에서는 부모가 가장 커야함
            largest = left;
        }
        if (right < length && array[right] > array[largest])
        {//최대 heap에서는 부모가 가장 커야함
            largest = right;
        }

        if (largest == ix)
        {
            break;
        }

        std::swap(array[ix], array[largest]);
        ix = largest;
    }
}

// 힙 정렬 함수 (HeapSort).
void HeapSort(std::vector<int>& array)
{
    int length = static_cast<int>(array.size());

    for (int ix = length / 2 - 1; ix>=0; --ix)
    {
        //힙 만들기
        Heapify(array, length, ix);
    }

    for (int ix = length - 1; ix > 0; --ix)
    {
        std::swap(array[0], array[ix]);
        Heapify(array, ix, 0);
    }
}

// 배열 출력 함수.
void PrintArray(std::vector<int>& array)
{
    for (int ix = 0; ix < array.size(); ++ix)
    {
        std::cout << array[ix] << (ix < (int)array.size() - 1 ? ", " : "");
    }

    std::cout << "\n";
}

int main()
{
    // 배열.
    std::vector<int> array = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };

    PrintArray(array);

    HeapSort(array);

    PrintArray(array);
}