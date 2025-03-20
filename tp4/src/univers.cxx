#include"univers.hxx"
#include<random>
#include<vector>

Univers::Univers(int dim, int nbParticules, float deb, float fin, Vecteur ld, float rcut):
    dim(dim), nbParticules(nbParticules), ld(ld), rcut(rcut)
    {
        nc = floor(ld[0]/rcut) + floor(ld[1]/rcut) + floor(ld[2]/rcut);
        cellules =(Cellule*) malloc(nc*sizeof(Cellule));

        // Initialisation des cellules
        for (int i = 0; i < nc[0]; i++) {
            for (int j = 0; j < nc[1]; j++) {
                for (int k = 0; k < nc[2]; k++) {
                    cellules[i][j][k] = Cellule(Vecteur(i, j, k));
                }
            }
        }
        //putCellulesVoisines();
    }


Cellule Univers::getCellule(const Vecteur &p) const{
    return cellules[(int) p.getX()][(int) p.getY()][(int) p.getZ()];
}

std::vector<Cellule> Univers::getCellulesVoisines(const Cellule &c) const{
    std::vector<Cellule> voisins;
    Vecteur pos = c.getPosition();
    int nc0 = (int) nc.getX();
    int nc1 = (int) nc.getY();
    int nc2 = (int) nc.getZ();
    int pos0 = (int) pos[0];
    int pos1 = (int) pos[1];
    int pos2 = (int) pos[2];

    // Cas 1D
    if(nc.getX() == 0 && nc.getY() == 0){
        voisins.push_back(getCellule(Vecteur((pos0-1+nc0) % nc0, 0, 0)));
        voisins.push_back(c);  // L'ajout de la cellule elle-même comme voisin
        voisins.push_back(getCellule(Vecteur((pos0+1) % nc0, 0, 0)));
    }
    // Cas 2D
    else if(nc.getX() == 0){
        voisins.push_back(c);  // La cellule elle-même comme voisin
        voisins.push_back(getCellule(Vecteur((pos0-1+nc0) % nc0, pos1, 0)));
        voisins.push_back(getCellule(Vecteur((pos0+1) % nc0, pos1, 0)));
        voisins.push_back(getCellule(Vecteur(pos0, pos1-1, 0)));
        voisins.push_back(getCellule(Vecteur(pos0, (pos1+1) % nc1, 0)));
        voisins.push_back(getCellule(Vecteur((pos0-1+nc0) % nc0, (pos1-1+nc1)%nc1, 0)));
        voisins.push_back(getCellule(Vecteur((pos0-1+nc0) % nc0, (pos1+1) % nc1, 0)));
        voisins.push_back(getCellule(Vecteur((pos0+1) % nc0, (pos1+1) % nc1, 0)));
        voisins.push_back(getCellule(Vecteur((pos0+1) % nc0, (pos1-1+nc1) % nc1, 0)));
    }
    // Cas 3D
    else {
        voisins.push_back(c);  // La cellule elle-même comme voisin
        voisins.push_back(getCellule(Vecteur((pos0-1+nc0) % nc0, pos1, pos2)));
        voisins.push_back(getCellule(Vecteur((pos0+1) % nc0, pos1, pos2)));
        voisins.push_back(getCellule(Vecteur(pos0, (pos1-1+nc1) % nc1, pos2)));
        voisins.push_back(getCellule(Vecteur(pos0, (pos1+1) % nc1, pos2)));
        voisins.push_back(getCellule(Vecteur(pos0, pos1, (pos2-1+nc2) % nc2)));
        voisins.push_back(getCellule(Vecteur(pos0, pos1, (pos2+1) % nc2)));

        // Diagonales dans le plan XY
        voisins.push_back(getCellule(Vecteur((pos0-1+nc0) % nc0, (pos1-1+nc1) % nc1, pos2)));
        voisins.push_back(getCellule(Vecteur((pos0-1+nc0) % nc0, (pos1+1) % nc1, pos2)));
        voisins.push_back(getCellule(Vecteur((pos0+1) % nc0, (pos1-1+nc1) % nc1, pos2)));
        voisins.push_back(getCellule(Vecteur((pos0+1) % nc0, (pos1+1) % nc1, pos2)));

        // Diagonales dans le plan XZ
        voisins.push_back(getCellule(Vecteur((pos0-1+nc0) % nc0, pos1, (pos2-1+nc2) % nc2)));
        voisins.push_back(getCellule(Vecteur((pos0-1+nc0) % nc0, pos1, (pos2+1) % nc2)));
        voisins.push_back(getCellule(Vecteur((pos0+1) % nc0, pos1, (pos2-1+nc2) % nc2)));
        voisins.push_back(getCellule(Vecteur((pos0+1) % nc0, pos1, (pos2+1) % nc2)));

        // Diagonales dans le plan YZ
        voisins.push_back(getCellule(Vecteur(pos0, (pos1-1+nc1) % nc1, (pos2-1+nc2) % nc2)));
        voisins.push_back(getCellule(Vecteur(pos0, (pos1-1+nc1) % nc1, (pos2+1) % nc2)));
        voisins.push_back(getCellule(Vecteur(pos0, (pos1+1) % nc1, (pos2-1+nc2) % nc2)));
        voisins.push_back(getCellule(Vecteur(pos0, (pos1+1) % nc1, (pos2+1) % nc2)));

        // Diagonales dans l'espace 3D
        voisins.push_back(getCellule(Vecteur((pos0-1+nc0) % nc0, (pos1-1+nc1) % nc1, (pos2-1+nc2) % nc2)));
        voisins.push_back(getCellule(Vecteur((pos0-1+nc0) % nc0, (pos1-1+nc1) % nc1, (pos2+1) % nc2)));
        voisins.push_back(getCellule(Vecteur((pos0-1+nc0) % nc0, (pos1+1) % nc1, (pos2-1+nc2) % nc2)));
        voisins.push_back(getCellule(Vecteur((pos0-1+nc0) % nc0, (pos1+1) % nc1, (pos2+1) % nc2)));
        voisins.push_back(getCellule(Vecteur((pos0+1) % nc0, (pos1-1+nc1) % nc1, (pos2-1+nc2) % nc2)));
        voisins.push_back(getCellule(Vecteur((pos0+1) % nc0, (pos1-1+nc1) % nc1, (pos2+1) % nc2)));
        voisins.push_back(getCellule(Vecteur((pos0+1) % nc0, (pos1+1) % nc1, (pos2-1+nc2) % nc2)));
        voisins.push_back(getCellule(Vecteur((pos0+1) % nc0, (pos1+1) % nc1, (pos2+1) % nc2)));
    }
    return voisins;
}


void Univers::displayUnivers(){
    int i = 1;
    int j;
    for(std::vector<std::vector<Cellule>> &deuxd : cellules){
        for(std::vector<Cellule> &und : deuxd){
            for(Cellule &c : und){
        std::cout << "cellule n° " << i << std::endl;
        std::cout << "position de la cellule : " << c.getPosition() << std::endl;
        j=1;
        for(Cellule &vois : getCellulesVoisines(c)){
            std::cout << "cellule voisine n° " << j << std::endl;
            std::cout << "position de la cellule : " << vois.getPosition() << std::endl;
            j+=1;
        }
        i+=1;
    } 
        }
    }
}

void Univers::createParticules(){
    std::vector<Particule> particules;
    Vecteur debut = Vecteur(0,0,0);
    Vecteur fin = ld;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> disx(0, fin.getX());
    std::uniform_real_distribution<> disy(0, fin.getY());
    std::uniform_real_distribution<> disz(0, fin.getZ());

    //création des particules
    for (int i=0 ; i<nbParticules ; i++){
        float x = disx(gen);
        float y = disy(gen);
        float z = disz(gen);
        Vecteur v = Vecteur(x,y,z);
        Particule p = Particule(v, Vecteur(1.0,1.0,0.0), 1.0,i,"particule");
        particules.push_back(p);
    }
    
    //Attribution des particules aux cellules
    for (Particule &p : particules){
        int taille = ld.getX()/nc.getX();
        int cellx = floor(p.getPosition().getX() / taille);
        int celly = floor(p.getPosition().getY() / taille);
        int cellz = floor(p.getPosition().getY() / taille);

        getCellule(Vecteur(cellx, celly, cellz)).addParticule(p);
    }
    


}



