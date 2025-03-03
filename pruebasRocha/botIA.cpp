#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>
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
    for (auto &row : table)
    {
      for (int &celda : row)
      {
        celda = 0;
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
    }
    return false;
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
        temp = table[row][colum];
        table[row][colum] = table[row + 1][colum];
        table[row + 1][colum] = temp;
        swap = true;
      }
      if (swap)
      {
        last = row + 1;
      }
      else
      {
        last = row;
        break;
      }
      row++;
    }
    return last;
  }

  int botMove()
  {
    const int rows = table.size();
    const int cols = table[0].size();
    int bestColumn = -1;

    auto isValidMove = [&](int col) -> bool {
      return table[0][col] == 0;
    };

    auto countAlignment = [&](int R, int C, int dR, int dC, int player) -> int {
      int count = 0;
      for (int i = 0; i < 3; i++)
      {
        R += dR;
        C += dC;
        if (R < 0 || R >= rows || C < 0 || C >= cols || table[R][C] != player)
          break;
        count++;
      }
      return count;
    };

    for (int c = 0; c < cols; c++)
    {
      if (!isValidMove(c))
        continue;

      int r = 0;
      while (r < rows - 1 && table[r + 1][c] == 0)
        r++;

      for (auto &[dR, dC] : vector<pair<int, int>>{{1, 0}, {0, 1}, {0, -1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}})
      {
        if (countAlignment(r, c, dR, dC, -1) >= 3)
          return c;
        if (countAlignment(r, c, dR, dC, 1) >= 3)
          bestColumn = c;
      }
    }

    if (bestColumn != -1)
      return bestColumn;

    vector<int> validCols;
    for (int c = 0; c < cols; c++)
      if (isValidMove(c))
        validCols.push_back(c);

    if (!validCols.empty())
      return validCols[rand() % validCols.size()];

    return -1;
  }

  vector<vector<int>> &getTable()
  {
    return table;
  }

};

int main()
{
  srand(time(0));
  matrix7x6 mat;
  int userColumn;

  while (true)
  {
    mat.printM();
    cout << "Ingrese columna (0-5): ";
    cin >> userColumn;
    if (userColumn < 0 || userColumn > 5 || !mat.insert(userColumn, 1))
    {
      cout << "Movimiento inválido, intente de nuevo." << endl;
      continue;
    }
    mat.gravity(userColumn);

    int botColumn = mat.botMove();
    if (botColumn != -1)
    {
      mat.insert(botColumn, -1);
      mat.gravity(botColumn);
      cout << "El bot jugó en la columna: " << botColumn << endl;
    }
    else
    {
      cout << "Empate, no hay más movimientos." << endl;
      break;
    }
  }

  return 0;
}
