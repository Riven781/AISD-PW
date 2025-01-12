#ifndef __TEST__H__
#define __TEST__H__

#include <string>

namespace TestAll
{
    bool checkResult(int *r1, int* r2, int size);
    void doTest(std::string expression, int  requiredResult [], int size, bool show = true, bool onlyResult = false);
    void conjTest();
    void alternativeTest();
    void implicationTest();
    void equivalenceTest();
    void xorTest();
    void negationTest();
    void doubleNegationTest();
    void negationAndConjTest();
    void equivalenceTestWith3Var();
    void advancedTest1();
    void advancedTest2();
    void advancedConjTest();
    void advancedConjAndNegTest();
}

void testAll();

#endif  //!__TEST__H__