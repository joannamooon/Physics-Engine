#pragma once

#include "Vector.hpp"

namespace pe
{

    class Force
    {
    public:
        virtual ~Force() = default;
        virtual Vector getCurrentValue() const = 0;
    };

    class ValueForce : public Force
    {
    public:
        ValueForce() : v() {}
        ValueForce(const Vector &vv) : v(vv) {}
        Vector getCurrentValue() const override { return v; }
        void set(const Vector &vv) { v = vv; }

    private:
        Vector v;
    };

} // namespace pe
