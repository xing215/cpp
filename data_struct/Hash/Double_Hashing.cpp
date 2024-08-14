#include <iostream>

using namespace std;

int lowerPrime(int n)
{
    int i = 2, calc = n;
    while (i < calc)
        if (calc % i == 0)
            calc /= i;
        else
            i++;
    if (calc < n)
        return calc;
    return lowerPrime(n - 1);
}

struct HashTable_Double
{
    int *data;
    bool *used;
    int N;
    int total;
    int hash;
    HashTable_Double(int in_N)
    {
        N = in_N;
        total = 0;
        data = new int[N];
        used = new bool[N];
        for (int i = 0; i < N; i++)
            used[i] = false;
        hash = lowerPrime(N);
    }
    ~HashTable_Double()
    {
        delete[] data;
    }
};

bool insert(HashTable_Double &table, int data)
{
    // Check if table is full
    if (table.total >= table.N)
        return false;

    // Find index
    int idx = data % table.N;
    int h2 = 1 + (data % (table.N - 1));
    int i = 0;
    for (; i < table.N && table.used[(idx + i * h2) % table.N]; i++);

    if (i == table.N)
        return false;

    idx = (idx + i * h2) % table.N;

    // Add
    table.data[idx] = data;
    table.used[idx] = true;
    ++table.total;
    return true;
}

int findData(const HashTable_Double &table, int data)
{
    int idx = data % table.N;
    int h2 = 1 + (data % (table.N - 1));
    for (int i = 0; i < table.N; i++)
    {
        int realIdx = (idx + i * h2) % table.N;
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
    HashTable_Double table(N);

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