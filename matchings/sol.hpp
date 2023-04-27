#pragma once
#include <Eigen/Core>
#include <vector>

namespace matchings {

    struct pt {
        int x;
        int y;
    };
    struct edge{
        int x;
        int y;
    };

    struct Graph {
        std::vector<pt> vrtx;
        std::vector<edge> edges;
    };

    std::vector<int> kasteleyn_label(const Graph& g) {
        std::vector<int> res(g.edges.size(), 0);

        

        return res;
    }

    long double count(Graph) {
        return 0;
    }

    size_t count_modp(Graph, size_t) {
        return 0;
    }
};