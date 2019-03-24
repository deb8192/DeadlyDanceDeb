#ifndef CargadorPuzzles_HPP
#define CargadorPuzzles_HPP

#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include "pugixml.hpp"
#include "Puzzles/Puzzle.hpp"
#include <vector>

using namespace std;

class CargadorPuzzles
{
    public:
        CargadorPuzzles();
        ~CargadorPuzzles();

        void CargarPuzzlesXml();
        Puzzle* GetPuzzle(unsigned short pos);
        const char* GetFondo();

    private:
        vector<Puzzle*> _listaPuzzles;
        const char* _fondo;
};
#endif