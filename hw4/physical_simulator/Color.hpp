#pragma once

#include <fstream>

class Color {
  public:
    Color();
    Color(double red, double green, double blue);
    double red() const;
    double green() const;
    double blue() const;
    void setColor(double red, double green, double blue);

  private:
    double r{};
    double g{};
    double b{};
};

inline std::istream& operator>>(std::ifstream& stream, Color& color) {
    double r{};
    double g{};
    double b{};
    stream >> r >> g >> b;
    color.setColor(r, g, b);
    return stream;
}

