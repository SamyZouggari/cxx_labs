#include"vecteur.hxx"
#include<iostream>

Vecteur::Vecteur(double x, double y, double z): x(x), y(y), z(z) {}

double Vecteur::getX() const {
    return x;
}

double Vecteur::getY() const {
    return y;
}
double Vecteur::getZ() const {
    return z;
}

void Vecteur::setX(double x) {
    this->x = x;
}
void Vecteur::setY(double y) {
    this->y = y;
}
void Vecteur::setZ(double z) {
    this->z = z;
}

Vecteur &Vecteur::operator+=(const Vecteur &other){
    x += other.getX();
    y += other.getY();
    z += other.getZ();
    return *this;
}

Vecteur &Vecteur::operator-=(const Vecteur &other){
    x -= other.getX();
    y -= other.getY();
    z -= other.getZ();
    return *this;
}

bool Vecteur::operator==(const Vecteur &other){
    return (x == other.getX() && y == other.getY() && z == other.getZ());
}

bool Vecteur::operator!=(const Vecteur &other){
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

Vecteur &Vecteur::operator=(const Vecteur &other){
    if(*this != other){
        this->x = other.getX();
        this->y = other.getY();
        this->z = other.getZ();
    }
    return *this;
}

std::ostream &operator<<(std::ostream &out,const Vecteur &v){
        out << "(" << v.getX() << "," << v.getY() << "," << v.getZ() << ")";
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