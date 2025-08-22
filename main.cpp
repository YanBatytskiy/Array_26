#include <chrono>
#include <ctime>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

size_t sum(const std::vector<size_t> &arr, size_t begin, size_t end) {

  auto it_first = arr.begin() + begin;
  auto it_end = arr.begin() + end + 1;

  size_t value = std::accumulate(it_first, it_end, size_t{0});

  return value;
}

int main() {

  size_t n = 100000000; // количество значений
  size_t m = 10;        // количество потоков
  std::vector<size_t> arr;

  size_t thr_quantity = n / m;

  std::srand(std::time(nullptr));

  for (size_t i = 0; i < n; ++i) {
    arr.push_back(std::rand() % n);
    auto it = arr.end();

    // std::cout << *(it - 1) << " ";
  }

  std::cout << std::endl;

  std::vector<std::thread> thr;
  std::vector<size_t> value(m, 0);

  size_t result = 0;

  auto thr_start = std::chrono::high_resolution_clock::now();

for (size_t i = 0; i < m; ++i) {
  size_t end = (i == m - 1) ? (n - 1) : ((i + 1) * thr_quantity - 1);
  thr.push_back(std::thread([&, i, end]() {
    value[i] = sum(arr, thr_quantity * i, end);
  }));
}

  for (auto &t : thr)
    t.join();

  auto thr_stop = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
      thr_stop - thr_start);

  for (auto sum : value)
    result += sum;

  std::cout << result << std::endl;
  ;
  std::cout << "Время работы " << m << " потоков = " << duration.count()
            << " наносекунд" << std::endl;
  std::cout << std::endl;

  thr_start = std::chrono::high_resolution_clock::now();

  result = sum(arr, 0, n - 1);

  thr_stop = std::chrono::high_resolution_clock::now();

  duration = std::chrono::duration_cast<std::chrono::nanoseconds>(thr_stop -
                                                                  thr_start);

  std::cout << result << std::endl;
  std::cout << "Время работы только одним потоком = " << duration.count()
            << " наносекунд" << std::endl;

  return 0;
}