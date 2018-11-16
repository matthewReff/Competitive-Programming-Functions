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
