#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class matrix7x6
{
private:
  vector<vector<int>> m;
  const int maxR = 7 - 1;
  const int maxC = 6 - 1;

public:
  matrix7x6()
  {
    m = vector<vector<int>>(7, vector<int>(6, 0));
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
    for (auto &row : m)
    {
      for (int &celda : row)
      {
        celda = a;
        a++;
      }
    }
  }
  void printM()
  {
    for (const auto &row : m)
    {
      for (const int val : row)
      {
        cout << setw(2) << val << " ";
      }
      cout << endl;
    }
  }

  void explore(int R, int C, int dR, int dC)
  {
    while (R >= 0 && R <= maxR && C >= 0 && C <= maxC)
    {
      // acá va la función que detecta un mismo numero 4 veces
      cout << m[R][C] << " ";
      R += dR * -1; // se multiplica por -1 para que -1 sea sur
      C += dC;
    }
    cout << endl;
  }

  void exploreDirections(int R, int C)
  {
    // Convirtiendo coordenadas humanas en computacionales
    R--;
    C--;
    cout << endl
         << "iniciando" << endl;
    // ERROR
    if (R > maxR || C > maxC || C < 0 || R < 0) return;

    // SOUTH
    explore(R, C, -1, 0);

    // WEST
    explore(R, C, 0, -1);
    
    // EAST
    explore(R, C, 0, 1);
    
    // N_WESTH
    explore(R, C, 1, -1);
    
    // N_EAST
    explore(R, C, 1, 1);
    
    // S_WEST
    explore(R, C, -1, -1);
    
    // S_EAST
    explore(R, C, -1, 1);
  }
};

int main()
{

  matrix7x6 mat;
  mat.printM();
  mat.exploreDirections(3, 3);

  cout << " Esto sirve " << endl;

  return 0;
}
