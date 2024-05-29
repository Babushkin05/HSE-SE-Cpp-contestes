#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string>
GetRoute(std::vector<std::vector<std::string> > flights) {
  std::map<std::string, std::vector<std::string> > mp;
  std::map<std::string, bool> visited;

  for (auto v : flights) {
    mp[v[0]].push_back(v[1]);
    mp[v[1]].push_back(v[0]);
    visited[v[0]] = false;
    visited[v[1]] = false;
  }
  std::string cur_city;
  for (auto &item : mp) {
    if (item.second.size() == 1) {
      cur_city = item.first;
    }
  }
  std::vector<std::string> ans;
  ans.push_back(cur_city);
  visited[cur_city] = true;
  for (int i = 0; i < flights.size(); i++) {
    if (visited[mp[cur_city][0]]) {
      cur_city = mp[cur_city][1];
    } else {
      cur_city = mp[cur_city][0];
    }
    visited[cur_city] = 1;
    ans.push_back(cur_city);
  }
  return ans;
}

int maxOnes(const std::vector<int>& nums){
  int ans = 0;
  int lastOnes = 0;
  int curOnes = 0;
  bool f = true;
  for(int i=0;i<nums.size();++i){
    if(nums[i]==1){
      ++curOnes;
      f = true;
      ans = std::max(ans,lastOnes+curOnes);
    }
    else{
      if(f){
        f = false;
        lastOnes = curOnes;
        curOnes = 0;
      }
      else{
        lastOnes = 0;
      }
    }
  }

  return ans;
}

double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
  int l=0;
  int r = nums1.size() + nums2.size() +1;
  while(l+1<r){
    int m = (l+r)/2;
    if(std::upper_bound(nums1.begin(), nums1.end(),m) + std::upper_bound(nums2.begin(), nums2.end(),m)< (nums1.size()+nums2.size())/2){

    }
  }
}

int main() {

  std::vector<int> v{1, 1, 0, 0, 1};
  std::cout<< maxOnes(v);

}