#include <iostream>

bool prime(int num, int div) {
  if (div * div > num) return true;
  if (num % div == 0) return false;
  return prime(num, div + 2);
}

bool prime(int num) {
  if (num < 2) return false;
  if (num % 2 == 0) return num == 2;
  return prime(num, 3);
}

int factorize(int& num, int div, int exp = 0) {
  if (num % div != 0) return exp;
  num /= div;
  return factorize(num, div, exp + 1);
}

bool primeFactorization(int& num, int div) {
  if (div * div > num) return false;
  auto res = factorize(num, div);
  if (prime(res)) return true;
  return primeFactorization(num, div + 2);
}

bool primeFactorization(int num) {
  if (num % 2 == 0) {
    if (prime(factorize(num, 2))) {
      return true;
    }
  }
  return primeFactorization(num, 3);
}

template <size_t SIZE>
struct Matrix {
  int data[SIZE][SIZE];
  size_t rows, cols;

  Matrix() : rows(0), cols(0) {}
  Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {}

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
      return;
    }
    auto mid = (low + high) / 2;
    read(is, low, mid, left, right);
    read(is, mid + 1, high, left, right);
  }
  void read(std::istream& is) { read(is, 0, rows - 1, 0, cols - 1); }

  void print(std::ostream& os, size_t low, size_t high, size_t left,
             size_t right) {
    if (low == high) {
      if (left == right) {
        os >> data[low][left];
        return;
      }
      auto mid = (left + right) / 2;
      print(os, low, high, left, mid);
      print(os, low, high, mid + 1, right);
      return;
    }
    auto mid = (low + high) / 2;
    print(os, low, mid, left, right);
    print(os, mid + 1, high, left, right);
  }

  int checkCol(size_t left, size_t right, size_t col) {
    if (left == right) {
    }
  }
};