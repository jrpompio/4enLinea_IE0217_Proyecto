#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class matrix7x6
{
private:
  vector<vector<int>> table;
  vector<int> path;
  const int maxR = 7 - 1;
  const int maxC = 6 - 1;

public:
  matrix7x6()
  {
    table = vector<vector<int>>(7, vector<int>(6, 0));
    this->fill();
  }

  void fill()
  {
    /*  Este metodo es solo para desarrollo
        la matriz debe iniciar en cero todos sus valores
        pero se rellenan los valores para verificar
        que el comportamiento sea el esperado.
    */
    int a = 0;
    for (auto &row : table)
    {
      for (int &celda : row)
      {
        celda = 0;
        a++;
      }
    }
  }
  void printM()
  {
    cout << endl;
    for (const auto &row : table)
    {
      for (const int val : row)
      {
        cout << setw(2) << val << " ";
      }
      cout << endl;
    }
  }

  void insert(int column, int player)
  {
    if (table[0][column] == 0)
    {
      table[0][column] = player;
    }
    gravity(column);
  }

  void gravity(int colum)
  {
    int row = 0;
    int temp;
    while (row < maxR)
    {
      if (table[row][colum] != 0 && table[row + 1][colum] == 0)
      {
        // this->printM();  
        // swap de valores
        temp = table[row][colum];
        table[row][colum] = table[row+1][colum];
        table[row+1][colum] = temp;
      }
      row++;
    }
  }

  bool explore(int R, int C, int dR, int dC)
  {
    path.clear();
    while (R >= 0 && R <= maxR && C >= 0 && C <= maxC)
    {
      // acá va la función que detecta un mismo numero 4 veces
      path.push_back(table[R][C]);
      R += dR * -1; // se multiplica por -1 para que -1 sea sur
      C += dC;
    }
    // Solo se revisan los primeros 4 elementos
    if (path.size() > 3 && path[0] == path[1] && path[1] == path[2] && path[2] == path[3])
    {
      cout << "todos iguales" << endl;
      return true;
    }
    return false;
  }

  bool exploreDirections(int R, int C)
  {
    // Convirtiendo coordenadas humanas en computacionales
    R--;
    C--;
    cout << endl
         << "iniciando" << endl;
    // ERROR
    if (R > maxR || C > maxC || C < 0 || R < 0)
      return;

    if (explore(R, C, -1, 0) ||   // SOUTH
        explore(R, C, 0, -1) ||   // WEST
        explore(R, C, 0, 1)  ||   // EAST
        explore(R, C, 1, -1) ||   // N_WESTH
        explore(R, C, 1, 1)  ||   // N_EAST
        explore(R, C, -1, -1)||   // S_WEST
        explore(R, C, -1, 1) ||   // S_EAST
       ) {return true}
    
  }
};

int main()
{

  matrix7x6 mat;
  mat.printM();
  // mat.exploreDirections(1, 3);
  mat.insert(0, -1);
  
  mat.printM();

  cout << " Esto sirve " << endl;

  return 0;
}
