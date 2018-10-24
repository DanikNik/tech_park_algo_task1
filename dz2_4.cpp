#include <iostream>
#include <cmath>

using namespace std;


int bin_search(const int *A, int Lb, int Ub, int Key) {

    while (Lb < Ub) {
        int M = Lb + (Ub - Lb) / 2;

        if (Key <= A[M]) {
            Ub = M;
        } else {
            Lb = M + 1;
        }

        if (A[Ub] == Key) {
            return Ub;
        }
    }
    return Ub;

}

int Search_Elem(const int *A, int Lb, int Ub, int Key) {
    for (int i = Lb; i < Ub; i *= 2) {
        if (A[i] <= Key && A[i * 2 < Ub ? i * 2 : Ub] >= Key) {
            return bin_search(A, i, i * 2 < Ub ? i * 2 : Ub, Key);
        }

        i += i == 0 ? 1 : 0;
    }
    return Ub;
}

int main() {
    int n = 10;
//    cin >> n;
//    int *A = new int[n];
    int A[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
//    for (int i = 0; i < n; ++i) {
//        cin >> A[i];
//    }

    int m = 5;
//    cin >> m;
//    int *B = new int[m];
//    for (int i = 0; i < m; ++i) {
//        cin >> B[i];
//    }
    int B[] = {50, 80, 20, 1800, 10};

//    int current_B_elem_index = 0;
    for (int i = 0; i < m; ++i) {
        cout << Search_Elem(A, 0, n, B[i]) << endl;
    }

    return 0;
}