//
// Created by xindong on 2/27/2023.
//

#include "dfs797.h"
#include "util.h"

vector<vector<int>> dfsTest(){
    vector<vector<int>> graph = {{4,3,1},{3,2,4},{3},{4},{}};
    vector<vector<int>> results;
    vector<int> path{0};
    int target = int(graph.size())-1;

    function<void(int, vector<int>&)> backtrack = [&](int currNode, vector<int>& path) {
        if (currNode == target) {
            results.push_back(vector(path));
            return;
        }
        for (int nextNode : graph[currNode]) {
            path.push_back(nextNode);
            backtrack(nextNode, path);
            path.pop_back();
        }
    };

    backtrack(0, path);
    return results;
}