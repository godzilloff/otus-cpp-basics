#include "Physics.hpp"

double dot(const Point& lhs, const Point& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

Physics::Physics(double timePerTick) : timePerTick{timePerTick} {}

void Physics::setWorldBox(const Point& p_topLeft, const Point& p_bottomRight) {
    this->topLeft = p_topLeft;
    this->bottomRight = p_bottomRight;
}

void Physics::update(std::vector<Ball>& balls, const size_t ticks) const {

    for (size_t i = 0; i < ticks; ++i) {
        move(balls);
        collideWithBox(balls);
        collideBalls(balls);
    }
}

void Physics::collideBalls(std::vector<Ball>& balls) const {
    for (auto a = balls.begin(); a != balls.end(); ++a) {
        for (auto b = std::next(a); b != balls.end(); ++b) {

            if (a->getCollidable() && b->getCollidable()) {
                const double distanceBetweenCenters2 =
                    distance2(a->getCenter(), b->getCenter());
                const double collisionDistance =
                    a->getRadius() + b->getRadius();
                const double collisionDistance2 =
                    collisionDistance * collisionDistance;

                if (distanceBetweenCenters2 < collisionDistance2) {
                    processCollision(*a, *b, distanceBetweenCenters2);
                }
            }
        }
    }
}

void Physics::collideWithBox(std::vector<Ball>& balls) const {
    for (Ball& ball : balls) {
        Point p = ball.getCenter();
        const double r = ball.getRadius();
        // определяет, находится ли v в диапазоне (lo, hi) (не включая границы)
        auto isOutOfRange = [](double v, double lo, double hi) {
            return v < lo || v > hi;
        };
        
        // попытка вписать все шары в область
        /*
        if (p.x > 2499 || p.x < -2501) {
            p = p; // временный код для удобства постановки бряки
        }

        if (p.y > 1999 || p.y < -1999) {
            p = p; // временный код для удобства постановки бряки
        }

        if ((p.x + r) > (bottomRight.x+1) ) { 
            p = {bottomRight.x - r, p.y};
            ball.setCenter(p);
        }

        if ((p.x - r) < (topLeft.x-1)) {
            p = {topLeft.x + r, p.y};
            ball.setCenter(p);
        }

        if ((p.y - r) < (topLeft.y-1) ) {
            p = {p.x, topLeft.y + r};
            ball.setCenter(p);
        }

        if ((p.y + r) > (bottomRight.y+1) ) {
            p = {p.x, bottomRight.y - r};
            ball.setCenter(p);
        }

            //*/

        if (isOutOfRange(p.x, topLeft.x + r, bottomRight.x - r)) {
            Point vector = ball.getVelocity().vector();
            vector.x = -vector.x;
            ball.setVelocity(vector);
        } else if (isOutOfRange(p.y, topLeft.y + r, bottomRight.y - r)) {
            Point vector = ball.getVelocity().vector();
            vector.y = -vector.y;
            ball.setVelocity(vector);
        } 
    }
}

void Physics::move(std::vector<Ball>& balls) const {
    for (Ball& ball : balls) {
        Point newPos =
            ball.getCenter() + ball.getVelocity().vector() * timePerTick;
        ball.setCenter(newPos);
    }
}

void Physics::processCollision(Ball& a, Ball& b,
                               double distanceBetweenCenters2) const {
    //if (a.getCollidable() && b.getCollidable())
    //if (a.getCollidable() || b.getCollidable())
    {

        // нормированный вектор столкновения
        const Point normal = (b.getCenter() - a.getCenter()) /
                             std::sqrt(distanceBetweenCenters2);

        // получаем скорость в векторном виде
        const Point aV = a.getVelocity().vector();
        const Point bV = b.getVelocity().vector();

        // коэффициент p учитывает скорость обоих мячей
        const double p = 2 * (dot(aV, normal) - dot(bV, normal)) /
                         (a.getMass() + b.getMass());

        // задаем новые скорости мячей после столкновения
        a.setVelocity(Velocity(aV - normal * p * a.getMass()));
        b.setVelocity(Velocity(bV + normal * p * b.getMass()));
    }
}
