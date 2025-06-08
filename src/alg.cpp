// Copyright 2022 NNTU-CS
#include "tree.h"
#include <algorithm>
#include <stdexcept>

PMTree::PMTree(const std::vector<char>& in) : elements(in) {
    if (in.empty()) return;
    std::vector<char> sorted = in;
    std::sort(sorted.begin(), sorted.end());
    elements = sorted;
}

size_t PMTree::factorial(size_t n) const {
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

std::vector<std::vector<char>> PMTree::getAllPerms() const {
    std::vector<std::vector<char>> result;
    if (elements.empty()) return result;

    std::vector<char> current;
    std::vector<bool> used(elements.size(), false);

    std::function<void()> backtrack = [&]() {
        if (current.size() == elements.size()) {
            result.push_back(current);
            return;
        }

        for (size_t i = 0; i < elements.size(); ++i) {
            if (!used[i]) {
                used[i] = true;
                current.push_back(elements[i]);
                backtrack();
                current.pop_back();
                used[i] = false;
            }
        }
    };

    backtrack();
    return result;
}

std::vector<char> PMTree::getPermByIndex(size_t index) const {
    if (elements.empty() || index == 0 || index > factorial(elements.size())) {
        return {};
    }

    std::vector<char> remaining = elements;
    std::vector<char> result;
    index--;  // convert to 0-based index

    for (size_t i = elements.size(); i > 0; --i) {
        size_t f = factorial(i - 1);
        size_t pos = index / f;
        result.push_back(remaining[pos]);
        remaining.erase(remaining.begin() + pos);
        index %= f;
    }

    return result;
}

std::vector<char> PMTree::getPermByTraversal(size_t index) const {
    auto all = getAllPerms();
    if (index == 0 || index > all.size()) {
        return {};
    }
    return all[index - 1];
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    return tree.getAllPerms();
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    if (num <= 0) return {};
    return tree.getPermByTraversal(static_cast<size_t>(num));
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    if (num <= 0) return {};
    return tree.getPermByIndex(static_cast<size_t>(num));
}
