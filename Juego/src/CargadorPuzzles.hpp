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
        // Puzzles
    	//const int P_OPCION = 1;
    	//const int P_HANOI = 2;
    	//const int P_ARRASTRAR = 3;

        CargadorPuzzles();
        void CargarPuzzlesXml();
        vector<Puzzle> GetPuzzles();

    private:
        vector<Puzzle> listaPuzzles;
};
#endif