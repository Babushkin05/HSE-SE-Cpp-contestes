#include <algorithm>
#include <cstdint>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>

struct Track {
  uint64_t id;
  int64_t rating;
};

inline bool operator<(Track first, Track second);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  uint64_t cnt = 1;

  std::priority_queue<Track> tracks;
  std::unordered_map<uint64_t, int64_t> music_data;
  std::unordered_map<std::string, uint64_t> map;
  std::string command;

  while (command != "EXIT") {
    std::cin >> command;
    if (command == "VOTE") {
      std::string user_ip;
      std::cin >> user_ip;
      uint64_t track_id = 0;
      std::cin >> track_id;
      int64_t score = 0;
      std::cin >> score;
      uint64_t time = 0;
      std::cin >> time;
      if (map.find(user_ip) != map.end()) {
        if (map[user_ip] + 600 > time) {
          std::cout << music_data[track_id] << "\n";
          continue;
        }
      }
      map[user_ip] = time;
      music_data[track_id] += score;
      tracks.push({track_id, music_data[track_id]});
      std::cout << music_data[track_id] << "\n";

    } else if (command == "GET") {
      Track max_track = {0, -1};
      if (!tracks.empty()) {
        max_track = tracks.top();
        tracks.pop();
      }
      while (!tracks.empty()) {
        if (music_data[max_track.id] != max_track.rating) {
          max_track = tracks.top();
          tracks.pop();
        } else {
          break;
        }
      }
      if (max_track.rating < 0 || (max_track.rating == 0 && max_track.id > cnt)) {
        while (true) {
          if (music_data.find(cnt) == music_data.end()) {
            music_data[cnt] = 0;
            max_track.id = cnt;
            max_track.rating = 0;
            break;
          }
          if (music_data[cnt] == 0) {
            max_track.id = cnt;
            max_track.rating = 0;
            break;
          }
          ++cnt;
        }
      }
      std::cout << max_track.id << " " << max_track.rating << "\n";
      music_data[max_track.id] = -1;
      tracks.push({max_track.id, -1});
    }
  }
  std::cout << "OK";
  return 0;
}

inline bool operator<(Track first, Track second) {
  return first.rating < second.rating || (first.rating == second.rating && first.id > second.id);
}