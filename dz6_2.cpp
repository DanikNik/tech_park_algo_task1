/*
 * Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n. Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с индексом k (0..n-1) в отсортированном массиве. Напишите нерекурсивный алгоритм.
Требования к дополнительной памяти: O(n). Требуемое среднее время работы: O(n).
Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении. Описание для случая прохода от начала массива к концу:
*
 */





#include <iostream>
#include <cassert>
using namespace std;


//template<class T>
void _swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}


//template<class int>
int median(const int *arr, int begin, int end) {
//    assert(begin < end);
//    if (arr[begin] > arr[end - 1]) {
//        if (arr[(begin + end) / 2] > arr[begin])
//            return begin;
//        return (arr[end - 1] > arr[(begin + end) / 2]) ? end - 1 : (end + begin) / 2;
//    }
//    if (arr[(begin + end) / 2] > arr[end - 1])
//        return end - 1;
//    return (arr[begin] > arr[(begin + end) / 2]) ? begin : (end + begin) / 2;
    return (begin + end) / 2;
}


//template<class T>
//int partition(int *arr, int begin, int end) {
//    int pivot = median(arr, begin, end);
//    _swap(arr[begin], arr[pivot]);
//
//    int i = end - 1;
//    int j = end - 1;
//
//    while (j > begin) {
//        if (arr[j] < arr[begin]) {
//            j--;
//        } else {
//            _swap(arr[i], arr[j]);
//            i--;
//            j--;
//        }
//    }
//
//    _swap(arr[begin], arr[i]);
//
//    return i;
//}

//10 0
//3 6 5 7 2 9 8 10 4 1



int partition (int *arr, int begin, int end)
{
    int pivot = arr[(begin+end)/2];    // pivot
    int i = (begin - 1);  // Index of smaller element

    for (int j = begin; j <= end- 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            _swap(arr[i], arr[j]);
        }
    }
    _swap(arr[i + 1], arr[end]);
    return (i + 1);
}






int k_statistic(int *arr, int begin, int end, int k) {
    assert(begin < end);

    int pivot = partition(arr, begin, end);
    if (pivot > k) {
        return k_statistic(arr, begin, pivot, k);
    }
    if (pivot < k) {
        return k_statistic(arr, pivot, end, k);
    }

    return arr[pivot];
}

int main() {
    int n = 0, k = 0;
    cin >> n >> k;

    int *arr = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    cout << k_statistic(arr, 0, n, k);

    return 0;
}