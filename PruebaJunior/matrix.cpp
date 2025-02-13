#include <iostream>
#include <vector>
using namespace std;
 
class matrix7x6{
  private:
    vector<vector<int>> m;
    const int maxR = 7-1;
    const int maxC = 6-1;

  public:
    matrix7x6(){
      m = vector<vector<int>>(7,vector<int>(6, 0));
      int a = 0;
      for(auto &row : m){
        for(int &celda : row){
          celda = a;
          a++;
        }
      }
    }
    void printM(){
      for (const auto &row : m){
        for (const int val : row){
          cout << val << " ";
        }
        cout << endl;
      }
    }

};
  

int main() {

matrix7x6 mat;
mat.printM();

cout << " Esto sirve " << endl;  

 return 0;
 } 
