#ifndef FIELDDPLANNER_H
#define FIELDDPLANNER_H

#include <cassert>
#include <cmath>
#include <limits>
#include <tuple>
#include <vector>
#include <utility>

#include "Macros.h"
#include "Graph.h"
#include "ExpandedMap.h"
#include "PriorityQueue.h"
#include "InterpolatedTraversal.h"
#include "ReplannerBase.h"

// TODO maybe use template bool instead of macros
#ifdef NO_HEURISTIC
using key_type = float;
#else
using key_type = std::pair<float, float>;
#endif

using elem_type = Node;
template<int OptimizationLevel>
using info_type = typename std::conditional<OptimizationLevel == 0, void, Node>::type;

template<int OptimizationLevel>
class FieldDPlanner : public ReplannerBase<FieldDPlanner<OptimizationLevel>,
                                           elem_type,
                                           info_type<OptimizationLevel>,
                                           key_type> {
 public:
  typedef ReplannerBase<FieldDPlanner<OptimizationLevel>,
                        elem_type,
                        info_type<OptimizationLevel>,
                        key_type> Base;
  friend Base;
  typedef typename Base::Key Key;
  typedef typename Base::Queue Queue;
  typedef typename Base::Map Map;
  using Base::grid;
  using Base::priority_queue;
  using Base::map;
 public:
  FieldDPlanner() = default;

  void set_start(const Position &pos);

 protected:
  void init();

  void update();

  void plan();

  Key calculate_key(const Node &s, float g, float rhs) const;

 private:
  std::vector<Node> start_nodes;
  std::vector<typename decltype(map)::nodeptr> start_nodes_it;

  float compute_optimal_cost(const Node &n, const Node &p_a, const Node &p_b, float ga, float gb) const;

  float compute_optimal_cost(const Node &n, const Node &p_a, const Node &p_b) const;

  bool end_condition() const;

  Key calculate_key(const Node &s) const;

  Key calculate_key(const Node &s, float cost_so_far) const;

  float min_rhs(const Node &s) const;

  float min_rhs(const Node &s, Node &bptr) const;

  float min_rhs_decreased_neighbor(const Node &sp, const Node &s, Node &bptr) const;

  void fill_traversal_costs(TraversalParams &t) const;

  void update_node(const Node &node);
};

template<>
void FieldDPlanner<0>::plan();

template<>
float FieldDPlanner<0>::min_rhs(const Node &) const;

template<>
void FieldDPlanner<1>::plan();

template<>
float FieldDPlanner<1>::min_rhs(const Node &, Node &bptr) const;

template<>
float FieldDPlanner<1>::min_rhs_decreased_neighbor(const Node &sp, const Node &s, Node &bptr) const;

#include "FieldDPlanner_impl.h"

#endif
