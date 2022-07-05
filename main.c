#include <stdio.h>
#include "sum.h"
#include <stdlib.h>
#include <math.h>
#include "cJSON.h"

#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <netdb.h>
#include <errno.h>
#include <stdarg.h>

double sum(int limit, ...);

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

/* Used by some code below as an example datatype. */
struct record
{
    const char *precision;
    double lat, lon;
    const char *address, *city, *state, *zip, *country;
};

/* Create a bunch of objects as demonstration. */
void create_objects()
{
    cJSON *root, *fmt, *img, *thm, *fld;
    char *out;
    int i; /* declare a few. */
    /* Our "days of the week" array: */
    const char *strings[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    /* Our matrix: */
    int numbers[3][3] = {{0, -1, 0}, {1, 0, 0}, {0, 0, 1}};
    /* Our "gallery" item: */
    int ids[4] = {116, 943, 234, 38793};
    /* Our array of "records": */
    struct record fields[2] = {
        {"zip", 37.7668, -1.223959e+2, "", "SAN FRANCISCO", "CA", "94107", "US"},
        {"zip", 37.371991, -1.22026e+2, "", "SUNNYVALE", "CA", "94085", "US"}};

    /* Here we construct some JSON standards, from the JSON site. */

    /* Our "Video" datatype: */
    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "name", cJSON_CreateString("Jack (\"Bee\") Nimble"));
    cJSON_AddItemToObject(root, "format", fmt = cJSON_CreateObject());
    cJSON_AddStringToObject(fmt, "type", "rect");
    cJSON_AddNumberToObject(fmt, "width", 1920);
    cJSON_AddNumberToObject(fmt, "height", 1080);
    cJSON_AddFalseToObject(fmt, "interlace");
    cJSON_AddNumberToObject(fmt, "frame rate", 24);

    out = cJSON_Print(root);
    cJSON_Delete(root);
    printf("%s\n", out);
    free(out); /* Print to text, Delete the cJSON, print it, release the string. */

    /* Our "days of the week" array: */
    root = cJSON_CreateStringArray(strings, 7);

    out = cJSON_Print(root);
    cJSON_Delete(root);
    printf("%s\n", out);
    free(out);

    /* Our matrix: */
    root = cJSON_CreateArray();
    for (i = 0; i < 3; i++)
        cJSON_AddItemToArray(root, cJSON_CreateIntArray(numbers[i], 3));

    /*	cJSON_ReplaceItemInArray(root,1,cJSON_CreateString("Replacement")); */

    out = cJSON_Print(root);
    cJSON_Delete(root);
    printf("%s\n", out);
    free(out);

    /* Our "gallery" item: */
    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "Image", img = cJSON_CreateObject());
    cJSON_AddNumberToObject(img, "Width", 800);
    cJSON_AddNumberToObject(img, "Height", 600);
    cJSON_AddStringToObject(img, "Title", "View from 15th Floor");
    cJSON_AddItemToObject(img, "Thumbnail", thm = cJSON_CreateObject());
    cJSON_AddStringToObject(thm, "Url", "http:/*www.example.com/image/481989943");
    cJSON_AddNumberToObject(thm, "Height", 125);
    cJSON_AddStringToObject(thm, "Width", "100");
    cJSON_AddItemToObject(img, "IDs", cJSON_CreateIntArray(ids, 4));

    out = cJSON_Print(root);
    cJSON_Delete(root);
    printf("%s\n", out);
    free(out);

    /* Our array of "records": */

    root = cJSON_CreateArray();
    for (i = 0; i < 2; i++)
    {
        cJSON_AddItemToArray(root, fld = cJSON_CreateObject());
        cJSON_AddStringToObject(fld, "precision", fields[i].precision);
        cJSON_AddNumberToObject(fld, "Latitude", fields[i].lat);
        cJSON_AddNumberToObject(fld, "Longitude", fields[i].lon);
        cJSON_AddStringToObject(fld, "Address", fields[i].address);
        cJSON_AddStringToObject(fld, "City", fields[i].city);
        cJSON_AddStringToObject(fld, "State", fields[i].state);
        cJSON_AddStringToObject(fld, "Zip", fields[i].zip);
        cJSON_AddStringToObject(fld, "Country", fields[i].country);
    }

    /*	cJSON_ReplaceItemInObject(cJSON_GetArrayItem(root,1),"City",cJSON_CreateIntArray(ids,4)); */

    out = cJSON_Print(root);
    cJSON_Delete(root);
    printf("%s\n", out);
    free(out);
}

/**
 * @brief  文件读取及文件写入
 *
 */
static void test_read_file()
{

    FILE *file;
    FILE *fileOut;
    file = fopen("/home/ubuntu/cprojects/testCmake/config.h.in", "rb");
    fileOut = fopen("/home/ubuntu/cprojects/testCmake/test.in", "w");

    char a = NULL;

    while ((a = getc(file)) != EOF)
    {
        putc(a, fileOut);
        /* code */
    }
}

static void testNet()
{
    struct sockaddr_in server;
    struct timeval timeout = {100, 0};
    struct hostent *hp;
    char ip[20] = {0};
    char *hostname = "blog.csdn.net";
    int sockfd;
    char message[1024];
    int size_recv, total_size = 0;
    int len;
    char slen[32];
    char chunk[512];
    FILE *filewrite = fopen("/home/ubuntu/cprojects/testCmake/test.in", "wb");

    memset(message, 0x00, sizeof(message));

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("could not create socket\n");
        return -1;
    }

    if ((hp = gethostbyname(hostname)) == NULL)
    {
        close(sockfd);
        return -1;
    }

    strcpy(ip, inet_ntoa(*(struct in_addr *)hp->h_addr_list[0]));

    printf("ip=%s\n", ip);

    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(80);

    /*连接服务端*/
    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("connect error： %s", errno);
        return 1;
    }

    /*http协议Get请求*/
    strcpy(message, "GET /weixin_30284355/article/details/97559730 HTTP/1.1\r\n");
    strcat(message, "Host: blog.csdn.net\r\n");
    strcat(message, "Content-Type: text/html\r\n");
    strcat(message, "Content-Length: ");
    len = strlen("/weixin_30284355/article/details/97559730");
    sprintf(slen, "%d", 0);
    strcat(message, slen);

    strcat(message, "Accept-Encoding: gzip, deflate, br\r\n");
    strcat(message, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9\r\n");
    strcat(message, "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/102.0.5005.63 Safari/537.36 Edg/102.0.1245.39\r\n");

    strcat(message, "\r\n");
    strcat(message, "\r\n");

    printf("%s\n", message);

    /*向服务器发送数据*/
    if (send(sockfd, message, strlen(message), 0) < 0)
    {
        printf("Send failed\n");
        printf("%s\n", message);
        close(sockfd);
        return -1;
    }

    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(struct timeval));

    while (1)
    {
        memset(chunk, 0x00, 512);

        /*获取数据*/
        if ((size_recv = recv(sockfd, chunk, 512, 0)) == -1)
        {
            if (errno == EWOULDBLOCK || errno == EAGAIN)
            {
                printf("recv timeout ...\n");
                break;
            }
            else if (errno == EINTR)
            {
                printf("interrupt by signal...\n");
                continue;
            }
            else if (errno == ENOENT)
            {
                printf("recv RST segement...\n");
                break;
            }
            else
            {
                printf("unknown error: %d\n", errno);
                close(sockfd);
                exit(1);
            }
        }
        else if (size_recv == 0)
        {
            printf("peer closed ...\n");
            break;
        }
        else
        {
            total_size += size_recv;
            fputs(chunk, filewrite);
            printf("%s", chunk);
        }
    }

    close(sockfd);

    return 0;
}

static void testF()
{
    /* http://27.124.33.27/ */
    struct sockaddr_in server;
    struct timeval timout = {10, 0};

    struct hostent *hp;

    char ip[100] = {0};

    char *hostname = "6mtqbxdvkore2wbq1bmwbb7oigup8.m.kf36s.vin";

    int sockfd;

    char message[10000];

    int size_rev, total_size = 0;
    int len;
    char slen[32];
    char chunk[512];

    memset(message, 0X00, sizeof(message));

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1)
    {
        fprintf(stderr, "could't not create socket\n");
        exit(-1);
    }
    if ((hp = gethostbyname(hostname)) == NULL)
    {
        fprintf(stderr, "gethostbyname:%s", hostname);
        close(sockfd);
        exit(-1);
    }

    strcpy(ip, inet_ntoa(*(struct in_addr *)hp->h_addr_list[0]));
    fprintf(stdout, "ip=%s\n", ip);
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(80);
    int i = 10000;
    while (i)
    {

        if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0)
        {
            fprintf(stderr, "connect fail");
            exit(-1);
        }
        fprintf(stdout, "connected");
        i--;
        /* code */
    }
}

static void test_zf()
{

    FILE *filewrite = fopen("/home/ubuntu/cprojects/testCmake/test.in", "wb");

    struct sockaddr_in server;
    struct timeval timout = {10, 0};

    struct hostent *hp;

    char ip[100] = {0};

    char *hostname = "szzf.hzzfxx.com";

    int sockfd;

    char message[10000];

    int size_rev, total_size = 0;
    int len;
    char slen[32];
    char chunk[512];

    memset(message, 0X00, sizeof(message));

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1)
    {
        fprintf(stderr, "could't not create socket\n");
        exit(-1);
    }
    if ((hp = gethostbyname(hostname)) == NULL)
    {
        fprintf(stderr, "gethostbyname:%s", hostname);
        close(sockfd);
        exit(-1);
    }

    strcpy(ip, inet_ntoa(*(struct in_addr *)hp->h_addr_list[0]));

    fprintf(stdout, "ip=%s\n", ip);

    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(65530);
    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        fprintf(stderr, "connect fail");
        exit(-1);
    }
    /*http协议Get请求*/
    // strcat(message, "Content-Length: ");
    // len = strlen("/?ddd=eee");
    // sprintf(slen, "%d", 0);
    // strcat(message, slen);
    // strcat(message, "\r\n");
    // strcat(message, "\r\n");

    strcpy(message, "POST /jsmart/sysuser/checkPassword HTTP/1.1\r\n");
    // strcpy(message, "\r\n");
    strcat(message, "Host: szzf.hzzfxx.com:65530\r\n");
    strcat(message, "Connection: keep-alive\r\n");
    strcat(message, "Accept: application/json, text/plain, */*\r\n");
    strcat(message, "XAuthToken: 377071f5-eeec-4e24-8d0f-b052f01f0522\r\n");
    strcat(message, "Content-Length: 233\r\n");
    strcat(message, "Content-Type: application/json;charset=UTF-8\r\n");
    strcat(message, "\r\n");
    // strcat(message, "\r\n");
    strcat(message, "{\"password\":\"04b27db8f62ccf4ad2d761785eaa561688e44d12eb943be987707bc1703129ebe9fa30851f150c1cea19da01abfab17e7ca9b885ee0d4251e10725b1724da2fb795e160f37b70b3ef82a322f2a4f255ec00111f497bb91d32c3bd992445aea7edcfe8bc17553285a4f14eb4e08\"}");
    fprintf(stdout, "\n");
    fprintf(stdout, message);

    if (send(sockfd, message, strlen(message), 0) < 0)
    {
        fprintf(stderr, "send faild\n");
        close(sockfd);
        exit(-1);
    }
    // 设置sock 的选项
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timout, sizeof(struct timeval));

    fprintf(stdout, "\n print response\n");

    while (1)
    {

        memset(chunk, 0X00, 512);

        if ((size_rev = recv(sockfd, chunk, 512, 0)) == -1)
        {

            if (errno == EWOULDBLOCK || errno == EAGAIN)
            {
                fprintf(stderr, "send faild\n");
                break;
            }

            else if (errno == EINTR)
            {
                printf("interrupt by signal...\n");
                continue;
            }
            else if (errno == ENOENT)
            {
                printf("recv RST segement...\n");
                break;
            }
            else
            {
                printf("unknown error: %d\n", errno);
                close(sockfd);
                exit(1);
            }
        }
        else if (size_rev == 0)
        {
            printf("peer closed ...\n");
            break;
        }
        else
        {
            total_size += size_rev;
            fputs(chunk, filewrite);
            printf("%s", chunk);
        }

        /* code */
    }

    close(sockfd);

    return 0;
}

typedef struct user
{
    char name[10];
    double sorce;
    /* data */
} User;

int main(int argc, const char *argv[])
{

    // testNet();
    /* a bunch of json: */
    // char text1[] = "{\n\"name\": \"Jack (\\\"Bee\\\") Nimble\", \n\"format\": {\"type\":       \"rect\", \n\"width\":      1920, \n\"height\":     1080, \n\"interlace\":  false,\"frame rate\": 24\n}\n}";
    // char text2[] = "[\"Sunday\", \"Monday\", \"Tuesday\", \"Wednesday\", \"Thursday\", \"Friday\", \"Saturday\"]";
    // char text3[] = "[\n    [0, -1, 0],\n    [1, 0, 0],\n    [0, 0, 1]\n	]\n";
    // char text4[] = "{\n		\"Image\": {\n			\"Width\":  800,\n			\"Height\": 600,\n			\"Title\":  \"View from 15th Floor\",\n			\"Thumbnail\": {\n				\"Url\":    \"http:/*www.example.com/image/481989943\",\n				\"Height\": 125,\n				\"Width\":  \"100\"\n			},\n			\"IDs\": [116, 943, 234, 38793]\n		}\n	}";
    // char text5[] = "[\n	 {\n	 \"precision\": \"zip\",\n	 \"Latitude\":  37.7668,\n	 \"Longitude\": -122.3959,\n	 \"Address\":   \"\",\n	 \"City\":      \"SAN FRANCISCO\",\n	 \"State\":     \"CA\",\n	 \"Zip\":       \"94107\",\n	 \"Country\":   \"US\"\n	 },\n	 {\n	 \"precision\": \"zip\",\n	 \"Latitude\":  37.371991,\n	 \"Longitude\": -122.026020,\n	 \"Address\":   \"\",\n	 \"City\":      \"SUNNYVALE\",\n	 \"State\":     \"CA\",\n	 \"Zip\":       \"94085\",\n	 \"Country\":   \"US\"\n	 }\n	 ]";

    // /* Process each json textblock by parsing, then rebuilding: */
    // doit(text1);
    // doit(text2);
    // doit(text3);
    // doit(text4);
    // doit(text5);

    /* Parse standard testfiles: */
    // dofile("./cjson/tests/test1");
    /*	dofile("../../tests/test2"); */
    /*	dofile("../../tests/test3"); */
    /*	dofile("../../tests/test4"); */
    /*	dofile("../../tests/test5"); */

    /* Now some samplecode for building objects concisely: */
    // create_objects();
    // testF();

    double sumnum = sum(3.3, 23.4, 231.34);

    fprintf(stdout, "sum is %.2lf", sumnum);

    fprintf(stdout,"test finished");
    // FILE *files = fopen("/home/ubuntu/cprojects/testCmake/test.red", "wb");
    // if (files == NULL)
    // {
    //     fprintf(stderr, "打开文件错误");
    //     exit(-1);
    // }
    // User num[2] = {{"testname", 10.0 / 3}, {"dddddd", 20.0 / 3}};
    // fwrite(num, sizeof(num), 1, files);

    // fclose(files);

    // FILE *read_num = fopen("/home/ubuntu/cprojects/testCmake/test.red", "rb");
    // User num33[2];

    // // memset(num33,0X00,sizeof(num33));

    // fread(num33, sizeof(User), 2, read_num);
    // fprintf(stdout, "%.4lf\n", num33[0].sorce * 3);
    // return 0;
}

/**
 * @brief 定义一个多参数的相加
 *
 * @param limit
 * @param ...
 * @return double
 */
double sum(int limit,...){
    // 定义接受的集合
    va_list ap;
    double sum = 0.0;
    int i;
    va_start(ap, limit);
    for (size_t i = 0; i < limit; i++)
    {
        /* code */
        sum += va_arg(ap, double);
    }
    va_end(ap);
    return sum;
}
