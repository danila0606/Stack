#include "funtions.cpp"

using namespace std;

int main() {
    Stack <int> S;


    S.Create (3);

    S.Push (9);
    S.Push (12);
    S.Push (5);


    cout << S.Pop() << endl;
    cout << S.Pop() << endl;
    cout << S.Pop() << endl;
    cout << S.Pop() << endl;


   S.Destruct();
}



