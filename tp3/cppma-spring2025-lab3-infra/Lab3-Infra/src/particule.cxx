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

Particule::Particule(Vecteur &position, Vecteur vitesse, float masse, int id, std::string categorie):
masse(masse), id(id), categorie(categorie) {
    this->position = position;
    this->vitesse = vitesse;
}

int Particule::getId(){
    return id;
}

Vecteur & Particule::getPosition(){
    return position;
}

Vecteur & Particule::getVitesse(){
    return vitesse;
}

float & Particule::getMasse(){
    return masse;
}

float Particule::calculateDistance(Particule other){
    return (sqrt(pow(position[0]-other.getPosition()[0],2) + pow(position[1]-other.getPosition()[0],2) + pow(position[2] - other.getPosition()[2],2)));
}

std::string Particule::getCategorie() {
    return categorie;
}