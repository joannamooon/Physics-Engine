#include "../include/CollisionRec.hpp"

namespace pe
{

    CollisionRec::CollisionRec(double x, double y, double sizeX_, double sizeY_)
        : GameObject(x, y), sizeX(sizeX_), sizeY(sizeY_)
    {
        colliders[0] = Rect{x + WALL_MARGIN, y - COLLIDER_WIDTH, sizeX - WALL_MARGIN * 2, COLLIDER_WIDTH};
        colliders[1] = Rect{x + WALL_MARGIN, y + sizeY, sizeX - WALL_MARGIN * 2, COLLIDER_WIDTH};
        colliders[2] = Rect{x - COLLIDER_WIDTH, y + WALL_MARGIN, COLLIDER_WIDTH, sizeY - WALL_MARGIN * 2};
        colliders[3] = Rect{x + sizeX, y + WALL_MARGIN, COLLIDER_WIDTH, sizeY - WALL_MARGIN * 2};
    }

    static bool rectsIntersect(const Rect &a, double ax, double ay, double aw, double ah)
    {
        return !(ax > a.x + a.w || ax + aw < a.x || ay > a.y + a.h || ay + ah < a.y);
    }

    CollisionEvent CollisionRec::collideWith(const KineticsWithSize &o) const
    {
        CollisionEvent e;
        if (!isUpdate)
            return e;
        double ox = o.getPosition().getX();
        double oy = o.getPosition().getY();
        double ow = o.getSizeX();
        double oh = o.getSizeY();
        std::array<bool, 4> pos{
            rectsIntersect(colliders[0], ox, oy, ow, oh),
            rectsIntersect(colliders[1], ox, oy, ow, oh),
            rectsIntersect(colliders[2], ox, oy, ow, oh),
            rectsIntersect(colliders[3], ox, oy, ow, oh)};
        std::array<double, 4> depth{0, 0, 0, 0};
        if (pos[0])
            depth[0] = ((oy + oh) - (GameObject::getPosition().getY() - COLLIDER_WIDTH));
        if (pos[1])
            depth[1] = (GameObject::getPosition().getY() + this->getSizeY() + COLLIDER_WIDTH - oy);
        if (pos[2])
            depth[2] = (ox + ow - (GameObject::getPosition().getX() - COLLIDER_WIDTH));
        if (pos[3])
            depth[3] = (GameObject::getPosition().getX() + getSizeX() + COLLIDER_WIDTH - ox);
        e.setCollisionPosition(pos);
        e.setDepth(depth);
        return e;
    }

    void CollisionRec::update(long elapsedTime)
    {
        if (isUpdate)
        {
            updateRelativePosition();
            double px = GameObject::getPosition().getX();
            double py = GameObject::getPosition().getY();
            double camx = getCameraPosition().getX();
            double camy = getCameraPosition().getY();
            colliders[0].x = px + WALL_MARGIN - camx;
            colliders[0].y = (py - COLLIDER_WIDTH) - camy;
            colliders[1].x = px + WALL_MARGIN - camx;
            colliders[1].y = (py + getSizeY()) - camy;
            colliders[2].x = px - COLLIDER_WIDTH - camx;
            colliders[2].y = py + WALL_MARGIN - camy;
            colliders[3].x = px + getSizeX() - camx;
            colliders[3].y = py + WALL_MARGIN - camy;
            updatePosition(elapsedTime);
        }
    }

    void CollisionRec::close()
    {
        GameObject::close();
        isUpdate = false;
    }

    void CollisionRec::setSizeX(double x)
    {
        sizeX = x;
        colliders[0].w = sizeX - WALL_MARGIN * 2;
        colliders[1].w = sizeX - WALL_MARGIN * 2;
    }

    void CollisionRec::setSizeY(double y)
    {
        sizeY = y;
        colliders[2].h = sizeY - WALL_MARGIN * 2;
        colliders[3].h = sizeY - WALL_MARGIN * 2;
    }

} // namespace pe
