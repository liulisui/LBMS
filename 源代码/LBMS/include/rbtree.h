#ifndef RBTREE_H
#define RBTREE_H

#include <bits/stdc++.h>
using namespace std;
enum RBTColor
{
    RED,
    BLACK
};

template <typename T, typename T0>
class RBTNode
{
public:
    RBTColor color;  // 颜色
    T key;           // 关键字
    RBTNode *left;   // 左孩子
    RBTNode *right;  // 右孩子
    RBTNode *parent; // 父结点
    T0 data;
    RBTNode();
    RBTNode(T value, RBTColor c, RBTNode *p, RBTNode *l, RBTNode *r, T0 d);
};
template <typename T, typename T0>
class RBTree
{
private:
    RBTNode<T, T0> *root; // 根结点

public:
    RBTree();
    ~RBTree();

    // 查找"红黑树"中键值为key的节点
    RBTNode<T, T0> *search(T key);

    // 将结点插入到红黑树中
    void insert(T key, T0 data);

    // 删除结点
    void remove(T key);

    // 销毁红黑树
    void destroy();
    RBTNode<T, T0> *get_root();
    bool empty();

private:
    // 查找节点
    RBTNode<T, T0> *search(RBTNode<T, T0> *x, T key);
    // 左旋
    void left_rotate(RBTNode<T, T0> *&root, RBTNode<T, T0> *x);
    // 右旋
    void right_rotate(RBTNode<T, T0> *&root, RBTNode<T, T0> *y);
    // 插入函数
    void insert(RBTNode<T, T0> *&root, RBTNode<T, T0> *node);
    // 插入修正函数
    void insert_fix(RBTNode<T, T0> *&root, RBTNode<T, T0> *node);
    // 删除函数
    void remove(RBTNode<T, T0> *&root, RBTNode<T, T0> *node);
    // 删除修正函数
    void remove_fix(RBTNode<T, T0> *&root, RBTNode<T, T0> *node, RBTNode<T, T0> *parent);
    // 销毁红黑树
    void destroy(RBTNode<T, T0> *&tree);
};



template <typename T, typename T0>
RBTNode<T,T0>::RBTNode() : left(NULL), right(NULL), parent(NULL){}
template <typename T, typename T0>
RBTNode<T,T0>::RBTNode(T value, RBTColor c, RBTNode<T,T0> *p, RBTNode<T,T0> *l, RBTNode<T,T0> *r, T0 d)
{
    key = value;
    color = c;
    parent = p;
    left = l;
    right = r;
    data = d;
}


template <typename T, typename T0>
bool RBTree<T, T0>::empty()
{
    return root == NULL;
}

template <typename T, typename T0>
RBTNode<T, T0> *RBTree<T, T0>::get_root()
{
    return root;
}

template <typename T, typename T0>
RBTree<T, T0>::RBTree()
{
    root = NULL;
}
template <typename T, typename T0>
RBTree<T, T0>::~RBTree()
{
    destroy();
}
template <typename T, typename T0>
RBTNode<T, T0> *RBTree<T, T0>::search(RBTNode<T, T0> *x, T key)
{
    if (x == NULL || x->key == key)
        return x;
    if (key < x->key)
        return search(x->left, key);
    else
        return search(x->right, key);
}

template <typename T, typename T0>
RBTNode<T, T0> *RBTree<T, T0>::search(T key)
{
    return search(root, key);
}

template <typename T, typename T0>
void RBTree<T, T0>::destroy(RBTNode<T, T0> *&x)
{
    if (x == NULL)
        return;
    if (x->left != NULL)
        destroy(x->left);
    if (x->right != NULL)
        destroy(x->right);
    delete x;
    x = NULL;
}

template <typename T, typename T0>
void RBTree<T, T0>::destroy()
{
    destroy(root);
}

template <typename T, typename T0>
void RBTree<T, T0>::left_rotate(RBTNode<T, T0> *&root, RBTNode<T, T0> *x)
{

    RBTNode<T, T0> *y = x->right;
    if (y->left == NULL)
    {
        x->right = NULL;
    }
    else
    {
        x->right = y->left;
        y->left->parent = x;
    }

    y->parent = x->parent;
    if (x->parent == NULL)
    {
        root = y;
    }
    else
    {
        if (x->parent->left == x)
            x->parent->left = y;
        else
            x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

template <typename T, typename T0>
void RBTree<T, T0>::right_rotate(RBTNode<T, T0> *&root, RBTNode<T, T0> *y)
{

    RBTNode<T, T0> *x = y->left;

    if (x->right == NULL)
    {
        y->left = NULL;
    }
    else
    {
        y->left = x->right;
        x->right->parent = y;
    }

    x->parent = y->parent;
    if (y->parent == NULL)
    {
        root = x;
    }
    else
    {
        if (y == y->parent->right)
            y->parent->right = x;
        else
            y->parent->left = x;
    }

    x->right = y;
    y->parent = x;
}

template <typename T, typename T0>
void RBTree<T, T0>::insert(T key, T0 data)
{
    RBTNode<T, T0> *z = NULL;
    // 创建节点
    z = new RBTNode<T, T0>(key, BLACK, NULL, NULL, NULL, data);

    insert(root, z);
}
template <class T, class T0>
void RBTree<T, T0>::insert(RBTNode<T, T0> *&root, RBTNode<T, T0> *node)
{
    RBTNode<T, T0> *y = NULL;
    RBTNode<T, T0> *x = root;

    //  将红黑树当作一颗二叉查找树，将节点添加到二叉查找树中。
    while (x != NULL)
    {
        y = x;
        if (node->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    node->parent = y;
    if (y != NULL)
    {
        if (node->key < y->key)
            y->left = node;
        else
            y->right = node;
    }
    else
        root = node;

    // 设置节点的颜色为红色
    node->color = RED;

    // 将它重新修正为一颗二叉查找树
    insert_fix(root, node);
}

template <typename T, typename T0>
void RBTree<T, T0>::insert_fix(RBTNode<T, T0> *&root, RBTNode<T, T0> *node)
{
    // 将根节点设为黑色
    root->color = BLACK;
    RBTNode<T, T0> *parent, *gparent;

    // 若父节点存在，并且父节点的颜色是红色
    while ((parent = node->parent) != NULL && parent->color == RED)
    {
        gparent = parent->parent;

        // 若父节点是祖父节点的左孩子
        if (parent == gparent->left)
        {
            // 若叔叔节点是红色
            {
                RBTNode<T, T0> *uncle = gparent->right;
                if (uncle != NULL && uncle->color == RED)
                {
                    uncle->color = BLACK;
                    parent->color = BLACK;
                    gparent->color = RED;
                    node = gparent;
                    continue;
                }
            }

            // 若叔叔是黑色，且当前节点是右孩子
            if (parent->right == node)
            {
                RBTNode<T, T0> *tmp;
                left_rotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            // 若叔叔是黑色，且当前节点是左孩子
            parent->color = BLACK;
            gparent->color = RED;
            right_rotate(root, gparent);
        }
        else // 若父节点是祖父节点的右孩子
        {
            // 若叔叔节点是红色
            {
                RBTNode<T, T0> *uncle = gparent->left;
                if (uncle != NULL && uncle->color == RED)
                {
                    uncle->color = BLACK;
                    parent->color = BLACK;
                    gparent->color = RED;
                    node = gparent;
                    continue;
                }
            }

            // 若叔叔是黑色，且当前节点是左孩子
            if (parent->left == node)
            {
                RBTNode<T, T0> *tmp;
                right_rotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            // 若叔叔是黑色，且当前节点是右孩子
            parent->color = BLACK;
            gparent->color = RED;
            left_rotate(root, gparent);
        }
    }
}

template <typename T, typename T0>
void RBTree<T, T0>::remove(T key)
{
    RBTNode<T, T0> *node;
    // 查找key对应的节点node，找到的话就删除该节点
    if ((node = search(root, key)) != NULL)
        remove(root, node);
}

template <typename T, typename T0>
void RBTree<T, T0>::remove(RBTNode<T, T0> *&root, RBTNode<T, T0> *node)
{
    RBTNode<T, T0> *child, *parent;
    RBTColor color;

    // 被删除节点的左右孩子都不为空的情况
    if ((node->left != NULL) && (node->right != NULL))
    {
        // 寻找被删节点的取代节点
        // 用它来取代被删节点的位置，然后再将被删节点去掉。
        RBTNode<T, T0> *replace = node;

        // 获取右子树中的最小节点
        replace = replace->right;
        while (replace->left != NULL)
            replace = replace->left;

        // node不是根节点
        if (node->parent != NULL)
        {
            if ((node->parent)->left == node)
                (node->parent)->left = replace;
            else
                (node->parent)->right = replace;
        }
        else
            // node节点是根节点
            root = replace;

        // child是"取代节点"的右孩子，也是需要"调整的节点"。
        child = replace->right;
        parent = replace->parent;
        color = replace->color;

        // "被删除节点"是"它的后继节点的父节点"
        if (parent == node)
        {
            parent = replace;
        }
        else
        {
            // child不为空
            if (child != NULL)
                child->parent = parent;
            parent->left = child;

            replace->right = node->right;
            (node->right)->parent = replace;
        }

        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;

        if (color == BLACK)
            remove_fix(root, child, parent);

        delete node;
        return;
    }

    if (node->left != NULL)
        child = node->left;
    else
        child = node->right;

    parent = node->parent;
    // 保存"取代节点"的颜色
    color = node->color;

    if (child != NULL)
        child->parent = parent;

    // "node节点"不是根节点
    if (parent != NULL)
    {
        if (parent->left == node)
            parent->left = child;
        else
            parent->right = child;
    }
    else
        root = child;

    if (color == BLACK)
        remove_fix(root, child, parent);
    delete node;
}
template <typename T, typename T0>
void RBTree<T, T0>::remove_fix(RBTNode<T, T0> *&root, RBTNode<T, T0> *node, RBTNode<T, T0> *parent)
{
    RBTNode<T, T0> *other;

    while ((!node || node->color == BLACK) && node != root)
    {
        // 为左子结点
        if (parent->left == node)
        {
            other = parent->right;
            if (other->color == RED)
            {
                // 情况2：兄弟是红色的
                other->color = BLACK;
                parent->color = RED;
                left_rotate(root, parent);
                other = parent->right;
            }
            if (((!other->left || (other->left)->color == BLACK)) &&
                (!other->right || (other->right)->color == BLACK))
            {
                // 情况3：父亲、兄弟和兄弟的两个儿子都是黑色的
                if (parent->color == BLACK)
                {
                    other->color = RED;
                    node = parent;
                    parent = node->parent;
                    continue;
                }
                // 情况4：兄弟和兄弟的两个儿子是黑色的，父亲是红色的
                else
                {
                    other->color = RED;
                    parent->color = BLACK;
                    break;
                }
            }
            else
            {
                if (!other->right || (other->right)->color == BLACK)
                {
                    // 情况5：兄弟是黑色的，兄弟的左孩子是红色，右孩子为黑色。
                    (other->left)->color = BLACK;
                    other->color = RED;
                    right_rotate(root, other);
                    other = parent->right;
                }
                // 情况6：兄弟是黑色的，兄弟的右孩子是红色的，左孩子任意颜色。
                other->color = parent->color;
                parent->color = BLACK;
                (other->right)->color = BLACK;
                left_rotate(root, parent);
                node = root;
                break;
            }
        }
        else
        {
            other = parent->left;
            if (other->color == RED)
            {
                // 情况2：兄弟是红色的
                other->color = BLACK;
                parent->color = RED;
                right_rotate(root, parent);
                other = parent->left;
            }
            if ((!other->left || (other->left)->color == BLACK) &&
                (!other->right || (other->right)->color == BLACK))
            {
                // 情况3：父亲、兄弟和兄弟的两个儿子都是黑色的
                if (parent->color == BLACK)
                {
                    other->color = RED;
                    node = parent;
                    parent = node->parent;
                    continue;
                }
                // 情况4：兄弟和兄弟的两个儿子是黑色的，父亲是红色的
                else
                {
                    other->color = RED;
                    parent->color = BLACK;
                    break;
                }
            }
            else
            {
                if (!other->left || (other->left)->color == BLACK)
                {
                    // 情况5：兄弟是黑色的，兄弟的右孩子是红色，左孩子为黑色。
                    (other->right)->color = BLACK;
                    other->color = RED;
                    left_rotate(root, other);
                    other = parent->left;
                }
                // 情况6：兄弟是黑色的，兄弟的左孩子是红色的，右孩子任意颜色。
                other->color = parent->color;
                parent->color = BLACK;
                (other->left)->color = BLACK;
                right_rotate(root, parent);
                node = root;
                break;
            }
        }
    }
    if (node != NULL)
        node->color = BLACK;
}


#endif