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
  void exploreDirections(int R, int C)
  {
    // Convirtiendo coordenadas humanas en computacionales
    R--;
    C--;
    cout << endl << "iniciando" << endl;
    // ERROR
    if (R > maxR || C > maxC || C < 0 || R < 0)
      return;
    // SOUTH
    for (int i = R, j = C; i <= maxR; i++)
    {
      cout << m[i][j] << " ";
    };
    cout << endl;

    // WEST
    for (int i = R, j = C; j >= 0; j--)
    {
      cout << m[i][j] << " ";
    };
    cout << endl;
    // EAST
    for (int i = R, j = C; j <= maxC; j++)
    {
      cout << m[i][j] << " ";
    };
    cout << endl;
    
    // NORTHWESTH
    for (int i = R, j = C; i >= 0 && j >= 0; i--, j--)
    {
      cout << m[i][j] << " ";
    };
    cout << endl;
    
    // NORTHEAST
    for (int i = R, j = C; i >= 0 && j <= maxC; i--, j++)
    {
      cout << m[i][j] << " ";
    };
    cout << endl;
    // SOUTHWEST
    for (int i = R, j = C; i <= maxR && j >= 0; i++, j--)
    {
      cout << m[i][j] << " ";
    };
    cout << endl;
    // SOUTHEAST
    for (int i = R, j = C; i <= maxR && j <= maxC; i++, j++)
    {
      cout << m[i][j] << " ";
    };
    cout << endl;
  }
};

int main()
{

  matrix7x6 mat;
  mat.printM();
  mat.exploreDirections(1, 5);

  cout << " Esto sirve " << endl;

  return 0;
}
