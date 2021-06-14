#include <stdio.h>
#include "utarray.h"
#include "uthash.h"
#include "utlist.h"
#include "utringbuffer.h"
#include "utstack.h"
#include "utstring.h"
#include <sys/types.h>
#include <wait.h>
#include <errno.h>

#include <unistd.h>

/* 获取当前执行线程 */
pid_t getpid(void);

pid_t getppid(void);
/* 线程终止方法，传入线程的pid */
void exit(int status);
/* 创建子进程 */
pid_t fork(void);
/* 等待子进程终止获取者停止*/
pid_t waitpid(pid_t t, int *statuasp, int options);

pid_t wait(int *statusp);

// int sum (int* x,int * y);

// int main(int argc,char** args){
//     int x = 4;
//     int y = 6;
//     int mm = sum(&x,&y);
//     printf("两个数的sum%d\n",mm);
//     printf("hello world");
//     getchar();
//     return 0;
// }
int sum(int *x, int *y);
struct hashTable
{
    int key;
    int val;
    UT_hash_handle hh;
};

struct hashTable *hashtable;

struct hashTable *find(int ikey)
{
    struct hashTable *tmp;
    HASH_FIND_INT(hashtable, &ikey, tmp);
    return tmp;
}

struct hashTable *insert(int ikey, int ival)
{
    struct hashTable *it = find(ikey);
    if (it == NULL)
    {
        struct hashTable *tmp = malloc(sizeof(struct hashTable));
        tmp->key = ikey, tmp->val = ival;
        HASH_ADD_INT(hashtable, key, tmp);
        return tmp;
    }
    else
    {
        it->val = ival;
    }
    return it;
}

int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
    hashtable = NULL;
    for (int i = 0; i < numsSize; i++)
    {
        struct hashTable *it = find(target - nums[i]);
        if (it != NULL)
        {
            int *ret = malloc(sizeof(int) * 2);
            ret[0] = it->val, ret[1] = i;
            *returnSize = 2;
            return ret;
        }
        insert(nums[i], i);
    }
    *returnSize = 0;
    return NULL;
}

void testSum()
{

    int num[] = {3, 4, 234, 5436, 36, 32, 23, 2, 26526, 23};
    int numSize = sizeof(num) / sizeof(int);

    struct hashTable *mbuffer;

    for (size_t i = 0; i < numSize; i++)
    {
        /* code */
        struct hashTable *m = insert(i, num[i]);
        if (m != NULL)
        {
            printf("%d,%d\n", m->key, m->val);
        }
        mbuffer = m;
    }

    if (mbuffer != NULL)
    {

        UT_hash_handle utHash = mbuffer->hh;
        while (utHash.hh_prev != NULL) // 不是指针可以直接使用. 的形式，如果是指针就需要使用->的格式   djskldfj
        {
            // 输出值指针前移
            // printf("%d\n", (int)(*utHash.key));
            struct UT_hash_handle test = (*utHash.hh_prev);
            printf("hello");
            /* code */
        }
    }

    int target = 55;
    int returnSize = 0;
    int xx = sum(&target, &returnSize);
    printf("sum is %d\n", xx);

    int *x = twoSum(num, numSize, target, &returnSize);
    for (size_t i = 0; i < returnSize; i++)
    {
        /* code */
        printf("第%d个数据%d\n", i, *(x + i));
    }
    printf("%d", *x);
}

void forkTest()
{

    pid_t test = getpid();
    printf("获取pid=%d\n", test);
    /*     exit(test);
    getchar(); */
    pid_t pid;
    int x = 1;

    pid = fork();

    if (pid == 0)
    {
        printf("child:x=%d\n", ++x);
        pid_t child_pid = getpid();
        printf("child process is :%d\n", child_pid);
        exit(0);
    }

    pid_t childoverPid = wait(NULL);
    printf("child is over is :%d\n", childoverPid);
    printf("parent:x= %d\n", --x);
    exit(0);
}

void testFork()
{
}

int main(int argc, char **args)
{
}
