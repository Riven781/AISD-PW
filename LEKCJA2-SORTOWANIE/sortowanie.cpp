#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
#include <random>    

using namespace std;


template <typename T>
void sortowanieBabelkowe(T* poczatek, T* koniec){
    if(poczatek >= koniec) return;
    T zmPomocnicza;
    int rozmiar = koniec - poczatek + 1;
    for (int i = 0; i < rozmiar; i++){
        for(int j = 0; j < rozmiar - i - 1; j++){
            if(poczatek[j] > poczatek[j+1]){
                zmPomocnicza = poczatek[j];
                poczatek[j] = poczatek[j+1];
                poczatek[j+1] = zmPomocnicza;
            }
        }

    }
}



template <typename T>
void merge(T*poczatek, T*srodek, T*koniec){
    std::vector<T> tablicaTymczasowa(koniec - poczatek + 1);
    T* poczatek1 = poczatek;
    T* koniec1 = srodek;
    T* poczatek2 = srodek + 1;
    T* koniec2 = koniec;
    int i = 0;
    while(poczatek1 <= koniec1 && poczatek2 <= koniec2){
        if(*poczatek1 <= * poczatek2){
            tablicaTymczasowa[i] = *poczatek1;
            poczatek1++;
        }
        else{
            tablicaTymczasowa[i] = * poczatek2;
            poczatek2++;
        }
        i++;
    }
    while (poczatek1 <= koniec1)
    {
        tablicaTymczasowa[i] = * poczatek1;
        poczatek1++;
        i++;
    }
    
    while (poczatek2 <= koniec2){
        tablicaTymczasowa[i] = * poczatek2;
        poczatek2++;
        i++;
    }

    for (int i = 0; i < koniec-poczatek+1; i++){
        *(poczatek + i) = tablicaTymczasowa[i];
    }

}

template <typename T>
void mergeSort(T*poczatek, T*koniec){
    if (poczatek < koniec){
        T* srodek =poczatek + (koniec - poczatek)/2;
        mergeSort(poczatek, srodek);
        mergeSort(srodek+1, koniec);
        merge(poczatek, srodek, koniec);
    }
}

template <typename T>
void wyswietlSortowanieBabelkowe(T *poczatek, T *koniec){
    size_t size = koniec - poczatek + 1;
    std::cout << "Przed posortowaniem: " << std::endl;;
    for (size_t i = 0; i < size; i++)
    {
        std::cout << poczatek[i] << "  ";
    }
    sortowanieBabelkowe(poczatek, koniec);

    std::cout << std::endl;
    std::cout << "Po posortowaniu babelkowym: " << std::endl;;
    for (size_t i = 0; i < size; i++)
    {
        std::cout << poczatek[i] << "  ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
}


template <typename T>
void wyswietlSortowanieMergeSort(T *poczatek, T *koniec){
    size_t size = koniec - poczatek + 1;
    std::cout << "Przed posortowaniem: " << std::endl;;
    for (size_t i = 0; i < size; i++)
    {
        std::cout << poczatek[i] << "  ";
    }
    mergeSort(poczatek, koniec);

    std::cout << std::endl;
    std::cout << "Po posortowaniu mergeSort: " << std::endl;;
    for (size_t i = 0; i < size; i++)
    {
        std::cout << poczatek[i] << "  ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
}


int main(int argc, char const *argv[])
{
    float tab_z_Float[] = {10.4,9.1,8.5,7.3,6.5,5,4};

    int tab_z_Int[] = {3,4,3,5,7,9,10,0};

    char tab_z_Char[] = {'z', 'x', 'r', 'y','w'};

    string tab_z_String[] = {"super", "antarktyda", "programowanie", "auto"};



    std::random_device rd;
    std::mt19937 generator(rd());

    int size = sizeof(tab_z_Float)/sizeof(tab_z_Float[0]);

    //SORTOWANIE DLA TABLICY Z FLOAT

    wyswietlSortowanieBabelkowe(tab_z_Float, tab_z_Float + size - 1);

    std::shuffle(tab_z_Float, tab_z_Float + size, generator);

    wyswietlSortowanieMergeSort(tab_z_Float, tab_z_Float + size - 1);


    //SORTOWANIE DLA TABLICY Z INT

    size = sizeof(tab_z_Int)/sizeof(tab_z_Int[0]);

    wyswietlSortowanieBabelkowe(tab_z_Int, tab_z_Int + size - 1);

    std::shuffle(tab_z_Int, tab_z_Int + size, generator);

    wyswietlSortowanieMergeSort(tab_z_Int, tab_z_Int + size - 1);

    //SORTOWANIE DLA TABLICY ZE CHAR

    size = sizeof(tab_z_Char)/sizeof(tab_z_Char[0]);

    wyswietlSortowanieBabelkowe(tab_z_Char, tab_z_Char + size - 1);

    std::shuffle(tab_z_Char, tab_z_Char + size, generator);

    wyswietlSortowanieMergeSort(tab_z_Char, tab_z_Char + size - 1);


    //SORTOWANIE DLA TABLICY ZE STRING

    size = sizeof(tab_z_String)/sizeof(tab_z_String[0]);

    wyswietlSortowanieBabelkowe(tab_z_String, tab_z_String + size - 1);

    std::shuffle(tab_z_String, tab_z_String + size, generator);

    wyswietlSortowanieMergeSort(tab_z_String, tab_z_String + size - 1);

   

    return 0;
}
