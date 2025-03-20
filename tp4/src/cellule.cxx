#include"cellule.hxx"

Cellule::Cellule(const Vecteur &pos):position(pos){};

Vecteur Cellule::getPosition() const{
    return position;
}

std::vector<Particule> Cellule::getParticules() const{
    return particules;
}

Cellule::Cellule() {
        // Initialisation des membres à des valeurs par défaut
        // Si tu as un membre comme 'Vecteur position', tu peux initialiser 'position' à une valeur par défaut
        position = Vecteur(0, 0, 0);  // Exemple d'initialisation
    }

void Cellule::addParticule(const Particule &p){
    particules.push_back(p);
}