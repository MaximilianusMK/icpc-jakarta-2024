#include <bits/stdc++.h>
using namespace std;

const int N = 200;
string cells[N + 5];

vector<int> lst[4 * N * N + 5];
int visited[4 * N * N + 5]; 

// North, west, south, east direction
char dir[] = "NWSE";
int dy[] = {-1, 0, 1, 0};
int dx[] = {0, -1, 0, 1};

inline int newCoord(int y, int x, int c, char d) {
  int flatten_cell = 4 * (y * c + x);
  for (int i = 0; i < 4; i++) {
    if (d == dir[i]) {
      flatten_cell += i;
      return flatten_cell;
    }
  }
  // This will cause crash.
  return -1;
}

inline int originalCell(int u) {
  return u / 4;
}

inline bool isMirrorCell(int u, int c) {
  u = originalCell(u);
  return cells[u / c][u % c] != '.';
}

void constructGraph(int r, int c) {
  // Construct the graph within the cell.
  for (int y = 0; y < r; y++) {
    for (int x = 0; x < c; x++) {
      int n = newCoord(y, x, c, 'N');
      int w = newCoord(y, x, c, 'W');
      int s = newCoord(y, x, c, 'S');
      int e = newCoord(y, x, c, 'E');
      if (cells[y][x] == '.') {
        // Connect north to south (and vice versa).
        lst[n].push_back(s);
        lst[s].push_back(n);
        // Connect west to east (and vice versa).
        lst[w].push_back(e);
        lst[e].push_back(w);
      } else if (cells[y][x] == '/') {
        // Connect north to west (and vice versa).
        lst[n].push_back(w);
        lst[w].push_back(n);
        // Connect south to east (and vice versa).
        lst[s].push_back(e);
        lst[e].push_back(s);
      } else { // Cells[y][x] == '\\'
        // Connect north to east (and vice versa).
        lst[n].push_back(e);
        lst[e].push_back(n);
        // Connect south to west (and vice versa).
        lst[s].push_back(w);
        lst[w].push_back(s);
      }
    }
  }

  // Construct the graph based on adjacent cell.
  for (int y = 0; y < r; y++) {
    for (int x = 0; x < c; x++) {
      for (int k = 0; k < 4; k++) {
        int ny = y + dy[k];
        int nx = x + dx[k];
        if (ny < 0 || nx < 0 || ny >= r || nx >= c) {
          // Out of bounds.
          continue;
        }
        int u = newCoord(y, x, c, dir[k]);
        int v = newCoord(ny, nx, c, dir[(k + 2) % 4]); // other side
        lst[u].push_back(v);
      }
    }
  }
}

int countNumMirrors(int r, int c) {
  int num_mirrors = 0;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (cells[i][j] != '.') {
        num_mirrors++;
      }
    }
  }
  return num_mirrors;
}

unordered_set<int> hit_mirrors;

void dfs(int u, const int start, const int c) {
  visited[u] = start;
  if (isMirrorCell(u, c)) {
    hit_mirrors.insert(originalCell(u));
  }
  for (auto v: lst[u]) {
    if (visited[v] == start) continue;
    dfs(v, start, c);
  }
}

vector<string> solve(int r, int c) {
  vector<string> answers;
  int num_mirrors = countNumMirrors(r, c);
  memset(visited, -1, sizeof visited);

  // Start from north
  for (int i = 0; i < c; i++) {
    int start = newCoord(0, i, c, 'N');
    hit_mirrors.clear();
    dfs(start, start, c);
    if (hit_mirrors.size() == num_mirrors) {
      answers.push_back("N" + to_string(i + 1));
    }
  }

  // Start from west
  for (int i = 0; i < r; i++) {
    int start = newCoord(i, 0, c, 'W');
    hit_mirrors.clear();
    dfs(start, start, c);
    if (hit_mirrors.size() == num_mirrors) {
      answers.push_back("W" + to_string(i + 1));
    }
  }

  // Start from south
  for (int i = 0; i < c; i++) {
    int start = newCoord(r - 1, i, c, 'S');
    hit_mirrors.clear();
    dfs(start, start, c);
    if (hit_mirrors.size() == num_mirrors) {
      answers.push_back("S" + to_string(i + 1));
    }
  }

  // Start from east
  for (int i = 0; i < r; i++) {
    int start = newCoord(i, c - 1, c, 'E');
    hit_mirrors.clear();
    dfs(start, start, c);
    if (hit_mirrors.size() == num_mirrors) {
      answers.push_back("E" + to_string(i + 1));
    }
  }

  sort(answers.begin(), answers.end());
  return answers;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int r, c;
  cin >> r >> c;
  for (int i = 0; i < r; i++) {
    cin >> cells[i];
  }

  constructGraph(r, c);
  vector<string> answers = solve(r, c);
  cout << answers.size() << endl;
  if (answers.size() != 0) {
    for (int i = 0; i < answers.size(); i++) {
      if (i != 0) cout << " ";
      cout << answers[i];
    }
    cout << endl;
  }
}