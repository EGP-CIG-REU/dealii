// ---------------------------------------------------------------------
//
// Copyright (C) 2017 by the deal.II authors
//
// This file is part of the deal.II library.
//
// The deal.II library is free software; you can use it, redistribute
// it, and/or modify it under the terms of the GNU Lesser General
// Public License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// The full text of the license can be found in the file LICENSE at
// the top level of the deal.II distribution.
//
// ---------------------------------------------------------------------



// test the correctness of the detection of the elements in
// internal::MatrixFreeFunctions::ShapeInfo

#include "../tests.h"

#include <deal.II/matrix_free/shape_info.h>

#include <deal.II/base/logstream.h>
#include <deal.II/fe/fe_dgp.h>
#include <deal.II/fe/fe_dgq.h>
#include <deal.II/fe/fe_q.h>
#include <deal.II/fe/fe_q_hierarchical.h>
#include <deal.II/fe/fe_q_dg0.h>
#include <deal.II/fe/fe_system.h>

#include <fstream>
#include <iostream>

std::ofstream logfile("output");


template <int dim>
void test (const FiniteElement<dim> &fe,
           const Quadrature<1>      &quad)
{
  for (unsigned int i=0; i<fe.n_base_elements(); ++i)
    {
      internal::MatrixFreeFunctions::ShapeInfo<double> shape_info;
      shape_info.reinit(quad, fe, i);
      deallog << "Detected shape info type for " << fe.base_element(i).get_name() << ": "
              << static_cast<unsigned int>(shape_info.element_type) << std::endl;
    }
}


int main ()
{
  initlog();
  QGauss<1> gauss3(3);
  QGauss<1> gauss8(8);
  test(FE_Q<1>(1), gauss3);
  test(FE_Q<1>(1), gauss8);
  test(FE_Q<1>(6), gauss3);
  test(FE_Q<1>(6), gauss8);
  test(FE_Q<1>(17), gauss3);
  test(FE_Q<1>(17), gauss8);
  test(FE_Q<1>(25), gauss3);
  test(FE_Q<1>(25), gauss8);
  test(FE_Q<1>(45), gauss3);
  test(FE_Q<1>(45), gauss8);

  test(FE_Q<2>(1), gauss3);
  test(FE_Q<2>(1), gauss8);
  test(FE_Q<2>(6), gauss3);
  test(FE_Q<2>(6), gauss8);
  test(FE_Q<2>(17), gauss3);
  test(FE_Q<2>(17), gauss8);
  test(FE_Q<2>(17), QGaussLobatto<1>(18));
  test(FE_Q<2>(25), gauss3);
  test(FE_Q<2>(25), gauss8);
  test(FE_Q<2>(45), gauss3);
  test(FE_Q<2>(45), gauss8);

  test(FE_Q<3>(1), gauss3);
  test(FE_Q<3>(6), gauss3);
  test(FE_Q<3>(17), gauss3);
  test(FE_Q<3>(25), gauss3);

  test(FE_DGQ<2>(1), gauss3);
  test(FE_DGQ<3>(6), gauss3);
  test(FE_Q_Hierarchical<3>(6), gauss8);
  test(FE_DGQ<2>(17), gauss8);
  test(FE_DGQ<2>(25), gauss3);

  test(FE_DGQArbitraryNodes<2>(QIterated<1>(QTrapez<1>(), 1)), gauss3);
  test(FE_DGQArbitraryNodes<3>(QIterated<1>(QTrapez<1>(), 6)), gauss3);
  test(FE_DGQArbitraryNodes<2>(QIterated<1>(QTrapez<1>(), 17)), gauss8);
  test(FE_DGQArbitraryNodes<2>(QGauss<1>(8)), gauss8);
  test(FE_DGQArbitraryNodes<2>(QGauss<1>(6)), gauss8);

  test(FE_DGP<2>(1), gauss3);
  test(FE_DGP<3>(3), gauss3);
  test(FE_DGP<2>(9), gauss8);
  test(FE_DGP<1>(17), gauss8);
  test(FE_DGP<3>(2), gauss8);

  test(FE_Q_DG0<3>(6), gauss3);

  test(FESystem<2>(FE_Q<2>(6), 2, FE_Q<2>(5), 3), gauss3);
  test(FESystem<2>(FE_Q<2>(6), 2, FE_DGP<2>(5), 3), gauss3);
  test(FESystem<2>(FE_Q<2>(6), 2, FE_Q_DG0<2>(5), 3), gauss3);
  test(FESystem<2>(FE_DGQ<2>(6), 2, FE_Q<2>(5), 3), gauss3);

  // define quadrature rule that is not symmetric around 0.5
  deallog << "Non-symmetric quadrature" << std::endl;
  std::vector<Point<1> > points(4);
  points[0][0] = 0.2;
  points[1][0] = 0.4;
  points[2][0] = 0.5;
  points[3][0] = 0.7;
  Quadrature<1> quad(points);
  test(FE_Q<2>(6), quad);
  test(FE_DGQ<2>(6), quad);
  test(FE_DGP<2>(6), quad);
}
