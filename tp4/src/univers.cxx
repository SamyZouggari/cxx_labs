#include"univers.hxx"
#include<random>
#include<vector>

Univers::Univers(int dim, int nbParticules, float deb, float fin, Vecteur ld, float rcut):
    dim(dim), nbParticules(nbParticules), ld(ld), rcut(rcut)
    {
        nc = Vecteur(floor(ld[0]/rcut), floor(ld[1]/rcut), floor(ld[2]/rcut));

        //Création des particules
        std::vector<Particule> particules;
        Vecteur debut = Vecteur(0,0,0);
        Vecteur fin = ld;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> disx(0, ld[0]);
        std::uniform_real_distribution<> disy(0, ld[1]);
        std::uniform_real_distribution<> disz(0, ld[2]);
        
        for (int i=0 ; i<nbParticules ; i++){
            float x = disx(gen);
            float y = disy(gen);
            float z = disz(gen);
            Vecteur v = Vecteur(x,y,z);
            Particule p = Particule(v, Vecteur(0.0,0.0,0.0), 1.0,i,"particule n° "+i);
            particules.push_back(p);
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
        particules[i] = p;
    }
    
    //Attribution des particules aux cellules
    for (Particule &p : particules){
        int taillex = ld.getX()/nc.getX();
        int tailley = ld.getY()/nc.getY();
        int taillez = ld.getZ()/nc.getZ();
        int cellx = floor(p.getPosition().getX() / taillex);
        int celly = floor(p.getPosition().getY() / tailley);
        int cellz = floor(p.getPosition().getY() / taillez);

        //linéarisation du vecteur
        int positionAbsolue = cellx*nc[2]*nc[1] + celly*nc[2] + cellz;

        auto it = cellules.find(positionAbsolue);
        if(it !=cellules.end()){
            it->second.addParticule(p);
        }
        else {
            cellules.insert({positionAbsolue, Cellule(Vecteur(cellx, celly,cellz))});
        }
        //recherche dans le dictionnairetrouver un element dans un dictionnaire c++
        
    }
    


}



