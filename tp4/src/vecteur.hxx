#pragma once

#include<iostream>

class Vecteur {
    private:
    double x, y, z;

    public:
    Vecteur(double x=0.0, double y=0.0, double z=0.0);
    double getX() const ;
    double getY() const;
    double getZ() const;

    Vecteur &operator+=(const Vecteur &other);
    Vecteur &operator-=(const Vecteur &other);
    bool operator==(const Vecteur &other);
    bool operator!=(const Vecteur &other);
    Vecteur &operator*=(const double i);
    double &operator[](int i);
    double operator[](int i) const;
    Vecteur &operator=(const Vecteur &other);
};

std::ostream &operator<<(std::ostream &out,const Vecteur &v);
Vecteur operator+(const Vecteur &v, const Vecteur &other);
Vecteur operator-(const Vecteur &v, const Vecteur &other);
Vecteur operator*(const Vecteur &v, const double i);