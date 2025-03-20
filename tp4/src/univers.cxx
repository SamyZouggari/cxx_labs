#include"univers.hxx"
#include<random>
#include<vector>

Univers::Univers(int dim, int nbParticules, float deb, float fin, Vecteur ld, float rcut):
    dim(dim), nbParticules(nbParticules), ld(ld), rcut(rcut)
    {
        // On caclule le nombre de cellule de chaque direction
        nc = Vecteur(floor(ld[0]/rcut), floor(ld[1]/rcut), floor(ld[2]/rcut));

        //Création des particules
        this->particules = (Particule*) malloc(nbParticules * sizeof(Particule));

        // std::vector<Particule> particules;
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
            // particules.push_back(p);
            particules[i] = p;

            // Après sa creation on va dans le meme temps attribuer une cellule à notre particule fraichement crée
            // Taille de la cellule dans chaque direction de l'espace
            int taillex = ld.getX()/nc.getX();
            int tailley = ld.getY()/nc.getY();
            int taillez = ld.getZ()/nc.getZ();

            // Nous permet de savoir où se positionne la cellule dans notre univers
            int cellx = floor(p.getPosition().getX() / taillex);
            int celly = floor(p.getPosition().getY() / tailley);
            int cellz = floor(p.getPosition().getY() / taillez);

            //linéarisation du vecteur
            int positionAbsolue = cellx*nc[2]*nc[1] + celly*nc[2] + cellz;


            auto it = cellules.find(positionAbsolue);
            if(it !=cellules.end()){
                // Si on a déjà vu cette clef, c'est que le cellule contient déjà une ou plusieurs particules
                it->second.addParticule(p); // Est-ce que c'est vraiment utile qu'une Cellule soit au courant des Particules qu'elle contient ???
            }
            else {
                // Sinon c'est que la cellule ne contient pas encore de particule
                cellules.insert({positionAbsolue, Cellule(Vecteur(cellx, celly,cellz))});
            }
        }
    }

// Pour moi la méthode qui suit est inutile
// void Univers::createParticules(){
//     std::vector<Particule> particules;
//     Vecteur debut = Vecteur(0,0,0);
//     Vecteur fin = ld;
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_real_distribution<> disx(0, fin.getX());
//     std::uniform_real_distribution<> disy(0, fin.getY());
//     std::uniform_real_distribution<> disz(0, fin.getZ());

//     //création des particules
//     for (int i=0 ; i<nbParticules ; i++){
//         float x = disx(gen);
//         float y = disy(gen);
//         float z = disz(gen);
//         Vecteur v = Vecteur(x,y,z);
//         Particule p = Particule(v, Vecteur(1.0,1.0,0.0), 1.0,i,"particule");
//         particules[i] = p;
//     }
    
//     //Attribution des particules aux cellules
//     for (Particule &p : particules){
//         int taillex = ld.getX()/nc.getX();
//         int tailley = ld.getY()/nc.getY();
//         int taillez = ld.getZ()/nc.getZ();
//         int cellx = floor(p.getPosition().getX() / taillex);
//         int celly = floor(p.getPosition().getY() / tailley);
//         int cellz = floor(p.getPosition().getY() / taillez);

//         //linéarisation du vecteur
//         int positionAbsolue = cellx*nc[2]*nc[1] + celly*nc[2] + cellz;

//         auto it = cellules.find(positionAbsolue);
//         if(it !=cellules.end()){
//             it->second.addParticule(p);
//         }
//         else {
//             cellules.insert({positionAbsolue, Cellule(Vecteur(cellx, celly,cellz))});
//         }
//         //recherche dans le dictionnairetrouver un element dans un dictionnaire c++
        
//     }
// }

Univers::~Univers() {
    free(particules);
}