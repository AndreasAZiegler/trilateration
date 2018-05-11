/**
 * \file solver.h
 * \author Andreas Ziegler
 * \date 11.05.2018
 * \brief Header file containing the required defintion for the solver
 */

#pragma once

#include <vector>
#include "ceres/ceres.h"

/**
 * Struct containing the residual of function and the constant parameters
 */
struct CostFunctor {
  /*
   * Initializing the constant parameters.
   */
  CostFunctor(std::vector<double>& a_n, double d_n)
  : a_n_(a_n), d_n_(d_n) {}

  /*
   * Residual
   * \f$f_n(x) = ((a_{n_1} - x_1)^2 + (a_{n_2} - x_2)^2 + (a_{n_3} - x_3)^2 - d_n^2)\f$
   */
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

/**
 * \brief Builds the optimization problem for the ceres solver
 *
 * \param[out] position The calculated position.
 * \param[in] distances The distances to the anchor points.
 * \param[in] world_coordinates The positions of the anchor points.
 */
void CalculatePosition(std::vector<double> &position,
                       std::vector<double> &distances,
                       std::vector<std::vector<double>> &world_coordinates);
