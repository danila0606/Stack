
#include <iostream>
#include <cstring>
#include "errors.h"

#define STACK_SIZE 100

using namespace std;

void OK (int stat) {
    if (stat == STACK_NOT_FOUND_SDESTROY) {
        cerr << endl <<"a null pointer is passed to Stack_Destroy";
        exit(STACK_NOT_FOUND_SDESTROY);
    }
    if (stat == STACK_WASNT_RESEIVED_SPUSH) {
        cerr << endl << "a null pointer is passed to Stack_Push";
        exit(STACK_WASNT_RESEIVED_SPUSH);
    }
    if (stat == STACK_WASNT_RESEIVED_SPOP) {
        cerr << endl << "a null pointer is passed to Stack_Push";
        exit(STACK_WASNT_RESEIVED_SPOP);
    }
    if (stat == REACHES_THE_MIN) {
        cerr << endl << "out of stack (stack is empty)";
        exit(REACHES_THE_MIN);
    }
    if (stat == FAILED_CREATE_STACK) {
        cerr << endl << "failed to set stack";
        exit(FAILED_CREATE_STACK);
    }
    if (stat == FAILED_CREATE_STACK_DATA) {
        cerr << endl << "failed to set stack";
        exit(FAILED_CREATE_STACK_DATA);
    }

}

template <typename X>
struct Stack {
    int size_all;
    int n;
    X *data;
};

template <typename T>
struct Stack<T> * stack_create(size_t stack_size) {
    struct Stack <T>*s;
    s = (struct Stack<T>*)calloc(1, sizeof(struct Stack<T>));
    if (s == NULL) {
        OK(FAILED_CREATE_STACK);
    }
    s->size_all = stack_size;
    s->data = (T*)calloc(stack_size, sizeof(T));
    if(s->data == NULL) {
        OK(FAILED_CREATE_STACK_DATA);
    }
    s->n = 0;
    return s;
}
template <typename T>
void stack_push(struct Stack<T> * s, T x) {
    if(s == NULL) {
        OK(STACK_WASNT_RESEIVED_SPUSH);
    }
    if (s -> size_all <= s -> n ) {

        s -> data = (T*)realloc(s -> data, s -> size_all * 2 * sizeof(T));
        s -> size_all *= 2;

    }
    s->data[s->n] = x;
    s->n = s->n + 1;
}
template <typename T>
T stack_pop(struct Stack <T> * s) {
    if (s == NULL)
        OK (STACK_WASNT_RESEIVED_SPOP);
    if (s->n <= 0)
        OK (REACHES_THE_MIN);
    T b = (s->data[--(s->n)]);
    return b;
}
template <typename T>
void stack_destroy(struct Stack<T> * s) {
    if (s == NULL)
        OK (STACK_NOT_FOUND_SDESTROY);
    free(s->data);
    free(s);
}