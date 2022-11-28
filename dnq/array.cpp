#include <iostream>

template <typename T>
struct array {
  size_t size;
  T* data;

  array(size_t size) : size(size) { data = new T[size]; }
  array() { data = nullptr; }
  ~array() { delete[] data; }

  void forEach(size_t left, size_t right, const auto& fn) {
    if (left == right) {
      fn(data[left]);
      return;
    }
    auto mid = (left + right) / 2;
    forEach(left, mid, fn);
    forEach(mid + 1, right, fn);
  }

  void forEach(const auto& fn) { forEach(0, size - 1, fn); }
};

int main() {
  size_t size;
  std::cin >> size;

  auto arr = array<int>(size);
  arr.forEach([&](auto& x) { std::cin >> x; });
  arr.forEach([&](auto& x) { std::cout << x << ' '; });
}