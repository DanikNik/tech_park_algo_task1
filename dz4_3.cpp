#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;

struct Train_Schedule {
    int Arrival;
    int Departure;

    bool operator<(const Train_Schedule &other) {
        return this->Departure < other.Arrival;
    }

    bool operator>(const Train_Schedule &other) {
        return this->Arrival > other.Arrival;
    }

    bool operator<=(const Train_Schedule &other) {
        return this->Arrival <= other.Arrival;
    }

    bool operator>=(const Train_Schedule &other) {
        return this->Arrival >= other.Arrival;
    }

    bool operator==(const Train_Schedule &other) {
        return this->Arrival == other.Arrival;
    }

    bool operator!=(const Train_Schedule &other) {
        return this->Arrival != other.Arrival;
    }
};

template<class T>
class Heap {
private:
    T *data;
    int size;
    int capacity;

    void SiftUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (data[index] >= data[parent])
                return;
            std::swap(data[index], data[parent]);
            index = parent;
        }
    }

    void SiftDown(int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
// Ищем большего сына, если такой есть.
        int largest = i;
        if (left > this->Size() && data[left] < data[i])
            largest = left;
        if (right < this->Size() && data[right] < data[largest])
            largest = right;
// Если больший сын есть, то проталкиваем корень в него.
        if (largest != i) {
            std::swap(data[i], data[largest]);
            SiftDown(largest);
        }
    }

    void resize() {
        this->capacity *= 2;
        auto *tmp = new T[this->capacity];
        for (int i = 0; i < this->size; ++i) {
            tmp[i] = this->data[i];
        }

        delete[] data;
        this->data = tmp;
    }

    bool is_full() {
        return this->size == this->capacity;
    }

public:
    Heap() : size(0), capacity(8) {
        this->data = new T[this->capacity];
    }

    Heap(const Heap &heap) {
        //deep copy
        this->size = heap.size;
        this->capacity = heap.capacity;
        this->data = new T[heap.capacity];
        for (int i = 0; i < heap.size; ++i) {
            this->data[i] = heap.data[i];
        }
    }

    Heap(Heap &&heap) : size(heap.size), capacity(heap.capacity) {
        this->data = heap.data;
        heap.capacity = 8;
        delete[] heap.data;
        heap.data = new T[heap.capacity];
        heap.size = 0;
    }

    ~Heap() {
        delete[] this->data;
    }


//    void BuildHeap(int *arr, int _size,  int i) {
//        for (int i = _size / 2 - 1; i >= 0; --i ) {
//            SiftDown(arr, i);
//        }
//    }

    void Push(T element) {
        if(is_full()){
            resize();
        }
        this->data[this->Size()] = element;
        this->size++;
        SiftUp(this->Size() - 1);
    }

    T Pop() {
        assert(!this->IsEmpty());
// Memorizing element value
        T result = this->data[0];
// Moving last leave to element position
        this->data[0] = this->data[this->size - 1];
        this->size--;
// SiftDown and SiftUp for element
        if (!this->IsEmpty()) {
            SiftDown(0);
//            SiftUp(0);
        }
        return result;
    }

    void print() {
        for (int i = 0; i < this->size; ++i) {
            cout << this->data[i] << ' ';
        }
        cout << endl;
    }

    T Top() {
        return this->data[0];
    }

    bool IsEmpty() {
        return this->size == 0;
    }

    int Size() const {
        return this->size;
    }

    Heap &operator=(Heap &&heap) = default;

    Heap &operator=(const Heap &heap) = default;

    T operator[](int index) {
        return this->data[index];
    }
};

//int get_heap_size(const Heap &heap) {
//    return ceil(log2(heap.Size()));
//}


int main() {
    Heap<Train_Schedule> schedule;
    int n = 0;
    cin >> n;

    auto *train_schedule = new Train_Schedule[n];

    int time_limit = -1;
    for (int i = 0; i < n; ++i) {
        cin >> train_schedule[i].Arrival >> train_schedule[i].Departure;
        time_limit = max(time_limit, train_schedule[i].Departure);
    }

//    int time_moment = 0;
    int max_trail_num = -1;
//    running through the timeline
    for (int time_moment = 0; time_moment <= time_limit; ++time_moment) {
        static int current_train_arriving = 0;
//        static int trails_busy = 0;
// Pushing arriving trains
        if (train_schedule[current_train_arriving].Arrival == time_moment) {
            schedule.Push(train_schedule[current_train_arriving]);
            current_train_arriving++;
//            trails_busy++;
        }

        max_trail_num = max(max_trail_num, schedule.Size());
//Checking for trains that could depart
        for (int i = 0; i < schedule.Size(); ++i) {
            if (schedule[i].Departure == time_moment) {
                schedule.Pop(i);
//                trails_busy--;
            }
        }
//        cout << time_moment << "    " << schedule.Size() << endl;
        max_trail_num = max(max_trail_num, schedule.Size());
    }

    cout << max_trail_num << endl;
    return 0;
}
