/*
 *6_2  Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n. Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с индексом k (0..n-1) в отсортированном массиве. Напишите нерекурсивный алгоритм.
Требования к дополнительной памяти: O(n). Требуемое среднее время работы: O(n).
Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении. Описание для случая прохода от начала массива к концу:
*
 */


#include <iostream>
#include <cassert>
//#include <algorithm>

using namespace std;


void _swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

int median(const int *arr, int begin, int end) {
    if (arr[begin] > arr[end - 1]) {
        if (arr[(begin + end) / 2] > arr[begin])
            return begin;
        return (arr[end - 1] > arr[(begin + end) / 2]) ? end - 1 : (end + begin) / 2;
    }
    if (arr[(begin + end) / 2] > arr[end - 1])
        return end - 1;
    return (arr[begin] > arr[(begin + end) / 2]) ? begin : (end + begin) / 2;
}


int partition(int *arr, int begin, int end) {
    int pivot = median(arr, begin, end);

    _swap(arr[pivot], arr[end - 1]);

    int i = end - 2;
    int j = end - 1;

    while (j >= begin) {
        if (arr[j] > arr[end - 1]) {
            _swap(arr[i], arr[j]);
            i--;
        }
        j--;
    }
    _swap(arr[++i], arr[end - 1]);

    return i;
}


int k_statistic(int *arr, int begin, int end, int k) {
    int pivot = partition(arr, begin, end);
    while (pivot != k) {
        if (pivot > k) {
            end = pivot;
            pivot = partition(arr, begin, end);
        } else if (pivot < k) {
            begin = pivot;
            pivot = partition(arr, begin, end);
        }
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
    delete[] arr;
    return 0;
}