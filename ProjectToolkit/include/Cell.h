//
// Created by patrick on 07/05/20.
//

#ifndef RONCAPAT_GLOBAL_PLANNERS_CELL_H
#define RONCAPAT_GLOBAL_PLANNERS_CELL_H

#include <robin_hood.h>
#include <utility>
#include <vector>

class Node;

class Position;

class Cell {
public:
    int x, y;

    Cell();

    Cell(int x, int y);

    Cell(const Cell &other);

    Cell(Cell &&other) noexcept;

    explicit Cell(const std::pair<int, int> &other);

    explicit Cell(const Position &n);  // Cell containing Position
    Cell &operator=(const Cell &other);

    Cell &operator=(Cell &&other) noexcept;

    [[nodiscard]] bool operator==(const Cell &other) const;

    [[nodiscard]] bool operator!=(const Cell &other) const;

    [[nodiscard]] Cell topCell() const;

    [[nodiscard]] Cell topLeftCell() const;

    [[nodiscard]] Cell topRightCell() const;

    [[nodiscard]] Cell bottomCell() const;

    [[nodiscard]] Cell bottomLeftCell() const;

    [[nodiscard]] Cell bottomRightCell() const;

    [[nodiscard]] Cell leftCell() const;

    [[nodiscard]] Cell rightCell() const;

    [[nodiscard]] Node topLeftNode() const;

    [[nodiscard]] Node topRightNode() const;

    [[nodiscard]] Node bottomLeftNode() const;

    [[nodiscard]] Node bottomRightNode() const;

    [[nodiscard]] Position centerPosition() const;

    [[nodiscard]] std::vector<Node> cornerNodes() const;

    [[nodiscard]] bool hasNode(const Node &n) const;;

    [[nodiscard]] float distance(const Cell &n) const;
};

namespace robin_hood {
    template<>
    struct hash<Cell> {
        std::size_t operator()(const Cell &n) const {
            std::size_t result = 17;
            result = 31 * result + hash<int>()(n.x);
            result = 31 * result + hash<int>()(n.y);
            return result;
        }
    };
}
#endif //RONCAPAT_GLOBAL_PLANNERS_CELL_H
