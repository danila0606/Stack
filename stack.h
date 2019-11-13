#include <iostream>
#include <cstring>
#include <ctime>
#include "errors.h"

using namespace std;

template <typename T>
class Stack {
private: unsigned long long st_canary1 = 0;
private: int size_all = 0;
private: int n = 1;
private: T *st_data = NULL;

private: T data_canary_value = 0;
private: unsigned long long st_canary1_value = 0;
private: unsigned long long st_canary2_value = 0;
private: unsigned long long st_hash = 0;
private: T *st_data_hash = NULL;
private: int st_status = 0;
private: void OK();
private: unsigned long long hasher ();
private: void Dump();
private: void DataCanaryGenerator();

public: void Create (size_t st_size);
public: void Push (T value);
public: T Pop ();
public: void Destruct ();

private: unsigned long long st_canary2 = 0;
};

