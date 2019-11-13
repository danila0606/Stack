#include "stack.h"

using namespace std;

template <typename T>
void Stack<T>::OK () {
    if (st_data == NULL) {
        cout << "st_data = NULL" << endl;
        exit(ST_DATA_NULL);
    }
    if (st_status == FAILED_CREATE_STACK_DATA) {
        cout << "FAILED CREATE STACK DATA" <<endl;
        exit(FAILED_CREATE_STACK_DATA);
    }
    if (st_status == ST_SIZE_IS_NOT_PLUS) {
        cout << "ST SIZE IS NOT PLUS" <<endl;
        exit(ST_SIZE_IS_NOT_PLUS);
    }
    if (st_status == STACK_WAS_CREATED_ALREADY) {
        cout << "STACK WAS CREATED ALREADY" <<endl;
        exit(STACK_WAS_CREATED_ALREADY);
    }
    if (st_status == STACK_IS_EMPTY_SPOP) {
        cout << "STACK_IS_EMPTY" <<endl;
        Dump();
        exit(STACK_IS_EMPTY_SPOP);
    }
    if (st_status == FAILED_TO_DESTROY_STACK) {
        cout << "FAILED TO DESTROY STACK" <<endl;
        Dump();
        exit(FAILED_TO_DESTROY_STACK);
    }
    if (st_data == NULL) {
        cout << "STACK WASN'T CREATED YET" <<endl;
        exit(STACK_WASNT_CREATED);
    }
    if (this == NULL) {
        cout << "THE POINTER TO STACK IS NULL. STACK NOT FOUND" <<endl;
        exit(STACK_NOT_FOUND);
    }
    if (st_hash != hasher()) {
        cout << "STACK HASH WAS CHANGED" <<endl;
        Dump();
        exit(ST_HASH_WAS_CHANGED);
    }
    if (st_data_hash != st_data) {
        cout << "ST DATA HASH WAS CHANGED" <<endl;
        Dump();
        exit(ST_DATA_HASH_WAS_CHANGED);
    }
    if (st_canary1 != st_canary1_value) {
        cout << "BROKEN STACK (st_canary1 was changed)";
        Dump();
        exit(ST_CANARY1_WAS_CHANGED);
    }
    if (st_canary2 != st_canary2_value) {
        cout << "BROKEN STACK (st_canary2 was changed)";
        Dump();
        exit(ST_CANARY2_WAS_CHANGED);
    }
    if (st_data[0] != data_canary_value) {
        cout << "BROKEN STACK (data_canary1 was changed)";
        Dump();
        exit(DATA_CANARY1_WAS_CHANGED);
    }
    if (st_data[size_all + 1] != data_canary_value) {
        cout << "BROKEN STACK (data_canary2 was changed)";
        Dump();
        exit(DATA_CANARY2_WAS_CHANGED);
    }
}
template <typename T>
void Stack<T>::Create (size_t st_size) {
    if (st_size<=0) {
        st_status = ST_SIZE_IS_NOT_PLUS;
        OK();
    }
    if(st_data != NULL) {
        st_status = STACK_WAS_CREATED_ALREADY;
        OK();
    }
    size_all = st_size;

    st_data = (T*)calloc(st_size + 2, sizeof(T));
    if( st_data == NULL) {
        st_status = FAILED_CREATE_STACK_DATA;
        OK();
    }
    DataCanaryGenerator();
    st_canary1 = st_canary1_value;
    st_canary2 = st_canary2_value;
    st_data[0] = (T)data_canary_value;
    st_data[size_all + 1] = (T)data_canary_value;
    st_status = 0;

    st_data_hash = st_data;
    st_hash = hasher();
}
template<typename T>
void Stack<T>::DataCanaryGenerator() {
    srand (time(NULL));
    static int r = rand();
    data_canary_value = (T)(r % 1000);
    st_canary1_value = (unsigned long long)(r%3222);
    st_canary2_value = (unsigned long long)(r%2288);
}
template <typename T>
void Stack<T>::Push (T value) {
    OK();
    if (n > size_all) {
        size_all = size_all * 2;
        T* tmp = (T*)realloc(st_data, (size_all + 2) * sizeof(T));
        st_data = tmp;
        st_data[size_all + 1] = (T)data_canary_value;
    }
    st_data[n++] = value;
    st_hash = hasher();
    st_status = 0;
    OK();
}
template <typename T>
T Stack<T>::Pop () {
    if (n <= 1) {
        st_status = STACK_IS_EMPTY_SPOP;
        OK();
    }

    T b = (st_data[--n]);
    st_data[n] = 0;
    st_hash = hasher();
    return b;
}
template <typename T>
void Stack<T>::Destruct () {
    OK();
    free(st_data);
}
template <typename T>
unsigned long long Stack<T>::hasher() {
    unsigned long long updated_hash = 0;
    srand (time(NULL));
    static int hash_value_r = rand();

    for (int i = 1; i <= n; i++) {
        updated_hash += i * (st_data[i] + hash_value_r);
    }

    return updated_hash;
}
template <typename T>
void Stack<T>::Dump() {
    cout<<"-------------STACK DUMP-------------"<<endl;
    cout<<"| st_canary1 = " <<st_canary1<<endl;
    cout<<"| st_size: "<<size_all<<endl;
    cout<<"| number of elem. in stack(without canaries): "<< (n-1) <<endl;
    cout<<"| st_data = "<<st_data<<endl;
    cout<<"| st_hash = "<<st_hash<<endl;
    cout<<"| st_data_hash = "<<st_data_hash<<endl;
    cout<<"| data_canary1 = "<<st_data[0]<<endl;
    for (int i = 1; i < size_all + 1; i++)
        cout <<"| st_data[" << i << "] = " << st_data[i] << endl;
    cout<<"| data_canary2 = "<<st_data[size_all + 1]<<endl;
    cout<<"| st_canary2 = " <<st_canary2<<endl;
    cout<<"------------------------------------"<<endl;
}