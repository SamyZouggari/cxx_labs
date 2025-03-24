#include"cellule.hxx"

Cellule::Cellule(const Vecteur &pos, const Vecteur &taille):position(pos), taille(taille)  {};

Vecteur Cellule::getPosition() const{
    return position;
}

Cellule::Cellule() {
        // Initialisation des membres à des valeurs par défaut
        // Si tu as un membre comme 'Vecteur position', tu peux initialiser 'position' à une valeur par défaut
        position = Vecteur(0, 0, 0);  // Exemple d'initialisation
    }