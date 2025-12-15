#pragma once

#include "Force.hpp"
#include "Kinetic.hpp"

namespace pe
{

    class Drag : public Force
    {
    public:
        Drag(Kinetic *obj, double dragCoe = 0.0) : obj(obj), dragCoe(dragCoe) {}
        Vector getCurrentValue() const override;
        double getDragCoe() const { return dragCoe; }
        void setDragCoe(double c) { dragCoe = c; }

    private:
        Kinetic *obj; // not owning
        double dragCoe{0.0};
    };

} // namespace pe
