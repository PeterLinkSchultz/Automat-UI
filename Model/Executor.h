#include "../State/StateList.h"
#include "../Binder/LambdaBinder.h"
#include "../Binder/DeltaBinder.h"
#include "Store.h"

#ifndef AUTOMAT_EXECUTOR_H
#define AUTOMAT_EXECUTOR_H

class Executor {
public:
    explicit Executor(StateList&);
    void start();
    void printShortedAuto();
    void init();
    bool next();
    vector<LambdaGroup *>* getLambdaGroups();
    vector<DeltaGroup*>* getDeltaGroups();
    std::string intToChars(int n)
    {
        std::ostringstream os;
        os << n;

        return os.str();
    }

    Nodes* getInitNodes();
private:
    void makeShortedAuto();
    LambdaBinder lambdaBinder;
    DeltaBinder deltaBinder;
    StateList stateList;
    Store store{};
    StateList finishList;
};

#endif //AUTOMAT_EXECUTOR_H
