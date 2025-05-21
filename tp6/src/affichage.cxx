#include"affichage.hxx"
#include<iostream>
#include<fstream>
#include<filesystem>

// classe qui permet de créer les fichier .vtk nécessaires à la visualisation sur Paraview

Affichage::Affichage(Univers &u): u(u){};

void Affichage::create_vtk(std::string filepath){
    namespace fs = std::filesystem;

    fs::path path(filepath);
    fs::path dir = path.parent_path();

    // Crée le répertoire s'il n'existe pas
    if (!fs::exists(dir)) {
        if (!fs::create_directories(dir)) {
            std::cerr << "Erreur : impossible de créer le dossier " << dir << std::endl;
            return;
        }
    }
    std::ofstream fichier(filepath, std::ios::out | std::ios::trunc);

    if(!fichier.is_open()){
        std::cerr << "Impossible d'ouvrir le fichier" << filepath << std::endl;
        return;
    }

    fichier << "<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"LittleEndian\">" << std::endl;

    const auto& particules = u.get_particules();

    fichier << "\t<UnstructuredGrid>" << std::endl;
    int nbPart = 0;
    for (const auto& [key, cell_pair] : u.getCellules()) {
        nbPart += cell_pair.second.size();
    }
    fichier << "\t\t <Piece NumberOfPoints=\"" << nbPart << "\" NumberOfCells=\"" << nbPart << "\">" << std::endl;
    fichier << "\t\t\t<Points>" << std::endl;
    fichier << "\t\t\t\t<DataArray name=\"Position\" type=\"Float32\" NumberOfComponents=\"3\" format=\"ascii\">" << std::endl;
    fichier << "\t\t\t\t\t";
    for(const auto& [key, cell_pair] : u.getCellules()){
        for(const auto& [id, part] : cell_pair.second){
            fichier << part.getPosition().getX() << " " << part.getPosition().getY() << " " << 0 << " ";
        }
    }
    fichier << std::endl;
    fichier << "\t\t\t\t</DataArray>" << std::endl;
    fichier << "\t\t\t</Points>" << std::endl;
    fichier << "\t\t\t<PointData Vectors=\"vector\">" << std::endl;
    fichier << "\t\t\t\t<DataArray type=\"Float32\" Name=\"Velocity\" NumberOfComponents=\"3\" format=\"ascii\">" << std::endl;
    fichier << "\t\t\t\t\t";
    for(const auto& [key, cell_pair] : u.getCellules()){
        for(const auto& [id, part] : cell_pair.second){
            fichier << part.getVitesse().getX() << " " << part.getVitesse().getY() << " " << 0 << " ";
        }
    }
    fichier << std::endl;
    fichier << "\t\t\t\t</DataArray>" << std::endl;
    fichier << "\t\t\t\t<DataArray type=\"Float32\" Name=\"Masse\" format=\"ascii\">" << std::endl;
    fichier << "\t\t\t\t\t";
    for(const auto& [key, cell_pair] : u.getCellules()){
        for(const auto& [id, part] : cell_pair.second){
            fichier << part.getMasse() << " ";
        }
    }
    fichier << std::endl;
    fichier << "\t\t\t\t</DataArray>" << std::endl;
    fichier << "\t\t\t</PointData>" << std::endl;
    fichier << "\t\t\t<Cells>" << std::endl;

    // connectivité : chaque cellule correspond à un seul point
    fichier << "\t\t\t\t<DataArray type=\"Int32\" Name=\"connectivity\" format=\"ascii\">" << std::endl;
    for (int i = 0; i < nbPart; ++i) {
        fichier << i << " ";
    }
    fichier << std::endl;
    fichier << "\t\t\t\t</DataArray>" << std::endl;

    // offsets
    fichier << "\t\t\t\t<DataArray type=\"Int32\" Name=\"offsets\" format=\"ascii\">" << std::endl;
    for (int i = 1; i <= nbPart; ++i) {
        fichier << i << " ";
    }
    fichier << std::endl;
    fichier << "\t\t\t\t</DataArray>" << std::endl;

    // types : VTK_VERTEX = 1
    fichier << "\t\t\t\t<DataArray type=\"UInt8\" Name=\"types\" format=\"ascii\">" << std::endl;
    for (int i = 0; i < nbPart; ++i) {
        fichier << "1 ";
    }
    fichier << std::endl;
    fichier << "\t\t\t\t</DataArray>" << std::endl;

    fichier << "\t\t\t</Cells>" << std::endl;


    fichier << "\t\t</Piece>" << std::endl;
    fichier << "\t</UnstructuredGrid>" << std::endl;
    fichier << "</VTKFile>" << std::endl;


    fichier.close();
}    
