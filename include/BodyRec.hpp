#pragma once

#include "Body.hpp"
#include "GameObject.hpp"
#include "Force.hpp"
#include "Drag.hpp"
#include <memory>

namespace pe
{

    class BodyRec : public GameObject, public Body
    {
    public:
        BodyRec(double x, double y, double sizeX, double sizeY);
        BodyRec(const Vector &v, double sizeX, double sizeY);
        ~BodyRec() override = default;

        // Body
        Vector getGravity() const override;
        Vector getDrag() const override;
        double getDragCoe() const override;
        Vector getNormalForce() const override;
        Vector getFriction() const override;
        void setGravity(const Vector &v) override;
        void setDragCoe(double dragCoe) override;
        void setNormalForce(const Vector &v) override;
        void setFriction(const Vector &v) override;

        // KineticsWithSize
        double getSizeX() const override { return sizeX; }
        double getSizeY() const override { return sizeY; }
        void setSizeX(double x) override { sizeX = x; }
        void setSizeY(double y) override { sizeY = y; }

        // Collision helper
        bool isCollide(const void *o) const override;

    private:
        double sizeX;
        double sizeY;
        std::shared_ptr<ValueForce> gravity;
        std::shared_ptr<Drag> drag;
        std::shared_ptr<ValueForce> friction;
        std::shared_ptr<ValueForce> normalForce;
    };

} // namespace pe
