#pragma once

#include "BodyRec.hpp"
#include <string>

namespace pe
{

    class BodyImage : public BodyRec
    {
    public:
        BodyImage(double x, double y, double sizeX, double sizeY, const std::string & /*imagePath*/)
            : BodyRec(x, y, sizeX, sizeY) {}
        BodyImage(const Vector &v, double sizeX, double sizeY, const std::string & /*imagePath*/)
            : BodyRec(v, sizeX, sizeY) {}
        ~BodyImage() override = default;
    };

} // namespace pe
