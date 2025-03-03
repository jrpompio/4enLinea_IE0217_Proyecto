#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

class matrix6x7 {
private:
  vector<vector<int>> table;
  vector<int> path;
  const int maxR = 6 - 1;
  const int maxC = 7 - 1;

public:
  matrix6x7() {
    table = vector<vector<int>>(6, vector<int>(7, 0));
  }

  void printM() {
    cout << endl;
    for (const auto &row : table) {
      for (const int val : row) {
        cout << setw(2) << val << " ";
      }
      cout << endl;
    }
  }

  bool insert(int column, int player) {
    if (table[0][column] == 0) {
      table[0][column] = player;
      return true;
    } 
    return false;
  }

  int gravity(int colum) {
    int row = 0;
    int temp;
    bool swap;
    int last;
    while (row < maxR) {
      swap = false;
      if (table[row][colum] != 0 && table[row + 1][colum] == 0) {
        temp = table[row][colum];
        table[row][colum] = table[row + 1][colum];
        table[row + 1][colum] = temp;
        swap = true;
      }
      if (swap) last = row + 1;
      else { last = row; break; }
      row++;
    }
    return last;
  }

  bool explore(int R, int C, int dR, int dC) {
    path.clear();
    while (R >= 0 && R <= maxR && C >= 0 && C <= maxC) {
      path.push_back(table[R][C]);
      R += dR * -1;
      C += dC;
    }
    // Verifica si hay 4 en línea
    if (path.size() > 3) {
      for (size_t i = 0; i <= path.size() - 4; i++) {
        if (path[i] != 0 && path[i] == path[i+1] && path[i+1] == path[i+2] && path[i+2] == path[i+3]) {
          return true; // Se encontró una línea de 4 iguales
        }
      }
    }
    return false;
  }

  bool exploreDirections(int R, int C) {
    R--; C--;
    if (R > maxR || C > maxC || C < 0 || R < 0) return false;

    return explore(R, C, -1, 0) ||  // SOUTH
           explore(R, C, 0, -1) ||  // WEST
           explore(R, C, 0, 1) ||   // EAST
           explore(R, C, 1, -1) ||  // N_WEST
           explore(R, C, 1, 1) ||   // N_EAST
           explore(R, C, -1, -1) || // S_WEST
           explore(R, C, -1, 1);    // S_EAST
  }

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

int main() {
  srand(time(0));
  matrix6x7 mat;
  int userColumn;

  while (true) {
    mat.printM();
    cout << "Ingrese columna (0-6): ";
    cin >> userColumn;
    if (userColumn < 0 || userColumn > 6 || !mat.insert(userColumn, 1)) {
      cout << "Movimiento inválido, intente de nuevo." << endl;
      continue;
    }
    int row = mat.gravity(userColumn);
    
    if (mat.exploreDirections(row + 1, userColumn + 1)) {
      mat.printM();
      cout << "¡Jugador gana!" << endl;
      break;
    }

    int botColumn = mat.botMove();
    if (botColumn != -1) {
      mat.insert(botColumn, -1);
      int botRow = mat.gravity(botColumn);
      cout << "El bot jugó en la columna: " << botColumn << endl;

      if (mat.exploreDirections(botRow + 1, botColumn + 1)) {
        mat.printM();
        cout << "¡El bot gana!" << endl;
        break;
      }
    } else {
      cout << "Empate, no hay más movimientos." << endl;
      break;
    }
  }

  return 0;
}