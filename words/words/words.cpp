#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#define DIFFERENCE ('A' - 'a')
using namespace std;

bool comp(const pair<string, string>& a, const pair<string, string>& b) { 
    return a.second < b.second;
}

int main() {
    vector <pair<string, string>> words; 
    string str;

    while (getline(cin, str, '\n')) {
        pair<string, string> word; 
        word.first = str;
        word.second = edit(str);
        sort(word.second.begin(), word.second.end()); 
        words.push_back(word);
    }

    sort(words.begin(), words.end(), comp);
    vector <int> indeces; 
    int Count = 0, MaxCount = 0, n = words.size();
    for (int i = 1; i < n; i++) {
        if (words[i - 1].second == words[i].second) Count++;
        else {
            if (Count > MaxCount) {
                MaxCount = Count;
                indeces.clear();
                indeces.push_back(i - 1);
            }
            else if (Count == MaxCount) indeces.push_back(i - 1);
            Count = 0;
        }
    }

    if (Count > MaxCount) {  
        MaxCount = Count;
        indeces.clear();
        indeces.push_back(n - 1);
    }

    else if (Count == MaxCount) indeces.push_back(n - 1);
    bool first = 1;
    for (int index : indeces) { 
        if (!first) cout << endl << "___" << endl;
        else first = 0;
        for (int i = 0; i <= MaxCount; i++) {
            if (i != 0) cout << endl;
            cout << words[index - i].first;
        }
    }
    return 0;
}