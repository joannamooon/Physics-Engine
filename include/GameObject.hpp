#pragma once

#include "PhysicsUpdate.hpp"
#include "Kinetic.hpp"
#include "CameraView.hpp"
#include "Force.hpp"
#include <vector>
#include <array>
#include <thread>
#include <memory>

namespace pe
{

    class GameObject : public PhysicsUpdate, public virtual Kinetic, public CameraView
    {
    public:
        GameObject(double x, double y);
        GameObject();
        GameObject(const Vector &v);
        virtual ~GameObject();

        // PhysicsUpdate
        void update(long elapsedTime) override;

        // Kinetic
        Vector getPosition() const override;
        void setPosition(const Vector &v) override;
        void addDisplacement(const Vector &v) override;
        Vector getVelocity() const override;
        void setVelocity(const Vector &v) override;
        void addVelocity(const Vector &v) override;
        Vector getAcceleration() const override;
        void setAcceleration(const Vector &v) override;
        void addAcceleration(const Vector &v) override;
        void setMass(double m) override;
        double getMass() const override;
        double getFrictionCoe() const override;
        void setFrictionCoe(double frictionCoefficient) override;
        bool isCollide(const void *o) const override;
        std::vector<Vector> getForceList() const override;
        std::array<double, 4> getElasticity() const override;
        void setElasticity(const std::array<double, 4> &elasticity) override;

        // CameraView
        void setCameraPosition(const Vector &v) override;
        void addCameraPosition(const Vector &v) override;
        Vector getCameraPosition() const override;

        // Additional helpers
        void updatePosition(long elapsedTime);
        void updateRelativePosition();
        Vector getRelativePosition() const;
        void setAppliedForce(const Vector &v);
        void addAppliedForce(const Vector &v);
        void setAppliedForce(const Vector &v, int durationMillis);
        Vector getAppliedForce() const;
        void addForce(const std::shared_ptr<Force> &f);
        std::vector<Vector> getForceValues() const;
        virtual void close();
        bool isClose() const;

    protected:
        std::array<double, 4> elasticity{0, 0, 0, 0};
        double frictionCoe{0.0};
        Vector ObjectPosition;
        Vector CameraPosition;
        Vector position; // relative position
        Vector velocity;
        Vector acceleration;
        std::vector<std::shared_ptr<Force>> forceList;
        std::shared_ptr<ValueForce> appliedForce;
        double mass{1.0};
        bool isUpdate{true};
    };

} // namespace pe
