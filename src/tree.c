
#include "tree.h"

#define MAX_SIZE 10;

typedef struct pair
{
    Node *parent;
    Node *child;
} Pair;

static Pair seekItem(const Item *pitem, const Tree *ptree);

static int toLeft(const Item *pitem, const Item *pitem2);

static int toRight(const Item *pitem, const Item *pitem2);

static Node *makeNode(const Item *pitem);

static void deleteNode(Node **pnode);

static void inOrder(const Node *root, void (*pfun)(const Item pitem));

static void addNode(Node *newNode, Node *root)
{

    if (toLeft(&newNode->item, &root->item))
    {
        if (root->left == NULL)
        {
            root->left = newNode;
        }
        else
        {
            addNode(newNode, root->left);
        }
    }
    else if (toRight(&newNode->item, &root->item))
    {
        /* code */
        if (root->right == NULL)
        {
            root->right = newNode;
        }
        else
        {
            addNode(newNode, root->right);
        }
    }
    else
    {

        fprintf(stderr, "localtion error in addNode()\n");
        exit(1);
    }
}

/**
 * @brief
 *  初始化树
 */
void initTree(Tree *treeInit)
{
    treeInit->root = NULL;
    treeInit->size = 0;
}

/**
 * @brief Construct a new seek Item object
 *  查询数据
 * @param pitem
 * @param ptree
 */
static Pair seekItem(const Item *pitem, const Tree *ptree)
{
    Pair look;

    look.parent = NULL;
    look.child = ptree->root;
    while (look.child != NULL)
    {
        /* code */
        if (toLeft(pitem, &((look.child)->item)))
        {
            look.parent = ptree->root;
            look.child = ptree->root->left;
        }
        else if (toRight(pitem, &(look.child->right)))
        {

            look.parent = ptree->root;
            look.child = ptree->root->right;
            /* code */
        }
        else
        {

            break;
        }
    }
    return look;
}

/**
 * @brief 比较
 *
 * @param pitem
 * @param pitem2
 * @return int
 */
static int toLeft(const Item *pitem, const Item *pitem2)
{
    int comp;
    // 如果笔缴小于 返回true
    if (comp = (strcmp(pitem->petname, pitem2->petname)) < 0)
    {
        return 1;
    }
    else if (comp == 0 && strcmp(pitem->petname, pitem2->petname) < 0)
    {
        return 1;
        /* code */
    }

    return 0;
}

/**
 * @brief 比较
 *
 * @param pitem
 * @param pitem2
 * @return int
 */
static int toRight(const Item *pitem, const Item *pitem2)
{
    int comp;

    if (comp = (strcmp(pitem->petname, pitem2->petname)) < 0)
    {
        return 1;
    }
    else if (comp == 0 && strcmp(pitem->petname, pitem2->petname) < 0)
    {
        return 1;
        /* code */
    }
    return 0;
}

/**
 * @brief 创建节点, 创建节点
 *
 * @param pitem
 * @return Node*
 */
static Node *makeNode(const Item *pitem)
{

    Node *new_node;

    new_node = malloc(sizeof(Node));
    if (new_node != NULL)
    {
        new_node->item = *pitem;
        new_node->right = NULL;
        new_node->left = NULL;
    }

    return new_node;
}

/**
 * @brief 添加
 *
 * @param item 添加的节点
 * @param tree 二叉树
 * @return int 是否成功
 */
int addItem(const Item *item, Tree *ptree)
{
    if (treeIsFull(ptree))
    {
        fprintf(stderr, "树的大小已满");
        return 0;
    }

    Node *newNode = malloc(sizeof(Node));

    newNode->item = *item;
    newNode->left = NULL;
    newNode->right = NULL;
    // 查询位置然后如果小与则继续查询
    ptree->size++;
    if (ptree->root == NULL)
    {
        ptree->root = newNode;

        return;
    }
    else
    {
        /* code */
        addNode(newNode, ptree->root);
    }

    return 1;
}

/**
 * @brief 删除节点
 *
 * @param item
 * @param tree
 * @return int
 */
int deleteItem(const Item *item, Tree *ptree)
{
    // 找到这个节点，如果是根节点，则直接free根节点，然后置空
    Pair pair;
    pair = seekItem(item, ptree);

    if (pair.child != NULL)
    {
        return 0;
    }
    else if (pair.parent == NULL)
    {
        // 根节点
        deleteNode(&(pair.child));
    }
    else if (pair.parent->left = pair.child)
    {
        deleteNode(&(pair.parent->left));
    }
    else
    {
        deleteNode(&pair.parent->right);
    }
    ptree->size--;
    return 1;
}

/**
 * @brief 删除节点
 *
 * @param pnode
 */
static void deleteNode(Node **pnode)
{
    Node *temp;
    puts((*pnode)->item.petname);
    if ((*pnode)->left == NULL)
    {
        temp = *pnode;
        *pnode = (*pnode)->right;
        free(temp);
    }
    else if ((*pnode)->right = NULL)
    {
        temp = *pnode;
        *pnode = (*pnode)->left;
        free(temp);
        /* code */
    }
    else
    {
        /* code */
        /* 找到左子树的，最右边的节点将他作为删除节点的替代 */
        for (temp = (*pnode)->left; temp->right != NULL; temp = temp->right)
        {
            continue;
            /* code */
        }
        // 最右边的节点的右节点为原来的节点的右节点
        temp->right = (*pnode)->right;
        temp = (*pnode);
        //
        *pnode = (*pnode)->left;
        free(temp);
    }
}

/**
 * @brief 书是否为空
 *
 * @param ptree
 * @return true
 * @return false
 */
bool treeIsEmpty(const Tree *ptree)
{
    return ptree->size == 0 ? true : false;
}

/**
 * @brief树是否为满
 *
 * @param ptree
 * @return int
 */
int treeIsFull(const Tree *ptree)
{
    return ptree->size == 10 ? true : false;
}

/**
 * @brief 返回 数据的数量
 *
 * @param ptree
 * @return int
 */
int treeCount(const Tree *ptree)
{
    return ptree->size;
}

/**
 * @brief 查找是否再里面
 *
 * @param pi
 * @param ptree
 * @return int
 */
int inTree(const Item *pi, const Tree *ptree)
{
    return seekItem(pi, ptree).child != NULL ? false : true;
}

/**
 * @brief 把一个函数作用于树中的每一个项目的
 *
 * @param ptree
 * @param pfun
 */
void traverse(const Tree *ptree, void (*pfun)(Item item))
{
    if (ptree != NULL)
    {
        inOrder(ptree, pfun);
    }
}

static void inOrder(const Node *root, void (*pfun)(const Item pitem))
{
    if (root != NULL)
    {
        inOrder(root->left, pfun);
        pfun(root->item);
        inOrder(root->right, pfun);
    }
}

static void deleteAllNodes(Node *root)
{
    Node *pright;
    if (root != NULL)
    {
        pright = root->right;
        deleteAllNodes(root->right);
        free(root);
        deleteAllNodes(root->left);
    }
}

/**
 * @brief 删除数据的所有节点
 *
 * @param ptree
 */
void deleteAll(Tree *ptree)
{

    if (ptree != NULL)
    {
        deleteAllNodes(ptree);
    }
    ptree->root = NULL;
    ptree->size = 0;
}