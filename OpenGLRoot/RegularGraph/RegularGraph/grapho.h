#pragma once
#ifndef GRAPHO
#define GRAPHO
#include<list>
#include<vector>

using namespace std;

vector<pair<float,float>> Dpoints;
vector<pair<pair<float,float>,pair<float,float>>>Dedges;

template<class G> 
class Cnode{
    public:
	typedef typename G::gedge nE;
	int px;
	int py;
	list<nE*> EdgeNode;
	Cnode(int x_, int y_){
		this->px=x_;
		this->py=y_;
	}
	~Cnode(){
		
	}
	//node(){};
};

template<class G>
class Cedge{
    public:
	typedef typename G::gnode eN;
	eN* enode[2];
	int y;
	Cedge(eN* n1, eN* n2){
		this->enode[0]=n1;
		this->enode[1]=n2;
	}
	/*
	void distancia() {
		return sqrt(pow(,2),pow(,2));
	}*/
	//node(){};
};

template<class H, class W>
class Cgrafo{
	public:
	
	typedef Cgrafo<H,W> self;
	typedef Cnode<self> gnode;
	typedef Cedge<self> gedge;
	
	gnode ***malla;//double pointer[#error!]
	int winr; int winc; //size window
	int row; int  col; //size malla
	int dis;
	/*
	int size = 0;
	map <Punto, int> IDs;
	map<int, Nodo*>nodos;
	set< pair<int, int> > Obstaculos;
	*/
	Cgrafo(int wr,int wc, int dif){
		this->winr=wr; 	this->row=wr/dif;
		this->winc=wc;	this->col=wc/dif;
		this->dis = dif;
		malla=new gnode**[row];
		for(int i=0; i<row; i++){
		   malla[i]=new gnode*[col];//#think in the constructor 
		}
	}
	~Cgrafo(){
		for(unsigned int i=0; i<row; i++){
			delete[]malla[i];
		}
		delete[]malla;
	}
	void createVertex();
	void createEdges();
	void collectToDraw();
	void print();
};
template<class H, class W>
void Cgrafo<H,W>::createVertex(){
	int k=1;
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
		     malla[i][j]=new gnode(0.1*j,0.1*i);
			 k++;
		} 	
	} 
}
template<class H, class W>
void Cgrafo<H,W>::createEdges(){
	gedge *newEdge;
	for(unsigned int i=0;i<row-1;i++){
		for(unsigned int j=0;j<col-1;j++){
			newEdge = new gedge(malla[i][j],malla[i][j+1]);
			malla[i][j]->EdgeNode.push_back(newEdge);
			newEdge = new gedge(malla[i][j],malla[i+1][j+1]);
			malla[i][j]->EdgeNode.push_back(newEdge);
			newEdge = new gedge(malla[i][j],malla[i+1][j]);
			malla[i][j]->EdgeNode.push_back(newEdge);
		}
	}
}
template<class H, class W>
void Cgrafo<H, W>::collectToDraw() {
	for (int i = 0; i<row; i++) {
		for (int j = 0; j<col; j++) {
			Dpoints.push_back(make_pair(malla[i][j]->px, malla[i][j]->py));
		}
	}
	for (unsigned int i = 0; i<row - 1; i++) {
		for (unsigned int j = 0; j<col - 1; j++) {
			//cout<<malla[i][j]->x<<","<<malla[i][j]->y<<" ";
			for (typename std::list<gedge *>::iterator it = malla[i][j]->EdgeNode.begin(); it != malla[i][j]->EdgeNode.end(); it++) {
				Dedges.push_back(make_pair(make_pair((*it)->enode[0]->px, (*it)->enode[0]->py), make_pair((*it)->enode[1]->px, (*it)->enode[1]->py)));
			}
		}
	}
}
template<class H, class W>
void Cgrafo<H,W>::print(){
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
		    cout<<malla[i][j]->px<<","<<malla[i][j]->py<<" ";
		}
		cout<<endl;
	}
	cout<<"edjesss  "<<endl;
	for(unsigned int i=0; i<row-1; i++){
		for(unsigned int j=0;j<col-1;j++){
			//cout<<malla[i][j]->x<<","<<malla[i][j]->y<<" ";
			for(typename std::list<gedge *>::iterator it = malla[i][j]->EdgeNode.begin(); it!=malla[i][j]->EdgeNode.end(); it++){
				cout<<(*it)->enode[0]->px<<","<<(*it)->enode[0]->py<<";"<<(*it)->enode[1]->px<<","<<(*it)->enode[1]->py<<" ";	
			}
			//cout<<endl;
		}
	}		
}
/*
bool bfs(int begin, int end, vector<pair<int, int> >& visitados, vector<int>& Anterior) {
	Anterior.resize(size);
	Anterior[begin] = -1;
	Anterior[end] = -1;
	bool Visitado[size];
	for (int i = 0; i<size; i++) {
		Visitado[i] = 0;
	}
	vector<Nodo*> BFS;
	Visitado[begin] = 1;
	BFS.push_back(nodos[begin]);
	int i = 0;
	while (i<BFS.size()) {
		for (auto it = (*BFS[i]).aristas.begin(); it != (*BFS[i]).aristas.end(); it++) {
			if (Obstaculos.find(make_pair(BFS[i]->ID, it->first)) == Obstaculos.end()) {
				if (it->first == end) {
					Anterior[it->first] = BFS[i]->ID;
					visitados.push_back(make_pair(BFS[i]->ID, it->first));
					return true;
				}
				if (!Visitado[it->first]) {
					visitados.push_back(make_pair(BFS[i]->ID, it->first));
					Visitado[it->first] = 1;
					Anterior[it->first] = BFS[i]->ID;
					BFS.push_back(it->second);
				}
			}
		}
		i++;
	}
	return false;
}
bool mejorElPrimero(int begin, int end, vector<pair<int, int> >& visitados, vector<int>& Anterior) {
	Anterior.resize(size);
	Anterior[begin] = -1;
	Anterior[end] = -1;
	priority_queue<pair<double, int>, vector<pair<double, int> >, greater<pair<double, int> > > Q;
	Q.push(make_pair((nodos[begin]->punto - nodos[end]->punto).norm(), begin));
	bool Visitado[size];
	for (int i = 0; i<size; i++) {
		Visitado[i] = 0;
	}
	Visitado[begin] = 1;
	while (!Q.empty()) {
		pair<long, int> p = Q.top();
		Q.pop();
		int here = p.second;
		if (here == end) {
			return true;
		}
		for (auto it = nodos[here]->aristas.begin(); it != nodos[here]->aristas.end(); it++) {
			if (!Visitado[it->first]) {
				if (Obstaculos.find(make_pair(here, it->first)) == Obstaculos.end()) {
					Visitado[it->first] = 1;
					Anterior[it->first] = here;
					visitados.push_back(make_pair(here, it->first));
					Q.push(make_pair(((it->second)->punto - nodos[end]->punto).norm(), it->first));
				}
			}
		}
	}
	return false;
}
*/
#endif // !GRAPHO