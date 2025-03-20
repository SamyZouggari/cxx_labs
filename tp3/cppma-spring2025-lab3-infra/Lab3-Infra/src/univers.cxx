#include"univers.hxx"
#include"particule.hxx"
#include<random>
#include<vector>

Univers::Univers(int dim, int nbParticules, float deb, float fin) : dim(dim), nbParticules(nbParticules){
    std::vector<Particule> points;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(deb, fin);

    for (int i=0 ; i<nbParticules ; i++){
        float x = dis(gen);
        float y = dis(gen);
        float z = dis(gen);
        Vecteur v = Vecteur(x,y,z);
        Particule p = Particule(v, Vecteur(1.0,1.0,1.0), 1.0,i,"particule");
        points.push_back(p);
    }
    particules = points;
}

void Univers::avance(Particule &p, const Vecteur dir){
    Vecteur new_dir = p.getPosition()+dir;
    p.setPosition(new_dir);
}

std::vector<float> Univers::calcul_forces(){
    std::vector<float> forces;
    for(Particule& p1 : particules){
        float somme = 0;
        for(Particule& p2 : particules){
            if(p1.getId() != p2.getId())    {
                float dist = p1.calculateDistance(p2);
                if(dist>1e-5){
                    somme += (p1.getMasse()*p2.getMasse())/pow(dist,2);
                }
            }
        }
        forces.push_back(somme);
    }
    return forces;
}

void Univers::setVitesse(const Vecteur &v){
    for (Particule& p : particules){
        p.setVitesse(v);
    }
}

void Univers::display_univers(){
    for(const Particule &p : particules) {
        std::cout << "id = " << p.getId() << std::endl;
        std::cout << "position = " << p.getPosition() << std::endl;
    }
}

void Univers::stromer_verlet(std::vector<float> f_old, float dt, float tend){
    std::vector<float> F = calcul_forces();
    float t = 0;
    float x=0;
    float y=0;
    float z=0;
    float vx=0;
    float vy=0;
    float vz=0;
    while (t < tend) {
        t = t + dt;
        auto it = F.begin();
        for(Particule& p : particules){ 
            x = (p.getPosition()[0] + (p.getVitesse()[0] + (0.5/p.getMasse())*(*it)*dt)*dt);
            y = (p.getPosition()[1] + (p.getVitesse()[1] + (0.5/p.getMasse())*(*it)*dt)*dt);
            z = (p.getPosition()[2] + (p.getVitesse()[2] + (0.5/p.getMasse())*(*it)*dt)*dt);
            Vecteur v = Vecteur (x,y,z);
            p.setPosition(v);
            std::advance(it,1);
        }
        //Calculer les forces F
        F = calcul_forces();
        auto itF = F.begin();
        auto itF_old = f_old.begin();
        for(Particule& p : particules){
            vx = p.getVitesse()[0] +  dt*(0.5/p.getMasse())*(*itF + *itF_old);
            vy = p.getVitesse()[1] + dt*(0.5/p.getMasse())*(*itF + *itF_old);
            vz = p.getVitesse()[2] + dt*(0.5/p.getMasse())*(*itF + *itF_old);
            Vecteur v = Vecteur (vx,vy,vz);
            p.setVitesse(v);
            std::advance(itF,1);
            std::advance(itF_old,1);
        }
    }
}
