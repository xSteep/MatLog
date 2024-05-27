#include <iostream>
#include <fstream>

using namespace std;

const int MAXN = 100005;

int n, m;
int x, y;

int sg[MAXN][2];

void precalc() {
    sg[1][0] = sg[1][1] = 0;
    for (int i = 2; i <= n; i++) {
        sg[i][0] = sg[i - 1][1] + 1;
        sg[i][1] = sg[i - 1][0] + 1;
    }
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    fin >> m;
    while (m--) {
        fin >> n >> x >> y;
        precalc();
        int ans = sg[x][y] ^ sg[n][n] ^ sg[x][n] ^ sg[n][y];
        if (ans == 0) {
            fout << "2\n";
        }
        else {
            fout << "1\n";
        }
    }

    fin.close();
    fout.close();
    return 0;
}
