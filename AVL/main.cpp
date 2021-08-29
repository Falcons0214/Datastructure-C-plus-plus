#include <iostream>

int _max(int A, int B)
{
    return A > B ? A : B;
}

class node
{
private:
    node *parent;
    node *left;
    node *right;
    int height;
    int key;

public:
    node(int k)
    {
        parent = left = right = NULL;
        height = 0;
        key = k;
    }
    void setParent(node *p)
    {
        parent = p;
    }
    void setLeft(node *l)
    {
        left = l;
    }
    void setRight(node *r)
    {
        right = r;
    }
    void setHeight(int h)
    {
        height = h;
    }
    void setKey(int k)
    {
        key = k;
    }
    node *getParent()
    {
        return parent;
    }
    node *getLeft()
    {
        return left;
    }
    node *getRight()
    {
        return right;
    }
    int getHeight()
    {
        return height;
    }
    int getKey()
    {
        return key;
    }
};

class AVL
{
private:
    node *root;
    int count;
    void increase()
    {
        count++;
    }
    void decrease()
    {
        count--;
    }
    int getNodeHeight(node *n)
    {
        return n == NULL ? 0 : n->getHeight() + 1;
    }
    void L_rotation(node *n)
    {
        node *nParent = n->getParent();
        node *grandParent = nParent->getParent();

        nParent->setRight(n->getLeft());
        
        if(n->getLeft())
            n->getLeft()->setParent(nParent);

        n->setLeft(nParent);
        nParent->setParent(n);

        if (!grandParent)
        {
            this->root = n;
            n->setParent(NULL);
        }
        else
        {
            if (grandParent->getLeft() == nParent)
            {
                grandParent->setLeft(n);
            }
            else
            {
                grandParent->setRight(n);
            }
            n->setParent(grandParent);
        }
        nParent->setHeight(_max(getNodeHeight(nParent->getLeft()), getNodeHeight(nParent->getRight())));
    }
    void R_rotation(node *n)
    {
        node *nParent = n->getParent();
        node *grandParent = nParent->getParent();

        nParent->setLeft(n->getRight());
        
        if(n->getRight()) 
            n->getRight()->setParent(nParent);

        n->setRight(nParent);
        nParent->setParent(n);

        if (!grandParent)
        {
            this->root = n;
            n->setParent(NULL);
        }
        else
        {
            if (grandParent->getRight() == nParent)
            {
                grandParent->setRight(n);
            }
            else
            {
                grandParent->setLeft(n);
            }
            n->setParent(grandParent);
        }
        nParent->setHeight(_max(getNodeHeight(nParent->getLeft()), getNodeHeight(nParent->getRight())));
    }
    void checkBalance(node *leaf)
    {
        while (leaf)
        {
            if ((!leaf->getLeft()) && (!leaf->getRight()))
            {
                leaf->setHeight(0);
            }
            else
            {
                int flag = 0;
                int R = getNodeHeight(leaf->getRight());
                int L = getNodeHeight(leaf->getLeft());
                if (L - R > 1)
                {
                    flag = 1;
                    node *temp = leaf->getLeft();
                    if (getNodeHeight(temp->getLeft()) > getNodeHeight(temp->getRight()))
                    {
                        R_rotation(temp);
                    }
                    else
                    {
                        L_rotation(temp->getRight()); 
                        R_rotation(temp->getParent());
                    }
                    leaf = temp;
                }
                if (L - R < -1)
                {
                    flag = 1;
                    node *temp = leaf->getRight();
                    if (getNodeHeight(temp->getRight()) > getNodeHeight(temp->getLeft()))
                    {
                        L_rotation(temp);
                    }
                    else
                    {
                        R_rotation(temp->getLeft());
                        L_rotation(temp->getParent());
                    }
                    leaf = temp;
                }
                if (!flag)
                    leaf->setHeight(_max(R, L));
            }
            leaf = leaf->getParent();
        }
    }
    void _print(node *cur)
    {
        if (cur)
        {
            std::cout << cur->getKey() << "\n";
            _print(cur->getLeft());
            // std::cout << cur->getKey() << "\n";
            _print(cur->getRight());
        }
    }
    node *_search(node *cur, int key) 
    {
        if(cur->getKey() == key) {
            return cur;
        }
        return cur->getKey() > key ? _search(cur->getLeft(), key) : _search(cur->getRight(), key);
    }
    node *searchMinNode(node *n)
    {
        if( !n->getLeft() )
            return n;
        return searchMinNode(n->getLeft());
    }
public:
    AVL()
    {
        root = NULL;
        count = 0;
    };
    node *searchNode(int k)
    {
        return _search(this->root, k);
    }
    void insertNode(node *n)
    {
        node *cur = this->root;
        this->increase();
        if (!cur)
        {
            this->root = n;
            return;
        }
        while (1)
        {
            if (cur->getKey() > n->getKey())
            {
                if (!cur->getLeft())
                {
                    cur->setLeft(n);
                    n->setParent(cur);
                    break;
                }
                cur = cur->getLeft();
            }
            else
            {
                if (!cur->getRight())
                {
                    cur->setRight(n);
                    n->setParent(cur);
                    break;
                }
                cur = cur->getRight();
            }
        }
        checkBalance(n);
    }
    node *removeNode(int k)
    {
        node *del = this->searchNode(k);
        node *replace = searchMinNode(del->getRight());

        if(replace->getParent() != del)
        {
            replace->getParent()->setLeft(replace->getRight());
            if(replace->getRight())
            {
                replace->getRight()->setParent(replace->getParent());
            }
        }

        if(del->getParent())
        {
            replace->setParent(del->getParent());
            if( del->getParent()->getLeft() == del ) {
                del->getParent()->setLeft(replace);
            }else{
                del->getParent()->setRight(replace);
            }
        }else{
            this->root = replace;
        }

        replace->setLeft(del->getLeft());
        replace->setRight(del->getRight());
        if(replace->getLeft()) {
            replace->getLeft()->setParent(replace);
        }
        if(replace->getRight()) {
            replace->getRight()->setParent(replace);
        }
        
        checkBalance(replace->getRight());
        return del;
    }
    void printTree()
    {
        _print(this->root);
    }
    int getCount()
    {
        return count;
    }
};

int main()
{
    std::cout << "start"
              << "\n";

    AVL tree;
    int n = 12, arr[n] = {10, 5, 15, 14, 17, 4, 7, 18, 1, 6, 8, 9};

    for (int i = 0; i < n; i++)
    {
        node *temp = new node(arr[i]);
        tree.insertNode(temp);
    }

    tree.removeNode(5);

    tree.printTree();

    return 0;
}