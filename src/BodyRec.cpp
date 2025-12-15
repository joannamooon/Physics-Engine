#include "../include/BodyRec.hpp"
#include "../include/CollisionRec.hpp"

namespace pe
{

    BodyRec::BodyRec(double x, double y, double sizeX_, double sizeY_)
        : GameObject(x, y), sizeX(sizeX_), sizeY(sizeY_)
    {
        gravity = std::make_shared<ValueForce>(Vector());
        drag = std::make_shared<Drag>(this, 0.0);
        friction = std::make_shared<ValueForce>(Vector());
        normalForce = std::make_shared<ValueForce>(Vector());
        addForce(gravity);
        addForce(drag);
        addForce(friction);
        addForce(normalForce);
    }

    BodyRec::BodyRec(const Vector &v, double sizeX_, double sizeY_)
        : BodyRec(v.getX(), v.getY(), sizeX_, sizeY_) {}

    Vector BodyRec::getGravity() const { return gravity->getCurrentValue(); }
    Vector BodyRec::getDrag() const { return drag->getCurrentValue(); }
    double BodyRec::getDragCoe() const { return drag->getDragCoe(); }
    Vector BodyRec::getNormalForce() const { return normalForce->getCurrentValue(); }
    Vector BodyRec::getFriction() const { return friction->getCurrentValue(); }

    void BodyRec::setGravity(const Vector &v) { gravity->set(v); }
    void BodyRec::setDragCoe(double dragCoe) { drag->setDragCoe(dragCoe); }
    void BodyRec::setNormalForce(const Vector &v) { normalForce->set(v); }
    void BodyRec::setFriction(const Vector &v) { friction->set(v); }

    bool BodyRec::isCollide(const void *o) const
    {
        if (!o)
            return false;
        const Rect *r = reinterpret_cast<const Rect *>(o);
        if (!r)
            return false;
        double x = GameObject::getPosition().getX();
        double y = GameObject::getPosition().getY();
        double w = sizeX;
        double h = sizeY;
        return !(r->x > x + w || r->x + r->w < x || r->y > y + h || r->y + r->h < y);
    }

} // namespace pe
#include "../include/Body.hpp"
#include "../include/Body.hpp"
#include "../include/Drag.hpp"
#include "../include/Force.hpp"

namespace pe
{

    class BodyRecImpl : public /* placeholder */ GameObject
    {
    };

} // namespace pe
