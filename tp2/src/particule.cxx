#include"particule.hxx"
#include<math.h>


Particule::Particule(double x, double y, double vitessex,double vitessey, double masse, int id, std::string categorie) :
x(x), y(y), vitessex(vitessex), vitessey(vitessey), masse(masse), id(id), categorie(categorie) {}


// Question 6, nous protégeons les données en écriture à l'aide du mot-clé const dans les méthodes d'accès.
int Particule::getId() const{
    return this->id;
}

double Particule::getX() const{
    return this->x;
}

double Particule::getVitessex() const{
    return this->vitessex;
}
double Particule::getVitessey() const{
    return this->vitessey;
}

double Particule::getY() const{
    return this->y;
}

double Particule::getMasse() const{
    return this->masse;
}

double Particule::calculateDistance(const Particule &other) const{
    double x_other = other.getX();
    double y_other = other.getY();
    return (sqrt(pow(x-x_other,2) + pow(y-y_other,2)));
}

std::string Particule::getCategorie() const{
    return this->categorie;
}

bool Particule::operator<(const Particule& other) const {
    return this->id < other.getId();
}
bool Particule::operator==(const Particule& other) const {
    return this->id == other.getId();
}
bool Particule::operator!=(const Particule& other) const {
    return this->id != other.getId();
}