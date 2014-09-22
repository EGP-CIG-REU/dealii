// ---------------------------------------------------------------------
//
// Copyright (C) 2009 - 2013 by the deal.II authors
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


// like task_01, but with return value

#include "../tests.h"
#include <iomanip>
#include <fstream>
#include <unistd.h>

#include <deal.II/base/thread_management.h>


int test ()
{
  sleep (3);
  return 42;
}




int main()
{
  std::ofstream logfile("output");
  deallog.attach(logfile);
  deallog.depth_console(0);
  deallog.threshold_double(1.e-10);

  Threads::Task<int> t = Threads::new_task (test);
  Assert (t.return_value() == 42, ExcInternalError());

  deallog << "OK" << std::endl;
}
