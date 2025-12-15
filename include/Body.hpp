#pragma once

#include "KineticsWithSize.hpp"
#include "Vector.hpp"

namespace pe
{

    class Body : public KineticsWithSize
    {
    public:
        virtual ~Body() = default;
        virtual Vector getGravity() const = 0;
        virtual Vector getDrag() const = 0;
        virtual double getDragCoe() const = 0;
        virtual Vector getNormalForce() const = 0;
        virtual Vector getFriction() const = 0;
        virtual void setGravity(const Vector &v) = 0;
        virtual void setDragCoe(double dragCoe) = 0;
        virtual void setNormalForce(const Vector &v) = 0;
        virtual void setFriction(const Vector &v) = 0;
    };

} // namespace pe
