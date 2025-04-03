#include"particule.hxx"
#include"vecteur.hxx"
#include <iostream>
#include<set>
#include<list>
#include<deque>
#include<vector>
#include<string>
#include<random>
#include<iostream>
#include<chrono>
#include<cmath>

Particule::Particule(Vecteur &position, Vecteur vitesse, float masse, int id, std::string categorie):
masse(masse), id(id), categorie(categorie) {
    this->position = position;
    this->vitesse = vitesse;
}

Particule::Particule()
{
    position = Vecteur(0,0,0);
    vitesse = Vecteur(0,0,0);
    masse=0;
    id=0;
    categorie="defaut";
}

int Particule::getId() const{
    return id;
}

Vecteur Particule::getPosition() const{
    return position;
}

void Particule::setPosition(const Vecteur &v){
    this->position = v;
}

Vecteur Particule::getVitesse() const{
    return vitesse;
}

void Particule::setVitesse(const Vecteur &v){
    this->position = v;
}

float Particule::getMasse() const{
    return masse;
}

float Particule::calculateDistance(Particule other){
    return (sqrt(pow(position[0]-other.getPosition()[0],2) + pow(position[1]-other.getPosition()[1],2) + pow(position[2] - other.getPosition()[2],2)));
}

std::string Particule::getCategorie() const {
    return categorie;
}

// Vecteur Particule::vecteurCylindrique(const Particule &p2) const{
//     float x = p2.getPosition().getX() - getPosition().getX();
//     float y = p2.getPosition().getY() - getPosition().getY();
//     float z = p2.getPosition().getZ() - getPosition().getZ();

//     float r = sqrt(pow(x,2) + pow(y,2));
//     float theta;
//     if (x!=0){
//         theta = atan(y/x);
//     }
//     else {
//         if(y>0){
//             theta = M_PI/2;
//         }
//         else{
//             theta = -M_PI/2;
//         }
//     }
//     Vecteur(r,theta,z);
// }