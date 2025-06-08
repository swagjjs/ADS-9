// Copyright 2022 NNTU-CS

#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "tree.h"

void runExperiment() {
    std::vector<int> sizes = {3, 4, 5, 6, 7, 8, 9, 10};
    std::random_device rd;
    std::mt19937 gen(rd());

    for (int n : sizes) {
        // Prepare elements
        std::vector<char> elements;
        for (int i = 0; i < n; ++i) {
            elements.push_back('1' + i);
        }

        // Create tree
        PMTree tree(elements);

        // Generate random permutation number
        std::uniform_int_distribution<> dis(1, tree.getAllPerms().size());
        int random_num = dis(gen);

        // Measure time for getAllPerms
        auto start = std::chrono::high_resolution_clock::now();
        auto all_perms = tree.getAllPerms();
        auto end = std::chrono::high_resolution_clock::now();
        auto all_perms_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        // Measure time for getPerm1
        start = std::chrono::high_resolution_clock::now();
        auto perm1 = getPerm1(tree, random_num);
        end = std::chrono::high_resolution_clock::now();
        auto perm1_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        // Measure time for getPerm2
        start = std::chrono::high_resolution_clock::now();
        auto perm2 = getPerm2(tree, random_num);
        end = std::chrono::high_resolution_clock::now();
        auto perm2_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        // Output results
        std::cout << "n = " << n << ":\n";
        std::cout << "  getAllPerms time: " << all_perms_time << " μs\n";
        std::cout << "  getPerm1 time:    " << perm1_time << " μs\n";
        std::cout << "  getPerm2 time:    " << perm2_time << " μs\n\n";
    }
}

int main() {
    // Example usage
    std::vector<char> in = {'1', '2', '3'};
    PMTree tree(in);

    // Get all permutations
    auto perms = getAllPerms(tree);
    std::cout << "All permutations:\n";
    for (const auto& perm : perms) {
        for (char c : perm) {
            std::cout << c;
        }
        std::cout << "\n";
    }

    // Get specific permutations
    std::cout << "\nPermutation 1: ";
    auto result1 = getPerm1(tree, 1);
    for (char c : result1) std::cout << c;
    std::cout << "\n";

    std::cout << "Permutation 2: ";
    auto result2 = getPerm2(tree, 2);
    for (char c : result2) std::cout << c;
    std::cout << "\n";

    // Run experiment
    std::cout << "\nRunning experiment...\n";
    runExperiment();

    return 0;
}
