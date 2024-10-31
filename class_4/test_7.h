#include<iostream>
#include<string>

using namespace std;

int test_7() {
    string str = "abcdefg";
    for (auto c: str) {
        cout << c << " ";
    }
    cout << endl;

    for(auto it = str.begin(); it != str.end(); it++){
        cout << *(it+1) << " ";
    }
    cout << endl;
    return 0;
}