#include"../include/univers.hxx"
#include"../include/vecteur.hxx"
#include"../include/particule.hxx"
#include<random>
#include<vector>

Univers::Univers(int dim, int nbParticules) : dim(dim), nbParticules(nbParticules){
    particules = std::vector<Particule>(nbParticules, Particule(Vecteur(0,0,0), Vecteur(0,0,0), 1.0, 0, "grille"));
}

void Univers::avance(Particule &p, const Vecteur dir){
    Vecteur new_dir = p.getPosition()+dir;
    p.setPosition(new_dir);
}

std::vector<Vecteur> Univers::calcul_forces(){
    std::vector<Vecteur> forces(particules.size(), Vecteur(0,0,0));
    for(size_t i = 0; i < particules.size(); ++i){
        Particule& p1 = particules[i];
        Vecteur f_total;
        for(size_t j = i+1; j < particules.size(); ++j){
            if(i != j){
                Particule& p2 = particules[j];
                Vecteur r = p2.getPosition() - p1.getPosition();
                double dist = r.norme();
                if(dist>1e-5){
                    double force = (p1.getMasse()*p2.getMasse())/(dist*dist*dist);
                    f_total += r * force;
                    forces[i] += f_total;
                    forces[j] -= f_total;
                }
            }
        }
    }
    return forces;
}


std::vector<Vecteur> Univers::calcul_forces_v2(){
    std::vector<Vecteur> forces(particules.size(), Vecteur(0,0,0));
    for(size_t i = 0; i < particules.size(); ++i){
        Particule& p1 = particules[i];
        Vecteur f_total;
        for(size_t j = 0; j < particules.size(); ++j){
            if(i != j){
                Particule& p2 = particules[j];
                Vecteur r = p2.getPosition() - p1.getPosition();
                double dist = r.norme();
                if(dist>1e-5){
                    double force = (p1.getMasse()*p2.getMasse())/(dist*dist*dist);
                    f_total += r * force;
                }
            }
        }
        forces[i]= f_total;
    }
    return forces;
}

void Univers::setVitesse(const Vecteur &v){
    for (Particule& p : particules){
        p.setVitesse(v);
    }
}

void Univers::affiche_univers() const {
    for(size_t i = 0; i < particules.size(); ++i){
        const Particule& p = particules[i];
        std::cout << "id = " << p.getId() << std::endl;
        std::cout << "position = " << p.getPosition() << std::endl;
    }
}

void Univers::stormer_verlet(std::vector<Vecteur> &f_old, double dt, double tend){
    std::vector<Vecteur> F = calcul_forces();
    double t = 0;
    double x=0;
    double y=0;
    double z=0;
    double vx=0;
    double vy=0;
    double vz=0;
    while (t < tend) {
        t = t + dt;
        for(size_t i = 0; i < particules.size(); ++i){
            Particule& p = particules[i]; 
            x = (p.getPosition()[0] + (p.getVitesse()[0] + (0.5/p.getMasse())*((F[i])[0])*dt)*dt);
            y = (p.getPosition()[1] + (p.getVitesse()[1] + (0.5/p.getMasse())*((F[i])[1])*dt)*dt);
            z = (p.getPosition()[2] + (p.getVitesse()[2] + (0.5/p.getMasse())*((F[i])[2])*dt)*dt);
            Vecteur v = Vecteur (x,y,z);
            p.setPosition(v);
        }
        //Calculer les forces F
        F = calcul_forces();
        for(size_t i = 0; i < particules.size(); ++i){
            Particule& p = particules[i];
            vx = p.getVitesse()[0] +  dt*(0.5/p.getMasse())*(F[i][0] + f_old[i][0]);
            vy = p.getVitesse()[1] + dt*(0.5/p.getMasse())*(F[i][1] + f_old[i][1]);
            vz = p.getVitesse()[2] + dt*(0.5/p.getMasse())*(F[i][2] + f_old[i][2]);
            Vecteur v = Vecteur (vx,vy,vz);
            p.setVitesse(v);
        }
        f_old = F;
    }
}

void Univers::ajouterParticule(const Particule &p) {
    particules.push_back(p);
}
