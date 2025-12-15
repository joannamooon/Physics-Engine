#pragma once

#include "Vector.hpp"

namespace pe
{

    class CameraView
    {
    public:
        virtual ~CameraView() = default;
        virtual void setCameraPosition(const Vector &v) = 0;
        virtual void addCameraPosition(const Vector &v) = 0;
        virtual Vector getCameraPosition() const = 0;
    };

} // namespace pe
