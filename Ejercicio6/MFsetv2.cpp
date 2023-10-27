#include <iostream>
using namespace std;

class MFSet
{
	int *altura, *parent, n;

public:
	MFSet(int n)
	{
		parent = new int[n];
		altura = new int[n];
		this->n = n;
		makeSet();
	}

	void makeSet()
	{
		for (int i = 0; i < n; i++)
		{
			parent[i] = i;
		}
	}

	int find(int x)
	{
		if (parent[x] != x)
		{
			// aplanamos el arbol
			parent[x] = find(parent[x]);
		}
		return parent[x];
	}

	void merge(int x, int y)
	{
		int xset = find(x);
		int yset = find(y);

		// si estan dentro del mismo set terminamos
		if (xset == yset)
			return;

		// evitamos aumentar la altura del arbol
		if (altura[xset] < altura[yset])
		{
			parent[xset] = yset;
		}
		else if (altura[xset] > altura[yset])
		{
			parent[yset] = xset;
		}

		// si ambas alturas con la misma usamos cualquiera y actualizamos la altura
		else
		{
			parent[yset] = xset;
			altura[xset] = altura[xset] + 1;
		}
	}
};
// fuente: https://www.geeksforgeeks.org/disjoint-set-data-structures/