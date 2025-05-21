#include"../include/vecteur.hxx"
#include<iostream>
#include<cmath>

Vecteur::Vecteur(double x, double y, double z): x(x), y(y), z(z) {}


Vecteur &Vecteur::operator+=(const Vecteur &other){
    x += other[0];
    y += other[1];
    z += other[2];
    return *this;
}

Vecteur &Vecteur::operator-=(const Vecteur &other){
    x -= other[0];
    y -= other[1];
    z -= other[2];
    return *this;
}

bool Vecteur::operator==(const Vecteur &other) const{
    return (x == other[0] && y == other[1] && z == other[2]);
}

bool Vecteur::operator!=(const Vecteur &other) const{
    return !(*this == other);
}

Vecteur &Vecteur::operator*=(const double i){
    x*=i;
    y*=i;
    z*=i;

    return *this;
}

double &Vecteur::operator[](const int i){
    if(i == 0){
        return x;
    }
    else if (i==1){
        return y;
    }

    else if (i==2) {
        return z;
    }

    else {
        std::cerr << "out of range" << std::endl;
        throw std::out_of_range("Index must be between 0 and 2.");
    }
}

double Vecteur::operator[](const int i) const{
    if(i == 0){
        return x;
    }
    else if (i==1){
        return y;
    }

    else if (i==2) {
        return z;
    }

    else {
        std::cerr << "out of range" << std::endl;
        throw std::out_of_range("Index must be between 0 and 2.");
    }
}

Vecteur &Vecteur::operator=(const Vecteur &other) {
    if(this == &other){
        return *this;
    }
    x = other[0];
    y = other[1];
    z = other[2];

    return *this;
}

std::ostream &operator<<(std::ostream &out,const Vecteur &v){
        out << "(" << v[0] << "," << v[1] << "," << v[2] << ")";
        return out;
    }

Vecteur operator+(const Vecteur &v, const Vecteur &other){
    Vecteur vv = Vecteur(v);
    vv+=other;
    
    return vv;
}

Vecteur operator-(const Vecteur &v, const Vecteur &other){
    Vecteur vv = Vecteur(v);
    vv-=other;
    
    return vv;
}

Vecteur operator*(const Vecteur &v, const double i){
    Vecteur vv = Vecteur(v);
    vv*=i;

    return vv;
}

double Vecteur::norme() const{
    return sqrt(x*x + y*y + z*z);
}