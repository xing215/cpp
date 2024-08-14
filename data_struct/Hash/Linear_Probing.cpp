#include <iostream>

using namespace std;

struct HashTable_Linear
{
    int *data;
    bool *used;
    int N;
    int total;
    HashTable_Linear(int in_N)
    {
        N = in_N;
        total = 0;
        data = new int[N];
        used = new bool[N];
        for (int i = 0; i < N; i++)
            used[i] = false;
    }
    ~HashTable_Linear()
    {
        delete[] data;
    }
};

bool insert(HashTable_Linear &table, int data)
{
    // Check if table is full
    if (table.total >= table.N)
        return false;

    // Find index
    int idx = data % table.N;
    while (table.used[idx])
        idx = (idx + 1) % table.N;

    // Add
    table.data[idx] = data;
    table.used[idx] = true;
    ++table.total;
    return true;
}

int findData(const HashTable_Linear &table, int data)
{
    int stop = (data - 1) % table.N;
    for (int idx = stop + 1; idx != stop && table.used[idx]; idx = (idx + 1) % table.N)
        if (table.data[idx] == data)
            return idx;
    if (table.used[stop] && table.data[stop] == data)
        return stop;
    return -1;
}

int main()
{
    int N, k, k_count;

    cout << "Enter size of table (N): ";
    cin >> N;
    HashTable_Linear table(N);

    cout << "Enter the total number of values: ";
    cin >> k_count;

    cout << "Enter " << k_count << " numbers: ";
    while (k_count--)
    {
        cin >> k;
        if (!insert(table, k))
            cout << "Cannot add " << k << ". Table is full.\n";
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