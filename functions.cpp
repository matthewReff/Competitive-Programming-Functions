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
