#include <vector>
#include <iostream>
#include <cassert>
 
template <typename T>
class Visitor
{
public:
    virtual void Visit (T & element) =0;
    virtual bool IsDone () const
	{ return false; }
};

template <typename T>
class AddingVisitor : public virtual Visitor<T>{
private:
    int sum = 0;
public:
    int wyswietl_sum(){
        int rezultat = sum;
        sum = 0;
        return rezultat;
    }

    void Visit(T &element) override {
        sum += element;
    }


};



template <typename T>
class Container 
{protected:
    
    Container (){};
 public:
    virtual int Count () const = 0;
    virtual bool IsEmpty () const {return Count()==0;};
    virtual bool IsFull () const = 0;
   	virtual void MakeNull() = 0;
 	virtual void Accept (Visitor<T> & v)=0; 
 };
 


template <typename T>
class Set : public virtual Container<T>
{
protected:
  int count;
  int universeSize;
public:
 Set (int n) : universeSize (n) {}
 int UniverseSize() const {return universeSize;}
 int Count() const {return count;};
 virtual void Insert (T element)=0;
 virtual bool IsMember (T element) const=0;
 virtual void Withdraw (T element)=0;
 };

template <typename T>
class Iterator{
public:
    virtual ~Iterator() {}
    virtual bool IsDone() const = 0;
    virtual T operator*() const = 0;
    virtual void operator++() = 0;
};

class SetAsArray : public Set<int>
{
    std::vector<bool> array;
public:
    class Iter : public Iterator<int>
    {
    private:
        std::vector<bool> data;
        int universeSize;
        int index;
    public:
        Iter(std::vector<bool> array, int us) : data(array), universeSize{us}{
            for (size_t i = 0; i < universeSize; i++)
            {
                if (data[i]){
                    index = i;
                    break;
                }
                if(i == universeSize - 1){
                    index = universeSize;
                }
            }
            
            
        }
        ~Iter(){}

        bool IsDone()const {
            return index == universeSize;
        }


        int operator* () const{
            return index;
        }

        void operator++(){
            if (index + 1 < universeSize){
                for (size_t i = index + 1; i < universeSize; i++)
                {
                    if (data[i]){
                        index = i;
                        break;
                    }
                    if (i == universeSize - 1){
                        index = universeSize;
                    }
                }
            }
            else{
                index = universeSize;
            }
        }
    };

    



    Iter& NewIterator(){
        return * new Iter(array, universeSize);
    }
    


    SetAsArray (unsigned int n);
	void MakeNull();//metody z containera
    void Insert (int element);
	bool IsMember (int element) const;
	void Withdraw (int element);
	bool IsFull () const {return (Count()==UniverseSize());};
	void Accept (Visitor<int> & v) ;
	//friend- funkcja uzyska prawo dostepu do prywatnych element�w danej klasy.

	friend SetAsArray operator + (
	SetAsArray const&, SetAsArray const&);
	friend SetAsArray operator - (
	SetAsArray const&, SetAsArray const&);
    friend SetAsArray operator * (
	SetAsArray const&, SetAsArray const&);
    friend bool operator == (
	SetAsArray const&, SetAsArray const&);
    friend bool operator <= (
	SetAsArray const&, SetAsArray const&);
    
    void Wypisz() const;	
};


SetAsArray operator+(const SetAsArray& lhs, const SetAsArray& rhs) {
    if (lhs.UniverseSize() == rhs.UniverseSize()){
        SetAsArray result(lhs.UniverseSize());
        for (size_t i = 0; i < lhs.UniverseSize(); i++)
        {
            result.array[i] = lhs.array[i] || rhs.array[i];
            if (result.array[i]){
                ++result.count;
            }
        }
        std::cout << "Licznik: " << result.Count() << std::endl;
        return result;
        
    }
    throw std::out_of_range("The size is not equal");
}

SetAsArray operator*(const SetAsArray& lhs, const SetAsArray& rhs) {
    if (lhs.UniverseSize() == rhs.UniverseSize()){
        SetAsArray result(lhs.UniverseSize());
        for (size_t i = 0; i < lhs.UniverseSize(); i++)
        {
            result.array[i] = lhs.array[i] && rhs.array[i];
            if (result.array[i]){
                ++result.count;
            }
        }
        return result;
        
    }
    throw std::out_of_range("The size is not equal");
}


SetAsArray operator-(const SetAsArray& lhs, const SetAsArray& rhs) {
    if (lhs.UniverseSize() == rhs.UniverseSize()){
        SetAsArray result(lhs.UniverseSize());
        for (size_t i = 0; i < lhs.UniverseSize(); i++)
        {
            result.array[i] = lhs.array[i] && !rhs.array[i];
            if (result.array[i]){
                ++result.count;
            }
        }
        return result;
        
    }
    throw std::out_of_range("The size is not equal");
}


bool operator==(const SetAsArray& lhs, const SetAsArray& rhs) {
    if (lhs.UniverseSize() == rhs.UniverseSize()){
        for (size_t i = 0; i < lhs.UniverseSize(); i++)
        {
            if (lhs.array[i] != rhs.array[i]){
                return false;
            }
        }
        return true;
        
    }
    throw std::out_of_range("The size is not equal");
}


bool operator<=(const SetAsArray& lhs, const SetAsArray& rhs) {
    if (lhs.UniverseSize() == rhs.UniverseSize()){
        for (size_t i = 0; i < lhs.UniverseSize(); i++)
        {
            if (!rhs.array[i] && lhs.array[i]){  //jesli należy do lewego i nie nalezy do prawgo to false
                return false;
            }
        }
        return true;
        
    }
    throw std::out_of_range("The size is not equal");
}

SetAsArray::SetAsArray(unsigned int n) : Set<int>(n), array(n, false){
    count = 0;
}

void SetAsArray::MakeNull(){
    count = 0;
}



void SetAsArray::Insert(int element){
    if (! array[element]){
        array[element] = true;
        ++count;
    }
}

void SetAsArray::Withdraw(int element){
    if (array[element]){
        array[element] = false;
        --count;
    }
}

bool SetAsArray::IsMember(int element) const {
    if (array[element]){
        return true;
    }
    return false;
}

void SetAsArray::Wypisz() const{
    for (int i = 0; i < UniverseSize(); ++i){
        if (array[i]){
            std::cout << i << " ";
        }
        
    }
    std::cout  << std::endl;
}

void SetAsArray::Accept(Visitor<int> & v){
    for(int i = 0; i < universeSize; ++i){
        if (!v.IsDone())
        {
            if(array[i]){
                v.Visit(i);
            }
        }

        if( v.IsDone()){
            std::cout << "Funkcja Accept zakonczyla przegladanie na komorce: " << i << std::endl;
            break;
        }
    }
    if( !v.IsDone()){
        std::cout << "Funkcja Accept przeszla przez wszystkie komorki" << std::endl;
    }

}

class Odd_Visitor:public Visitor<int>
{
protected:
    bool IsDone_;
public:
    Odd_Visitor():IsDone_(false){};
    void Visit(int & element) override {
        if (element%2==1){
            IsDone_ = true;
        }
        
        
    
    };
    bool IsDone() const override {
        return IsDone_;
    }
};


void test(int n){
    SetAsArray A(n);
    SetAsArray B(n);
    SetAsArray C(n);
    SetAsArray D(n);
    for (size_t i = 0; i < n; i++)
    {
        if(i % 2 == 0){
            A.Insert(i);
        }
        else{
            B.Insert(i);
        }
    }

    C = A + B;
    D = C - B;

    std::cout << "Wartosci zbioru A" << std::endl;
    A.Wypisz();
    std::cout << "Wartosci zbioru B" << std::endl;
    B.Wypisz();
    std::cout << "Wartosci zbioru C" << std::endl;
    C.Wypisz();
    std::cout << "Wartosci zbioru D" << std::endl;
    D.Wypisz();

    assert(D == A);
    std::cout << "Czy D == A? " << (D == A) << std::endl;
    assert(D <= A);
    std::cout << "Czy D <= A? " << (D <= A) << std::endl;
    assert(!(C == B));
    std::cout << "Czy C == B? " << (C == B) << std::endl;
    assert(B <= C);
    std::cout << "Czy B <= C? " << (B <= C) << std::endl;

    std::cout << "Wstawiam 1 do zbioru A" <<  std::endl;

    A.Insert(1);
    assert(!(D == A));
    std::cout << "Czy D == A? " << (D == A) << std::endl;
    assert(D <= A);
    std::cout << "Czy D <= A? " << (D <= A) << std::endl;


    //Nowa cześć testu
    A.Insert(5);

    AddingVisitor<int> v_A;
    A.Accept(v_A);
    std::cout << "Suma zbioru A, ktory zawiera nastepujace elementy: " << std::endl;
    A.Wypisz();
    std::cout << "wynosi: ";
    std::cout << v_A.wyswietl_sum() << std::endl;

    SetAsArray E = A*B;
    AddingVisitor<int> v_E;
    E.Accept(v_E);
    std::cout << "Suma zbioru E, ktory zawiera nastepujace elementy: " << std::endl;
    E.Wypisz();
    std::cout << "wynosi: ";
    std::cout << v_E.wyswietl_sum() << std::endl;
    E.Withdraw(1);


    E.Accept(v_E);
    std::cout << "Suma zbioru E, ktory zawiera nastepujace elementy: " << std::endl;
    E.Wypisz();
    std::cout << "wynosi: ";
    std::cout << v_E.wyswietl_sum() << std::endl;

    //zadanie 4



    std::cout << "Zbior B:" << std::endl;
    B.Wypisz();

    Odd_Visitor oV_B;
    B.Accept(oV_B);

    std::cout << "Czy w zbiorze B jest nieparzysta liczba? " << std::endl;
    std::cout << oV_B.IsDone() << std::endl;



    std::cout << "Zbior A:" << std::endl;
    A.Wypisz();

    Odd_Visitor oV_A;
    A.Accept(oV_A);
    

    std::cout << "Czy w zbiorze A jest nieparzysta liczba? " << std::endl;
    std::cout << oV_A.IsDone() << std::endl;

    A.Withdraw(1);
    //A.Withdraw(5);

    
    std::cout << "Zbior A:" << std::endl;
    A.Wypisz();

    Odd_Visitor oV_A2;
    A.Accept(oV_A2);

    std::cout << "Czy w zbiorze A jest nieparzysta liczba? " << std::endl;
    std::cout << oV_A2.IsDone() << std::endl;


    std::cout << "PART 3" << std::endl;

    std::cout << "Zbior A" << std::endl;

    Iterator<int> & it = A.NewIterator();
    while (!it.IsDone())
    {
        std::cout << *it << " ";
        ++it;
    }

    std::cout<< std::endl;

    std::cout << "Zbior B" << std::endl;
    
    Iterator<int> & it2 = B.NewIterator();
    while (!it2.IsDone())
    {
        std::cout << *it2 << " ";
        ++it2;
    }

    std::cout << std::endl;

    std::cout << "Pusty zbior: " << std::endl;

    SetAsArray G(10);

    Iterator<int> & it3 = G.NewIterator();
    while (!it3.IsDone())
    {
        std::cout << *it3 << " ";
        ++it3;
    }

    std::cout << std::endl;






    
}


int main(int argc, char const *argv[])
{
    test(10);
    return 0;
}
