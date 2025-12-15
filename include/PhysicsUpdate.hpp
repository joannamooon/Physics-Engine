#pragma once

namespace pe
{

    class PhysicsUpdate
    {
    public:
        virtual ~PhysicsUpdate() = default;
        /**
         * Update object state. elapsedTime is in nanoseconds (same as Java version).
         */
        virtual void update(long elapsedTime) = 0;
    };

} // namespace pe
