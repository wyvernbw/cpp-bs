#include <iostream>

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

};

int main() {
  size_t rows, cols;
  std::cin >> rows >> cols;
  auto mat = matrix<100>(rows, cols);
  mat.read(std::cin);
  mat.print(std::cout);
  mat.lineSome
}