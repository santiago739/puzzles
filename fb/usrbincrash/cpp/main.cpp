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

//void printTable(const dynamic_array<int>& dp, int n, int W)
//{
    //cout << "\t";
    //for (int j = 0; j <= W; j++)
    //{
        //cout << "\t" << j;
    //}
    //cout << endl;
    //for (int i = 0; i <= n; i++)    
    //{
        //cout << "\t" << i;
        //for (int j = 0; j <= W; j++)
        //{
            //cout << "\t" << dp[i][j];
        //}
        //cout << endl;
    //}
    //cout << endl;
//}

int knapsackMin(const int W, const vector<Item>& items)
{
    int n = static_cast<int>(items.size() - 1);
    int k = 2;
    vector<vector<int> > dp(k, vector<int>(W + 1, 0));

    // Allocate memory
    //int **dp = new int*[k];
    //for (int i = 0; i < k; ++i)
    //{
        //try
        //{
            //dp[i] = new int[W];
        //}
        //catch (std::bad_alloc e)
        //{
            //cout << e.what() << endl;
        //}
    //}

    for (int j = 0; j <= W; j++)
    {
        dp[0][j] = 0;
    }

    for (int i = 0; i < k; i++)
    {
        dp[i][0] = 0;
    }

    int i, i1, i2;

    for (i = 1; i <= n; i++)
    {
        i1 = i % 2 ? 1 : 0;
        i2 = i % 2 ? 0 : 1;

        for (int j = 1; j <= W; j++)
        {
            if (j - items[i].weight > 0)
            {
                if (i == 1)
                {
                    dp[i1][j] = dp[i1][j - items[i].weight] + items[i].cost; 
                } 
                else
                {
                    dp[i1][j] = std::min(dp[i2][j], dp[i1][j - items[i].weight] + items[i].cost);
                }
            }
            else
            {
                if (i == 1)
                {
                    dp[i1][j] = items[i].cost; 
                } 
                else
                {
                    dp[i1][j] = std::min(dp[i2][j], items[i].cost);

                }
            }
        }
        //printTable(dp, n, 10);
    }

    return i % 2 ? dp[0][W] : dp[1][W];
}

bool readInput(const char* fileName, int& maxWeight, vector<Item>& items)
{
    ifstream inFile(fileName);
    istringstream iss;
    string fileLine;
    Item tmpItem;
    char tmpSku[256];

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
    }

    while (!getline(inFile, fileLine).eof())
    {
        iss.clear();
        iss.str(fileLine);
        iss >> tmpSku >> tmpItem.weight >> tmpItem.cost;
        items.push_back(tmpItem);
    }

    return true;
}

int main(int argc, char *argv[])
{
    int maxWeight, totalValue;
    vector<Item> items;
    Item empty;

    empty.weight = empty.cost = 0;
    items.push_back(empty);

    if (argc != 2 || !readInput(argv[1], maxWeight, items))
    {
        return 1;
    }

#ifdef DEBUG
    cout << "Max weight:\n" << maxWeight << endl;
    cout << "Unsorted items:\n";
    for (size_t i = 0; i < items.size(); i++)
    {
        cout << items[i].weight << " " << items[i].cost << endl;
    }
#endif

    totalValue = knapsackMin(maxWeight, items);
    cout << totalValue << endl;

    return 0;
}
