#ifndef _TREE_H_
#define _TREE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdio.h>



    /**
     * @brief 存储的数据
     *
     */
    typedef struct item
    {
        char petname[40];
        char petkind[20];
    } Item;

    /**
     * @brief 定义节点
     *
     */
    typedef struct node
    {
        Item item;
        struct node *left;
        struct node *right;
    } Node;

    /**
     * @brief tree
     *
     */
    typedef struct tree
    {
        Node *root;
        size_t size;
    } Tree;

    /**
     * @brief
     *  初始化树
     */
    void initTree(Tree *treeInit);

    /**
     * @brief 添加
     *
     * @param item 添加的节点
     * @param tree 二叉树
     * @return int 是否成功
     */
    int addItem(const Item *item, Tree *ptree);

    /**
     * @brief 删除节点
     *
     * @param item
     * @param tree
     * @return int
     */
    int deleteItem(const Item *item, Tree *ptree);

    /**
     * @brief 书是否为空
     *
     * @param ptree
     * @return true
     * @return false
     */
    bool treeIsEmpty(const Tree *ptree);

    /**
     * @brief树是否为满
     *
     * @param ptree
     * @return int
     */
    int treeIsFull(const Tree *ptree);

    /**
     * @brief 返回 数据的数量
     *
     * @param ptree
     * @return int
     */
    int treeCount(const Tree *ptree);

    /**
     * @brief 查找是否再里面
     *
     * @param pi
     * @param ptree
     * @return int
     */
    int inTree(const Item *pi, const Tree *ptree);

    /**
     * @brief 把一个函数作用于树中的每一个项目的
     *
     * @param ptree
     * @param pfun
     */
    void traverse(const Tree *ptree, void (*pfun)(Item item));

    /**
     * @brief 删除数据的所有节点
     *
     * @param ptree
     */
    void deleteAll(Tree *ptree);

#ifdef __cplusplus
}
#endif

#endif
