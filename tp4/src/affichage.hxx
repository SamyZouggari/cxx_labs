#pragma once

#include"univers.hxx"

class Affichage{
    private:
        Univers u;

    public:
        void create_vtk(std::string filename);
        Affichage(Univers u);
};