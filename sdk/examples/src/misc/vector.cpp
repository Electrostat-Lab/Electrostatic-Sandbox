#include <iostream>
#include <vector>

int main() {
    // 1. Initialize vector with 10 integers
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // 2. Insert 99 in the middle
    std::vector<int>::iterator mid = vec.begin() + vec.size() / 2;
    vec.insert(mid, 99);

    // 3. Delete the second element (index 1)
    vec.erase(vec.begin() + 1);

    // Print the final vector
    for (int val : vec) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    return 0;
}