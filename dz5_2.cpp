#include <iostream>
#include <cassert>
#include <cstring>
#include <algorithm>

using namespace std;


template<class T>
T _max(T v1, T v2) {
    return v1 > v2 ? v1 : v2;
}

template<class T>
T _min(T v1, T v2) {
    return v1 > v2 ? v2 : v1;
}

template<class T>
void merge(T arr[], size_t left_border, size_t median, size_t right_border) {

    size_t left_arr_size = median - left_border + 1;
    size_t right_arr_size = right_border - median;

    T *left_arr = new T[left_arr_size], *right_arr = new T[right_arr_size];


    for (size_t i = 0; i < left_arr_size; i++)
        left_arr[i] = arr[left_border + i];
    for (size_t j = 0; j < right_arr_size; j++)
        right_arr[j] = arr[median + 1 + j];


    size_t i = 0, j = 0, k = left_border;
    while (i < left_arr_size && j < right_arr_size) {
        if (left_arr[i] <= right_arr[j]) {
            arr[k++] = left_arr[i++];
        } else {
            arr[k++] = right_arr[j++];
        }
    }

    while (i < left_arr_size) {
        arr[k++] = left_arr[i++];
    }

    while (j < right_arr_size) {
        arr[k++] = right_arr[j++];
    }
}

template<class T>
void merge_sort(T *arr, size_t left_border, size_t right_border) {
    if (left_border < right_border) {
        size_t median = left_border + (right_border - left_border) / 2;

        merge_sort(arr, left_border, median);
        merge_sort(arr, median + 1, right_border);

        merge(arr, left_border, median, right_border);
    }
}

struct Date {
    int day;
    int month;
    int year;
    bool is_birth;

    int get_julyan_day() {
        auto a = (14 - month) / 12;
        auto y = year + 4800 - a;
        auto m = month + 12 * a - 3;

        return (day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045);
    }

    bool operator>(Date &other) {
        return this->get_julyan_day() > other.get_julyan_day();
    }

    bool operator<(Date &other) {
        return this->get_julyan_day() < other.get_julyan_day();
    }

    bool operator>=(Date &other) {
        return this->get_julyan_day() >= other.get_julyan_day();
    }

    bool operator<=(Date &other) {
        return this->get_julyan_day() <= other.get_julyan_day();
    }

    bool operator!=(Date &other) {
        return this->get_julyan_day() != other.get_julyan_day();
    }

    bool operator==(Date &other) {
        return this->get_julyan_day() == other.get_julyan_day();
    }
};

istream &operator>>(istream &is, Date &dt) {
    is >> dt.day >> dt.month >> dt.year;
    return is;
}


struct Person {
    Date birth;
    Date death;

    int get_life_length() {
        return (death.get_julyan_day() - birth.get_julyan_day());
    }

    bool operator>(Person &other) {
        return this->birth > other.birth;
    }

    bool operator<(Person &other) {
        return this->birth < other.birth;
    }

    bool operator>=(Person &other) {
        return this->birth >= other.birth;
    }

    bool operator<=(Person &other) {
        return this->birth <= other.birth;
    }

    bool operator==(Person &other) {
        return this->birth == other.birth;
    }

    bool operator!=(Person &other) {
        return this->birth != other.birth;
    }
};

istream &operator>>(istream &is, Person &pers) {
    is >> pers.birth >> pers.death;
    pers.birth.is_birth = 1;
    pers.death.is_birth = 0;
    return is;
}

int main() {
    int n = -1;
    cin >> n;

    int people_count = n;
    auto *people = new Person[n];

    for (int i = 0; i < people_count; ++i) {
        static int j = 0;
        cin >> people[j++];
        if (people[j].get_life_length() < 6574) {
            j--;
            people_count--;
        }
    }

//    Date *dates = new Date[people_count * 2];
//
//    size_t datesAmount = 0;
//    for (auto &i : datesList) {
//         приводим интервалы дат к интервалам длины (80 - 18)
//        Date leftBorder(i.first.getDay(), i.first.getMonth(), i.first.getYear() + 18);
//        Date rightBorder(i.first.getDay(), i.first.getMonth(), i.first.getYear() + 80);
//
//        if (leftBorder >= i.second) {
//            continue;
//        }
//
//        if (rightBorder > i.second) {  // if a man dies earlier than gets 80 years old than move the right border
//            rightBorder = i.second;
//        }
//
//        dateInterval[datesAmount++] = {leftBorder, true};
//        dateInterval[datesAmount++] = {rightBorder, false};
//    }


//  for (int j = 0; j < n; ++j) {
//        cout << people[j].get_life_length() << endl;
//    }

//    Date minDate = people[0].birth, maxDate = people[0].death;
//
//    for (int k = 0; k < people_count; ++k) {
//        minDate = _min(minDate, people[k].birth);
//        maxDate = _max(maxDate, people[k].death);
//    }
//
//    merge_sort(people, 0, static_cast<size_t>(people_count));
cout << people_count << endl;

    return 0;
}