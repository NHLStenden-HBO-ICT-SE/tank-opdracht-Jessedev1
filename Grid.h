#pragma once
#include "precomp.h"

namespace Tmpl8 {

    class Cell
    {
    public:
        std::vector<Tank*> tanks;
    };

    class Grid
    {
    public:
        Grid(int width, int height, int cellSize);
        ~Grid();

        //adds tank to cell and determines what cell it is in
        void AddTank(Tank* tank);
        //adds tank to specified cell
        void AddTank(Tank* tank, Cell* cell);
        //gets cell using x,y coordinates
        Cell* GetCell(int x, int y);
        //gets cell using position
        Cell* GetCell(const vec2& pos);
        //Gets cell with clamp
        //vec2 cGetCell(const vec2& pos);
        //Grab offset to cell from array
        int GetCellOffset(const vec2& pos);
        //removes tank from cell
        void RemoveTank(Tank* tank);
        //gets cells from particle_beam
        std::vector<Cell*> GetCells(Particle_beam* beam);

        // Gets neightbouring cells
        std::vector<Tank*> GetNeighbouringTanks(const Tank& current_tank);
        std::vector<Tank*> GetNeighbouringTanksByRocket(Rocket& current_rocket);
        std::vector<Cell*> GetNeighbouringCells(const vec2& pos);

        // Remove and add in one function
        void SwitchCells(Tank* tank, Cell* cell);

    private:
        std::vector<Cell> m_cells;
        int m_cellSize;
        int m_width;
        int m_height;
        int numXcells;
        int numYcells;
        const int OffsetToCells = 2000 / m_cellSize;

    };
}