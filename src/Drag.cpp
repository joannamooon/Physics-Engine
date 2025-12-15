#include "../include/Drag.hpp"
#include <cmath>

namespace pe
{

    Vector Drag::getCurrentValue() const
    {
        Vector vel = obj->getVelocity();
        double speed = vel.length();
        Vector tempDrag = vel.multiply(speed * dragCoe).multiply(-1.0);
        return tempDrag;
    }

} // namespace pe
