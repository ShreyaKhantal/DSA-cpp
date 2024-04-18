#include <iostream>
using namespace std;

struct node
{
    node *leftchild;
    int data;
    node *rightchild;
} *root = NULL;

void preOrder(node *r);
void inOrder(node *r);
void postOrder(node *r);
void levelOrder();
node *insertion2(node *r, int data);
void print(node *r, int);
node *searchIt(int val);
node *searchRec(node *r, int val);
int height(node *r);
void printGivenLevel(node *r, int level);
node *deletion(node *r, int value);
node *minValue(node *r);
node *leftRotate(node *y);
node *rightRotate(node *y);
int getBF(node *r);

int main()
{

    cout << "Enter 1 for Insertion" << endl
         << "Enter 2 for Pre-Order Traversal" << endl
         << "Enter 3 for In-Order Traversal" << endl
         << "Enter 4 for Post-Order Traversal" << endl
         << "Enter 5 for Level-Order Traversal" << endl
         << "Enter 6 for print" << endl
         << "Enter 7 for Search (Iterative)" << endl
         << "Enter 8 for Search (Recursive)" << endl
         << "Enter 9 for Height" << endl
         << "Enter 10 for Print Given Level" << endl
         << "Enter 11 for Deletion" << endl
         << "Enter 12 to clear screen" << endl
         << "Enter 0 to EXIT" << endl;

    int ch;

    do
    {

        cout << "Enter Function no.: ";
        cin >> ch;

        switch (ch)
        {
        case 0:
            break;
        case 1:
            int data;
            cout << "Enter data for new node: ";
            cin >> data;

            root = insertion2(root, data);
            break;
        case 2:
            preOrder(root);
            break;

        case 3:
            inOrder(root);
            break;

        case 4:
            postOrder(root);
            break;

        case 5:
            levelOrder();
            break;

        case 6:
            print(root, 0);
            break;

        case 7:
            cout << "Enter data to search: ";
            int value;
            cin >> value;
            if (searchIt(value) == NULL)
            {
                cout << "Value not found." << endl;
            }
            else
            {
                cout << searchIt(value) << endl;
            }

            break;

        case 8:
            cout << "Enter data to search: ";

            cin >> value;
            if (searchRec(root, value) == NULL)
            {
                cout << "Value not found." << endl;
            }
            else
            {
                cout << searchRec(root, value) << endl;
            }

            break;

        case 9:
            cout << height(root) << endl;
            break;

        case 10:
            int level;
            cout << "Enter level no. to print: ";
            cin >> level;
            printGivenLevel(root, level);
            break;

        case 11:
            cout << "Enter value to delete: ";
            cin >> value;
            root = deletion(root, value);
            break;
        case 12:
            system("cls");
            break;
        }

        cout << endl;

    } while (ch != 0);

    return 0;
}

void print(node *r, int space)
{
    if (r == NULL)
    {

        return;
    }
    else
    {
        space += 10;
        print(r->rightchild, space);
        cout << endl;
        for (int i = 0; i < space; i++)
        {
            cout << " ";
        }
        cout << r->data << endl;
        print(r->leftchild, space);
    }
}

void preOrder(node *r)
{
    if (r == NULL)
    {
        return;
    }
    else
    {
        cout << r->data << " ";
        preOrder(r->leftchild);
        preOrder(r->rightchild);
    }
}

void inOrder(node *r)
{
    if (r == NULL)
    {
        return;
    }
    else
    {

        inOrder(r->leftchild);
        cout << r->data << " ";
        inOrder(r->rightchild);
    }
}

void postOrder(node *r)
{
    if (r == NULL)
    {
        return;
    }
    else
    {

        postOrder(r->leftchild);
        postOrder(r->rightchild);
        cout << r->data << " ";
    }
}

void levelOrder()
{
    int h = height(root);
    for (int i = 0; i <= h; i++)
    {
        printGivenLevel(root, i);
    }
}

int getBF(node *r)
{
    if (r == NULL)
    {
        return -1;
    }
    else
    {
        return (height(r->leftchild) - height(r->rightchild));
    }
}

node *leftRotate(node *y)
{

    node *x = y->rightchild;
    node *t2 = x->leftchild;
    x->leftchild = y;
    y->rightchild = t2;
    return x;
}

node *rightRotate(node *y)
{
    node *x = y->leftchild;
    node *t2 = x->rightchild;
    x->rightchild = y;
    y->leftchild = t2;
    return x;
}

node *insertion2(node *r, int data)
{
    if (r == NULL)
    {
        r = new node;
        r->leftchild = r->rightchild = NULL;
        r->data = data;
    }
    else
    {
        if (data < r->data)
        {
            r->leftchild = insertion2(r->leftchild, data);
        }
        else
        {
            r->rightchild = insertion2(r->rightchild, data);
        }
    }
    int BF = getBF(r);
    if (BF > 1 && data < (r->leftchild)->data)
    {
        return rightRotate(r);
    }
    else if (BF < -1 && data > (r->rightchild)->data)
    {
        return leftRotate(r);
    }
    else if (BF > 1 && data > (r->leftchild)->data)
    {
        r->leftchild = leftRotate(r->leftchild);
        return rightRotate(r);
    }
    else if (BF < -1 && data < (r->rightchild)->data)
    {
        r->rightchild = rightRotate(r->rightchild);
        return leftRotate(r);
    }

    return r;
}

node *searchIt(int val)
{
    if (root == NULL)
    {
        return root;
    }
    else
    {
        node *temp = root;
        while (temp != NULL)
        {
            if (val == temp->data)
            {
                return temp;
            }
            else if (val < temp->data)
            {
                temp = temp->leftchild;
            }
            else
            {
                temp = temp->rightchild;
            }
        }
        return NULL;
    }
}

node *searchRec(node *r, int val)
{
    if (r == NULL || r->data == val)
    {
        return r;
    }
    else if (val < r->data)
    {
        return searchRec(r->leftchild, val);
    }
    else
    {
        return searchRec(r->rightchild, val);
    }
}

int height(node *r)
{

    if (r == NULL)
    {
        return -1;
    }
    else
    {
        int lheight = height(r->leftchild);
        int rheight = height(r->rightchild);
        if (lheight > rheight)
        {
            return lheight + 1;
        }
        else
        {
            return rheight + 1;
        }
    }
}

void printGivenLevel(node *r, int level)
{

    if (r == NULL)
    {
        return;
    }
    else if (level == 0)
    {
        cout << r->data << " ";
    }
    else
    {
        printGivenLevel(r->leftchild, level - 1);
        printGivenLevel(r->rightchild, level - 1);
    }
}

node *deletion(node *r, int value)
{

    if (r == NULL)
    {
        return NULL;
    }
    else if (value < r->data)
    {
        r->leftchild = deletion(r->leftchild, value);
    }
    else if (value > r->data)
    {
        r->rightchild = deletion(r->rightchild, value);
    }
    else
    {
        if (r->leftchild == NULL)
        {
            return r->rightchild;
        }
        else if (r->rightchild == NULL)
        {
            return r->leftchild;
        }
        else
        {
            node *temp = minValue(r->rightchild);
            r->data = temp->data;
            r->rightchild = deletion(r->rightchild, temp->data);
        }
    }

    int BF = getBF(r);
    if (BF == 2 && getBF(r->leftchild) >= 0)
    {
        return rightRotate(r);
    }
    else if (BF == 2 && getBF(r->leftchild) == -1)
    {
        r->leftchild = leftRotate(r->leftchild);
        return rightRotate(r);
    }
    else if (BF == -2 && getBF(r->rightchild) <= 0)
    {
        return leftRotate(r);
    }
    else if (BF == -2 && getBF(r->rightchild) == 1)
    {
        r->rightchild = rightRotate(r->rightchild);
        return leftRotate(r);
    }

    return r;
}

node *minValue(node *r)
{
    node *temp = r;
    while (temp->leftchild != NULL)
    {
        temp = temp->leftchild;
    }
    return temp;
}