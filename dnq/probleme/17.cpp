#include <iostream>

inline auto max(auto a, auto b) { return a > b ? a : b; }
inline auto min(auto a, auto b) { return a < b ? a : b; }

template <size_t SIZE>
struct matrix {
  int data[SIZE][SIZE];
  size_t rows, cols;

  matrix() = default;
  matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {}

  void read(std::istream& is, size_t low, size_t high, size_t left,
            size_t right) {
    if (low == high) {
      if (left == right) {
        is >> data[low][left];
        return;
      }
      auto mid = (left + right) / 2;
      read(is, low, high, left, mid);
      read(is, low, high, mid + 1, right);
    } else {
      auto mid = (low + high) / 2;
      read(is, low, mid, left, right);
      read(is, mid + 1, high, left, right);
    }
  }

  void read(std::istream& is) { read(is, 0, rows - 1, 0, cols - 1); }

  void print(std::ostream& os, size_t low, size_t high, size_t left,
             size_t right, bool line_break = true) {
    if (low == high) {
      if (line_break) os << '\n';
      if (left == right) {
        os << data[low][left] << ' ';
        return;
      }
      auto mid = (left + right) / 2;
      print(os, low, high, left, mid, false);
      print(os, low, high, mid + 1, right, false);
    } else {
      auto mid = (low + high) / 2;
      print(os, low, mid, left, right, true);
      print(os, mid + 1, high, left, right, true);
    }
  }

  void print(std::ostream& os) { print(os, 0, rows - 1, 0, cols - 1, true); }

  bool checkTwoLines(size_t left, size_t right, size_t line1, size_t line2,
                     float mul) {
    if (left == right) {
      if (data[line2][left] * mul != (float)data[line1][left]) {
        std::cout << data[line2][left] << " * " << mul
                  << " != " << data[line1][left] << '\n';
        return false;
      }
      return true;
    }
    auto mid = (left + right) / 2;
    return checkTwoLines(left, mid, line1, line2, mul) &&
           checkTwoLines(mid + 1, right, line1, line2, mul);
  }

  bool checkAllLines(size_t low, size_t high) {
    if (low == high) {
      if (data[low + 1][0] == 0) {
        return false;
      }
      auto mul = (float)data[low][0] / (float)data[low + 1][0];
      return checkTwoLines(0, cols - 1, low, low + 1, mul);
    }
    auto mid = (low + high) / 2;
    return checkAllLines(low, mid) || checkAllLines(mid + 1, high);
  }
};

int main() {
  size_t rows, cols;
  std::cin >> rows >> cols;

  auto mat = matrix<100>(rows, cols);
  mat.read(std::cin);
  std::cout << (mat.checkAllLines(0, mat.rows - 2) ? "YES 🔥" : "NO 🤡")
            << "\n";
}