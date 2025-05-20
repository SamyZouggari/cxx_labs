#include "particule.hxx"
#include <vector>
#include<math.h>
#include <iostream>



std::vector<std::pair<double, double>> calculateForce(std::vector<Particule> VecteurParticule){
    std::vector<std::pair<double, double>> forces(VecteurParticule.size(), {0.0, 0.0});

    
    for(size_t i = 0; i < VecteurParticule.size(); ++i){
        double fx = 0.0;
        double fy = 0.0;
        const Particule& p1 = VecteurParticule[i];
        for(size_t j = 0; j < VecteurParticule.size(); ++j){
            if(i != j){
                const Particule& p2 = VecteurParticule[j];
                // Calculer la distance entre p1 et p2 selon x et y
                double dx = p2.getX() - p1.getX();
                double dy = p2.getY() - p1.getY();

                double dist = std::sqrt(dx * dx + dy * dy);
                if(dist < 1e-6f){
                    continue; // Éviter la division par zéro
                }

                double ux = dx / dist;
                double uy = dy / dist;

                double force_ij= (p1.getMasse()*p2.getMasse())/(dist*dist);
                fx += force_ij * ux;
                fy += force_ij * uy;

            }
        }
        forces[i] = {fx, fy};
    }
    return forces;   
    }

void stormer_verlet(std::vector<Particule> &VecteurParticule,std::vector<std::pair<double,double>> f_old, double dt, double tend){
    std::vector<std::pair<double, double>> F = calculateForce(VecteurParticule);
    
    double t = 0;
    while (t < tend) {
        t = t + dt;
        for(size_t i = 0; i < VecteurParticule.size(); ++i){
            Particule& p = VecteurParticule[i];

            p.setX(p.getX()+ dt*(p.getVitessex() + (0.5/p.getMasse())*(F[i].first)*dt));
            p.setY(p.getY()+ dt*(p.getVitessey() + (0.5/p.getMasse())*(F[i].second)*dt));
        }
        

        //Calculer les forces F
        F = calculateForce(VecteurParticule);

        for(size_t i = 0; i < VecteurParticule.size(); ++i){
            Particule& p = VecteurParticule[i];
            p.setVitessex(p.getVitessex() + dt*(0.5/p.getMasse())*(F[i].first + f_old[i].first));
            p.setVitessey(p.getVitessey() + dt*(0.5/p.getMasse())*(F[i].second + f_old[i].second));
        }
        
        std::cout << "t = " << t << std::endl;
        for(Particule p : VecteurParticule){
            std::cout << p.getCategorie() << std::endl;
            std::cout << "x = " << p.getX() << std::endl;
            std::cout << "y = " << p.getY() << std::endl;
        }
        f_old = F;
    }
}

int main(){
    std::vector<Particule> particuleVecteur;    // Question 2, nous crééons une collection de particules, ici nous avons choisi une liste.
    
    
    Particule soleil = Particule(0.0,0.0,0.0,0.0,1.0, 0, "Soleil");
    Particule terre = Particule(0.0,1.0,-1.0,0.0,3.0e-6,1,"Terre");
    Particule jupiter = Particule(0.0,5.36,-0.425,0.0,9.55e-4,2,"Jupiter");
    Particule haley = Particule(34.75,0.0,0.0,0.0296,1.e-14,3,"Haley");

    particuleVecteur.push_back(soleil);
    particuleVecteur.push_back(terre);
    particuleVecteur.push_back(jupiter);
    particuleVecteur.push_back(haley);

    std::vector<std::pair<double, double>> forces = calculateForce(particuleVecteur);
    stormer_verlet(particuleVecteur, forces, 0.015, 468.5);

    return 0;
}