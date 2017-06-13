#include "corn.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void printCorn(Corn& corn)
{    
    Corn::Iterator cornIt = corn.createIterator();
    while (cornIt.hasNext())
    {
        CobLayer::Iterator cobIt = (*cornIt)->createIterator();
        while (cobIt.hasNext())
        {
            std::cout << "[" + std::to_string(*cobIt) + "]";
            ++cobIt;
        }
        std::cout << std::endl;
        ++cornIt;
    }
    std::cout << std::endl;
}

vector<int> makeVector(size_t numElements)
{
    vector<int> v;
    for (int i = 0; i < numElements; ++i)
    {
        v.push_back(i);
    }
    return move(v);
}

void runCornIterations(int iterations)
{
    cout << "Running " << iterations << " iterations" << endl;
    
    vector<pair<int,vector<int>>> testCases;
    testCases.push_back({1,{1,2}});
    testCases.push_back({5,{1,2,3,4,5,6}});
    testCases.push_back({10,{1,2,3,4,5,6}});
    testCases.push_back({1,{1,2,3,4,5,6}});
    testCases.push_back({20,makeVector(100)});
    testCases.push_back({6,makeVector(100)});

    for (int i = 0; i < iterations; ++i)
    {
        for (auto& testCase : testCases)
        {        
            Corn c(testCase.first);
            for (auto& value : testCase.second)
            {
                c.insert(value);
            }
            printCorn(c);
        }
    }
}

void testCornIterator(int iterations)
{

}

int main(int argc, char **argv)
{
    int iterations = 1;
    if (argc > 1)
    {
        iterations = atoi(argv[1]);
    }
    runCornIterations(iterations);
    testCornIterator(iterations);
    return 0;
}
