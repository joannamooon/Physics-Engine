#pragma once

#include "Kinetic.hpp"

namespace pe
{

    class KineticsWithSize : public virtual Kinetic
    {
    public:
        virtual ~KineticsWithSize() = default;
        virtual double getSizeX() const = 0;
        virtual double getSizeY() const = 0;
        virtual void setSizeX(double x) = 0;
        virtual void setSizeY(double y) = 0;
    };

} // namespace pe
