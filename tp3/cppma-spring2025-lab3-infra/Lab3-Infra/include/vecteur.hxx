#pragma once

#include<iostream>

class Vecteur {
    private:
    double x, y, z;

    public:
    Vecteur(double x=0.0, double y=0.0, double z=0.0);
    Vecteur(const Vecteur &other) = default;  // constructeur par recopie par défaut car les attributs sont des types de base.

    //Surcharges d'opérateur
    Vecteur &operator+=(const Vecteur &other);
    Vecteur &operator-=(const Vecteur &other);
    bool operator==(const Vecteur &other) const;
    bool operator!=(const Vecteur &other) const;
    Vecteur &operator*=(const double i);
    double &operator[](const int i);
    double operator[](const int i) const;
    Vecteur &operator=(const Vecteur &other);
    double norme() const;
};

std::ostream &operator<<(std::ostream &out,const Vecteur &v);
Vecteur operator+(const Vecteur &v, const Vecteur &other);
Vecteur operator-(const Vecteur &v, const Vecteur &other);
Vecteur operator*(const Vecteur &v, const double i);