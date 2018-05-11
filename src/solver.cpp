/**
 * \file solver.cpp
 * \author Andreas Ziegler
 * \date 11.05.2018
 * \brief Implementation of the optimization problem to calculate the position.
 */

#include "solver.h"

void CalculatePosition(std::vector<double> &position,
                       std::vector<double> &distances,
                       std::vector<std::vector<double>> &world_coordinates) {

  // The variables to solve for
  std::vector<double> x = {0.0, 0.0, 0.0};

  // Build the problem
  ceres::Problem problem;

  // Add residual term to the problem usin the autodiff
  for (int i = 0; i < distances.size(); i++) {
    ceres::CostFunction *cost_function =
      new ceres::AutoDiffCostFunction<CostFunctor, 1, 3>(
          new CostFunctor(world_coordinates[i], distances[i]));

    problem.AddResidualBlock(cost_function,
                             NULL,
                             x.data());
  }

  // Run the solver
  ceres::Solver::Options options;
  options.minimizer_progress_to_stdout = false;
  ceres::Solver::Summary summary;
  ceres::Solve(options, &problem, &summary);

  //std::cout << summary.BriefReport() << std::endl;

  for (int i = 0; i < 3; i++) {
    position[i] = x[i];
  }
}
