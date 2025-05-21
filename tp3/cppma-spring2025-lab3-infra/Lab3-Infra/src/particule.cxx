#include"../include/particule.hxx"
#include"../include/vecteur.hxx"
#include <iostream>
#include<set>
#include<list>
#include<deque>
#include<vector>
#include<string>
#include<random>
#include<iostream>
#include<chrono>

Particule::Particule(const Vecteur &position,const Vecteur &vitesse, double masse, int id, std::string categorie):
masse(masse), id(id), categorie(categorie), position(position), vitesse(vitesse) {}

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

double Particule::getMasse() const{
    return masse;
}

std::string Particule::getCategorie() const {
    return categorie;
}