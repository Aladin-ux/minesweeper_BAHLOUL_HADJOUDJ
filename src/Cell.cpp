#include "Cell.hpp"
#include <iostream>
#include <vector>

// Constructeur : on initialise les variables avec le '_' comme tu l'as fait
Cell::Cell()
{
    _mine = false;
    _discovered = false;
    _neighbours = 0;
}

Cell::~Cell()
{
}

// CORRECTION : Accolades remises dans le bon sens et utilisation de _mine
void Cell::add_mine()
{
    _mine = true;
}

// CORRECTION : Utilise _neighbours (avec le underscore)
int Cell::get_neighbours()
{
    return _neighbours;
}

void Cell::set_neighbours(std::vector<std::vector<Cell>> &grid, size_t x, size_t y)
{
    _neighbours = 0;
    if (_mine)
        return;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            // Vérification des bords de la grille
            if (x + i >= 0 && y + j >= 0 && x + i < grid.size() && y + j < grid[0].size())
            {
                if (grid[x + i][y + j].is_a_mine())
                    _neighbours++;
            }
        }
    }
}

// CORRECTION : Utilise _discovered
bool Cell::is_discovered()
{
    return _discovered;
}

// CORRECTION : Utilise _mine
bool Cell::is_a_mine()
{
    return _mine;
}

bool Cell::discover(std::vector<std::vector<Cell>> &grid, size_t x, size_t y)
{
    if (is_a_mine())
        return true;
    
    _discovered = true;

    // Si la case a des voisins minés, on s'arrête là (pas de propagation)
    if (_neighbours > 0)
        return false;

    // Propagation (découverte récursive des cases vides)
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (x + i >= 0 && y + j >= 0 && x + i < grid.size() && y + j < grid[0].size())
            {
                if (!grid[x + i][y + j].is_a_mine() && !grid[x + i][y + j].is_discovered())
                    grid[x + i][y + j].discover(grid, x + i, y + j);
            }
        }
    }
    return false;
}

bool Cell::is_flagged() { return false; }
void Cell::flag() {}
