#include <stdio.h>
#include <stdlib.h>

typedef struct ListEle_
{

    void *data;

    struct ListEle_ *next;

} ListEle;

typedef struct List_
{
    int size;
    void (*match)(const void *key1, const void *key2);
    void (*destory)(void *data);
    ListEle *head;
    ListEle *tail;

} List;

void init_list(List *lists, void (*destory)(void *data));

int list_ins_next(List *lists, ListEle *next, const void *data);

int main(int argc, char const *argv[])
{

    List list;
    ListEle element;
    int *data, i;
    init_list(&list, free);
    for (size_t i = 0; i < 19; i++)
    {
        /* code */

        if ((data = (int *)malloc(sizeof(int))) == NULL)
            return 1;
        *data = i;
        if ((list_ins_next(&list, NULL, data) != 0))
        {
            return 1;
        }
    }

    fprintf(stdout, "输出集合");
    // 遍历
    ListEle *buffer = (&list)->head;
    int x = 0;
    while (buffer != NULL)
    {
        /* code */
        int *data = buffer->data;
        fprintf(stdout, "--list[%03d]=%03d\n", x, *data);
        x++;
        buffer = buffer->next;
    }

    return 0;
}

void init_list(List *lists, void (*destory)(void *data))
{
    lists->size = 0;
    lists->destory = destory;
    lists->head = NULL;
    lists->tail = NULL;
}

int list_ins_next(List *lists, ListEle *next, const void *data)
{
    // 先分配空间

    ListEle *new_elemnet;

    if ((new_elemnet = (ListEle *)malloc(sizeof(ListEle))) == NULL)
        return -1;
    new_elemnet->data = data;
    if (next == NULL)
    {
        if (lists->size == 0)
        {
            lists->tail = new_elemnet;
        }
        new_elemnet->next = lists->head;
        lists->head = new_elemnet;
    }
    else
    {
        /* code */

        if (next->next == NULL)
        {
            lists->tail = new_elemnet;
        }

        new_elemnet->next = lists->head;
        next->next = new_elemnet;
    }

    lists->size++;
    return 0;
}