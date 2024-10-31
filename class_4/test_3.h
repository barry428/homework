#include <iostream>
#include <map>
#include <string>

int test_3() {
    // 创建一个 map 容器，存储员工的姓名和年龄
    std::map<std::string, int> employees;

    // 插入员工信息
    employees["Alice"] = 30;
    employees["Bob"] = 25;
    employees["Charlie"] = 35;

    auto res = employees.find("Bob");
    if (employees.find("Bob") != employees.end()) {
        std::cout << "Find Bob: " << employees["Bob"];
    }

    // 遍历 map 并打印员工信息
    for (auto& entry : employees) {
        std::cout << "Name: " << entry.first << ", Age: " << entry.second << std::endl;
    }

    return 0;
}