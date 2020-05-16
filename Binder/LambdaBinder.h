#include <vector>
#include <algorithm>
#include "../State/StateList.h"

using namespace std;

class LambdaBinder
{
public:
    void bindNodes(StateList &);
    vector<LambdaGroup*>* getData();
    pGroupCondition getCondition(int);
private:
    void bindGroup(StateNode &);
    int counter = 1;
	vector<LambdaGroup *> data;
};

