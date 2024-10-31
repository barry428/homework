#include <iostream>
#include <string>
#include <vector>

using namespace std;

string decode(const string& msg) {
    string decoded;
    string curNum;

    for (char ch: msg) {
        if (ch == '#' || ch == '-') {
            if (!curNum.empty()) {
                int num = stoi(curNum);
                decoded += (char) ('A' + num - 1);
                curNum.clear();
            }

            if (ch == '#'){
                decoded += ' ';
            }
        } else if (isdigit(ch)) {
            curNum += ch;
        }
    }

    // 处理字符串末尾可能残留的最后一个数字
    if (!curNum.empty()) {
        int num = stoi(curNum);
        decoded += (char) ('A' + num - 1);
    }

    return decoded;
}

int test_9() {
    int C;
    cin >> C;
    cin.ignore();

    vector<string> results;
    for (int i = 0; i < C; ++i) {
        string msg;
        getline(cin, msg);
        cout << decode(msg) << endl;
    }
    return 0;
}

/*
4
9#23-9-12-12#19-20-5-1-12#1-20#12-5-1-19-20#15-14-5#10-5-23-5-12
1-14-4#12-5-1-22-5#20-8-5#13-21-19-5-21-13#9-14#20#13-9-14-21-20-5-19
1-6-20-5-18#20-8-5#15-16-5-14-9-14-7#15-6#20-8-5#5-24-8-9-2-9-20-9-15-14
7-15-15-4#12-21-3-11
 */