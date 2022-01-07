#include <bits/stdc++.h>

// with all questions and suggestions write to the e-mail:
// ypodlesov@gmail.com

using namespace std;

int partition(vector<int> &a, int left, int right);
void quicksort(vector<int> &a, int left, int right);

int main() {

    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    quicksort(a, 0, n - 1);
    for (int i = 0; i < n; ++i) cout << a[i] << ' ';
    cout << endl;


    return 0;
}

int partition(vector<int> &a, int left, int right) {
    int x = a[right];
    int j = left - 1;
    for (int i = left; i < right; ++i) {
        if (a[i] <= x) {
            ++j;
            swap(a[i], a[j]);
        }
    }
    ++j;
    swap(a[j], a[right]);
    return j;
}

void quicksort(vector<int> &a, int left, int right) {
    if (left <= right) {
        int mid = partition(a, left, right);
        quicksort(a, left, mid - 1);
        quicksort(a, mid + 1, right);
    }
}
