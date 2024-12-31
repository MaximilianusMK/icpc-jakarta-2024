#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>
#include <set>

void ac() {
  std::cout << "AC\n";
  exit(0);
}

void wa(std::string reason="") {
  std::cout << "WA\n";
  if (reason != "") {
    std::cout << reason << '\n';
  }
  exit(0);
}

int readInt(std::ifstream &ifs) {
  int ret;
  if (!(ifs >> ret)) wa();
  return ret;
}

long long readLongLong(std::ifstream &ifs) {
  long long ret;
  if (!(ifs >> ret)) wa();
  return ret;
}

bool eof(std::ifstream &ifs) {
  std::string dummy;
  if (ifs >> dummy) return false;
  return true;
}

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cerr << "Must be run with arguments [input-file] [output-file] [contestant-output]\n";
    exit(0);
  }

  std::ifstream inp(argv[1]);
  std::ifstream out(argv[2]);
  std::ifstream con(argv[3]);

  int K = readInt(inp);
  int N = readInt(con);
  int M = readInt(con);

  if (N == -1) {
    int judgeN = readInt(out);

    if (M != -1) wa();
    if (judgeN != -1) wa();
    if (!eof(con)) wa();

    ac();
  }
  int maxN = 32768;
  if (!(1 <= N && N <= maxN)) wa();
  
  int maxM = 65536;
  if (!(1 <= M && M <= maxM)) wa();

  std::vector<std::vector<int>> adj(N+1);
  std::set<std::pair<int, int>> seen;

  for (int i = 0 ; i < M ; i++) {
    int u = readInt(con);
    int v = readInt(con);
    if (u > v) std::swap(u, v);

    if (!(1 <= u && u <= N)) wa();
    if (!(1 <= v && v <= N)) wa();
    if (u == v) wa();
    if (seen.count({u, v})) wa();

    seen.insert({u, v});
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  if (!eof(con)) wa();

  int counter = 0;
  std::vector<int> visited(N+1, 0);
  std::stack<int> st;

  st.push(1);
  while (!st.empty()) {
    int now = st.top();
    st.pop();

    counter += adj[now].size();
    if (counter > K) wa();

    // if this is commented, we get the original algorithm
    // but it will be O(NM) instead of O(N+M)
    // by the way, with this handling, the algorithm became a legit DFS
    if (visited[now]) {
      continue;
    }

    visited[now] = 1;
    sort(adj[now].begin(), adj[now].end());
    for (int nex : adj[now]) {
      if (!visited[nex]) {
        st.push(nex);
      }
    }
  }

  if (counter != K) wa();
  ac();
}
