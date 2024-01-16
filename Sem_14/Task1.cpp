#include <iostream>
#include <vector>
#include <unordered_map>

std::vector<int> twoSum(std::vector<int>& nums, int target) 
{ 
    std::unordered_map<int, int> map;

    for (int i = 0; i < nums.size(); i++) 
    {
        int completement = target - nums[i];

        if (map.find(completement) == map.end())
            map[nums[i]] = i;
        else
            return { map[completement], i };
    }

    return {};
}

int main()
{
   
}
