#include <algorithm>
#include <benchmark/benchmark.h>
#include <vector>
// DUmmy benchmark function to demonstrate how to use Google Benchmark
static void BM_VectorSort(benchmark::State& state) {
	// Setup outside the measurement loop
	std::vector<int> data(state.range(0));

	for (auto _ : state) {
		// Pause timing while resetting data for each iteration
		state.PauseTiming();
		std::generate(data.begin(), data.end(), rand);
		state.ResumeTiming();

		std::sort(data.begin(), data.end());
		benchmark::DoNotOptimize(data.data());
	}
}

// Register the function and pass input sizes (e.g., 64 to 4096)
BENCHMARK(BM_VectorSort)->Range(64, 4096);

// Generates the main() entry point
BENCHMARK_MAIN();