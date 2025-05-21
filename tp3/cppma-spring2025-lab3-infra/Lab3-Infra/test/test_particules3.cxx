#include"../include/particule.hxx"
#include"../include/univers.hxx"
#include"../include/vecteur.hxx"
#include<math.h>
#include<chrono>


void init_univers_uniforme(Univers &univers, int n, double deb,double fin){
    double step = (fin - deb) / (n - 1);
    int id = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                double x = deb + i * step;
                double y = deb + j * step;
                double z = deb + k * step;

                Vecteur pos(x, y, z);
                Vecteur vit(0.0, 0.0, 0.0);
                double masse = 1.0;

                Particule p(pos, vit, masse, id++, "grille");
                univers.ajouterParticule(p);
            }
        }
    }
}

int main(){
    for (int k=3; k<=7; k++){
        Univers u = Univers(3,pow(pow(2,k),3));
        auto start = std::chrono::high_resolution_clock::now();

        init_univers_uniforme(u, pow(2,k), 0, 1.0);
        std::vector<Vecteur> fold = u.calcul_forces_v2();

        //u.affiche_univers();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Time taken: " << elapsed.count() << " seconds (k=" <<k << ")"<< std::endl;
    }
    
    return 1;
}