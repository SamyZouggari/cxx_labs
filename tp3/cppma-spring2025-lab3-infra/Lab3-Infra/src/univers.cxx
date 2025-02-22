#include"univers.hxx"
#include"particule.hxx"
#include<random>

Univers::Univers(int nbParticules, float deb, float fin) : nbParticules(nbParticules){
    Particule *points = (Particule*) calloc(nbParticules, sizeof(Particule));
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(deb, fin);

    for (int i=0 ; i<nbParticules ; i++){
        float x = dis(gen);
        float y = dis(gen);
        float z = dis(gen);
        Vecteur v = Vecteur(x,y,z);
        Particule p = Particule(v);

        points[i]= p;
    }
    particules = points;
}

Univers::Univers(const Univers &u){
    nbParticules = u.nbParticules;
    particules = (Particule *) calloc(nbParticules, sizeof(Particule));
    for(int i = 0; i< nbParticules ; i++) {
        particules[i] = u.particules[i];
    }
}