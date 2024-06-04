#include <iostream>
#include <vector>

int main() {
  size_t n = 0;
  size_t k = 0;
  std::cin >> n >> k;
  std::vector<std::vector<size_t>> g(n + 1);

  for (size_t it = 0; it < k; ++it) {
    size_t op_t = 0;
    std::cin >> op_t;
    if (op_t == 1) {
      size_t u = 0;
      size_t v = 0;
      std::cin >> u >> v;
      g[u].push_back(v);
      g[v].push_back(u);
    } else {
      size_t u = 0;
      std::cin >> u;
      for (size_t i = 0; i < g[u].size(); i++) {
        std::cout << g[u][i] << ' ';
      }
      std::cout << '\n';
    }
  }

  return 0;
}