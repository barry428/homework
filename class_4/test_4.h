#include <algorithm>
#include <vector>
#include <iostream>

int test_4() {
    std::vector<int> numbers = {5, 2, 9, 1, 5, 6};
    std::sort(numbers.begin(), numbers.end());

    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;


    int nums[100] = {5, 2, 9, 1, 5, 6};
    std::sort(nums, nums + 6);
    for (int i = 0; i < 6; ++i) {
        std::cout << nums[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}