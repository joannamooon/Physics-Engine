#include "../include/Vector.hpp"
#include <cmath>

namespace pe
{

    Vector::Vector(double x_, double y_) : x(x_), y(y_) {}
    Vector::Vector() : x(0.0), y(0.0) {}
    Vector::Vector(const Vector &v) : x(v.x), y(v.y) {}

    void Vector::set(const Vector &v)
    {
        x = v.x;
        y = v.y;
    }
    double Vector::getX() const { return x; }
    double Vector::getY() const { return y; }
    void Vector::setX(double x_) { x = x_; }
    void Vector::setY(double y_) { y = y_; }

    std::string Vector::toString() const
    {
        std::ostringstream ss;
        ss << "<" << x << "," << y << ">";
        return ss.str();
    }

    Vector Vector::add(const Vector &o) const { return Vector(x + o.x, y + o.y); }
    double Vector::dotProduct(const Vector &o) const { return x * o.x + y * o.y; }
    double Vector::length() const { return std::sqrt(x * x + y * y); }
    Vector Vector::multiply(double coe) const { return Vector(x * coe, y * coe); }
    bool Vector::operator==(const Vector &o) const { return x == o.x && y == o.y; }
    const Vector &Vector::getCurrentValue() const { return *this; }
    double Vector::getAngle() const { return std::atan2(y, x) * 180.0 / std::acos(-1.0); }

    std::ostream &operator<<(std::ostream &os, const Vector &v)
    {
        os << "<" << v.x << "," << v.y << ">";
        return os;
    }

} // namespace pe
