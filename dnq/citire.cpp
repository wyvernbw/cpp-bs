#include <iostream>

template <typename T>
struct array {
  T* data;
  size_t size;

  array(size_t size) : data(new T[size]), size(size) {}
  array() : data(nullptr), size(0) {}
  ~array() { delete[] data; }

  T& operator[](size_t i) { return data[i]; }
  const T& operator[](size_t i) const { return data[i]; }

  void forEach(size_t left, size_t right, const auto& fn) {
    if (left == right) {
      fn(data[left]);
    } else {
      size_t mid = (left + right) / 2;
      forEach(left, mid, fn);
      forEach(mid + 1, right, fn);
    }
  }

  void forEach(const auto& fn) { forEach(0, size - 1, fn); }
};

template <typename T>
struct matrix {
  size_t rows;
  size_t cols;
  array<array<T>> data;

  matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
    data = array<array<T>>(rows);
    data.forEach([&](auto& row) { row = array<T>(cols); });
  }

  void forEach(const auto& fn) {
    data.forEach([&](auto& row) { row.forEach(fn); });
  }
};

int main() {
  size_t n, m;
  std::cin >> n >> m;

  auto a = matrix<int>(n, m);
  a.forEach([&](auto& x) { std::cin >> x; });
}