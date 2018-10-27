//
// Created by daniknik on 27.10.18.
//

#include <iostream>
#include <climits>
#include <algorithm>
#include <cstring>

using namespace std;

typedef unsigned long long int UINT_64;


//UINT_64 test_set[10][10] = {
//
//        {18619504, 25181641, 37385165, 38062508, 39502897, 41948855, 69298631, 89596078, 93668201, 96064349},
//        {5515010,  6500948,  12780179, 27807903, 31091656, 40669028, 55224433, 64285022, 67768079, 72354843},
//        {40501239, 41782714, 45743184, 52214377, 59219568, 66133260, 66936887, 73374285, 89143509, 92781047},
//        {9688944,  20906741, 35141557, 51234350, 55090599, 60441446, 70980659, 86958853, 87832173, 92996598},
//        {3637475,  23876423, 25052126, 34189348, 44215092, 53739459, 76356786, 77245583, 78906455, 93532436},
//        {6058678,  6820406,  31506722, 45671046, 69668865, 80971179, 88095277, 91072097, 96982038, 99964549},
//        {10755668, 12412021, 20265954, 41108655, 44204890, 61612601, 64058396, 69011658, 73948200, 96296734},
//        {13300286, 25806563, 33753189, 35624819, 61079772, 72993945, 80706640, 91436641, 95625216, 95707531},
//        {8675986,  29923615, 32391082, 36399661, 39171443, 49693149, 65920006, 70613016, 82414855, 82431922},
//        {13329652, 18997626, 24539229, 31242181, 36357464, 46216143, 59580131, 64379619, 67269636, 88425030}
//};


int get_digit(UINT_64 value, int dig_order) {
    UINT_64 tmp = 0;
    tmp = value >> 8 * dig_order;
    tmp = tmp << 8 * 7;
    tmp = tmp >> 8 * 7;
    return (int) tmp;
}


void MSD_sort(UINT_64 *arr, int size, int dig_order) {
    while (dig_order != 8) {

        size_t bins_count = 256;

        int *bins = new int[bins_count];
        for (int m = 0; m < bins_count; ++m) {
            bins[m] = 0;
        }

        for (int i = 0; i < size; ++i) {
            bins[get_digit(arr[i], dig_order)]++;
        }

        for (int j = 1; j < bins_count; ++j) {
            bins[j] += bins[j - 1];
        }

        auto *tmp = new UINT_64[size];

        for (int l = 0; l < size; ++l) {
            tmp[l] = arr[l];
        }

        for (int k = size - 1; k >= 0; --k) {
            int &bin = bins[get_digit(tmp[k], dig_order)];
            arr[--bin] = tmp[k];
        }

        delete[] tmp;
        delete[] bins;

        dig_order++;
    }
}

int main() {
    int n = -1;
    std::cin >> n;


    auto *arr = new UINT_64[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
//    for (int i = 0; i < 10; ++i) {
//        UINT_64 *arr = test_set[i];

    MSD_sort(arr, n, 0);
    for (int j = 0; j < n; ++j) {
        std::cout << arr[j] << ' ';
    }
    cout << endl;
    delete[] arr;
//    }
    return 0;
}