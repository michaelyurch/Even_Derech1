#ifndef SOLUTION_H
#define SOLUTION_H

#include <string>
#include <vector>

class Solution
{
	std::vector<std::string> optimalPath;
public:
	Solution(std::vector<std::string> _optimalPath) {
        this->optimalPath = _optimalPath;
    }    
    std::vector<std::string> getOptimalPath() {
        return this->optimalPath;
    }
};

#endif
