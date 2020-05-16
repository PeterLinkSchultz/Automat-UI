#include "../pch.h"
#include <vector>
#include "../State/StateList.h"

using namespace std;
#ifndef AUTOMAT_STORE_H
#define AUTOMAT_STORE_H

class Store {
public:
    void initStore(StateList &);
    int getGroupNumber(int);
    void updateStore(int);
    void swapStore();
private:
    vector<int> *saved = new vector<int>;
    vector<int> *current = new vector<int>;
};
#endif //AUTOMAT_STORE_H
