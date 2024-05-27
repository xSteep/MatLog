#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class SegmentTree {
public:
    SegmentTree(int n) {
        size = n;
        tree.resize(4 * n); // размер дерева отрезков: 4 * n
    }

    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        }
        else {
            int mid = (start + end) / 2;
            build(arr, 2 * node, start, mid);
            build(arr, 2 * node + 1, mid + 1, end);
            tree[node] = max(tree[2 * node], tree[2 * node + 1]);
        }
    }

    int query(int node, int start, int end, int left, int right) {
        if (start > right || end < left) {
            return INT_MIN;
        }
        else if (start >= left && end <= right) {
            return tree[node];
        }
        else {
            int mid = (start + end) / 2;
            int leftMax = query(2 * node, start, mid, left, right);
            int rightMax = query(2 * node + 1, mid + 1, end, left, right);
            return max(leftMax, rightMax);
        }
    }

    void update(int node, int start, int end, int idx, int value) {
        if (start == end) {
            tree[node] = value;
        }
        else {
            int mid = (start + end) / 2;
            if (idx <= mid) {
                update(2 * node, start, mid, idx, value);
            }
            else {
                update(2 * node + 1, mid + 1, end, idx, value);
            }
            tree[node] = max(tree[2 * node], tree[2 * node + 1]);
        }
    }

private:
    vector<int> tree; // массив дерева отрезков
    int size; // размер исходного массива
};

int main() {
    ifstream input("input.txt");
    int n;
    input >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        input >> arr[i];
    }

    SegmentTree tree(n);
    tree.build(arr, 1, 0, n - 1);

    int choice = 0;
    while (choice != 4) {
        cout << "1 Rmq(i, j)" << endl;
        cout << "2 Add1(i, D)" << endl;
        cout << "3 Add2(i, j, D)" << endl;
        cout << "4 Exit" << endl;

        cin >> choice;

        switch (choice) {
        case 1: {
            int i, j;
            cout << "Enter i, j: ";
            cin >> i >> j;
            int maxVal = tree.query(1, 0, n - 1, i - 1, j - 1);
            cout << "Max value: " << maxVal << endl;
            break;
        }
        case 2: {
            int i, D;
            cout << "Enter i, D: ";
            cin >> i >> D;
            int oldValue = arr[i - 1];
            int newValue = oldValue + D;
            tree.update(1, 0, n - 1, i - 1, newValue);
            arr[i - 1] = newValue;
            break;
        }
        case 3: {
            int i, j, D;
            cout << "Enter i, j, D: ";
            cin >> i >> j >> D;
            for (int k = i - 1; k <= j - 1; k++) {
                int oldValue = arr[k];
                int newValue = oldValue + D;
                tree.update(1, 0, n - 1, k, newValue);
                arr[k] = newValue;
            }
            break;
        }
        case 4: {
            break;
        }
        default: {
            cout << "Invalid choice" << endl;
        }
        }
    }

    return 0;
}
