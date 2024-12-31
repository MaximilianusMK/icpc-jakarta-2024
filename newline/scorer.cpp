#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

void ac() {
  std::cout << "AC\n";
  exit(0);
}

void wa(std::string reason="") {
  std::cout << "WA\n";
  if (reason != "") {
    // UNCOMMENT THIS FOR USEFUL WA REASONS
    //std::cout << reason << '\n';
    //std::cerr << reason << '\n';
  }
  exit(0);
}

std::string readLine(std::istream &is) {
  std::string ret;
  if (!std::getline(is, ret)) wa();
  return ret;
}

int readInt(std::istream &is) {
  int ret;
  if (!(is >> ret)) wa();
  return ret;
}

bool eof(std::istream &is) {
  std::string dummy;
  if (is >> dummy) return false;
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

  std::string S;
  inp >> S;
  int judgeAns = readInt(out);

  std::stringstream row1(readLine(con));
  int conAns = readInt(row1);

  if (conAns < judgeAns) { // We still check whether contestant answer might be better!
    wa("Judge answer is better");
  }
  
  if (!eof(row1)) {
    wa("The first line must be a single integer");
  }

  std::vector<std::string> A(conAns);

  int totLen = S.length();
  for (int i = 0; i < conAns; ++i) {
    con >> A[i];
    if (A[i].length() > totLen) wa("Total length is greater than the input");
    totLen -= A[i].length();
  }
  if (!eof(con)) wa("There are additional outputs detected");
  if (totLen != 0) wa("Total length is lesser than the input");
  
  for (int i = 1; i < conAns; ++i) {
    if (A[i] <= A[i-1]) wa("Dictionary is not sorted");
  }
  
  std::string B;
  for (int i = 0; i < conAns; ++i) {
    B += A[i];
  }
  
  if (B == S) {
    if (conAns > judgeAns) {
      wa("JUDGE ERROR: Contestant answer is better!");
    }
    ac();
  } else {
    wa("Concatenation of words does not correspond to the input");
  }
}
