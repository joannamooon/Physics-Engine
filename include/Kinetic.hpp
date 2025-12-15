#pragma once

#include "Vector.hpp"
#include <vector>
#include <array>

namespace pe
{

    class Kinetic
    {
    public:
        virtual ~Kinetic() = default;
        virtual Vector getPosition() const = 0;
        virtual void setPosition(const Vector &v) = 0;
        virtual void addDisplacement(const Vector &v) = 0;
        virtual Vector getVelocity() const = 0;
        virtual void setVelocity(const Vector &v) = 0;
        virtual void addVelocity(const Vector &v) = 0;
        virtual Vector getAcceleration() const = 0;
        virtual void setAcceleration(const Vector &v) = 0;
        virtual void addAcceleration(const Vector &v) = 0;
        virtual void setMass(double m) = 0;
        virtual double getMass() const = 0;
        virtual double getFrictionCoe() const = 0;
        virtual void setFrictionCoe(double frictionCoefficient) = 0;
        virtual bool isCollide(const void *o) const = 0;
        virtual std::vector<Vector> getForceList() const = 0;
        virtual std::array<double, 4> getElasticity() const = 0;
        virtual void setElasticity(const std::array<double, 4> &elasticity) = 0;
    };

} // namespace pe
