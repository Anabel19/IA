#pragma once
#ifndef GRAPHO
#define GRAPHO
#include<list>
#include<vector>

using namespace std;

vector<pair<float, float>>points;
vector<pair<float, float>>edges;


template<class G>
class CNode
{
	public:
    typedef class G::Edge Edge;//typename because is a dependent scope
	//typedef typename G::n_ N;
	typedef class G::Node N;
	N value;
	int px; int py;
	list<Edge*> EdgeNod;
	pair<float, float> point;

	CNode(int x, int y){
		this->px = x; 
		this->py = y;
	}
	
	void RemEdgeN(CNode <G> *tmp){
		//lista de aristas del nodo inicio
        for (typename list<Edge*>::iterator it= EdgeNod.begin(); it != EdgeNod.end(); it++){
			//lista de aristas del nodo fin
			for (typename list<Edge*>::iterator itt= tmp->EdgeNod.begin(); itt != tmp->EdgeNod.end(); itt++){	
				if(*it == *itt){
					 EdgeNod.remove(*it);
					 tmp->EdgeNod.remove(*itt);
					 
					 delete *it;
					return;
				}
			}	
		}
    }
	
	void RemEdges(){
        Edge *tmp;
        while(!EdgeNod.empty()){
            tmp = EdgeNod.front();
            ((tmp->enodo[0])->EdgeNod).remove(tmp);
            ((tmp->enodo[1])->EdgeNod).remove(tmp);
            delete tmp;
        }
    }
	~CNode(){};
};

template<class G>
class CEdge
{
	public:
	typedef typename G::Node Node;
	typedef typename G::e_ E;
	//typedef typename G::Edge E;
	E value;
	Node *enodo[2]; //Node extremos
	bool mdir; //0[bidireccional] 1[unidireccional]
	//CEdge(E date, bool dir){
	CEdge(bool dir) {
		this->value=date;
		this->mdir=dir;
		enodo[0]=enodo[1]=nullptr;
	}
	~CEdge(){};
};

//template<class T, class C>
template<class N, class E>
class CGraph
{
	public:
	typedef CGraph<N,E>  self;
	typedef CNode<self>  Node;
	typedef CEdge<self>  Edge;
	typedef N n_;
	typedef E e_;
	int rowy, colx;//size of windows rows and columns
	int numr, numc; //number of rows and columns
	int dif;//distance between node[input]
	//vector<Node*> mnodes;
	Node**mnodes; //matrix
	
	CGraph(int wind_row, int wind_col, int dif) {
		this->rowy = wind_row;
		this->colx = wind_col;
		this->numr = (wind_row / dif);
		this->numc = (wind_row / dif);
		this->dif = dif;

		this->mnodes = new Node*[numr];
		for (unsigned i = 0; i < numr; i++) {
			this->mnodes[i] = new Node[numc];
		}
	}
	bool findN(N, unsigned&);
	bool InsNode(N);
	bool InsEdge(Node *&,Node *&,E ,bool);
	bool RemNode(N);
	bool RemEdge(N, N);
	//void printGraph();
	void Malla();
	void printVertex();
};

template<class N, class E>
//para no repetir código
bool CGraph<N,E>::findN(N d, unsigned &id){
	/*
	for(id=0;id < mnodes.size();id++){
		if(mnodes[id]->value==d)  return 1;
	}			
	return 0;
	*/
}
	
template<class N, class E>	
void CGraph<N, E>::InsNode() {
	for (unsigned int i = 0; i < numr; i++) {
		for (unsigned int j = 0; j < numc; j++) {
			mnodes[i][j] = new node(dif*j, dif*i);
		}
	}
}

template<class N, class E>
bool CGraph<N,E>::InsEdge(){			
	for (unsigned int i = 0; i <numr ; i++) {
		for (unsigned int j = 0; j < numc; j++) {
			Edge(mnodes[i][j],mnodes[i+1][j]);
			Edge(mnodes[i][j], mnodes[i+1][j+1]);
			Edge(mnodes[i][j], mnodes[i][j+1]);
		}
	}
}
template<class N, class E>
bool CGraph<N, E>::Edge(Node *&a, Node *&b) {
	Edge* new_edge = new Edge(dir);
	a->EdgeNod.push_back(new_edge);
	b->EdgeNod.push_back(new_edge);
	new_edge->enodo[0] = a; 	new_edge->enodo[1] = b;
	//prob necesitamos ya ir calculando cant de edges
	return 1;
}

template<class N, class E>
void CGraph<N, E>::Malla()
{
	for (unsigned int i = 0; i < numr; i++) {
		for (unsigned int j = 0; j < numc; j++) {
			points.push_back(make_pair(mnodes[i][j].px, mnodes[i][j].py));
		}
	}

	for (unsigned int i = 0; i < numr; i++) {
		for (unsigned int j = 0; j < numc; j++) {
			typename std::list<Edge *>::iterator it;
			for (it = mnodes[i][j]->EdgeNod.begin(); it != mnodes[i][j]->EdgeNod.end(); it++) {
				edges.push_back(make_pair(mnodes[i][j].px, mnodes[i][j].py));
				edges.push_back(make_pair((*it)->px, (*it)->py));
			}
		}
	}
}
/*
template<class N, class E>
bool CGraph<N, E>::Edge(Node *&a, Node *&b, E dato, bool dir) {
	Edge* new_edge = new Edge(dato, dir);
	a->EdgeNod.push_back(new_edge);
	b->EdgeNod.push_back(new_edge);
	new_edge->enodo[0] = a; 	new_edge->enodo[1] = b;
	//prob necesitamos ya ir calculando cant de edges
	return 1;
}
*/

template<class N, class E>
bool CGraph<N,E>::RemEdge(N a, N b){
		unsigned ia, ib;
		if(!(findN(a,ia) and findN(b,ib))) {cout<<"no hay nodos[extremos]"<<endl; return 0;}
		mnodes[ia]->RemEdgeN(mnodes[ib]);
		return 1;
}

template<class N, class E>	
bool CGraph<N,E>::RemNode(N date){
	unsigned idate;
	if(!findN(date,idate)) return 0;
		
	mnodes[idate]->RemEdges();
	delete mnodes[idate];
	mnodes->erase(mnodes.begin()+idate);
	//mnodes.erase(mnodes.begin()+idate);
	return 1;
}
/*
template<class N, class E>	
void CGraph<N,E>::printGraph(){
	for(int i=0; i<mnodes.size(); i++) {//ingreso al vector de nodos del grafo
		Node *temp_node = mnodes[i]; // cada nodo
		cout<<temp_node->value;// etiqueta-valor de cada nodo

		for (typename list<Edge*>::iterator it= temp_node->EdgeNod.begin(); it != temp_node->EdgeNod.end(); ++it){
	     	//recorrer la lista de punteros a aristas del nodo
			if(temp_node->value != (*it)->enodo[1]->value){
				cout<<" ---> "<< (*it)->value<<"("<<((*it)->enodo[1])->value<<")";
				cout<<endl;
			}
		}
		cout<<"\n";
	}
}
*/
template<class N, class E>
void CGraph<N, E>::printVertex() {
	for (unsigned i = 0; i<this->numr; i++) {
		for (unsigned j = 0; j<this->numc; j++) {
			if (this->mnodes[i][j] != NULL)
				std::cout << "(" << this->mnodes[i][j].px << ","
				<< this->mnodes[i][j].py << ")\t";
		}
		std::cout << "\n";
	}
}

#endif // !GRAPHO
