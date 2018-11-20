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

//return index of set that contains the element in vector of sets
int findSet(vector< set< int > > vertSets, int element)
{
	for (unsigned int i = 0; i < vertSets.size(); i++)
	{
		set<int>::iterator j = vertSets[i].begin();
		while (j != vertSets[i].end())
		{
			if ((*j) == element)
			{
				return i;
			}
			j++;
		}
	}
	return -1; 
}


vector<mstEdge> kruskal(priority_queue<mstEdge> q, int verticies)
{
	vector< set< int > > vertSets(verticies);
	for (int i = 0; i < verticies; i++)
	{
		vertSets[i].insert(i);
	}
	vector<mstEdge> mst;
	mstEdge temp;
	int index1, index2;
	while (mst.size() != verticies - 1)
	{
		temp = q.top();
		q.pop();
		index1 = findSet(vertSets, temp.dest);
		index2 = findSet(vertSets, temp.src);
		if (index1 != index2)
		{
			mst.push_back(temp);
			for (set<int>::iterator i = vertSets[index2].begin(); i != vertSets[index2].end(); i++)
			{
				vertSets[index1].insert((*i));
			}
			vertSets.erase(vertSets.begin() + index2);
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
