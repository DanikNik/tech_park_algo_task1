#include <iostream>

int* merge(int* arr1, int* arr2, int arr1_size, int arr2_size){

}

void merge_sort(int* arr, int left_b, int rigth_b){
    if (rigth_b - left_b <=1){
        return;
    }

    int median = (rigth_b + left_b)/2;
    merge_sort(arr, left_b, median);
    merge_sort(arr, median, rigth_b);

    int* merged_arr = merge();
}


int main() {



    return 0;
}