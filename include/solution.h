#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>

class Solution {
public:
    Solution(int k, const std::vector<int> &v_colors);

    static int get_cost(int k, const std::vector<int> &color_count);
    void print_solution() const;
    bool operator<(const Solution &other) const;
    std::vector<int> v_colors;
    int cost;
private:
    int k;
    std::vector<int> color_use;

    virtual void calculate_cost();
};
#endif
