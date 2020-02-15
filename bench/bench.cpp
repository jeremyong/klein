#include <benchmark/benchmark.h>
#include <klein/klein.hpp>
#include <random>

static std::random_device r;
static std::minstd_rand lcg{r()};
static std::uniform_real_distribution<float> dist{-100.f, 100.f};

kln::rotor random_rotor()
{
    return {dist(lcg), dist(lcg), dist(lcg), dist(lcg)};
}

kln::motor random_motor()
{
    return {dist(lcg),
            dist(lcg),
            dist(lcg),
            dist(lcg),
            dist(lcg),
            dist(lcg),
            dist(lcg),
            dist(lcg)};
}

kln::point random_point()
{
    return {dist(lcg), dist(lcg), dist(lcg)};
}

static void BM_rotor_composition(benchmark::State& state)
{
    kln::rotor r1;
    kln::rotor r2;
    for (auto _ : state)
    {
        state.PauseTiming();
        r1 = random_rotor();
        r2 = random_rotor();
        state.ResumeTiming();
        benchmark::DoNotOptimize(r1 * r2);
    }
}
BENCHMARK(BM_rotor_composition);

static void BM_rotor_application(benchmark::State& state)
{
    kln::rotor r;
    kln::point p;
    for (auto _ : state)
    {
        state.PauseTiming();
        r = random_rotor();
        p = random_point();
        state.ResumeTiming();
        benchmark::DoNotOptimize(r(p));
    }
}
BENCHMARK(BM_rotor_application);

static void BM_rotor_matrix_conversion(benchmark::State& state)
{
    kln::rotor r;
    for (auto _ : state)
    {
        state.PauseTiming();
        r = random_rotor();
        state.ResumeTiming();
        benchmark::DoNotOptimize(r.as_matrix());
    }
}
BENCHMARK(BM_rotor_matrix_conversion);

static void BM_motor_composition(benchmark::State& state)
{
    kln::motor m1;
    kln::motor m2;
    for (auto _ : state)
    {
        state.PauseTiming();
        m1 = random_motor();
        m2 = random_motor();
        state.ResumeTiming();
        benchmark::DoNotOptimize(m1 * m2);
    }
}
BENCHMARK(BM_motor_composition);

static void BM_motor_application(benchmark::State& state)
{
    kln::motor m;
    kln::point p;
    for (auto _ : state)
    {
        state.PauseTiming();
        m = random_motor();
        p = random_point();
        state.ResumeTiming();
        benchmark::DoNotOptimize(m(p));
    }
}
BENCHMARK(BM_motor_application);

static void BM_motor_matrix_conversion(benchmark::State& state)
{
    kln::motor m;
    for (auto _ : state)
    {
        state.PauseTiming();
        m = random_motor();
        state.ResumeTiming();
        benchmark::DoNotOptimize(m.as_matrix());
    }
}
BENCHMARK(BM_motor_matrix_conversion);

BENCHMARK_MAIN();