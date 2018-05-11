/**
 * \file main.cpp
 * \author Andreas Ziegler
 * \date 11.05.2018
 * \brief Performing trilateration with at least
 *        four known point in 3D and the distances
 *        in order to determine the location.
 */

#include <iostream>
#include <vector>

#include "solver.h"

/**
 * Reads coordinates of the points and the distances from std input.
 * \param[in] num_points The number of points the user want to add.
 * \param[out] distances A vector containing the distances to the defined points.
 * \param[out] A vector containing a vector with the 3D coordinates of the defined points.
 */
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

/**
 * Print coordinates of the points and the distances to the std input.
 * \param[in] distances A vector containing the distances to the defined points.
 * \param[in] A vector containing a vector with the 3D coordinates of the defined points.
 */
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


int main(void) {
  int num_points = 0;

  while (4 > num_points) {
    std::cout << "How many corresponding 3D point distance pairs do you want to enter? Please provide at least three pairs." << std::endl;
    std::cin >> num_points;
  }

  std::vector<double> distances(num_points);
  std::vector<std::vector<double>> world_coordinates(num_points, std::vector<double>(3, 0));

  GetPointsAndDistances(num_points, distances, world_coordinates);
  PrintPointsAndDistances(distances, world_coordinates);

  std::vector<double> position = {0.0, 0.0, 0.0};
  CalculatePosition(position, distances, world_coordinates);

  std::cout << std::endl << "Calculated position: x = "
            << position[0] << ", y = " << position[1]
            << ", z = " << position[2] << std::endl;

  return 0;
}
