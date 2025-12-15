#pragma once

#include <array>
#include <vector>

namespace pe
{

    class CollisionEvent
    {
    public:
        CollisionEvent() = default;
        void setCollisionPosition(const std::array<bool, 4> &pos) { collisionPosition = pos; }
        void setDepth(const std::array<double, 4> &d) { depth = d; }
        std::array<bool, 4> getCollisionPosition() const { return collisionPosition; }
        std::array<double, 4> getDepth() const { return depth; }

    private:
        std::array<bool, 4> collisionPosition{false, false, false, false};
        std::array<double, 4> depth{0, 0, 0, 0};
    };

} // namespace pe
