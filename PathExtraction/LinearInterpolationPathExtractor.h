#ifndef RONCAPAT_GLOBAL_PLANNERS_LINEARINTERPOLATIONPATHEXTRACTOR_H
#define RONCAPAT_GLOBAL_PLANNERS_LINEARINTERPOLATIONPATHEXTRACTOR_H

#include "Node.h"
#include "Graph.h"
#include "ExpandedMap.h"

template<typename E, typename T>
class LinearInterpolationPathExtractor {
public:
    LinearInterpolationPathExtractor(const ExpandedMap<E, T> &map, const Graph &grid);

    void extract_path();

    std::vector<Position> path_{};
    std::vector<float> cost_{};
    float total_cost = 0;
    float total_dist = 0;
    bool lookahead = true;
    int max_steps = 20;
    float e_time = 0;
    bool allow_indirect_traversals = true;
 private:
    const ExpandedMap<E, T> &map;
    const Graph &grid;

    PathAdditions getPathAdditions(const Position &p, const bool &do_lookahead, float &step_cost);

    PathAdditions traversalFromEdge(const Position &p, const Node &p_a, const Node &p_b, float &step_cost);

    PathAdditions traversalFromOppositeEdge(const Position &p, const Node &p_a, const Node &p_b, float &step_cost);

    PathAdditions traversalFromContiguousEdge(const Position &p, const Node &p_a, const Node &p_b, float &step_cost);

    PathAdditions traversalFromCorner(const Position &p, const Node &p_a, const Node &p_b, float &step_cost);

    bool goalReached(const Position &p);

    void fill_traversal_costs(TraversalParams &t);
};
#include "LinearInterpolationPathExtractor_impl.h"
#endif //RONCAPAT_GLOBAL_PLANNERS_LINEARINTERPOLATIONPATHEXTRACTOR_H
