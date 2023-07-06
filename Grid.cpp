#include "precomp.h"
#include "Grid.h"

Grid::Grid(int width, int height, int cellSize)
    : m_cellSize(cellSize), m_width(width), m_height(height)
{
    numXcells = width / cellSize;
    numYcells = height / cellSize;
    m_cells.resize(numXcells * numYcells);
}

Grid::~Grid()
{
    // No need to manually delete tanks, as they are not dynamically allocated
}

void Grid::AddTank(Tank* tank)
{
    Cell* cell = GetCell(tank->position);
    AddTank(tank, cell);
}

void Grid::AddTank(Tank* tank, Cell* cell)
{
    cell->tanks.push_back(tank);
    tank->owner_cell = cell;
}

Cell* Grid::GetCell(int x, int y)
{
    int cellX = x / m_cellSize;
    int cellY = y / m_cellSize;
    return &m_cells[cellY * numXcells + cellX];
}

Cell* Grid::GetCell(const vec2& pos)
{
    return GetCell(pos.x, pos.y);
}

int Grid::GetCellOffset(const vec2& pos)
{
    int cellX = static_cast<int>(pos.x) / m_cellSize;
    int cellY = static_cast<int>(pos.y) / m_cellSize;
    return cellY * numXcells + cellX;
}

void Grid::RemoveTank(Tank* tank)
{
    Cell* cell = tank->owner_cell;
    auto& tanks = cell->tanks;
    tanks.erase(std::remove(tanks.begin(), tanks.end(), tank), tanks.end());
    tank->owner_cell = nullptr;
}

vector<Cell*> Grid::GetCells(Particle_beam* beam)
{
    vector<Cell*> cells;
    vec2 beamStart = beam->min_position;
    vec2 beamEnd = beam->max_position;

    int startX = std::max(0, std::min(static_cast<int>(beamStart.x), m_width - 1));
    int startY = std::max(0, std::min(static_cast<int>(beamStart.y), m_height - 1));
    int endX = std::max(0, std::min(static_cast<int>(beamEnd.x), m_width - 1));
    int endY = std::max(0, std::min(static_cast<int>(beamEnd.y), m_height - 1));

    int cellSize = m_cellSize;
    int startCellX = startX / cellSize;
    int startCellY = startY / cellSize;
    int endCellX = endX / cellSize;
    int endCellY = endY / cellSize;

    for (int y = startCellY; y <= endCellY; ++y)
    {
        for (int x = startCellX; x <= endCellX; ++x)
        {
            cells.push_back(&m_cells[y * numXcells + x]);
        }
    }

    return cells;
}
std::vector<Tank*> Grid::GetNeighbouringTanks(const Tank & current_tank)
{
    std::vector<Tank*> neighbouring_tanks;
    vec2 current_position = current_tank.get_position();
    std::vector<Cell*> neighbouring_cells = GetNeighbouringCells(current_position);

    for (Cell* cell : neighbouring_cells) {
        std::vector<Tank*> tanks_in_cell = cell->tanks;
        neighbouring_tanks.insert(neighbouring_tanks.end(), tanks_in_cell.begin(), tanks_in_cell.end());
    }

    return neighbouring_tanks;
}

std::vector<Tank*> Grid::GetNeighbouringTanksByRocket(Rocket& current_rocket) {
    std::vector<Tank*> neighbouring_tanks;
    vec2 current_position = current_rocket.position;
    std::vector<Cell*> neighbouring_cells = GetNeighbouringCells(current_position);

    for (Cell* cell : neighbouring_cells) {
        std::vector<Tank*> tanks_in_cell = cell->tanks;
        neighbouring_tanks.insert(neighbouring_tanks.end(), tanks_in_cell.begin(), tanks_in_cell.end());
    }

    return neighbouring_tanks;
}

vector<Cell*> Grid::GetNeighbouringCells(const vec2& pos)
{
    vector<Cell*> cells;
    int cellX = static_cast<int>(pos.x) / m_cellSize;
    int cellY = static_cast<int>(pos.y) / m_cellSize;

    for (int y = -1; y <= 1; ++y)
    {
        for (int x = -1; x <= 1; ++x)
        {
            int newX = cellX + x;
            int newY = cellY + y;
            if (newX >= 0 && newX < numXcells && newY >= 0 && newY < numYcells)
            {
                cells.push_back(&m_cells[newY * numXcells + newX]);
            }
        }
    }

    return cells;
}

void Grid::SwitchCells(Tank* tank, Cell* cell)
{
    RemoveTank(tank);
    AddTank(tank, cell);
}
