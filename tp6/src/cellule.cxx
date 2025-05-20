#include"cellule.hxx"

Cellule::Cellule(const Vecteur &pos, const Vecteur &taille):position(pos), taille(taille)  {
    // Initialisation des indices (utile pour la visualisation avec paraview)
    if(taille.getZ()==0 && taille.getY()==0){
        // 1D
        indices.push_back(Vecteur(pos.getX(), 0, 0));
        indices.push_back(Vecteur(pos.getX()+ taille.getX(), 0, 0));
    }
    else if(taille.getZ() ==0 ){
        // 2D
        indices.push_back(Vecteur(pos.getX(), pos.getY(), 0));
        indices.push_back(Vecteur(pos.getX()+ taille.getX(), pos.getY(), 0));
        indices.push_back(Vecteur(pos.getX()+ taille.getX(), pos.getY()+taille.getY(), 0));
        indices.push_back(Vecteur(pos.getX(), pos.getY()+taille.getY(), 0));
    }
    else {
        // 3D
        indices.push_back(Vecteur(pos.getX(), pos.getY(), pos.getZ()));
        indices.push_back(Vecteur(pos.getX() + taille.getX(), pos.getY(), pos.getZ()));
        indices.push_back(Vecteur(pos.getX() + taille.getX(), pos.getY() + taille.getY(), pos.getZ()));
        indices.push_back(Vecteur(pos.getX(), pos.getY() + taille.getY(), pos.getZ()));

        indices.push_back(Vecteur(pos.getX(), pos.getY(), pos.getZ() + taille.getZ()));
        indices.push_back(Vecteur(pos.getX() + taille.getX(), pos.getY(), pos.getZ() + taille.getZ()));
        indices.push_back(Vecteur(pos.getX() + taille.getX(), pos.getY() + taille.getY(), pos.getZ() + taille.getZ()));
        indices.push_back(Vecteur(pos.getX(), pos.getY() + taille.getY(), pos.getZ() + taille.getZ()));
    }
};

Vecteur Cellule::getPosition() const{
    return position;
}

std::vector<Vecteur> Cellule::getIndices() const{
    return indices;
}

Cellule::Cellule() {
        // Initialisation des membres à des valeurs par défaut
        // Si tu as un membre comme 'Vecteur position', tu peux initialiser 'position' à une valeur par défaut
        position = Vecteur(0, 0, 0);  // Exemple d'initialisation
    }