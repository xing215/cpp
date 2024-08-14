#include <iostream>

using namespace std;

struct ListNode
{
    int data;
    ListNode *next;
    ListNode(int in_data = 0)
    {
        data = in_data;
        next = nullptr;
    }
};

void clear(ListNode* head)
{
    if (head)
    {
        auto nextNode = head->next;
        delete head;
        clear(nextNode);
    }
}

struct LinkedList
{
    ListNode *head;
    ListNode *tail;
    LinkedList()
    {
        head = tail = nullptr;
    }
    ~LinkedList()
    {
        clear(head);
    }
};

void insert(LinkedList &list, int data)
{
    auto newNode = new ListNode(data);
    if (list.head == nullptr)
        list.head = newNode; 
    else
        list.tail->next = newNode;
    list.tail = newNode;
}

bool isInList(const LinkedList &list, int data)
{
    auto traverse = list.head;
    if (traverse == nullptr)
        return false;
    for (;traverse; traverse = traverse->next)
        if (traverse->data == data)
            return true;
    return false;
}

struct HashTable_Chaining
{
    LinkedList * data;
    int N;
    HashTable_Chaining(int in_N)
    {
        N = in_N;
        data = new LinkedList[N];
    }
    ~HashTable_Chaining()
    {
        delete [] data;
    }
};

void insert(HashTable_Chaining &table, int data)
{
    int idx = data % table.N;
    insert(table.data[idx], data);
}
int findData(const HashTable_Chaining &table, int data)
{
    int idx = data % table.N;
    if (isInList(table.data[idx], data))
        return idx;
    return -1;
}

int main()
{
    int N, k, k_count;

    cout << "Enter size of table (N): ";
    cin >> N;
    HashTable_Chaining table(N);

    cout << "Enter the total number of values: ";
    cin >> k_count;

    cout << "Enter " << k_count << " numbers: ";
    while (k_count--)
    {
        cin >> k;
        insert(table, k);
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