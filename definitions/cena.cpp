#include <iostream>

using namespace std;

class Cena{
public:
    int* l[10];
    int ambiente[3];
    int* obj[10];
    int contador = 0;

    void luz(int luz[]){
        int L[6];
        for(int i = 0; i< 3; i++){
            L[i] = luz[i];
        };
        for(int i = 3; i< 6; i++){
            L[i] = luz[i];
        };
        l[contador] = L;
        contador++;
    };

    void ambi(int amb[]){
        for(int i = 0; i< 3; i++){
            ambiente[i] = amb[i];

        };
    };
};

int main(){
    cout << "Hello world!" << endl;
    char value;
    int luza[6];
    int ambientes[3];
    int val;

    Cena cena;
    while (cin >> value){
      if(value=='l'){
            for(int i=0; i<6; i++){
                cin >> val;
                luza[i] = val;
            }
            cena.luz(luza);
      }else if(value == 'a'){
            for(int i=0; i<3; i++){
                    cin >> val;
                ambientes[i] = val;
            }
            cena.ambi(ambientes);
      }
    };
    cout << "Hello world!" << endl;
    return 0;
}
