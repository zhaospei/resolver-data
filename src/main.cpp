#include <iostream>
#include <cassert>
#include <random>
#include <chrono>
using namespace std;
// Name of file
const string NAME = "data-submissions";
// Number of data values
const int NDATA = 100;
// Number of users
const int NUSER = 10;
// Number of problems
const int NPROBLEM = 6;
// Max of Point
const int POINT_MAX = 100;
// Time distance
const int TIME_DISTANCE = 20;
// Time 
int cur_time = 0;

mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());
#define rand rd

// Random [l, h]
long long Rand(long long l, long long h) {
    assert(l <= h);
    return l + rd() * 1LL * rd() % (h - l + 1);
}
long long RandPoint(int point_zero, int point_ac) {
    int point_part = 100 - point_ac - point_zero;
    int value = Rand(0, 100);
    if (value <= point_zero) {
        return 0;
    } else {
        if (value <= point_ac + point_zero) {
            return POINT_MAX;
        } else {
            return Rand(1, 99);
        }
    }
}

int main() {
    srand(time(NULL));
    freopen((NAME + ".txt").c_str(), "w", stdout);
    cout <<"    \"solutions\":{\n";
    for (int id = 1; id <= NDATA; id++) {
        cout << "       \"" << id << "\":{" << "\n";
        cout << "         \"user_id\":" << Rand(1, NUSER) << ",\n";
        cout << "         \"problem_index\":" << Rand(1, NPROBLEM) << ",\n";
        cout << "         \"point\":" << RandPoint(20, 20) << ",\n";
        cur_time = cur_time + Rand(0, TIME_DISTANCE);
        cout << "         \"submitted_seconds\":" << cur_time << "\n";
        cout << "       },\n";
    }
    return 0;
}