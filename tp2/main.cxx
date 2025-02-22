#include<set>
#include<list>
#include<deque>
#include<vector>
#include<string>
#include<random>
#include<iostream>
#include<chrono>
#include<math.h>

class Particule;
void stromer_valet(std::list<Particule> particuleListe,std::list<float> f_old, float dt, float tend);
std::list<float> calculateForce(std::list<Particule> listeParticule);


class Particule {
    public:
    Particule(float x, float y, float vitessex,float vitessey, float masse, int id, std::string categorie) :
    x(x), y(y), vitessex(vitessex), vitessey(vitessey), masse(masse), id(id), categorie(categorie) {}

    int getId(){
        return id;
    }

    float & getX(){
        return x;
    }

    float & getVitessex(){
        return vitessex;
    }
    float & getVitessey(){
        return vitessey;
    }

    float & getY(){
        return y;
    }

    float & getMasse(){
        return masse;
    }

    float calculateDistance(Particule other){
        float x_other = other.getX();
        float y_other = other.getY();
        return (sqrt(pow(x-x_other,2) + pow(y-y_other,2)));
    }

    std::string getCategorie() {
        return categorie;
    }

    private:
    float x, y;
    float vitessex, vitessey;
    float masse;
    int id;
    std::string categorie;
};

int main(){
    std::list<Particule> particuleListe;
    
    
    Particule soleil = Particule(0.0,0.0,0.0,0.0,1.0, 0, "Soleil");
    Particule terre = Particule(0.0,1.0,-1.0,0.0,3.0e-6,1,"Terre");
    Particule jupiter = Particule(0.0,5.36,-0.425,0.0,9.55e-4,2,"Jupiter");
    Particule haley = Particule(34.75,0.0,0.0,0.0296,1.e-14,3,"Haley");

    particuleListe.push_back(soleil);
    particuleListe.push_back(terre);
    particuleListe.push_back(jupiter);
    particuleListe.push_back(haley);

    std::list<float> forces = calculateForce(particuleListe);
    stromer_valet(particuleListe, forces, 0.015, 468.5);

    return 0;
}

std::list<float> calculateForce(std::list<Particule> listeParticule){
    std::list<float> forces;
    
    for(Particule& p1 : listeParticule){
        float somme = 0;
        for(Particule& p2 : listeParticule){
            if(p1.getId() != p2.getId())    {
                float dist = p1.calculateDistance(p2);
                somme += (p1.getMasse()*p2.getMasse())/pow(dist,2);
            }
        }
        forces.push_back(somme);
    }
    return forces;   
    }

void stromer_valet(std::list<Particule> particuleListe,std::list<float> f_old, float dt, float tend){
    std::list<float> F = calculateForce(particuleListe);
    
    float t = 0;
    while (t < tend) {
        t = t + dt;
        auto it = F.begin();
        for(Particule& p : particuleListe){ 
            p.getX() = p.getX()+ dt*(p.getVitessex() + (0.5/p.getMasse())*(*it)*dt);
            
            p.getY() = p.getY()+ dt*(p.getVitessey() + (0.5/p.getMasse())*(*it)*dt);
            std::advance(it,1);
        }
        

        //Calculer les forces F
        F = calculateForce(particuleListe);


        auto itF = F.begin();
        auto itF_old = f_old.begin();
        for(Particule& p : particuleListe){
            p.getVitessex() = p.getVitessex() + dt*(0.5/p.getMasse())*(*itF + *itF_old);

            p.getVitessey() = p.getVitessey() + dt*(0.5/p.getMasse())*(*itF + *itF_old);

            std::advance(itF,1);
            std::advance(itF_old,1);
        }
        
        std::cout << "t = " << t << std::endl;
        for(Particule p : particuleListe){
            std::cout << p.getCategorie() << std::endl;
            std::cout << "x = " << p.getX() << std::endl;
            std::cout << "y = " << p.getY() << std::endl;
        }
    }
}
