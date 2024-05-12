#include "Ball.hpp"
#include <cmath>

constexpr double PI = 3.14159265358979323846; /* pi */

Ball::Ball(const Point& p_coordinates_center, const Velocity& p_velocity_vector,
     const Color& p_color, double p_radius, bool p_isCollidable)
    : coordinates_center(p_coordinates_center),
      velocity_vector(p_velocity_vector), color(p_color), radius(p_radius),
      isCollidable(p_isCollidable)
{
    mass = calcMass();
};

void Ball::InitBall(const Point& p_coordinates_center,
              const Velocity& p_velocity_vector, const Color& p_color,
              double p_radius, bool p_isCollidable)
{
    coordinates_center = p_coordinates_center;
    velocity_vector = p_velocity_vector;
    color = p_color;
    radius = p_radius;
    isCollidable = p_isCollidable;
    mass = calcMass();
}

/**
 * Задает скорость объекта
 * @param velocity новое значение скорости
 */
void Ball::setVelocity(const Velocity& p_velocity) {
    velocity_vector = p_velocity;
}

/**
 * @return скорость объекта
 */
Velocity Ball::getVelocity() const {
    return velocity_vector;
}

/**
 * @brief Выполняет отрисовку объекта
 * @details объект Ball абстрагирован от конкретного
 * способа отображения пикселей на экране. Он "знаком"
 * лишь с интерфейсом, который предоставляет Painter
 * Рисование выполняется путем вызова painter.draw(...)
 * @param painter контекст отрисовки
 */
void Ball::draw(Painter& painter) const {
    painter.draw(coordinates_center, radius, color);
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Ball::setCenter(const Point& center) {
    coordinates_center = center;
}

/**
 * @return центр объекта
 */
Point Ball::getCenter() const {
    return coordinates_center;
}

/**
 * @brief Возвращает радиус объекта
 * @details обратите внимание, что метод setRadius()
 * не требуется
 */
double Ball::getRadius() const {
    return radius;
}

/**
 * @brief Возвращает массу объекта
 * @details В нашем приложении считаем, что все шары
 * состоят из одинакового материала с фиксированной
 * плотностью.
 */
double Ball::getMass() const {
    return mass;
}

/**
 * @brief Рассчитывает массу объекта
 * @details В нашем приложении считаем, что все шары
 * состоят из одинакового материала с фиксированной
 * плотностью.
 */
double Ball::calcMass() {
    return (PI * pow(radius, 3) * 4. / 3.);
}

/**
 * @brief Возвращает флаг объекта по реакции на столкновение
 * @details bool
 */
bool Ball::getCollidable() const {
    return isCollidable;
}
