#include <fstream>
#include <iostream>

bool someDigits(int n, const auto& predicate) {
  if (n == 0) {
    return false;
  }
  auto digit = n % 10;
  if (predicate(digit)) {
    return true;
  }
  return someDigits(n / 10, predicate);
}

template <typename T>
struct matrix {
  T** data;
  size_t rows, cols;

  matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
    data = new T*[rows];
    forEach([](...) {}, [&](auto& line, size_t i) { data[i] = new T[cols]; });
  }

  void forEach(const auto& fn, const auto& lfn, size_t low, size_t high,
               size_t left, size_t right, bool rowMajor = true) {
    if (low == high) {
      if (left == right) {
        fn(data[low][left], low, left);
        return;
      }
      if (rowMajor) {
        lfn(data[low], low);
      }
      auto hmid = (left + right) / 2;
      forEach(fn, lfn, low, high, left, hmid, false);
      forEach(fn, lfn, low, high, hmid + 1, right, false);
      return;
    }
    auto vmid = (low + high) / 2;
    forEach(fn, lfn, low, vmid, left, right);
    forEach(fn, lfn, vmid + 1, high, left, right);
  }

  void forEach(const auto& fn, const auto& lfn) {
    forEach(fn, lfn, 0, rows - 1, 0, cols - 1, true);
  }

  void read(std::istream& is) {
    forEach([&](auto& x, size_t i, size_t j) { is >> x; }, [](...) {});
  }

  void print(std::ostream& os) {
    forEach([&](auto& x, size_t i, size_t j) { os << x << " "; },
            [&](...) { os << "\n"; });
  }

  bool some(const auto& predicate) {
    bool res = false;
    forEach(
        [&](const auto& x, size_t i, size_t j) {
          if (predicate(x)) {
            res = true;
          }
        },
        [](...) {});
    return res;
  }
};

int main() {
  auto mat = matrix<int>(3, 3);
  mat.read(std::cin);
  std::cout << "\n";
  mat.print(std::cout);
  std::cout << "\n";
  auto odd = [](int x) -> bool { return x % 2 == 1; };
  std::cout << mat.some([&odd](auto x) { return someDigits(x, odd); }) << "\n";
}
