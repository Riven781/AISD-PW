#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Vertex
{
    int number;
public:
    int weight{};
    std::string label;
    Vertex(int n) : number{n}{};
    int Number() const{return number;};
};

template <typename T>
class Iterator{
public:
    virtual ~Iterator() {}
    virtual bool IsDone() const = 0;
    virtual T& operator*() const = 0;
    virtual void operator++() = 0;
};

class Edge
{
protected:
    Vertex* v0;
    Vertex* v1;
public:
    int weight{};
    std::string label;
    Edge (Vertex *V0, Vertex* V1) : v0{V0}, v1{V1}{};
    Vertex* V0 (){return v0;};
    Vertex* V1 (){return v1;};
    Vertex* Mate (Vertex *v);




};

Vertex* Edge::Mate(Vertex *v){
    return (v0 == v)? v1 : v0;
}




class GraphAsMatrix
{
    std::vector<Vertex *> vertices;
    std::vector< std::vector<Edge *> > adjacencyMatrix;
    bool isDirected;
    int numberOfVertices;
    int numberOfEdges=0;
    class AllVerticesIter: public Iterator<Vertex>
    {
        GraphAsMatrix & owner;
        int current;
        public:
        AllVerticesIter(GraphAsMatrix &owner);
        bool IsDone() const;
        Vertex & operator*() const;
        void operator++();
    };
    class AllEdgesIter: public Iterator<Edge>
    {
        GraphAsMatrix & owner;
        int row;
        int col;
        public:
        void next();
        AllEdgesIter(GraphAsMatrix &owner);
        bool IsDone();
        Edge & operator*();
        void operator++(){next();}
    };
    class EmanEdgesIter: public Iterator<Edge>
    {
    GraphAsMatrix & owner;
        int row;
        int col;
        public:
        void next();
        EmanEdgesIter(GraphAsMatrix &owner,int v);
        bool IsDone();
        Edge & operator*();
        void operator++(){next();}
    };
    class InciEdgesIter: public Iterator<Edge>
    {
        GraphAsMatrix & owner;
        int row;
        int col;
        public:
        void next();
        InciEdgesIter(GraphAsMatrix &owner,int v);
        bool IsDone();
        Edge & operator*();
        void operator++(){next();}
    };
public:
    GraphAsMatrix (int n, bool b);
    int NumberOfVertices(){return numberOfVertices;};
    bool IsDirected(){return isDirected;};
    int NumberOfEdges(){return numberOfEdges;};
    bool IsEdge(int u, int v);
    void MakeNull(){numberOfVertices = 0;};
    void AddEdge (int u, int v);
    Edge * SelectEdge (int u, int v);
    Vertex * SelectVertex(int v){return vertices[v];};

    void wypisz(){
        for (auto i : adjacencyMatrix){
            for (auto j : i){
                std::cout << j << " ";
            }
            std::cout << std::endl;
        }
    }
    Iterator<Vertex> & VerticesIter(){
        Iterator<Vertex> * ptr = new AllVerticesIter(*this);
        std::cout << "z klasy adres" << ptr << std::endl;
        //return * new AllVerticesIter(*this);
        return *ptr;
    };
//    Iterator<Edge> & EdgesIter();
//    Iterator<Edge> & EmanatingEdgesIter(int v);
//    Iterator<Edge> & IncidentEdgesIter(int v);
};

GraphAsMatrix::AllVerticesIter::AllVerticesIter(GraphAsMatrix &owner) : current{0}, owner{owner}{}

void GraphAsMatrix::AllVerticesIter::operator++(){
    ++current;
}

Vertex & GraphAsMatrix::AllVerticesIter::operator*() const{
    return *owner.vertices[current];
}

bool GraphAsMatrix::AllVerticesIter::IsDone() const{
    if ( current >= owner.numberOfVertices){
        return true;
    }
    return false;
}



GraphAsMatrix::GraphAsMatrix (int n, bool b) : numberOfVertices{n}, isDirected{b}, vertices(n), adjacencyMatrix(n, vector<Edge*>(n)){
    for (size_t i = 0; i < n; i++)
    {
        vertices[i] = new Vertex(i);
    }
    
}


bool GraphAsMatrix::IsEdge(int u, int v){
    if (/*u != v & */ u < numberOfVertices & v < numberOfVertices){
        //std::cout << adjacencyMatrix[u][v] << std::endl;
        return adjacencyMatrix[u][v];
    }
    else{
        throw std::range_error("graph error");
    }
    
}

void GraphAsMatrix::AddEdge(int u, int v){
    if (u != v & u < numberOfVertices & v < numberOfVertices){
        if (!IsEdge(u, v)){
            Edge * e1 = new Edge(vertices[u],vertices[v]);
            adjacencyMatrix[u][v] = e1;
            ++numberOfEdges;
        }
        if (!IsDirected()){
            if (!IsEdge(v, u)){
                Edge * e2 = new Edge(vertices[v], vertices[u]);
                adjacencyMatrix[v][u] = e2;
            }
        }
    }
}

Edge * GraphAsMatrix::SelectEdge(int u, int v){
    if (u != v & u < numberOfVertices & v < numberOfVertices){
        return adjacencyMatrix[u][v];
    }
    else{
        throw std::range_error("graph error");
    }

    

}

void test(GraphAsMatrix& graph){
    
    std::cout << "Liczba krawedzi" << std::endl;
    cout << graph.NumberOfEdges() << endl;

    std::cout << "Liczba wierzcholkow" << std::endl;
    cout << graph.NumberOfVertices() << endl;

    
    Vertex* v= graph.SelectVertex(2);
    std::cout << "unikalny Numer v:" << std::endl;
    std::cout << (*v).Number() << std::endl;

    v->weight = 5;

    std::cout << "Waga v:" << std::endl;
    std::cout << v->weight << std::endl;

    std::cout << "Dodanie krawedzi" << std::endl;

    graph.AddEdge(1,2);
    graph.AddEdge(1,2);
    graph.AddEdge(2,3);
    graph.AddEdge(3,4);
    graph.AddEdge(9,9);

    std::cout << "Liczba wierzcholkow" << std::endl;
    cout << graph.NumberOfVertices() << endl;

    std::cout << "Liczba krawedzi" << std::endl;
    cout << graph.NumberOfEdges() << endl;

    std::cout << "Czy istnieje krawedz (1,1)" << std::endl;

    cout << graph.IsEdge(1,1) << endl;

    std::cout << "Czy istnieje krawedz (1,2)" << std::endl;

    cout << graph.IsEdge(1,2) << endl;

    std::cout << "Czy istnieje krawedz (2,1)" << std::endl;

    cout << graph.IsEdge(2,1) << endl;


    std::cout << "TEST (1,2)" << std::endl;

    Edge* e = graph.SelectEdge(1,2);

    Vertex * V0 =  (e->V0());
    Vertex * V1 =  (e->V1());

    std::cout << "V0: " << V0 << " o numerze: " <<  V0->Number() << std::endl;
    std::cout << "V1: " << V1 << " o numerze " <<  V1->Number() << std::endl;

    std::cout << "sasiada (V0) dla to: " << e->Mate(V0) << " i ma numer: "<< e->Mate(V0)->Number() << std::endl;
    std::cout << "sasiada (V1) dla to: " << e->Mate(V1) << " i ma numer: "<< e->Mate(V1)->Number() << std::endl;

    e->weight = V0->weight + V1->weight;

    std::cout << "waga e: " << e->weight << std::endl;


    std::cout << "TEST (2,3)" << std::endl;


    e = graph.SelectEdge(2,3);

    V0 =  (e->V0());
    V1 =  (e->V1());

    std::cout << "V0: " << V0 << " o numerze: " <<  V0->Number() << std::endl;
    std::cout << "V1: " << V1 << " o numerze " <<  V1->Number() << std::endl;

    std::cout << "sasiada (V0) dla to: " << e->Mate(V0) << " i ma numer: "<< e->Mate(V0)->Number() << std::endl;
    std::cout << "sasiada (V1) dla to: " << e->Mate(V1) << " i ma numer: "<< e->Mate(V1)->Number() << std::endl;

    e->weight = V0->weight + V1->weight;

    std::cout << "waga e: " << e->weight << std::endl;


    std::cout << "TEST (3,4)" << std::endl;


    e = graph.SelectEdge(3,4);

    V0 =  (e->V0());
    V1 =  (e->V1());

    std::cout << "V0: " << V0 << " o numerze: " <<  V0->Number() << std::endl;
    std::cout << "V1: " << V1 << " o numerze " <<  V1->Number() << std::endl;

    std::cout << "sasiada (V0) dla to: " << e->Mate(V0) << " i ma numer: "<< e->Mate(V0)->Number() << std::endl;
    std::cout << "sasiada (V1) dla to: " << e->Mate(V1) << " i ma numer: "<< e->Mate(V1)->Number() << std::endl;

    e->weight = V0->weight + V1->weight;

    std::cout << "waga e: " << e->weight << std::endl;

    /*std::cout << "TEST (9,9)" << std::endl;


    e = graph.SelectEdge(9,9);

    V0 =  (e->V0());
    V1 =  (e->V1());

    std::cout << "V0: " << V0 << " o numerze: " <<  V0->Number() << std::endl;
    std::cout << "V1: " << V1 << " o numerze " <<  V1->Number() << std::endl;

    std::cout << "sasiada (V0) dla to: " << e->Mate(V0) << " i ma numer: "<< e->Mate(V0)->Number() << std::endl;
    std::cout << "sasiada (V1) dla to: " << e->Mate(V1) << " i ma numer: "<< e->Mate(V1)->Number() << std::endl;

    e->weight = V0->weight + V1->weight;

    std::cout << "waga e: " << e->weight << std::endl;*/

    Iterator<Vertex>& iter_vertex = graph.VerticesIter();
    Iterator<Vertex>* ptr = &iter_vertex; 
    std::cout << "Adres z testu: " << ptr << std::endl;
    //delete ptr;

    std::cout << "/* message */" << std::endl;

   




}



int main(int argc, char const *argv[])
{
    GraphAsMatrix graph{10, true};
    std::cout << "TEST GRAFU SKIEROWANEGO" << std::endl;
    test(graph);

    std::cout << "TEST GRAFU NIESKIEROWANEGO" << std::endl;
    GraphAsMatrix graph_nieskierowany{10, false};
    test(graph_nieskierowany);









    return 0;
}


