#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

class Matrix6x7
{
private:
  vector<vector<int>> table;
  vector<int> path;
  const int maxR = 6 - 1;
  const int maxC = 7 - 1;

public:
  Matrix6x7()
  {
    table = vector<vector<int>>(6, vector<int>(7, 0));
    this->fill();
  }

  void fill()
  {
    /*  Este metodo es solo para desarrollo
     *        la matriz debe iniciar en cero todos sus valores
     *        pero se rellenan los valores para verificar
     *        que el comportamiento sea el esperado.
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

  bool insert(int column, int player)
  {
    if (table[0][column] == 0)
    {
      table[0][column] = player;
      return true;
    } else return false;
  }

  int gravity(int colum)
  {
    int row = 0;
    int temp;
    bool swap;
    int last;
    while (row < maxR)
    {
      swap = false;
      if (table[row][colum] != 0 && table[row + 1][colum] == 0)
      {
        // this->printM();
        // swap de valores
        temp = table[row][colum];
        table[row][colum] = table[row + 1][colum];
        table[row +1 ][colum] = temp;
        swap = true;
      }
      if (swap) {last = row + 1;}
      else {last = row; break;}
      row++;
    }
    return last;
  }

  bool explore(int R, int C, int dR, int dC)
  {
    path.clear();
    while (R >= 0 && R <= maxR && C >= 0 && C <= maxC)
    {
      // acá va la función que detecta un mismo numero 4 veces
      path.push_back(table[R][C]);
      R += dR ;
      C += dC;
    }
    // Solo se revisan los primeros 4 elementos
    if (path.size() > 3 && path[0] == path[1] && path[1] == path[2] && path[2] == path[3] && path[0] != 0)
    {
      // cout << "todos iguales" << endl;
      return true;
    }
    return false;
  }

  bool exploreDirections(int C, int R)
  {
    // ERROR
    // if (R > maxR || C > maxC || C < 0 || R < 0)
    //  return;

    if (explore(R, C, 1, 0) ||   // SOUTH
      explore(R, C, 0, -1) ||   // WEST
      explore(R, C, 0, 1)  ||   // EAST
      explore(R, C, -1, -1) ||   // N_WESTH
      explore(R, C, -1, 1)  ||   // N_EAST
      explore(R, C, 1, -1)||   // S_WEST
      explore(R, C, 1, 1)   // S_EAST
    ){
      return true;
    } else {return false;}

  }
};

class SaveLoad{
public:
  void save(){

  }
};

int main()
{
  int lastRow;
  bool win;
  Matrix6x7 mat;
  mat.printM();

  mat.insert(0, -1);
  lastRow = mat.gravity(0);
  win = mat.exploreDirections(0, lastRow);
  cout << " win = " << win << endl;

  mat.insert(0, -1);
  lastRow = mat.gravity(0);
  win = mat.exploreDirections(0, lastRow);
  cout << " win = " << win << endl;

  mat.insert(0, 1);
  lastRow = mat.gravity(0);
  win = mat.exploreDirections(0, lastRow);
  cout << " win = " << win << endl;

  mat.insert(0, 1);
  lastRow = mat.gravity(0);
  win = mat.exploreDirections(0, lastRow);
  cout << " win = " << win << endl;

  mat.insert(0, 1);
  lastRow = mat.gravity(0);
  win = mat.exploreDirections(0, lastRow);
  cout << " win = " << win << endl;

  mat.insert(0, 1);
  lastRow = mat.gravity(0);
  win = mat.exploreDirections(0, lastRow);
  cout << " win = " << win << endl;


  mat.printM();

  return 0;
}
