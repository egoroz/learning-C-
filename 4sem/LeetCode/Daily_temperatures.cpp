#include <iostream>
#include <vector>
#include <stack>

class Solution {
public:
    std::vector<int> dailyTemperatures(std::vector<int>& temperatures) {
        std::stack<std::pair<int, size_t>> storage;
        std::vector<int> result(temperatures.size(), 0);

        storage.push({temperatures[0], 0});
        for(size_t i = 1; i < temperatures.size(); ++i){
            if(!storage.empty() && storage.top().first < temperatures[i]) {
                while(!storage.empty() && storage.top().first < temperatures[i]){
                    result[storage.top().second] = i - storage.top().second;
                    storage.pop();
                }
                storage.push({temperatures[i], i});
            }
            else storage.push({temperatures[i], i});
        }
        return result;
    }
};

int main(){
    Solution A;
    std::vector<int> temp = {73,74,75,71,69,72,76,73};
    std::vector<int> res = A.dailyTemperatures(temp);
    for(size_t i = 0; i < res.size(); ++i){
        std::cout << res[i] << " ";
    }
}