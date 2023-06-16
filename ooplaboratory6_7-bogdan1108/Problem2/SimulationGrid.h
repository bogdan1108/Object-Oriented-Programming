#include <iostream>

#define MAX_ROWS 100
#define MAX_COLS 100
// forward class declaration for Entity
class Entity;
class SimulationGrid {
private:
    
public:
	Entity* grid[MAX_ROWS][MAX_COLS];
    int rows, cols;
    SimulationGrid(int r, int c);
	// constructor from file
	SimulationGrid(std::string filename);
	// constructor with random entities
	SimulationGrid(int r, int c, int n);
    ~SimulationGrid() {}
    friend std::ostream& operator<<(std::ostream& os, const SimulationGrid& sg);
    Entity* getEntity(int row, int col) const { return grid[row][col]; }
    void setEntity(Entity* e, int row, int col) { grid[row][col] = e; }
    int getRows() const { return rows; }
    int getCols() const { return cols; }

	void simulate(int n);
};

