#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class FenwickTree {
public:
    FenwickTree(int n) {
        tree.resize(n + 1);
    }

    void update(int i, int delta) {
        while (i < tree.size()) {
            tree[i] += delta;
            i += i & (-i);
        }
    }

    int query(int i) {
        int sum = 0;
        while (i > 0) {
            sum += tree[i];
            i -= i & (-i);
        }
        return sum;
    }

private:
    vector<int> tree;
};

int main() {
    ifstream input("input.txt");
    int n;
    input >> n;

    FenwickTree tree(n);

    for (int i = 0; i < n; i++) {
        int x;
        input >> x;
        tree.update(i + 1, x);
    }

    int choice = 0;
    while (choice != 5) {
        cout << "1 output" << endl;
        cout << "2 Rsq(i, j)" << endl;
        cout << "3 Add(i, v)" << endl;
        cout << "4 Update(i, v)" << endl;
        cout << "5 Exit" << endl;

        cin >> choice;

        switch (choice) {
        case 1: {
            for (int i = 0; i < n; i++) {
                cout << tree.query(i + 1) - tree.query(i) << " ";
            }
            cout << endl;
            break;
        }
        case 2: {
            int i, j;
            cin >> i >> j;
            cout << tree.query(j + 1) - tree.query(i) << endl;
            break;
        }
        case 3: {
            int i, v;
            cin >> i >> v;
            tree.update(i + 1, v);
            break;
        }
        case 4: {
            int i, v;
            cin >> i >> v;
            int delta = v - (tree.query(i + 1) - tree.query(i));
            tree.update(i + 1, delta);
            break;
        }
        case 5: {
            break;
        }
        default: {
            cout << "Invalid choice" << endl;
        }
        }
    }

    return 0;
}
