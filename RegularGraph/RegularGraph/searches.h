#pragma once

#ifndef SEARCHES
#define SEARCHES

vector<int>  sols2;
int ll2 = 0;
void DFS()
{

	vector<int >aux, aux2, aux3;
	aux.push_back(coord_ini);
	int tmp;
	cout << "- DFS -" << endl;

	while (aux.size()>0 and ll2 != puntos.size())
	{
		cout << "INI" << coord_ini << "FIN" << coord_fin << endl;
		tmp = aux[0];

		if (Llenos2[tmp] == 0)
		{
			aux.erase(aux.begin());
			if (tmp == coord_fin) { sols2.push_back(tmp); return; }
			else {
				for (int i = 0; i<aux.size(); i++)
					cout << ", " << aux[i];
				for (int i = 0; i<relacion[tmp].second.size(); i++)
				{       
					int relaciones = 0;
					for (int j = 0; j<familia[tmp].size(); j++)
					{
						cout << "comparo " << relacion[tmp].second[i] << " con " << familia[tmp][j] << endl;
						if (relacion[tmp].second[i] == familia[tmp][j])
						{
							relaciones++;
							break;
						}
					}		
					if (relaciones == 0)
					{
						aux2 = aux;
						aux.clear();
						aux.push_back(relacion[tmp].second[i]);
						for (int i = 0; i<aux2.size(); i++)
							aux.push_back(aux2[i]);
						cout << "PORTE:  " << aux.size() << endl;
						familia[tmp].push_back(relacion[tmp].second[i]);
					}
				}
			}
		}
		cout << "saLIANDO";
		Llenos2[tmp] = 1;
		ll2++;
	}
}


void DFS_ORG()
{
	ll2 = 0;
	DFS();
	if (ll2 == puntos.size() and sols2.size() == 0)
		cout << "No hay camino" << endl;
	for (int i = 0; i<sols2.size(); i++)
	{
		camino.push_back(make_pair(puntos[coord_ini], puntos[familia[sols2[i]][0]]));
		for (int j = 0; j<familia[sols2[i]].size(); j++)
		{
			cout << familia[sols2[i]][j] << "..";
			puntos_recorridos.push_back(puntos[familia[sols2[i]][j]]);
			if (j<familia[sols2[i]].size() - 1)
				camino.push_back(make_pair(puntos[familia[sols2[i]][j]], puntos[familia[sols2[i]][j + 1]]));
			else
				camino.push_back(make_pair(puntos[familia[sols2[i]][j]], puntos[coord_fin]));
		}
	}
}


int cercano(int de)
{
	int llegada;
	float min = 10000, mini;//sqrt((proximidad*4)*2);cout<<"HERE"<<min<<endl;	
	for (int i = 0; i<puntos.size(); i++)
	{
		float dist = distancia(puntos[i].first, puntos[coord_fin].first, puntos[i].second, puntos[coord_fin].second);
		if (grafo[de][i] != 0 and dist <= min)
		{
			min = dist; //nuevo minimo
			mini = grafo[de][i];
			llegada = i;
		}
	}
	costo += mini;
	puntos_recorridos.push_back(puntos[de]);
	Llenos[de] = 1;
	camino.push_back(make_pair(puntos[de], puntos[llegada]));
	return llegada;
}
void hill_climbing(vector <vector<float>> grafo)
{
	int a, de;//de=origen //a= destino
	bool prueba = true;
	de = coord_ini;
	for (int i = 0; i<puntos.size(); i++)
	{
		Llenos.push_back(0);
	}
	while (de != coord_fin)
	{
		if (Llenos[de] == 1)
		{
			cout << "no se puede llegar con el camino más próximo" << endl;
			prueba = false;
			break;
		}
		de = cercano(de);
	}

	if (prueba)	cout << "LLEGO ! Costo " << costo << endl;
}

void a_asterisco(vector <vector<float>> grafo)
{
	cout << " A* " << endl;
	int a, de;//de=origen //a= destino
	bool prueba = true;
	de = coord_ini;
	for (int i = 0; i<puntos.size(); i++)
	{
		Llenos.push_back(0);
	}
	while (de != coord_fin)
	{
		if (Llenos[de] == 1)
		{
			cout << "no se puede llegar con el camino más próximo" << endl;
			prueba = false;
			break;
		}
		de = cercanoA(de);
	}

	if (prueba)	cout << "LLEGO ! Costo " << costo << endl;
}

#endif // !SEARCHES
