#include"particule.hxx"
#include<list>
#include<random>
#include<vector>
#include<deque>
#include<set>
#include<string>
#include<iostream>
#include<chrono>


//Création d'une fonction universelle pour créer des particules, à l'aide d'un template, pour pouvoir l'utiliser avec n'importe quel conteneur.
template <typename Conteneur>
void creation_particules(Conteneur &particuleConteneur, int n, std::string nomConteneur) {
    auto start = std::chrono::high_resolution_clock::now();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    
    for(int i = 0; i < n; ++i) {
        double x = dis(gen);
        double y = dis(gen);
        double vitessex = dis(gen);
        double vitessey = dis(gen);
        double masse = dis(gen);
        int id = i;
        std::string categorie = "Particule_" + std::to_string(i);
        
        Particule p(x, y, vitessex, vitessey, masse, id, categorie);

        particuleConteneur.emplace_back(p);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Temps de création de " << n << " particules dans un " << nomConteneur << ": " << elapsed.count() << " secondes." << std::endl;
}


// Création d'une fonction pour créer des particules dans un set, car le set ne peut pas être utilisé avec le template ci-dessus (emplace_back pas possible).
// Cette fonction est similaire à celle du dessus à part au moment de l'insertion dans le conteneur.
void creation_particules_set(std::set<Particule>particuleSet, int n) {
    auto start = std::chrono::high_resolution_clock::now();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    
    for(int i = 0; i < n; ++i) {
        double x = dis(gen);
        double y = dis(gen);
        double vitessex = dis(gen);
        double vitessey = dis(gen);
        double masse = dis(gen);
        int id = i;
        std::string categorie = "Particule_" + std::to_string(i);
        
        Particule p(x, y, vitessex, vitessey, masse, id, categorie);
        // Insertion dans le set
        particuleSet.insert(p);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Temps de création de " << n << " particules dans un set : " << elapsed.count() << " secondes." << std::endl;
}

int main(){
    int* tailles = (int*) malloc(sizeof(int)*15);

    // Création d'un vecteur de tailles de particules, nous allons faire des tests de performance sur cette base
    for(int i = 0; i < 15; i++){

        tailles[i] = pow(2, i+6);
    }

    // test sur un std::vector, std::list, std::deque et std::set
    std::vector<Particule> VecteurListe;
    std::list<Particule> ListeParticules;
    std::deque<Particule> DequeParticules;
    std::set<Particule> SetParticules;
    for(int i = 0; i < 15; i++){
        creation_particules(VecteurListe, tailles[i], "std::vector");
        creation_particules(ListeParticules, tailles[i], "std::list");
        creation_particules(DequeParticules, tailles[i], "std::deque");
        creation_particules_set(SetParticules, tailles[i]);
    }

    free(tailles);
    return 0;
}


