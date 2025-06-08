// Copyright 2022 NNTU-CS
#ifndef TREE_H
#define TREE_H

#include <vector>
#include <memory>

class PMTree {
 private:
    struct Node {
        char value;
        std::vector<std::shared_ptr<Node>> children;
        Node(char v) : value(v) {}
    };

    std::shared_ptr<Node> root;
    std::vector<char> elements;
    size_t factorial(size_t n) const;

 public:
    explicit PMTree(const std::vector<char>& in);
    std::vector<std::vector<char>> getAllPerms() const;
    std::vector<char> getPermByIndex(size_t index) const;
    std::vector<char> getPermByTraversal(size_t index) const;
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // TREE_H
