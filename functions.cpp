struct mstEdge
{
    long double distance;
    int src;
    int dest;
    //operator are backwards due to default priority queue
    //placing longer distances higher in queue
    bool operator< (const mstEdge & other) const
    {
        return distance > other.distance;
    }

};

vector<mstEdge> kruskal(priority_queue<mstEdge> q, int verticies)
{
	parent.resize(verticies, 0);
	sizeArr.resize(verticies, 0);

	for(int i = 0; i < verticies; i++)
	{
		make_set(i);
	}
    vector<mstEdge> mst;
    mstEdge temp;
    int index1, index2;
    while (mst.size() != verticies - 1)
    {
        temp = q.top();
        q.pop();
        index1 = find_set(temp.src);
        index2 = find_set(temp.dest);
        
        if (index1 != index2)
        {
            mst.push_back(temp);
            union_sets(index1, index2);
            //vertSets.erase(vertSets.begin() + index2);
        }
    }

    return mst;
}


vector<string> pySplit(string & splitString, char seperator = ' ')
{
	int endIndex = 0;
	vector<string > seperated;
	seperated.push_back("");
	for (unsigned int i = 0; i < splitString.size(); i++)
	{
		if (splitString[i] == seperator)
		{
			endIndex++;
			seperated.push_back("");
		}
		else
		{
			seperated[endIndex] += splitString[i];
		}
	}
	return seperated;
}

void primeSeive(vector<bool> & primes, long long n)
{
    primes[0] = false;
    primes[1] = false;
    for (int i = 2; i < n; i++)
    {
        if (primes[i])
        {
            for (int j = 0; j < n / i; j++)
            {
                if (i < 10000 && (i*i) + (i * j) < n)
                {
                    primes[(i*i) + (i * j)] = false;
                }
            }
        }
    }
}

void floodFill(ll currentRow, ll currentCol, vector<string> &image, vector<vector<bool>> &found, ll rows, ll cols)
{
    found[currentRow][currentCol] = true;
    ll tempRow, tempCol;
    for (ll k = 0; k < 4; k++)
    {
        switch (k) {
        case 0:
            tempRow = currentRow - 1;
            tempCol = currentCol;
            break;
        case 1:
            tempRow = currentRow;
            tempCol = currentCol + 1;
            break;
        case 2:
            tempRow = currentRow + 1;
            tempCol = currentCol;
            break;
        case 3:
            tempRow = currentRow;
            tempCol = currentCol - 1;
            break;
        };


        if (tempRow >= 0 && tempRow < rows && tempCol >= 0 &&
            tempCol < cols && !found[tempRow][tempCol] &&
            ({fill_condition})
        {
            floodFill(tempRow, tempCol, image, found, rows, cols);
        }
    }
}

	    
	    
vector<ll> parent;
vector<ll> sizeArr;

//shamelessly stolen from
//https://cp-algorithms.com/data_structures/disjoint_set_union.html
void make_set(int v) {
    parent[v] = v;
    sizeArr[v] = 1;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (sizeArr[a] < sizeArr[b])
            swap(a, b);
        parent[b] = a;
        sizeArr[a] += sizeArr[b];
    }
}
	
//taken from cp-algorithms
struct FenwickTree {
    vector<int> bit;  // binary indexed tree
    int n;

    FenwickTree(int n) {
        this->n = n;
        bit.assign(n, 0);
    }

    FenwickTree(vector<int> a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }

    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};

	    
const ll INF = ll(1) << 60;
vector<vector<pair<int, int>>> adj;

//stolen again from cp-algorithms
void dijkstra(int startingLoc, vector<ll> & distArr, vector<ll> & parentArr) {
    int n = adj.size();
    distArr.assign(n, INF);
    parentArr.assign(n, -1);

    distArr[startingLoc] = 0;
    set<pair<int, int>> q;
    q.insert({0, startingLoc});
    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase(q.begin());

        for (auto edge : adj[v]) {
            ll to = edge.first;
            ll len = edge.second;

            if (distArr[v] + len < distArr[to]) {
                q.erase({distArr[to], to});
                distArr[to] = distArr[v] + len;
                parentArr[to] = v;
                q.insert({distArr[to], to});
            }
        }
    }
}
	    
// stolen from my coach	    
// Implementation of Hopcroft-Karp algorithm
struct BipartiteMatcher {
    vector<vector<int>> G;
    vector<int> L, R, Viz;
    vector<bool> visitedA, visitedB;
    BipartiteMatcher(int n, int m) :
        G(n), L(n, -1), R(m, -1), Viz(n), visitedA(n), visitedB(m) {}

    void AddEdge(int a, int b) {
        G[a].push_back(b);
    }

    bool Match(int node) {
        if (Viz[node])
            return false;
        Viz[node] = true;
        for (auto vec : G[node]) {
            if (R[vec] == -1 || Match(R[vec])) {
                L[node] = vec;
                R[vec] = node;
                return true;
            }
        }
        return false;
    }
    int Solve() {
        bool ok = true;
        while (ok) {
            ok = false;
            fill(Viz.begin(), Viz.end(), 0);
            for (int i = 0; i < L.size(); ++i)
                if (L[i] == -1)
                    ok |= Match(i);
        }

        int ret = 0;
        for (int i = 0; i < L.size(); ++i)
            ret += (L[i] != -1);
        return ret;
    }
    void dfs(int node) {
        visitedA[node] = true;
        for (auto to : G[node]) {
            if (!visitedB[to] && R[to] != -1) {
                visitedB[to] = true;
                dfs(R[to]);
            }
        }
    }
    //returns all the nodes in the min vertex cover
    //O(time to find max matching) + O(n)
    //first vector: all nodes in the cover on the left side
    //second vector: all nodes in the cover on the right side
    pair<vector<int>, vector<int>> getMinVertexCover() {
        Solve();
        for (int i = 0; i < L.size(); ++i) {
            if (L[i] == -1) {
                dfs(i);
            }
        }
        pair<vector<int>, vector<int>> cover;
        for (int i = 0; i < L.size(); ++i) {
            if (!visitedA[i]) cover.first.push_back(i);
        }
        for (int i = 0; i < R.size(); ++i) {
            if (visitedB[i]) cover.second.push_back(i);
        }
        return cover;
    }
};
