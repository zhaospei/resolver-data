#include <iostream>
#include <cassert>
#include <random>
#include <chrono>
using namespace std;
// Name of file
const string NAME = "contest";
// Number of users
const int NUSER = 12;
// Number of problems
const int NPROBLEM = 3;
// Max of Point
// Time distance
const int TIME_DISTANCE = 20;
// Range of subtasks
const int MIN_SUBTASK = 3;
const int MAX_SUBTASK = 6;
// Time 
int cur_time = 0;

mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());
#define rand rd

// Random [l, h]
long long Rand(long long l, long long h) {
    assert(l <= h);
    return l + rd() * 1LL * rd() % (h - l + 1);
}
long long RandPoint(int point_zero, int point_ac, int point_max) {
    int point_part = 100 - point_ac - point_zero;
    int value = Rand(0, 100);
    if (value <= point_zero) {
        return 0;
    } else {
        if (value <= point_ac + point_zero) {
            return point_max;
        } else {
            return Rand(1, point_max - 1);
        }
    }
}
int nsubtask[NPROBLEM + 1][7];

int main() {
    srand(time(NULL));
    freopen((NAME + ".json").c_str(), "w", stdout);
    cout << "{\n";
    int subtasks[MAX_SUBTASK + 1];
    for (int i = 1; i <= NPROBLEM; i++) {
        subtasks[i] = Rand(MIN_SUBTASK, MAX_SUBTASK);
    }
    cout <<"  \"problem_sub\":[";
    for (int i = 1; i <= NPROBLEM; i++) {
        if (i < NPROBLEM) {
            cout << subtasks[i] << ", ";
        } else {
            cout << subtasks[i];
        }
    }
    cout <<"],\n";
    cout <<"  \"problems\":{\n";
    for (int id = 1; id <= NPROBLEM; id++) {
        cout << "    \"" << id << "\":{" << "\n";
        int cur_point = 100;
        for (int subtask = 1; subtask <= subtasks[id]; subtask++) {
            int point;
            if (subtask < subtasks[id]) {
                point = Rand(10, cur_point - 10 * (subtasks[id] - subtask + 1));
                nsubtask[id][subtask] = point;
                cur_point -= point;
                cout << "      \"" << subtask << "\":" << point << ",\n";
            } else {
                point = cur_point;
                nsubtask[id][subtask] = point;
                cout << "      \"" << subtask << "\":" << point << "\n";
            }
        }
        if (id < NPROBLEM) {
            cout << "    },\n";
        } else {
            cout << "    }\n"; 
        }
    }
    cout << "  },\n";
    cout <<"  \"user_id\":{\n";
    for (int id = 1; id <= NUSER; id++) {
        cout << "    \"" << id << "\":{ " << "\n";
        cout << "      \"username\":\"user" << id << "\",\n";
        cout << "      \"name\":\"Nguyen Van A" << char(97 + id - 1) << "\",\n";
        cout << "      \"school\":\"School " << char(65 + id - 1) << "\",\n";
        cout << "      \"problems\":{\n";
        int cnt = 0;
        for (int j = 1; j <= NPROBLEM; j++) {
            int pass = Rand(1, 20 - j * 5);
            if (pass == 1) continue;
            cnt++;
            if (cnt > 1) {
                cout << "        },\n";
            }
            cout << "        \"" << j << "\":{\n";
            cout << "          \"points\":{\n";
            int nsub = 0;
            for (int i = 1; i <= 6; i++) {
                if (nsubtask[j][i] == 0) {
                    break;
                }
                nsub = i;
            }
            int frozen_point[7];
            for (int i = 1; i <= nsub; i++) {
                int subpoint = RandPoint(30 - (6 - i) * 5, 70 - (i - 1) * 10, nsubtask[j][i]);
                while (true) {
                    frozen_point[i] = RandPoint(30 - (6 - i) * 5, 30 - (i - 1) * 5, nsubtask[j][i]);
                    if (subpoint >= frozen_point[i]) break;
                }
                if (i < nsub) {
                    cout << "            \""<< i << "\":" << subpoint << ",\n";
                } else {
                    cout << "            \""<< i << "\":" << subpoint << "\n";
                }
            }
            cout << "          },\n";
            cout << "          \"frozen_points\":{\n";
            for (int i = 1; i <= nsub; i++) {
                if (i < nsub) {
                    cout << "            \""<< i << "\":" << frozen_point[i] << ",\n";
                } else {
                    cout << "            \""<< i << "\":" << frozen_point[i] << "\n";
                }
            }
            cout << "          }\n";
        }
        if (cnt > 0) cout << "        }\n";
        cout << "      }\n";
        if (id < NUSER) {
            cout << "    },\n";
        } else {
            cout << "    }\n";
        }
    }
    cout <<"  }\n";
    cout << "}\n";
    return 0;
}