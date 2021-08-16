#include <iostream>

class treeNode
{
private:
    int data;
    treeNode *left, *right;

public:
    treeNode();
    treeNode(int d)
    {
        this->data = d;
        this->right = nullptr;
        this->left = nullptr;
    }
    treeNode(int d, treeNode *l, treeNode *r)
    {
        this->data = d;
        this->left = l;
        this->right = r;
    }
    int getData()
    {
        return this->data;
    }
    treeNode *getLeft()
    {
        return this->left;
    }
    treeNode *getRight()
    {
        return this->right;
    }
    void setData(int d)
    {
        this->data = d;
    }
    void setLeft(treeNode *l)
    {
        this->left = l;
    }
    void setRight(treeNode *r)
    {
        this->right = r;
    }
};

class BinaryTree
{
private:
    treeNode *root;
    int count;
    void _print(treeNode *cur)
    {
        if (cur)
        {
            _print(cur->getLeft());
            std::cout << cur->getData() << " ";
            _print(cur->getRight());
        }
    }

public:
    BinaryTree()
    {
        this->root = nullptr;
        this->count = 0;
    }

    void insertNode(treeNode *node)
    {
        this->count++;
        int tempCount = this->count;
        if (this->root == nullptr)
        {
            this->root = node;
        }
        else
        {
            treeNode *cur = this->root;
            int mask = 1;
            while (mask <= tempCount)
            {
                mask = mask << 1;
            }
            mask = mask >> 2;
            while (mask > 1)
            {
                // std::cout << mask << " ";
                if (mask & tempCount)
                {
                    cur = cur->getRight();
                }
                else
                {
                    cur = cur->getLeft();
                }
                mask = mask >> 1;
            }
            if (mask & tempCount)
            {
                cur->setRight(node);
            }
            else
            {
                cur->setLeft(node);
            }
        }
    }

    void deleteNode(treeNode *node)
    {
    }

    void printTree()
    {
        _print(this->root);
    }
};

int main()
{
    BinaryTree YOYO;

    for (int i = 1; i <= 8; i++)
    {
        treeNode *node = new treeNode(i);
        YOYO.insertNode(node);
    }
    YOYO.printTree();

    return 0;
}