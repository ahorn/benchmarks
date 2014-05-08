#include <iostream>
#include <chrono>
#include <smt>

#ifndef _REPORT_H_
#define _REPORT_H_

template<typename T>
void report_time(T total_time) {
  const std::chrono::seconds total_seconds =
    std::chrono::duration_cast<std::chrono::seconds>(total_time);

  const smt::Solver::Stats& solver_stats = crv::sequential_dfs_checker().solver().stats();
  const smt::Solver::ElapsedTime check_elapsed_time = solver_stats.check_elapsed_time;
  const smt::Solver::ElapsedTime encode_elapsed_time = solver_stats.encode_elapsed_time;

  const std::chrono::seconds check_elapsed_seconds =
    std::chrono::duration_cast<std::chrono::seconds>(check_elapsed_time);

  const std::chrono::seconds encode_elapsed_seconds =
    std::chrono::duration_cast<std::chrono::seconds>(encode_elapsed_time);

  const crv::SequentialDfsChecker::Stats& stats = crv::sequential_dfs_checker().stats();

  const std::chrono::seconds branch_seconds =
    std::chrono::duration_cast<std::chrono::seconds>(stats.branch_time);

  const std::chrono::seconds replay_seconds =
    std::chrono::duration_cast<std::chrono::seconds>(stats.replay_time);

  std::cout << "-----------------------:" << std::endl;
  std::cout << "Number of paths exlored: " <<  crv::sequential_dfs_checker().path_cnt() << std::endl;

  if (stats.branch_cnt == 0)
    std::cout << "Literal branch percentage: 'undefined'" << std::endl;
  else
    std::cout << "Literal branch percentage: " <<
      ((stats.branch_literal_cnt * 100) /
        stats.branch_cnt)  << "\%" << std::endl;

  std::cout << "Total runtime (s): " << total_seconds.count() << std::endl;
  std::cout << "Encoder time (s): " << encode_elapsed_seconds.count() << std::endl;
  std::cout << "Solver time (s): " << check_elapsed_seconds.count() << std::endl;
  std::cout << "Branch time (s): " << branch_seconds.count() << std::endl;
  std::cout << "Replay time (s): " << replay_seconds.count() << std::endl;

  if (total_time == T::zero())
  {
    std::cout << "Solver percentage: 'undefined'" << std::endl;
    std::cout << "Branch percentage: 'undefined'" << std::endl;
    std::cout << "Replay percentage: 'undefined'" << std::endl;
  }
  else
  {
    std::cout << "Solver percentage: " << ((check_elapsed_time * 100) / total_time) << "\%" << std::endl;
    std::cout << "Branch percentage: " << ((stats.branch_time * 100) / total_time) << "\%" << std::endl;
    std::cout << "Replay percentage: " << ((stats.replay_time * 100) / total_time) << "\%" << std::endl;
  }
}

#endif
