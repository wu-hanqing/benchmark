#include <cstdlib>
#include <ostream>
#include <sstream>

#include "absl/strings/str_cat.h"
#include "benchmark/benchmark.h"

namespace {

thread_local unsigned int seed_oss = 0;
thread_local unsigned int seed_str_cat = 0;

std::string oss_format() {
  std::ostringstream oss;
  oss << rand_r(&seed_oss) << "/" << rand_r(&seed_oss);
  return oss.str();
}

void BM_ostringstream(benchmark::State& state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(oss_format());
  }
}

std::string str_cat_format() {
  return absl::StrCat(rand_r(&seed_str_cat), "/", rand_r(&seed_str_cat));
}

void BM_str_cat(benchmark::State& state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(str_cat_format());
  }
}

}  // namespace

BENCHMARK(BM_ostringstream)->ThreadRange(1, 16);
BENCHMARK(BM_str_cat)->ThreadRange(1, 16);

BENCHMARK_MAIN();
