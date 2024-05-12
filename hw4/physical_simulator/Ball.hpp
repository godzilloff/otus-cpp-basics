#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
public:
    inline Ball() = default;
    Ball(const Point& p_coordinates_center, const Velocity& p_velocity_vector,
         const Color& p_color, double p_radius, bool p_isCollidable);

    void InitBall(const Point& p_coordinates_center,
                  const Velocity& p_velocity_vector, const Color& p_color,
                  double p_radius, bool p_isCollidable);

    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
    bool getCollidable() const;

 private:
    Point coordinates_center;
    Velocity velocity_vector;
    Color color;
    double radius = 0.;
    bool isCollidable = false;
    double mass = 0.;
    double calcMass();

};


inline std::ifstream& operator>>(std::ifstream& stream, Ball& p_ball) {
    Point center_ball;
    Velocity velocity_ball;
    Color color_ball;
    double radius = 0.;
    bool isCollidable = false;

    stream >> center_ball >> velocity_ball >> color_ball >> radius;
    stream >> std::boolalpha >> isCollidable;

    p_ball.InitBall(center_ball, velocity_ball, color_ball, radius,
                    isCollidable);
    return stream;
}
