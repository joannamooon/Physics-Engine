#pragma once

#include "GameObject.hpp"
#include "KineticsWithSize.hpp"
#include "CollisionEvent.hpp"
#include <array>

namespace pe
{

    struct Rect
    {
        double x, y, w, h;
    };

    class CollisionRec : public GameObject, public KineticsWithSize
    {
    public:
        CollisionRec(double x, double y, double sizeX, double sizeY);
        CollisionEvent collideWith(const KineticsWithSize &o) const;
        void update(long elapsedTime) override;
        void close() override;
        double getSizeX() const override { return sizeX; }
        double getSizeY() const override { return sizeY; }
        void setSizeX(double x) override;
        void setSizeY(double y) override;

    private:
        const double COLLIDER_WIDTH = 3.0;
        const double WALL_MARGIN = 3.0;
        bool isUpdate = true;
        std::array<Rect, 4> colliders;
        double sizeX;
        double sizeY;
    };

} // namespace pe
