#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

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

void unknown(std::string reason="") {
  // We don't have such verdict. There may be something in the judge's output.
  std::cout << "UNKNOWN\n";
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

std::string readString(std::ifstream &ifs, bool is_judge) {
  std::string ret;
  if (!(ifs >> ret)) {
    if (is_judge) unknown();
    else wa();
  }
  return ret;
}

bool eof(std::ifstream &ifs) {
  std::string dummy;
  if (ifs >> dummy) return false;
  return true;
}

bool IsIdentical(std::vector<std::string> judge_results, std::vector<std::string> con_results) {
  std::sort(judge_results.begin(), judge_results.end());
  std::sort(con_results.begin(), con_results.end());
  
  for (int i = 0; i < judge_results.size(); i++) {
    if (judge_results[i] != con_results[i]) return false;
  }
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

  int judge_ans = readInt(out);
  int con_ans = readInt(con);

  if (judge_ans != con_ans) {
    wa();
  }

  std::vector<std::string> judge_results;
  std::vector<std::string> con_results;
  for (int i = 0; i < judge_ans; i++) {
    judge_results.emplace_back(readString(out, /*is_judge=*/true));
    con_results.emplace_back(readString(con, /*is_judge=*/false));
  }

  if (!eof(con)) wa();

  if (!IsIdentical(judge_results, con_results)) {
    wa();
  }
  ac();
}
