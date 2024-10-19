#include <iostream>
#include <map>
#include "custom_allocator.hpp"
#include "custom_container.hpp"

int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

int main() {
    std::map<int, int> standard_map;
    for (int i = 0; i < 10; ++i) {
        standard_map[i] = factorial(i);
    }

    std::cout << "Standard map elements:\n";
    for (const auto& [key, value] : standard_map) {
        std::cout << key << " " << value << "\n";
    }

    // std::map<int, int> с кастомным аллокатором
    std::map<int, int, std::less<int>, CustomAllocator<std::pair<const int, int>>> custom_map;

    for (int i = 0; i < 10; ++i) {
        custom_map[i] = factorial(i);
    }

    // Вывод элементов std::map с кастомным аллокатором
    std::cout << "Custom allocator map elements:\n";
    for (const auto& [key, value] : custom_map) {
        std::cout << key << " " << value << "\n";
    }

    // Свой контейнер для хранения значений int
    CustomContainer<int> standard_container;
    for (int i = 0; i < 10; ++i) {
        standard_container.push_back(i);
    }

    // Вывод элементов своего контейнера
    std::cout << "Standard custom container elements:\n";
    for (int value : standard_container) {
        std::cout << value << "\n";
    }

    // Свой контейнер с кастомным аллокатором
    CustomContainer<int, CustomAllocator<int>> custom_container;
    for (int i = 0; i < 10; ++i) {
        custom_container.push_back(i);
    }

    // Вывод элементов своего контейнера с кастомным аллокатором
    std::cout << "Custom allocator container elements:\n";
    for (int value : custom_container) {
        std::cout << value << "\n";
    }

    return 0;
}
