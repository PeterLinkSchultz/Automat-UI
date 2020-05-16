#include "../pch.h"
#include <vector>
#include "../State/StateList.h"
#include "../Model/Store.h"

using namespace std;

#ifndef AUTOMAT_GROUPDELTA_H
#define AUTOMAT_GROUPDELTA_H

class DeltaBinder {
public:
    void bindNodes(StateList &);
    void bindStore(Store *);
    vector<DeltaGroup *> getData();
    bool isGroupRepeatetly();
private:
    void bindGroup(StateNode &);
    vector<DeltaGroup *> data;
    Store *store;
    int counter = 1;
    int lastNumbersGroup = 0;
};
#endif //AUTOMAT_GROUPDELTA_H
