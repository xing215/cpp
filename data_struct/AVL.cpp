#include <iostream>
#include <queue>
using namespace std;

struct AVL_Node
{
    int data, height;
    AVL_Node *pLeft, *pRight;
};

AVL_Node *createNode(int data)
{
    AVL_Node *newNode = new AVL_Node;
    newNode->data = data;
    newNode->pLeft = nullptr;
    newNode->pRight = nullptr;
    newNode->height = 1;
    return newNode;
}

int height(AVL_Node *root)
{
    if (root == nullptr)
        return 0;
    return root->height;
}

AVL_Node *rightRotate(AVL_Node *root)
{
    AVL_Node *newRoot = root->pLeft;
    AVL_Node *x = newRoot->pRight;
    newRoot->pRight = root;
    root->pLeft = x;

    root->height = max(height(root->pLeft), height(root->pRight)) + 1;
    newRoot->height = max(height(newRoot->pLeft), height(newRoot->pRight)) + 1;

    return newRoot;
}

AVL_Node *leftRotate(AVL_Node *root)
{
    AVL_Node *newRoot = root->pRight;
    AVL_Node *x = newRoot->pLeft;
    newRoot->pLeft = root;
    root->pRight = x;

    root->height = max(height(root->pLeft), height(root->pRight)) + 1;
    newRoot->height = max(height(newRoot->pLeft), height(newRoot->pRight)) + 1;

    return newRoot;
}

int getBalance(AVL_Node *root)
{
    if (root == nullptr)
        return 0;
    return height(root->pLeft) - height(root->pRight);
}

AVL_Node *insert(AVL_Node *root, int data)
{
    if (root == nullptr)
        return createNode(data);

    if (root->data > data)
        root->pLeft = insert(root->pLeft, data);
    else if (root->data < data)
        root->pRight = insert(root->pRight, data);
    else
        return root;

    root->height = max(height(root->pLeft), height(root->pRight)) + 1;

    int balance = getBalance(root);
    // LL
    if (balance > 1 && getBalance(root->pLeft) > 0)
        return rightRotate(root);
    // RR
    if (balance < -1 && getBalance(root->pRight) < 0)
        return leftRotate(root);
    // LR
    if (balance > 1 && getBalance(root->pLeft) < 0)
    {
        root->pLeft = leftRotate(root->pLeft);
        return rightRotate(root);
    }
    // RL
    if (balance < -1 && getBalance(root->pRight) > 0)
    {
        root->pRight = rightRotate(root->pRight);
        return leftRotate(root);
    }

    return root;
}

void printPreorder(AVL_Node *root)
{
    if (root != nullptr)
    {
        cout << root->data << ' ';
        printPreorder(root->pLeft);
        printPreorder(root->pRight);
    }
}
void printInorder(AVL_Node *root)
{
    if (root != nullptr)
    {
        printInorder(root->pLeft);
        cout << root->data << ' ';
        printInorder(root->pRight);
    }
}
void printPostorder(AVL_Node *root)
{
    if (root != nullptr)
    {
        printPostorder(root->pLeft);
        printPostorder(root->pRight);
        cout << root->data << ' ';
    }
}
void LevelOrder(AVL_Node *pRoot)
{
    queue<AVL_Node *> list;
    list.push(pRoot);
    while (!list.empty())
    {
        AVL_Node *current = list.front();
        list.pop();
        cout << current->data << ' ';

        if (current->pLeft)
            list.push(current->pLeft);
        if (current->pRight)
            list.push(current->pRight);
    }
}
AVL_Node *search(AVL_Node *root, int data)
{
    if (root == nullptr)
        return nullptr;
    if (root->data == data)
        return root;
    if (root->data > data)
        return search(root->pLeft, data);
    return search(root->pRight, data);
}

AVL_Node *remove(AVL_Node *root, int data)
{
    if (root == nullptr)
        return root;

    if (root->data > data)
        root->pLeft = remove(root->pLeft, data);
    else if (root->data < data)
        root->pRight = remove(root->pRight, data);
    else
    {
        if (root->pLeft == nullptr)
        {
            AVL_Node *pRight = root->pRight;
            delete root;
            return pRight;
        }
        if (root->pRight == nullptr)
        {
            AVL_Node *pLeft = root->pLeft;
            delete root;
            return pLeft;
        }

        AVL_Node *min = root->pRight;
        while (min->pLeft)
            min = min->pLeft;

        root->data = min->data;
        root->pRight = remove(root->pRight, min->data);
    }

    if (root == nullptr)
        return root;

    root->height = max(height(root->pLeft), height(root->pRight)) + 1;

    int balance = getBalance(root);
    // LL
    if (balance > 1 && getBalance(root->pLeft) > 0)
        return rightRotate(root);
    // RR
    if (balance < -1 && getBalance(root->pRight) < 0)
        return leftRotate(root);
    // LR
    if (balance > 1 && getBalance(root->pLeft) < 0)
    {
        root->pLeft = leftRotate(root->pLeft);
        return rightRotate(root);
    }
    // RL
    if (balance < -1 && getBalance(root->pRight) > 0)
    {
        root->pRight = rightRotate(root->pRight);
        return leftRotate(root);
    }

    return root;
}

AVL_Node *clear(AVL_Node *root)
{
    if (root == nullptr)
        return nullptr;
    root->pLeft = clear(root->pLeft);
    root->pRight = clear(root->pRight);
    delete root;
    return nullptr;
}

int main()
{
    AVL_Node *root = nullptr;

    root = insert(root, 44);
    root = insert(root, 17);
    root = insert(root, 32);
    root = insert(root, 31);
    root = insert(root, 15);
    root = insert(root, 30);

    cout << "Before adding 16";
    cout << "\nPreorder: ";
    printPreorder(root);
    cout << "\nInorder: ";
    printInorder(root);
    cout << "\nPostorder: ";
    printPostorder(root);

    root = insert(root, 16);
    cout << "\n\nAfter adding 16";
    cout << "\nPreorder: ";
    printPreorder(root);
    cout << "\nInorder: ";
    printInorder(root);
    cout << "\nPostorder: ";
    printPostorder(root);

    root = remove(root, 32);
    cout << "\n\nAfter removing 32";
    cout << "\nPreorder: ";
    printPreorder(root);
    cout << "\nInorder: ";
    printInorder(root);
    cout << "\nPostorder: ";
    printPostorder(root);

    root = clear(root);
    return 0;
}