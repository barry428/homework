#include <iostream>
#include <string>
#include <map>
#include <cctype>

using namespace std;

int calcMass(const string& s) {
    map<char, int> conf = {{'H', 1},
                           {'C', 12},
                           {'N', 14},
                           {'O', 16},
                           {'F', 19},
                           {'P', 31},
                           {'S', 32},
                           {'K', 39}};

    int total = 0;
    int i = 0;

    while (i < s.size()) {
        char elem = s[i];
        int mass = conf[elem];
        int count = 0;

        // 检查下一个字符是否是数字，获取元素的数量
        if (i + 1 < s.size() && isdigit(s[i + 1])) {
            count = s[i + 1] - '0';
            i += 2; // 跳过元素和数量的字符
        } else {
            count = 1; // 没有数字则默认数量为 1
            i += 1;
        }

        // 计算当前元素的总质量
        total += mass * count;
    }

    return total;
}

int test_10() {
    int n;
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; ++i) {
        string s;
        getline(cin, s);
        cout << calcMass(s) << endl;
    }

    return 0;
}
