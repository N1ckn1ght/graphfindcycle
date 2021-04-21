#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
typedef unsigned int unt;

const string inf = "./input.txt";
const string ouf = "./output.txt";
const int LOC = 4;

vector <bool> used;
vector <vector <unt>> graph;

vector <int> ans;
unt target;
bool found;

ifstream in;
ofstream out;

void dfs(int depth, unt node, vector <bool>& used)
{
	if (found)
	{
		return;
	}
	if (depth == 0)
	{
		return;
	}
	for (unt next : graph[node])
	{
		if (depth > 1)
		{
			if (!used[next])
			{
				used[node] = true;
				dfs(depth - 1, next, used);
				used[node] = false;
			}
		}
		else
		{
			if (next == target)
			{
				found = true;
				return;
			}
		}
	}
}

void read(vector <vector <unt>>& g)
{
	unt nodes, edges, first, second;

	in >> nodes >> edges;
	g.resize(nodes);

	for (unt i = 0; i < edges; i++)
	{
		in >> first >> second;
		first--;
		second--;

		g[first].push_back(second);
		g[second].push_back(first);
	}
}

int main()
{
	in.open(inf);
	if (!in.is_open())
	{
		cout << "Kernel panic!\nFile " << inf << " does not exist!\n";
		return 0;
	}
	
	unt n;
	in >> n;
	ans.resize(n, -1);

	for (unt i = 0; i < n; i++)
	{
		read(graph);
		found = false;

		for (unt j = 0; j < graph.size(); j++)
		{
			used.clear();
			used.resize(graph.size(), false);

			target = j;
			dfs(LOC, j, used);
			if (found)
			{
				ans[i] = 1;
				break;
			}
		}
		graph.clear();
	}
	in.close();

	out.open(ouf);
	for (int i = 0; i < n; i++)
	{
		cout << ans[i] << " ";
		out << ans[i] << " ";
	}
	out.close();
}