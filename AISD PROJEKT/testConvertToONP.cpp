#include <iostream>
#include <vector>
#include "onp.h"
#include <cassert>
#include "logicvariable.h"
#include "testConvertToONP.h"

using namespace std;

//{L'¬',L'∧',L'∨',L'⇒', L'⇔',L'⊕'};

namespace ONPTest{
    void conjTest(){
        vector<wchar_t> lista = convertToONP(L"p∧q∧r∧s∧t");
        displayONP(lista);
        assert(lista == (std::vector<wchar_t>{L'p', L'q',L'∧', L'r',L'∧', L's' ,L'∧', L't',L'∧'}));
    }

    void alternativeTest(){
        vector<wchar_t> lista = convertToONP(L"p∨q∨r∨s∨t");
        displayONP(lista);
        assert(lista == (std::vector<wchar_t>{L'p', L'q',L'∨', L'r',L'∨', L's' ,L'∨', L't',L'∨'}));
    }

    void implicationTest(){
        vector<wchar_t> lista = convertToONP(L"p⇒q⇒r⇒s⇒t");
        displayONP(lista);
        assert(lista == (std::vector<wchar_t>{L'p', L'q',L'⇒', L'r',L'⇒', L's' ,L'⇒', L't',L'⇒'}));
    }

    void equivalenceTest(){
        vector<wchar_t> lista = convertToONP(L"p⇔q⇔r⇔s⇔t");
        displayONP(lista);
        assert(lista == (std::vector<wchar_t>{L'p', L'q',L'⇔', L'r',L'⇔', L's' ,L'⇔', L't',L'⇔'}));
    }

    void xorTest(){
        vector<wchar_t> lista = convertToONP(L"p⊕q⊕r⊕s⊕t");
        displayONP(lista);
        assert(lista == (std::vector<wchar_t>{L'p', L'q',L'⊕', L'r',L'⊕', L's' ,L'⊕', L't',L'⊕'}));
    }


    void implicationAndConjTest(){
        vector<wchar_t> lista = convertToONP(L"p⇒q∧q");
        displayONP(lista);
        assert(lista == (std::vector<wchar_t>{L'p', L'q', L'q', L'∧', L'⇒'}));
    }


    void bracketTest(){
        vector<wchar_t> lista = convertToONP(L"(p⇒q)∧q");
        displayONP(lista);
        assert(lista == (std::vector<wchar_t>{L'p', L'q', L'⇒', L'q', L'∧'}));
    }

    void negationAndConjTest(){
        vector<wchar_t> lista = convertToONP(L"¬p∧q");
        displayONP(lista);
        assert(lista == (std::vector<wchar_t>{L'p', L'¬', L'q', L'∧'}));
    }

    void equivalenceAndAlternativeTest(){
        vector<wchar_t> lista = convertToONP(L"p∨(q⇔r)∨s");
        displayONP(lista);
        assert(lista == (std::vector<wchar_t>{L'p', L'q', L'r', L'⇔',L'∨', L's',L'∨'}));
    }

    void conjAndAlternativeTest(){
        vector<wchar_t> lista = convertToONP(L"p∨(q∧q)");
        displayONP(lista);
        assert(lista == (std::vector<wchar_t>{L'p', L'q', L'q', L'∧',L'∨'}));
    }


    void negationTest(){
        vector<wchar_t> lista = convertToONP(L"¬p");
        displayONP(lista);
        assert(lista == (std::vector<wchar_t>{L'p', L'¬'}));
    }


    void doubleNegationTest(){
        vector<wchar_t> lista = convertToONP(L"¬(¬p)");
        displayONP(lista);
        assert(lista == (std::vector<wchar_t>{L'p', L'¬',  L'¬'}));
    }

}


    void testConvertToONP(){
        ONPTest::conjTest();
        ONPTest::alternativeTest();
        ONPTest::implicationTest();
        ONPTest::equivalenceTest();
        ONPTest::xorTest();
        ONPTest::implicationAndConjTest();
        ONPTest::bracketTest();
        ONPTest::negationAndConjTest();
        ONPTest::equivalenceAndAlternativeTest();
        ONPTest::conjAndAlternativeTest();
        ONPTest::negationTest();
        ONPTest::doubleNegationTest();
        std::cout << "ConvertToONP TESTS PASSED" << std::endl;
    }