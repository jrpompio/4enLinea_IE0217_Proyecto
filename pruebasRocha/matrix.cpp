#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

class Matrix6x7
{
public:
  vector<vector<int>> table;
  vector<int> path;
  const int maxR = 6 - 1;
  const int maxC = 7 - 1;


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


class AiPlayer : public Matrix6x7
{
public:
   int botMove() {
    const int rows = table.size();
    const int cols = table[0].size();
    int bestColumn = -1;

    auto isValidMove = [&](int col) -> bool {
      return table[0][col] == 0;
    };

    auto countAlignment = [&](int R, int C, int dR, int dC, int player, bool allowGap) -> int {
      int count = 0, gaps = 0;
      for (int i = 0; i < 3; i++) {
        R += dR;
        C += dC;
        if (R < 0 || R >= rows || C < 0 || C >= cols) break;
        if (table[R][C] == player) count++;
        else if (table[R][C] == 0 && allowGap) gaps++;
        else break;
      }
      return (allowGap && gaps == 1) ? count + 1 : count;
    };

    for (int c = 0; c < cols; c++) {
      if (!isValidMove(c)) continue;

      int r = 0;
      while (r < rows - 1 && table[r + 1][c] == 0) r++;

      for (auto &[dR, dC] : vector<pair<int, int>>{{1, 0}, {0, 1}, {1, 1}, {1, -1}}) {
        if (countAlignment(r, c, dR, dC, -1, false) >= 3) return c;
        if (countAlignment(r, c, dR, dC, -1, true) >= 3) return c;
        if (countAlignment(r, c, dR, dC, 1, false) >= 3) bestColumn = c;
        if (countAlignment(r, c, dR, dC, 1, true) >= 3) bestColumn = c;
      }
    }

    if (bestColumn != -1) return bestColumn;

    vector<int> validCols;
    for (int c = 0; c < cols; c++)
      if (isValidMove(c)) validCols.push_back(c);

    if (!validCols.empty()) return validCols[rand() % validCols.size()];

    return -1;
  }
};


int main()
{
    Matrix6x7 game;
    AiPlayer bot;
    int currentPlayer = 1;
    bool gameOver = false;

    while (!gameOver)
    {
        game.printM();
        int column;

        if (currentPlayer == 1)
        {
            cout << "Jugador 1, elija una columna (0-6): ";
            cin >> column;
        }
        else
        {
            column = bot.botMove();
            cout << "El bot elige la columna: " << column << endl;
        }

        if (column < 0 || column > 6 || !game.insert(column, currentPlayer))
        {
            cout << "Movimiento inválido. Intente de nuevo.\n";
            continue;
        }

        int row = game.gravity(column);

        if (game.exploreDirections(row, column))
        {
            game.printM();
            cout << "El jugador " << currentPlayer << " ha ganado!\n";
            gameOver = true;
        }

        currentPlayer = (currentPlayer == 1) ? -1 : 1;
    }

    return 0;
}