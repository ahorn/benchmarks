// This small C++11 file can be compiled with various options. For example,
// "g++ -std=c++11 -D_EXPOSE_BUG_ thread_chain.cpp" produces an executable
// file that when run exposes the violation of the verification condition
// when plain-old threads are used instead of Thread Chains.

#include <thread>
#include <utility>
#include <cassert>

#ifdef _EXPOSE_BUG_
#include <chrono>

constexpr std::chrono::seconds TINY_DELAY(1);
constexpr std::chrono::seconds SHORT_DELAY(3);
constexpr std::chrono::seconds LONG_DELAY(5);
#endif

// ========= Thread Chain library =========

// A chain is like a chain of threads `f, g, ...` where `f`
// must terminate before `g` can start to run, and so forth.
class Chain
{
private:
  std::thread thread;

  template<typename F, typename... Args>
  static void chain_start_routine(std::thread&& thread, F f, Args&&... args)
  {
    if (thread.joinable())
      thread.join();

    f(std::forward<Args>(args)...);
  }

public:
  // Throws a std::system_error if the thread could not be started.
  template<typename F, typename... Args>
  void run(F f, Args&&... args)
  {
    thread = std::thread(chain_start_routine<F, Args...>,
      std::move(thread), f, std::forward<Args>(args)...);
  }

  bool joinable() const noexcept
  {
    return thread.joinable();
  }

  // Wait for entire chain of threads to terminate
  void join()
  {
    thread.join();
  }
};

// ========= Symbolic test =========

char test_global;

void test_write_a()
{
#ifdef _EXPOSE_BUG_
  std::this_thread::sleep_for(SHORT_DELAY);
#endif

  test_global = 'A';
}

void test_write_b()
{
  test_global = 'B';
}

int main()
{
#ifdef _ENABLE_CHAIN_
  Chain chain;
  chain.run(test_write_a);
  chain.run(test_write_b);
#else
  std::thread a_thread(test_write_a);
  std::thread b_thread(test_write_b);
#endif

#ifdef _EXPOSE_BUG_
  std::this_thread::sleep_for(TINY_DELAY);
#endif

  char x = test_global;

#ifdef _EXPOSE_BUG_
  std::this_thread::sleep_for(LONG_DELAY);
#endif

  char y = test_global;

  // Verification condition:
  //
  //  If global variable equals 'B', then it cannot change.
  //
  // It is expected that this implication
  // fails if _ENABLE_CHAIN_ is undefined.
  assert(x != 'B' || y == 'B');

#ifdef _ENABLE_CHAIN_
  chain.join();
#else
  a_thread.join();
  b_thread.join();
#endif

  return 0;
}
