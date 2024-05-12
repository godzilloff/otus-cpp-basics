#pragma once
#include "Point.hpp"
#include <cmath>
#include <fstream>

class Velocity {
  public:
    inline Velocity() = default;

    // TODO: комментарии
    inline Velocity(double abs, double angle) {
        const double x = std::cos(angle);
        const double y = std::sin(angle);
        vec = Point{x, y} * abs;
    }

    inline Velocity(const Point& vector) {
        setVector(vector);
    }

    inline void setVector(const Point& vector) {
        vec = vector;
    }

    inline Point vector() const {
        return vec;
    }

  private:
    Point vec;
};

inline std::ifstream& operator>>(std::ifstream& stream, Velocity& p_Velocity) {
    Point vec;
    stream >> vec;
    p_Velocity.setVector(vec);
    return stream;
}

