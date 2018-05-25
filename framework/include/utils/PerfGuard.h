//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef PERFGUARD_H
#define PERFGUARD_H

#include "MooseTypes.h"
#include "PerfGraph.h"

/**
 * Scope guard for starting and stopping timing for a node
 *
 * Note that the PerfGuard timing itself will take
 * approximately 0.00015 milliseconds.
 *
 * That might not sound very long - but you still don't want
 * that in the inside of tiny loops
 */
class PerfGuard
{
public:
  /**
   * Start timing for the given ID
   *
   * @param graph The graph to add time into
   * @param id The unique id of the section
   */
  PerfGuard(PerfGraph & graph, const PerfID id) : _graph(graph)
  {
    if (_graph.active())
    {
      _graph.push(id);
      _start = std::chrono::steady_clock::now();
    }
  }

  /**
   * Stop timing
   */
  ~PerfGuard()
  {
    if (_graph.active())
      _graph.pop(std::chrono::steady_clock::now() - _start);
  }

protected:
  ///The graph we're working on
  PerfGraph & _graph;

  /// The beginning time of the section
  std::chrono::time_point<std::chrono::steady_clock> _start;
};

#endif
