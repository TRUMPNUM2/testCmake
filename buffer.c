
#include "getIpByDomain.h"
#define N 5

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

void unix_error(char *msg);
/* 加载并执行程序 */
// int execve(const char *__path, char *const __argv[],
//            char *const __envp[]);

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
    int status, i;
    pid_t pid;

    /* Parent creates N children */
    for (i = 0; i < N; i++)                  // line:ecf:waitpid1:for
        if ((pid = fork()) == 0) /* child */ // line:ecf:waitpid1:fork
            exit(100 + i);                   // line:ecf:waitpid1:exit

    /* Parent reaps N children in no particular order */
    while ((pid = waitpid(-1, &status, 0)) > 0)
    {                          // line:ecf:waitpid1:waitpid
        if (WIFEXITED(status)) // line:ecf:waitpid1:wifexited
            printf("child %d terminated normally with exit status=%d\n",
                   pid, WEXITSTATUS(status)); // line:ecf:waitpid1:wexitstatus
        else
            printf("child %d terminated abnormally\n", pid);
    }

    /* The only normal termination is if there are no more children */
    if (errno != ECHILD)
    {
        printf("waitpid error\n");
        exit(0);
    } // line:ecf:waitpid1:errno
    exit(0);
}

void loadFileToExcute()
{
    const char *test = "/home/ubuntu/cprojects/testCmake/test/test";
    int x = execve(test, NULL, NULL);
    printf("执行返回的数据%d\n", x);
}

int get_ip_by_domain(const char *domain, char *ip); // 根据域名获取ip
int get_local_mac(const char *eth_inf, char *mac);  // 获取本机mac
int get_local_ip(const char *eth_inf, char *ip);    // 获取本机ip

void testMain()
{
    char ip[IP_SIZE];
    char mac[MAC_SIZE];
    const char *test_domain = "fanyi.baidu.com";
    const char *test_eth = "eth0";

    get_ip_by_domain(test_domain, ip);
    printf("%s ip: %s\n", test_domain, ip);

    get_local_mac(test_eth, mac);
    printf("local %s mac: %s\n", test_eth, mac);

    get_local_ip(test_eth, ip);
    printf("local %s ip: %s\n", test_eth, ip);
}

int test_file(){

    char *filename = "/home/ubuntu/cprojects/testCmake/异常控制流/微信图片_20210602213100.png";

    FILE *p = fopen(filename, "r");
    if (p == NULL)
    {
        exit(0);
    }
    char *tes = NULL;

    tes = malloc(sizeof(char) * 256);

    char *filename2 = "/home/ubuntu/cprojects/testCmake/异常控制流/testa2.png";

    char *filename3 = "/home/ubuntu/cprojects/testCmake/异常控制流/进程控制.md";
    // int filefd = Open(filename3, O_RDONLY, 0);
    // printf("ddddddddddddddd:%d", filefd);
    struct stat *st_test;

    // stat(filename3, st_test);

    // if((*st_test).st_mode&S_IRUSR){
    //     printf("readOnly");
    // }

    FILE *p2 = fopen(filename2, "w");

    size_t length;
    while (1)
    {
        memset(tes, 0, sizeof(tes));
        length = fread(tes, 1, sizeof(tes), p);
        if (length == 0)
        {
            break;
        }
        printf("读取的数据%s,长度大小%d\n", tes, length);
        /* code */
        fwrite(tes, 1, length, p2);
    }
    free(tes);
    fclose(p);
    fclose(p2);
    printf("输出完成\n");
    return 0;
}


typedef enum { FALSE = 0, TRUE = !FALSE } BOOL;
//__int64可以改成long long，VC++6.0不支持long long，C99中才添加long long 
__int64_t my_atoll(char* str)
{
	__int64_t s = 0;
	BOOL isMinus = FALSE;//负

	while (*str == ' ')//跳过空格
	{
		str++;
	}
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			isMinus = TRUE;
		str++;
	}
	else if (*str < '0' || *str > '9')//如果第1位既不是符号也不是数字，直接返回异常值
		return 0;
	while (*str != '\0' && *str >= '0' && *str <= '9')
	{
		s = s * 10 + *str - '0';
		str++;
	}
	return s * (isMinus ? -1 : 1);
}

void ltoh(long long x, char* p) 
{
	int div;
	int cnt = 0;
	if (x == 0) {
		*p = '0';
	}
	if (x < 0) {
		x = -x;
		*p = '-';
		p++;
	}
	for (int i = 0; x != 0; i++) {
		div = x % 16;
		x = x / 16;
		if ((div - 10) < 0)
			*(p + i) = div + '0';
		else *(p + i) = 'A' + div - 10;
		div = 0;
		cnt++;
	}
	//reverse颠倒
	for (int i = 0; i < cnt / 2; i++) {
		char temp = p[i];
		p[i] = p[cnt - 1 - i];
		p[cnt - 1 - i] = temp;
	}
}


void test_int_to_hex(){

   /*  int n = 16;

    int d = ((1 << (n - 1)) + (1 << (n - 1)) - 1);

    printf("%d", d);
    unsigned char *pBuf = NULL;

    pBuf = (unsigned char *)malloc(72 * 128 * sizeof(char));

    pBuf[0] = (unsigned char)(d & 0Xf);

    pBuf[1] = (unsigned char)((d >> 8) & 0xff);

    printf("bruce int2byte  ==>> pBuf[0]=%s,pBuf[1]=%d\n", pBuf[0], pBuf[1]); */

   char str[] = "86281102005404";
   char strhex[100] = {0};
   long long data = 0;
   data = my_atoll(str);
   printf("str=%lld\r\n", data);
   ltoh(data, strhex);
   printf("strhex=%s\r\n", strhex);
   return 0;
}

/* Parse text to JSON, then render back to text, and print! */
void doit(char *text)
{
    char *out;
    cJSON *json;

    json = cJSON_Parse(text);
    if (!json)
    {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr());
    }
    else
    {
        out = cJSON_Print(json);
        cJSON_Delete(json);
        printf("%s\n", out);
        free(out);
    }
}

/* Read a file, parse, render back, etc. */
void dofile(char *filename)
{
    FILE *f;
    long len;
    char *data;

    f = fopen(filename, "rb");
    fseek(f, 0, SEEK_END);
    len = ftell(f);
    fseek(f, 0, SEEK_SET);
    data = (char *)malloc(len + 1);
    fread(data, 1, len, f);
    fclose(f);
    doit(data);
    free(data);
}