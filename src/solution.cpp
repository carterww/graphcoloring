#include "solution.h"
#include "colors.h"

#include <iostream>

Solution::Solution(int k, const std::vector<int> &v_colors) {
    this->k = k;
    this->v_colors = std::vector<int>(v_colors);
    this->color_use.resize(k + 1, 0);
    for (int i = 0; i < v_colors.size(); i++) {
        this->color_use[v_colors[i]]++;
    }
    this->calculate_cost();
}


Solution::Solution(int k, const std::vector<int> &v_colors, int cost, const std::vector<int> &color_count) {
    this->k = k;
    this->v_colors = std::vector<int>(v_colors);
    this->color_use = std::vector<int>(color_count);
    this->cost = cost;
}

int Solution::get_cost(int k, const std::vector<int> &color_count) {
    int cost = 0;
    for (int i = 1; i < k; i++) {
        cost += abs(color_count[i] - color_count[i + 1]);
    }
    return cost;
}

void Solution::calculate_cost() {
    this->cost = 0;
    for (int i = 1; i < this->color_use.size() - 1; i++) {
        this->cost += abs(this->color_use[i] - this->color_use[i + 1]);
    }
}

bool Solution::operator<(const Solution &other) const {
    return this->cost < other.cost;
}

void Solution::print_solution() const {
    std::cout << "(";
    for (int i = 1; i < this->color_use.size() - 1; i++) {
        std::cout << this->color_use[i] << ",";
    }
    std::cout << this->color_use[this->color_use.size() - 1] << ")" << std::endl;
    std::vector<std::string> color_uses(this->k + 1, "");
    for (int i = 1; i < color_uses.size(); i++) {
        color_uses[i] += COLORS[i];
        int str_len = color_uses[i].length();
        for (int j = 0; j < 10 - str_len; j++) {
            color_uses[i] += " ";
        }
        color_uses[i] += ": ";
    }
    int *has_added = new int[this->k + 1] {0};
    for (int i = 0; i < this->v_colors.size(); i++) {
        if (has_added[this->v_colors[i]] == 0) {
            color_uses[this->v_colors[i]] += std::to_string(i);
            has_added[this->v_colors[i]] = 1;
        } else {
            color_uses[this->v_colors[i]] += ", ";
            color_uses[this->v_colors[i]] += std::to_string(i);
        }
    }
    delete[] has_added;
    for (int i = 1; i < color_uses.size(); i++) {
        std::cout << color_uses[i] << std::endl;
    }
}
