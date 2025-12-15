#include "../include/GameObject.hpp"
#include <chrono>
#include <thread>

namespace pe
{

    GameObject::GameObject(double x, double y)
        : ObjectPosition(x, y), velocity(), acceleration(), appliedForce(std::make_shared<ValueForce>()), forceList(), CameraPosition()
    {
        forceList.push_back(appliedForce);
    }

    GameObject::GameObject() : GameObject(0, 0) {}
    GameObject::GameObject(const Vector &v) : GameObject(v.getX(), v.getY()) {}

    GameObject::~GameObject() = default;

    void GameObject::update(long elapsedTime)
    {
        if (isUpdate)
        {
            updateRelativePosition();
            updatePosition(elapsedTime);
        }
    }

    void GameObject::updatePosition(long elapsedTime)
    {
        double elapsedSeconds = elapsedTime / 1e9;
        Vector netF;
        for (const auto &f_ptr : forceList)
        {
            if (f_ptr)
                netF = netF.add(f_ptr->getCurrentValue());
        }
        acceleration = netF.multiply(1.0 / mass);
        velocity = velocity.add(acceleration.multiply(elapsedSeconds));
        ObjectPosition = ObjectPosition.add(velocity.multiply(elapsedSeconds));
    }

    void GameObject::updateRelativePosition()
    {
        position = ObjectPosition.add(CameraPosition.multiply(-1.0));
    }

    Vector GameObject::getRelativePosition() const { return position; }

    Vector GameObject::getPosition() const { return ObjectPosition; }
    void GameObject::setPosition(const Vector &v) { ObjectPosition = v; }
    void GameObject::addDisplacement(const Vector &v) { ObjectPosition = ObjectPosition.add(v); }
    Vector GameObject::getVelocity() const { return velocity; }
    void GameObject::setVelocity(const Vector &v) { velocity = v; }
    void GameObject::addVelocity(const Vector &v) { acceleration = acceleration.add(v); }
    Vector GameObject::getAcceleration() const { return acceleration; }
    void GameObject::setAcceleration(const Vector &v) { acceleration.set(v); }
    void GameObject::addAcceleration(const Vector &v) { addAppliedForce(v); }

    void GameObject::setAppliedForce(const Vector &v) { appliedForce->set(v); }
    void GameObject::addAppliedForce(const Vector &v) { appliedForce->set(appliedForce->getCurrentValue().add(v)); }

    void GameObject::setAppliedForce(const Vector &v, int durationMillis)
    {
        appliedForce->set(v);
        std::thread([this, durationMillis]()
                    {
        std::this_thread::sleep_for(std::chrono::milliseconds(durationMillis));
        appliedForce->set(Vector()); })
            .detach();
    }

    Vector GameObject::getAppliedForce() const { return appliedForce->getCurrentValue(); }

    void GameObject::addForce(const std::shared_ptr<Force> &f) { forceList.push_back(f); }

    std::vector<Vector> GameObject::getForceValues() const
    {
        std::vector<Vector> out;
        out.reserve(forceList.size());
        for (const auto &f : forceList)
        {
            if (f)
                out.push_back(f->getCurrentValue());
        }
        return out;
    }

    std::vector<Vector> GameObject::getForceList() const
    {
        return getForceValues();
    }

    void GameObject::setCameraPosition(const Vector &v) { CameraPosition.set(v); }
    void GameObject::addCameraPosition(const Vector &v) { CameraPosition.set(CameraPosition.add(v)); }
    Vector GameObject::getCameraPosition() const { return CameraPosition; }

    void GameObject::setMass(double m) { mass = m; }
    double GameObject::getMass() const { return mass; }

    void GameObject::close()
    {
        forceList.clear();
        velocity = Vector();
        position = Vector();
        isUpdate = false;
    }

    double GameObject::getFrictionCoe() const { return frictionCoe; }
    void GameObject::setFrictionCoe(double friction) { frictionCoe = friction; }

    std::array<double, 4> GameObject::getElasticity() const { return elasticity; }
    void GameObject::setElasticity(const std::array<double, 4> &e) { elasticity = e; }

    bool GameObject::isCollide(const void * /*o*/) const { return false; }

    bool GameObject::isClose() const { return !isUpdate; }

} // namespace pe
