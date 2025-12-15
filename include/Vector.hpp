#pragma once

#include <cmath>
#include <string>
#include <sstream>
#include <iostream>

namespace pe
{

    class Vector
    {
    private:
        double x;
        double y;

    public:
        Vector(double x, double y);
        Vector();
        Vector(const Vector &v);
        void set(const Vector &v);
        double getX() const;
        double getY() const;
        void setX(double x);
        void setY(double y);
        std::string toString() const;
        Vector add(const Vector &o) const;
        double dotProduct(const Vector &o) const;
        double length() const;
        Vector multiply(double coe) const;
        bool operator==(const Vector &o) const;
        const Vector &getCurrentValue() const;
        double getAngle() const;
        friend std::ostream &operator<<(std::ostream &os, const Vector &v);
    };

} // namespace pe
