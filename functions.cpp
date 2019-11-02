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

vector<mstEdge> kruskal(vector<pair<double, double> > points)
{
    priority_queue<mstEdge> q;
    int verticies = points.size();
    vector< set< int > > vertSets(verticies);
    unordered_map<int, int> setLoc;
    vector<mstEdge> mst;
    mstEdge temp;
    int index1, index2;
    
    //create vector of sets with one vertex per set
    //ex: {{0}, {1}, {2}, {3}}
    for (int i = 0; i < verticies; i++)
    {
        vertSets[i].insert(i);
        setLoc[i] = i;
    }
    
    //calculate and push all edges into queue
    for (int i = 0; i < points.size(); i++)
    {
        for (int j = i + 1; j < points.size(); j++)
        {
            temp.distance = sqrt((points[j].first - points[i].first) *
                (points[j].first - points[i].first) + (points[j].second - points[i].second)
                * (points[j].second - points[i].second));
            temp.src = j;
            temp.dest = i;
            q.push(temp);
        }
    }
  
    //starting at shortest edge distance, if edge is across different sets, combine them
    //also add edge to mst, when mst is complete return it
    while (mst.size() != verticies - 1)
    {
        temp = q.top();
        q.pop();
        index1 = setLoc[temp.src];
        index2 = setLoc[temp.dest];        
        if (index1 != index2)
        {
            mst.push_back(temp);
            for (set<int>::iterator i = vertSets[index2].begin(); i != vertSets[index2].end(); i++)
            {
                vertSets[index1].insert((*i));
                setLoc[*i] = index1;
            }
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
            break;
        case 1:
            tempRow = currentRow;
            tempCol = currentCol + 1;
            break;
        case 2:
            tempRow = currentRow + 1;
            tempCol = currentCol;
            break;
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
