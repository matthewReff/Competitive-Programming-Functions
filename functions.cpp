void pySplit(string & splitString, char seperator, vector<string> & seperated)
{
    int endIndex = 0;
    seperated.clear();
    seperated.push_back("");
    for(unsigned int i = 0; i < splitString.size(); i++)
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