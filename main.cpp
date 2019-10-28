#include "stack.h"

using namespace std;

int main() {
    Stack <int> *si;
    si = stack_create<int>(STACK_SIZE);

    stack_push <int>(si,10);
    stack_push <int>(si,100);
    stack_push <int>(si,1000);

    cout<<stack_pop(si)<<endl;
    cout<<stack_pop(si)<<endl;
    cout<<stack_pop(si)<<endl;
    cout<<stack_pop(si)<<endl;

    stack_destroy(si);
}

