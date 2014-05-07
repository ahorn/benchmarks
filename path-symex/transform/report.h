#include <iostream>
#include <chrono>
#include <smt>

#ifndef _REPORT_H_
#define _REPORT_H_

template<typename T>
void report_time(T total_time) {
  const std::chrono::seconds total_seconds =
    std::chrono::duration_cast<std::chrono::seconds>(total_time);

  const smt::Solver::Stats& stats = crv::sequential_dfs_checker().solver().stats();
  const smt::Solver::ElapsedTime check_elapsed_time = stats.check_elapsed_time;
  const smt::Solver::ElapsedTime encode_elapsed_time = stats.encode_elapsed_time;

  const std::chrono::seconds check_elapsed_seconds =
    std::chrono::duration_cast<std::chrono::seconds>(check_elapsed_time);

  const std::chrono::seconds encode_elapsed_seconds =
    std::chrono::duration_cast<std::chrono::seconds>(encode_elapsed_time);

  std::cout << "-----------------------:" << std::endl;
  std::cout << "Total runtime (s): " << total_seconds.count() << std::endl;
  std::cout << "Encoder time (s): " << encode_elapsed_seconds.count() << std::endl;
  std::cout << "Solver time (s): " << check_elapsed_seconds.count() << std::endl;

  if (total_time == T::zero())
    std::cout << "Solver time / Total runtime: 'undefined'" << std::endl;
  else
    std::cout << "Solver time / Total runtime: " << ((check_elapsed_time * 100) / total_time) << "\%" << std::endl;
}

#endif
