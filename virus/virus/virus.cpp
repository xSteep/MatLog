#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstring>
#include <chrono>
using namespace std;

const int MAXN = 10000;
const int MAXM = 10;
const int dx[] = { 0, 1, 0, -1 };
const int dy[] = { 1, 0, -1, 0 };

int n, m;
bool virus[MAXN][MAXN];
int dist[MAXN][MAXN];
vector<pair<int, int>> viruses;

bool inRange(int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= n;
}

void bfs(int vx, int vy) {
    queue<pair<int, int>> q;
    q.push(make_pair(vx, vy));
    dist[vx][vy] = 0;
    while (!q.empty()) {
        pair<int, int> cur = q.front();
        q.pop();
        int x = cur.first, y = cur.second;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (inRange(nx, ny) && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push(make_pair(nx, ny));
            }
        }
    }
}

int main(int argc, char* argv[]) {
    auto start_time = chrono::high_resolution_clock::now();
    if (argc != 3)
    {
        cout << "Invalid arguments count\n"
            << "Usage: copyfile.exe <input file> <output file>\n";
        return 1;
    }

    ifstream fin(argv[1]);
    if (!fin.is_open()) {
        cerr << "Error opening input file\n";
        return 1;
    }
    fin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y;
        fin >> x >> y;
        virus[x][y] = true;
        viruses.push_back(make_pair(x, y));
    }
    fin.close();

    memset(dist, -1, sizeof(dist));
    for (int i = 0; i < m; i++) {
        bfs(viruses[i].first, viruses[i].second);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (!virus[i][j]) {
                int minDist = n * n;
                for (int k = 0; k < m; k++) {
                    minDist = min(minDist, dist[viruses[k].first][viruses[k].second] + abs(viruses[k].first - i) + abs(viruses[k].second - j));
                }
                ans = max(ans, minDist);
            }
        }
    }

    ofstream fout(argv[2]);
    if (!fout.is_open()) {
        cerr << "Error opening output file\n";
        return 1;
    }
    fout << ans << endl;
    fout.close();

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
    cout << "Time taken: " << duration << " microseconds" << endl;

    return 0;
}
