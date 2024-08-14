#include <iostream>

using namespace std;

struct HashTable_Quadratic
{
    int * data;
    bool * used;
    int N;
    int total;
    HashTable_Quadratic(int in_N)
    {
        N = in_N;
        total = 0;
        data = new int[N];
        used = new bool[N];
        for (int i = 0; i < N; i++)
            used[i] = false;
    }
    ~HashTable_Quadratic()
    {
        delete [] data;
    }
};

bool insert(HashTable_Quadratic &table, int data)
{
    // Check if table is full
    if (table.total >= table.N)
        return false;
    
    // Find index
    int idx = data % table.N;
    int i = 0;
    for (; i < table.N && table.used[(idx + i*i) % table.N]; i++);
    
    if (i == table.N)
        return false;
    
    idx = (idx + i*i) & table.N;

    // Add
    table.data[idx] = data;
    table.used[idx] = true;
    ++table.total;
    return true;
}

int findData(const HashTable_Quadratic &table, int data)
{
    int idx = data % table.N;
    for (int i = 0; i < table.N; i++)
    {
        int realIdx = (idx + i*i) % table.N;
        if (!table.used[realIdx])
            return -1;
        if (table.data[realIdx] == data)
            return realIdx;
    }
    return -1;
}

int main()
{
    int N, k, k_count;

    cout << "Enter size of table (N): ";
    cin >> N;
    HashTable_Quadratic table(N);

    cout << "Enter the total number of values: ";
    cin >> k_count;

    cout << "Enter " << k_count << " numbers: ";
    while (k_count--)
    {
        cin >> k;
        if (!insert(table, k))
            cout << "Cannot add " << k << ".\n";
    }
    
    cout << "Enter a value to find its index in table: ";
    cin >> k;
    int idx = findData(table, k);
    if (idx < 0)
        cout << k << " is not found in table!";
    else
        cout << k << " is found at " << idx << ".";
    
    return 0;
}