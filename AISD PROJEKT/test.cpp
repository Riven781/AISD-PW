#include <iostream>
#include <vector>
#include "onp.h"
#include <cassert>
#include "logicvariable.h"
#include "test.h"
#include "truthTable.h"
#include "utils.h"
#include "math.h"

//{L'¬',L'∧',L'∨',L'⇒', L'⇔',L'⊕'};

using namespace std;

namespace TestAll{

    bool checkResult(int *r1, int* r2, int size){
        for (int i = 0; i < size; i++)
        {
            if(r1[i] != r2[i]){
                return false;
            }
        }
        return true;
        
    }



    void doTest(string strExpression, int  requiredResult [], int size,bool show, bool onlyResult){
        std::cout << "---------------------------------------------------------------" << std::endl;
        vector<wchar_t> onpExpression = convertToONP(convertFromLatex(strExpression));
        std::cout << "TEST: " << std::endl;
        displayExpression(convertFromLatex(strExpression));
        std::cout << "ONP: " << std::endl;
        displayONP(onpExpression);

        if (show)
        {
            std::cout << "TRUTH TABLE: " << std::endl;
        }
        else{
            std::cout << "TRUTH TABLE WASN'T DISPLAYED" << std::endl;
        }
        

        std::vector<LogicVariable> result = generateTruthTable(strExpression, show, onlyResult);

        
        assert(checkResult(result.back().getValues(), requiredResult, size));
        
    }

    void conjTest(){
        int requiredResult []{0,0,0,1};
        doTest("p \\\\and q", requiredResult, 4);
    }


    void alternativeTest(){
        int requiredResult []{0,1,1,1};
        doTest("p \\\\or q", requiredResult, 4);
    }

    void implicationTest(){
        int requiredResult []{1,0,1,1};
        doTest("p \\\\impl q", requiredResult, 4);
    }

    void equivalenceTest(){
        int requiredResult []{1,0,0,1};
        doTest("p \\\\equi q", requiredResult, 4);
    }

    void xorTest(){
        int requiredResult []{0,1,1,0};
        doTest("p \\\\xor q", requiredResult, 4);
    }

    void negationTest(){
        int requiredResult []{1,0};
        doTest("\\\\neg p", requiredResult, 2);
    }


    void doubleNegationTest(){
        int requiredResult []{0,1};
        doTest("\\\\neg\\\\neg p", requiredResult, 2); 
    }

    void negationAndConjTest(){
        int requiredResult []{1,1,1,0};
        doTest("\\\\neg  (p  \\\\and  q)", requiredResult, 4);

    }


    void equivalenceTestWith3Var(){
        int requiredResult []{0,1,1,0,1,0,0,1};
        doTest("p \\\\equi q \\\\equi r", requiredResult, 8);
        
    }

    void advancedTest1(){
        int requiredResult []{0,1,1,1,0,0,0,0,1,0,0,0,1,1,1,1};
        doTest("((p  \\\\or  q)  \\\\impl  r)  \\\\equi  u", requiredResult, 16);
    }


    void advancedTest2(){
        int requiredResult []{0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1};
        doTest("((p \\\\or q) \\\\impl r) \\\\equi (( \\\\neg u \\\\or u) \\\\and s)", requiredResult, 32);
    }

    void advancedConjTest(){
        int numberRow = 512;
        int requiredResult [numberRow];
        for (int i = 0; i < numberRow - 1; ++i){
            requiredResult[i] = 0;
        }
        requiredResult[numberRow - 1] = 1;
        doTest("p \\\\and  q \\\\and r \\\\and s \\\\and t \\\\and u \\\\and w \\\\and z \\\\and x", requiredResult, numberRow, false);
    }


    void advancedConjAndNegTest(){
        int numberRow = 512;
        int requiredResult [numberRow];
        for (int i = 0; i < numberRow - 1; ++i){
            requiredResult[i] = 1;
        }
        requiredResult[numberRow - 1] = 0;
        doTest("\\\\neg (p \\\\and  q \\\\and r \\\\and s \\\\and t \\\\and u \\\\and w \\\\and z \\\\and x)", requiredResult, numberRow, false);
    }


}



void testAll(){
    TestAll::conjTest();
    TestAll::alternativeTest();
    TestAll::implicationTest();
    TestAll::equivalenceTest();
    TestAll::xorTest();
    TestAll::negationTest();
    TestAll::doubleNegationTest();
    TestAll::negationAndConjTest();
    TestAll::equivalenceTestWith3Var();
    TestAll::advancedTest1();
    TestAll::advancedTest2();
    TestAll::advancedConjTest();
    TestAll::advancedConjAndNegTest();
    std::cout << "ALL TESTS PASSED" << std::endl;
}