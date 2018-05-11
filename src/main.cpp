#include <iostream>
#include <vector>

#include "ceres/ceres.h"

void GetPointsAndDistances(const int num_points,
                           std::vector<double> &distances,
                           std::vector<std::vector<double>> &world_coordinates) {

  for (int i = 0; i < num_points; i++) {
    double x_world = 0;
    double y_world = 0;
    double z_world = 0;
    double distance = 0;

    std::cout << "Point nr. " << i << ":" << std::endl;
    std::cout << "Please enter the world coordinates of the point: X, Y, Z: ";
    std::cin >> x_world >> y_world >> z_world;

    std::cout << std::endl << "Please enter the distance to the point: ";
    std::cin >> distance;

    world_coordinates[i][0] = x_world;
    world_coordinates[i][1] = y_world;
    world_coordinates[i][2] = z_world;
    distances[i] = distance;
  }
}

void PrintPointsAndDistances(const std::vector<double> &distances,
                             const std::vector<std::vector<double>> &world_coordinates) {

  std::cout << "You entered the following coordinates and distances:" << std::endl;

  for (int i = 0; i < distances.size(); i++) {
    std::cout << "Point nr.: " << i << std::endl;

    std::cout << "World coordinates: X, Y, Z: ";
    std::vector<double> vec = world_coordinates[i];
    for (double value : vec) {
      std::cout << value << " ";
    }
    std::cout << std::endl;

    std::cout << "Distance: ";
    std::cout << distances[i] << std::endl;
  }
}

struct CostFunctor {
  CostFunctor(std::vector<double>& a_n, double d_n)
  : a_n_(a_n), d_n_(d_n) {}
  template <typename T>
  bool operator()(const T* const x,
                  T* residual) const {
    residual[0] = ((T(a_n_[0]) - x[0]) * (T(a_n_[0]) - x[0])
                 + (T(a_n_[1]) - x[1]) * (T(a_n_[1]) - x[1])
                 + (T(a_n_[2]) - x[2]) * (T(a_n_[2]) - x[2])
                 - T(d_n_) * T(d_n_));
    return true;
  }

 private:
    const std::vector<double>& a_n_;
    const double d_n_;
};

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
  options.minimizer_progress_to_stdout = true;
  ceres::Solver::Summary summary;
  ceres::Solve(options, &problem, &summary);

  std::cout << summary.BriefReport() << std::endl;
  std::cout << "x: " << x[0] << ", " << x[1] << ", " << x[2] << std::endl;

  for (int i = 0; i < 3; i++) {
    position[i] = x[i];
  }
}

int main(void) {
  int num_points = 0;

  while (3 > num_points) {
    std::cout << "How many corresponding 3D point distance pairs do you want to enter? Please provide at least three pairs." << std::endl;
    std::cin >> num_points;
  }

  std::vector<double> distances(num_points);
  std::vector<std::vector<double>> world_coordinates(num_points, std::vector<double>(3, 0));

  GetPointsAndDistances(num_points, distances, world_coordinates);
  PrintPointsAndDistances(distances, world_coordinates);

  std::vector<double> position = {0.0, 0.0, 0.0};
  CalculatePosition(position, distances, world_coordinates);

  return 0;
}
