#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <limits> 
#include <algorithm> 

using namespace std;

struct Item
{
    int weight;
    int cost;
};

int _knapsack(const int W, const vector<int>& wts, const vector<int>& cost)
{
    size_t n = wts.size();
    vector<int> dp(W + 1);
    dp[0] = 0;
    for (int w = 1; w <= W; w++)
    {
        dp[w] = dp[w-1];
        for (size_t i = 0; i < n; i++)
        {
            if (wts[i] <= w)
            {
                dp[w] = max(dp[w], dp[w - wts[i]] + cost[i]);
            }
        }
    }
    return dp[W];
}

int knapsack(const int W, const vector<Item>& items)
{
    size_t n = items.size();
    vector<int> dp(W + 1);

    dp[0] = 0;
    for (int w = 1; w <= W; w++)
    {
        dp[w] = dp[w - 1];
        for (size_t i = 0; i < n; i++)
        {
            if (items[i].weight <= w)
            {
                dp[w] = min(dp[w], dp[w - items[i].weight] + items[i].cost);
            }
        }
        //cout << w << ": " << dp[w] << endl;
    }
    return dp[W];
}

bool readInput(const char* fileName, int& maxWeight, vector<Item>& items)
{
    ifstream inFile(fileName);
    istringstream iss;
    string fileLine;
    Item tmpItem;
    //int tmpWeight, tmpCost;
    char tmpSku[128];

    if (!inFile)
    {
        cerr << "Cannot open " << fileName << endl;
        return false;
    }

    if (!getline(inFile, fileLine).eof())
    {
        iss.clear();
        iss.str(fileLine);
        iss >> maxWeight;

#ifdef DEBUG
        cout << maxWeight << endl;
#endif        
    }

    while (!getline(inFile, fileLine).eof())
    {
        iss.clear();
        iss.str(fileLine);
        //iss >> tmpSku >> tmpWeight >> tmpCost;
        iss >> tmpSku >> tmpItem.weight >> tmpItem.cost;
        items.push_back(tmpItem);
        //weights.push_back(tmpWeight);
        //costs.push_back(tmpCost);
#ifdef DEBUG
        //cout << tmpSku << " " << tmpWeight << " " << tmpCost << endl;
#endif        
    }

    return true;
}

bool sort_items(const Item &lhs, const Item &rhs) 
{
	return lhs.weight < rhs.weight;
}

int main(int argc, char *argv[])
{
    int maxWeight, totalValue;
    //vector<int> weights;
    //vector<int> costs;
    vector<Item> items;

    if (argc != 2 || !readInput(argv[1], maxWeight, items))
    {
        return 1;
    }

#ifdef DEBUG
    cout << "Unsorted items:\n";
    for (size_t i = 0; i < items.size(); i++)
    {
        cout << items[i].weight << " " << items[i].cost << endl;
    }
#endif
    sort(items.begin(), items.end(), sort_items);
#ifdef DEBUG
    cout << "Sorted items:\n";
    for (size_t i = 0; i < items.size(); i++)
    {
        cout << items[i].weight << " " << items[i].cost << endl;
    }
#endif


    totalValue = knapsack(maxWeight, items);

    cout << totalValue << endl;


    //playGame(moves, nMoves);

    return 0;
}
