#include <vector>
#include <string>
#include <iostream>

//15.05.2025

using namespace std;

template <typename T>
class Visitor
{
public:
    virtual void Visit (T & element) =0;
    virtual bool IsDone () const
	{ return false; }
};

template <typename T>
class CountingVisitor : public virtual Visitor<T>{
private:
    int counter = 0;
public:
    int zwroc_licznik(){
        int rezultat = counter;
        counter = 0;
        return rezultat;
    }

    void Visit(T &element) override {
        counter += 1;
    }

};




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
        bool IsDone() const;
        Edge & operator*() const;
        void operator++(){next();}
    };
    class EmanEdgesIter: public Iterator<Edge> //wychodzace z danego wierzcholka
    {
        GraphAsMatrix & owner;
        int row;
        int col;
        public:
        void next();
        EmanEdgesIter(GraphAsMatrix &owner,int v);
        bool IsDone() const;
        Edge & operator*() const;
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
        bool IsDone() const;
        Edge & operator*() const;
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
    void DFS(Vertex* v);
    void DFS(Visitor<Vertex *> & visitor,Vertex* v);
    bool IsConnected();
    void DFS_Spanning_Tree(Vertex * v);
    

    void wypisz(){
        for (auto i : adjacencyMatrix){
            for (auto j : i){
                std::cout << j << " ";
            }
            std::cout << std::endl;
        }
    }
    Iterator<Vertex> & VerticesIter(){
        return * new AllVerticesIter(*this);
   
    };
    Iterator<Edge> & EdgesIter(){
        return * new AllEdgesIter(*this);
    }
    Iterator<Edge> & EmanatingEdgesIter(int v){
        return * new EmanEdgesIter(*this, v);
    }
    Iterator<Edge> & IncidentEdgesIter(int v){
        return * new InciEdgesIter(*this, v);
    }
private:
    void DFS1(Vertex* v, std::vector<bool> & visited);
    void DFS_visitor(Visitor<Vertex *> & visitor, Vertex* v, std::vector<bool> & visited);
    void DFS_Spannging_Tree_1(Vertex *v, std::vector<bool> & visited, std::vector<int> & parent);
};

void GraphAsMatrix::DFS_Spanning_Tree(Vertex * v){
    if(IsConnected() && !IsDirected()){
        std::vector<bool> visited(numberOfVertices, false);
        std::vector<int> parent(numberOfVertices, -1);
        DFS_Spannging_Tree_1(v, visited, parent);
    }
}

void GraphAsMatrix::DFS_Spannging_Tree_1(Vertex *v, std::vector<bool> & visited, std::vector<int> & parent){
    visited[v->Number()] = true;
    for (size_t i = 0; i < vertices.size(); i++)
    {
        if(vertices[i] != v  && IsEdge(v->Number(), vertices[i]->Number()) && !visited[vertices[i]->Number()]){
            parent[i] = v->Number();
            std::cout << "Rodzicem wierzcholka: " << i << " jest: " << parent[i] << std::endl;
            DFS_Spannging_Tree_1(vertices[i], visited, parent);
        }
    }
}
    



//tu
bool GraphAsMatrix::IsConnected(){
    if (!IsDirected()){
        CountingVisitor<Vertex *> *visitor = new CountingVisitor<Vertex *>();
        if (vertices.size() == 0){
            return false;
        }
        
        std::vector<bool> visited(vertices.size(), false);
        DFS_visitor(*visitor, vertices[0], visited);

        if(visitor->zwroc_licznik() != vertices.size()){
            return false;
        }


        /*for (auto v : visited){
            if (!v){
                return false;
            }
        }*/
        
        
        return true;
    }
    else{
        CountingVisitor<Vertex *> *visitor = new CountingVisitor<Vertex *>();
        for (size_t i = 0; i < vertices.size() ; i++)
        {
            std::vector<bool> visited(vertices.size(), false);
            DFS_visitor(*visitor, vertices[i], visited);

            if(visitor->zwroc_licznik() != vertices.size()){
                return false;
            }

            /*for (auto v : visited){
                if (!v){
                    //std::cout << i << std::endl;
                    return false;
                }
            }*/
        }
        return true;
    }

} //napisz testy 

void GraphAsMatrix::DFS(Vertex * v){
    std::vector<bool> visited(vertices.size(), false);
    DFS1(v, visited);
    for (size_t i = 0; i < vertices.size(); i++)
    {
        if(!visited[vertices[i]->Number()]){
            DFS1(vertices[i], visited);
        }
    }
}



void GraphAsMatrix::DFS(Visitor<Vertex *> & visitor, Vertex* v){
    std::vector<bool> visited(vertices.size(), false);
    DFS_visitor(visitor, v, visited);
    for (size_t i = 0; i < vertices.size(); i++)
    {
        if(!visited[vertices[i]->Number()]){
            DFS_visitor(visitor, vertices[i], visited);
        }
    }
}

void GraphAsMatrix::DFS1(Vertex* v, std::vector<bool> & visited){
    visited[v->Number()] = true;
    std::cout << "Odwiedzony: " << v->Number() << std::endl;
    for (size_t i = 0; i < vertices.size(); i++)
    {
        if(vertices[i] != v  && IsEdge(v->Number(), vertices[i]->Number()) && !visited[vertices[i]->Number()]){
            DFS1(vertices[i], visited);
        }
    }
}

void GraphAsMatrix::DFS_visitor(Visitor<Vertex *> & visitor, Vertex* v, std::vector<bool> & visited){
    visited[v->Number()] = true;
    visitor.Visit(v);
    for (size_t i = 0; i < vertices.size(); i++)
    {
        if(vertices[i] != v  && IsEdge(v->Number(), vertices[i]->Number()) && !visited[vertices[i]->Number()]){
            DFS_visitor(visitor, vertices[i], visited);
        }
    }
}

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


GraphAsMatrix::AllEdgesIter::AllEdgesIter(GraphAsMatrix &owner) : owner{owner}, row{0}, col{0}{
    for (size_t i = 0; i < owner.NumberOfVertices(); i++)
    {
        for (size_t j = 0; j < owner.NumberOfVertices(); j++)
        {
            if (owner.IsEdge(i, j)){
                row = i;
                col = j;
                return;
            }
        }   
    }
    row = col = owner.NumberOfVertices();
}

void GraphAsMatrix::AllEdgesIter::next(){
    for (size_t i = row; i < owner.NumberOfVertices(); i++)
    {
        size_t startCol = (i == row) ? col + 1 : 0;
        for (size_t j = startCol; j < owner.NumberOfVertices(); j++)
        {
            if (owner.IsEdge(i, j)){
                row = i;
                col = j;
                return;
            }
        }   
    }
    row = col = owner.NumberOfVertices();
}

bool GraphAsMatrix::AllEdgesIter::IsDone() const{
    if(row == owner.NumberOfVertices() && col == owner.NumberOfVertices()){
        return true;
    }
    return false;
}


Edge & GraphAsMatrix::AllEdgesIter::operator*() const{
    return *owner.SelectEdge(row, col);
}

GraphAsMatrix::EmanEdgesIter::EmanEdgesIter(GraphAsMatrix &owner,int v) : owner{owner}, row{v}, col{0} {
    for (size_t i = 0; i < owner.NumberOfVertices(); i++)
    {
        if (owner.IsEdge(row, i)){
            col = i;
            return;
        }
    }
    col = owner.NumberOfVertices();
}

void GraphAsMatrix::EmanEdgesIter::next(){
    for (size_t i = col + 1; i < owner.NumberOfVertices(); i++)
    {
        if (owner.IsEdge(row, i)){
            col = i;
            return;
        }
    }
    col = owner.NumberOfVertices();
}

bool GraphAsMatrix::EmanEdgesIter::IsDone() const{
    if(col == owner.NumberOfVertices()){
        return true;
    }
    return false;
}

Edge & GraphAsMatrix::EmanEdgesIter::operator*() const{
    return *owner.SelectEdge(row, col);
}

GraphAsMatrix::InciEdgesIter::InciEdgesIter(GraphAsMatrix &owner,int v) : owner{owner}, col{v}{
    for (size_t i = 0; i < owner.NumberOfVertices(); i++)
    {
        if(owner.IsEdge(i, col)){
            row = i;
            return;
        }
    }
    row = owner.NumberOfVertices();
}

void GraphAsMatrix::InciEdgesIter::next(){
    for (size_t i = row + 1; i < owner.NumberOfVertices(); i++)
    {
        if (owner.IsEdge(i, col)){
            row = i;
            return;
        }
    }
    row = owner.NumberOfVertices();
}

bool GraphAsMatrix::InciEdgesIter::IsDone() const{
    if(row == owner.NumberOfVertices()){
        return true;
    }
    return false;
}

Edge & GraphAsMatrix::InciEdgesIter::operator*() const{
    return *owner.SelectEdge(row, col);
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





int main(int argc, char const *argv[])
{
    GraphAsMatrix* graph = new GraphAsMatrix{10, false};
    graph->AddEdge(0,1);
    graph->AddEdge(1,2);
    graph->AddEdge(2,3);
    graph->AddEdge(3,4);
    graph->AddEdge(3,7);
    graph->AddEdge(4,5);
    graph->AddEdge(5,9);
    graph->AddEdge(9,9);
    graph->AddEdge(6,8);
    graph->AddEdge(8,6);
    graph->AddEdge(0,8);

    graph->DFS_Spanning_Tree(graph->SelectVertex(0));

    graph->AddEdge(3,9);
    graph->AddEdge(5,7);
    graph->AddEdge(9,8);
    
    std::cout << "/* message */" << std::endl;

    graph->DFS_Spanning_Tree(graph->SelectVertex(0));







    return 0;
}


