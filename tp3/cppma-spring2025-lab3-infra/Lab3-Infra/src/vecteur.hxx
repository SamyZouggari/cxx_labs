# pragma once

#include<iostream>

class Vecteur {
    private:
    float x, y, z;

    public:
    Vecteur(float x=0, float y=0, float z=0);
    float getX() const ;
    float getY() const;
    float getZ() const;

    Vecteur &operator+=(const Vecteur &other);
    Vecteur &operator-=(const Vecteur &other);
    bool operator==(const Vecteur &other);
    bool operator!=(const Vecteur &other);
    Vecteur &operator*=(const int i);
    float &operator[](int i);
    Vecteur &operator=(const Vecteur &other);
};

std::ostream &operator<<(std::ostream &out,const Vecteur &v);
Vecteur operator+(const Vecteur &v, const Vecteur &other);
Vecteur operator-(const Vecteur &v, const Vecteur &other);
Vecteur operator*(const Vecteur &v, const int i);