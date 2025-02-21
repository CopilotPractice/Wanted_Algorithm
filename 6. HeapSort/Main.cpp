#include <iostream>
#include <vector>

// �� ����� (Heapify) �Լ�.
void Heapify(std::vector<int>& array, int length, int ix)
{
    while (true)
    {
        int largest = ix; //root �ε��� ���
        int left = 2 * ix + 1; // left �ε��� ���
        int right = 2 * ix + 2; // right �ε��� ���
        
        if (left < length && array[left] > array[largest])
        {//�ִ� heap������ �θ� ���� Ŀ����
            largest = left;
        }
        if (right < length && array[right] > array[largest])
        {//�ִ� heap������ �θ� ���� Ŀ����
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

// �� ���� �Լ� (HeapSort).
void HeapSort(std::vector<int>& array)
{
    int length = static_cast<int>(array.size());

    for (int ix = length / 2 - 1; ix>=0; --ix)
    {
        //�� �����
        Heapify(array, length, ix);
    }

    for (int ix = length - 1; ix > 0; --ix)
    {
        std::swap(array[0], array[ix]);
        Heapify(array, ix, 0);
    }
}

// �迭 ��� �Լ�.
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
    // �迭.
    std::vector<int> array = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };

    PrintArray(array);

    HeapSort(array);

    PrintArray(array);
}