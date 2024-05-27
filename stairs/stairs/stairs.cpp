#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Person {
    int time;
    int steps;
    int index;
};

bool compareByTime(const Person& a, const Person& b) {
    return a.time < b.time;
}

bool compareByIndex(const Person& a, const Person& b) {
    return a.index < b.index;
}

int main() {
    std::ifstream input("input.txt");
    std::ofstream output("output.txt");

    int N;
    input >> N;

    std::vector<Person> people(N);

    for (int i = 0; i < N; i++) {
        input >> people[i].time >> people[i].steps;
        people[i].index = i;
    }

    std::sort(people.begin(), people.end(), compareByTime);

    std::vector<int> timeToFinish(N);

    for (int i = 0; i < N; i++) {
        timeToFinish[people[i].index] = people[i].time * people[i].steps;
    }

    for (int i = 1; i < N; i++) {
        if (timeToFinish[i] < timeToFinish[i - 1]) {
            timeToFinish[i] = timeToFinish[i - 1];
        }
    }

    std::sort(people.begin(), people.end(), compareByIndex);

    for (int i = 0; i < N; i++) {
        output << timeToFinish[i] << std::endl;
    }

    input.close();
    output.close();

    return 0;
}
