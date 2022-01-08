#include <bits/stdc++.h>

using namespace std;

void max_heapify(vector<int> &a, int i);
void build_heap(vector<int> &a);
void heap_sort(vector<int> &a);

int heap_size, n;

int main() {

    cin >> n;
    heap_size = n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a.begin(), a.end());
    for (int i = 0; i < n; ++i) cout << a[i] << ' ';
    cout << endl;

    return 0;
}

void max_heapify(vector<int> &a, int i) {
    int largest = i, left = i * 2, right = i * 2 + 1;
    if (left < heap_size && a[left] > a[largest]) largest = left;
    if (right < heap_size && a[right] > a[largest]) largest = right;
    if (i != largest) {
        swap(a[i], a[largest]);
        max_heapify(a, largest);
    }
}

void build_heap(vector<int> &a) {
    for (int i = (a.size() + 1) / 2; i >= 0; --i) max_heapify(a, i);
}

void heap_sort(vector<int> &a) {
    build_heap(a);
    for (int i = a.size() - 1; i > 0; --i) {
        swap(a[i], a[0]);
        --heap_size;
        max_heapify(a, 0);
    }
}
