#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>


void list_l(struct stat filee, int a, const char *c, const char *path);
int compare2( const void *a, const void *b);
int compare1(const void *a, const void *b);
// char **sort_t(char **p, int a, const char *file)
// {
//     //printf("%s   \n",p[4]);
//     //printf("%s:\n",file);
//     // for(int j = 0; j < a; j++)
//     // {
//     //     if(strcmp(p[j],"..") == 0)
//     //     p[j] = "";
//     // }
//     char **q = (char **)malloc(a * sizeof(char*));
//     //printf("%s   \n",p[5]);
//     for(int i = 0; i < a; i++)
//     {
//         q[i] = (char *)malloc(1024);
//         sprintf(q[i],"%s/%s",file,p[i]);
//         //printf("%s   \n",p[i]);
//     }
//     qsort(q, a, sizeof(char*), compare2);
//     int b = strlen(file);
//     //printf("%d\n",b);
//     for(int i = 0; i < a; i++)
//     {
//         memmove(q[i], q[i]+b+1, strlen(q[i])-b+1);
//         //printf("%s\n",q[i]);
//     }
//     return q;
// }
int color(const char *file)
{
    struct stat ff;
    //printf("%s\n",file);
    if(stat(file, &ff))
    {
        perror("stat");
        printf("333\n");
        exit(-1);
    }
    if(S_ISDIR(ff.st_mode))
    return 34;
    else if(S_ISREG(ff.st_mode)&&(ff.st_mode & S_IXUSR))
    return 32;
    return 37;
}

void permission(mode_t mond)
{
    char p[10] = "----------";
    if(S_ISDIR(mond))
    p[0] = 'd';
    if(mond & S_IRUSR)
    p[1] = 'r';
    if(mond & S_IWUSR)
    p[2] = 'w';
    if(mond & S_IXUSR)
    p[3] = 'x';
    if(mond & S_IRGRP)
    p[4] = 'r';
    if(mond & S_IWGRP)
    p[5] = 'w';
    if(mond & S_IXGRP)
    p[6] = 'x';
    if(mond & S_IROTH)
    p[7] = 'r';
    if(mond & S_IWOTH)
    p[8] = 'w';
    if(mond & S_IXOTH)
    p[9] = 'x';
    printf("%s ",p);
}


char** sort(const char *file,int *z)
{
    //printf("%s:\n",file);
    int i = 0;
    int a = 1000;
    DIR *dir = opendir(file);
    if(dir == NULL)
    {
        perror("opendir");
        exit(1);
    }
    struct dirent *f;
    char **p = (char**)malloc(a * sizeof(char*));
    char **q = (char**)malloc(a * sizeof(char*));
    while((f = readdir(dir)) != NULL)
    {
        p[i] = (char*)malloc(1024 * sizeof(char));
        q[i] = (char*)malloc(1024 * sizeof(char));
        p[i] = f->d_name;
        //printf("%s\n",p[i]);
        snprintf(q[i], 1024, "%s/%s", file, p[i]);
        //printf("%s\n",q[i]);
        // int b = strlen(p[i]);
        // p[i][b] = '\0';
        i++;
        if(i+1 >= a)
        {
            a = a*2;
            p = (char**)realloc(p, a*sizeof(char*));
            q = (char**)realloc(q, a*sizeof(char*));
        }  
        //printf("%s\n",p[i-1]); 
    }
    closedir(dir);
    //printf("%s\n",p[4]);
    //printf("   %d\n",i);
    *z = i;
    //free(p);
    //p = NULL;
    return q;
}

int compare1(const void *a, const void *b)
{
    return strcmp(*(const char **)b, *(const char **)a);
}

void list(const char *file, int a, int l, int i, int s, int r, int t, int R)
{
    char **fi = (char**)malloc(400 * sizeof(char*));
    int h = 400;
    //char fi[400][1024];
    if(R == 1)
    printf("%s:\n",file);
    int num_s = 0;
    int fil = 0;
    DIR *dir = opendir(file);
    if(dir == NULL)
    {
        //printf("111");
        perror("opendir");
        return;
    }
    struct dirent *f;
    int z = 0, k = 0;
    char **p = sort(file, &z);
    if(r == 1)
    qsort(p, z, sizeof(char*), compare1);
    if(t == 1)
    {
        // p = sort_t(p, z, file);
        qsort(p, z, sizeof(char*), compare2);
    }
    //printf("111\n");
    int idd = 0;
    while((f = readdir(dir)) != NULL)
    {
    // if(a == 1 || ((strncmp(p[k], ".", 1) != 0 && strncmp(p[k],"..",2) != 0)))
    // {
    idd++;
        struct stat filee;
        char path[1024];
        int b = strlen(file);
        //printf("%d\n",b);
        memmove(p[k], p[k]+b+1, strlen(p[k])-b+1);
        //printf("%s\n",p[i]);
        snprintf(path, sizeof(path), "%s/%s", file, p[k]);
        //printf("%s\n",path);
        if((lstat(path, &filee) == -1))
        {
            printf("%s   ",p[k]);
            k++;
            //perror("lstat");
            continue;
        }
        
        if((access(path, F_OK) == -1))
        {
            printf("\033[31m\033[1m%s\033[0m   ",p[k]);
            k++;
            continue;
        }
        // if(lstat(path, &filee) == -1)
        // {
        //     printf("111%s\n",path);
        //     perror("stat");
        //     return;
        // }
        if(((S_ISDIR(filee.st_mode)) && (!S_ISLNK(filee.st_mode)) && R == 1) && (strncmp(f->d_name,".",1) != 0))
        {
            fi[fil] = (char *)malloc(1024);
            snprintf(fi[fil], 1024, "%s", path);
            //snprintf(q[i], 1024, "%s/%s", file, p[i]);
            //printf("%s %s\n",fi[fil],fi[0]);
            fil++;
            if(fil > h)
            {
                h = h*2;
                fi = (char**)realloc(fi, h*sizeof(char*));
            }
            //printf("%d",fil);
        }
        if(s == 1)
        {
            printf("%2ld ",filee.st_blocks/2);
            num_s += filee.st_blocks/2;
        }
        if(i == 1)
        {
            printf("%ld ",filee.st_ino);
        }
        if(l == 1)
        {
            list_l(filee, a, p[k], path);
            k++;
        }

    // printf("%s\n",path);
    // printf("12\n");
    if(l != 1)
    {
        //printf("\033[37m\033[1m%s\033[0m\n",p[k]);
        if(a == 1 && (strncmp(p[k], ".", 1) == 0 || strncmp(p[k],"..",2) == 0))
        {
            printf("\033[%dm\033[1m%s\033[0m  ",color(path),p[k]);
            k++;
        }
        else if(strcmp(p[k],"..") != 0 && strncmp(p[k], ".",1) != 0)
        {
            if(color(path) == 37)
            {
                printf("\033[%dm%s  ",color(path),p[k]);
                k++;
            }
            else
            {
                printf("\033[%dm\033[1m%s\033[0m  ",color(path),p[k]);
                k++;
                //printf("%s\n",path);
            }
        }
        else
        k++;
        //printf("%s\n",path);
    }
    }
    //printf("%d\n",idd);
    if((fil > 0) && (R == 1))
    {
        
        for(int j = 0; j < fil; j++)
        {
            printf("\n\n");
            //printf("%s:\n",fi[j]);
            list(fi[j],a,l,i,s,r,t,R);
        }
    }
    //free(p);
    if(s == 1)
    printf("总计 %d\n",num_s);
    closedir(dir);
}

int compare2( const void *a, const void *b)
{
    const char *a1 = *(const char **)a;
    const char *b1 = *(const char **)b;
    struct stat p;
    struct stat q;
    if(stat(b1, &q) == -1)
    {
        printf("%s\n",b1);
        perror("stat");
        printf("222\n");
        exit(1);
    }
    if(stat(a1, &p) == -1)
    {
        printf("%s\n",a1);
        perror("stat");
        printf("2222\n");
        exit(1);
    }
    return (q.st_mtime - p.st_mtime); 
}
void list_l(struct stat filee, int a,const char *c, const char *path)
{
    permission(filee.st_mode);
    printf("%ld ",filee.st_nlink);
    struct passwd *name = getpwuid(filee.st_uid);
    if(name == NULL)
    {
        printf("%d ",filee.st_uid);
    }
    else
    {
        printf("%s ",name->pw_name);
    }
    struct group *group = getgrgid(filee.st_gid);
    if(group == NULL)
    {
        printf("%d ",filee.st_gid);
    }
    else
    {
        printf("%s ",group->gr_name);
    }
    printf("%5ld ",filee.st_size);
    char time[200];
    struct tm *t = localtime(&filee.st_mtime);
    strftime(time, sizeof(time), "%m月 %e %H:%M", t);
    printf("%s ",time);
    if(a == 1 && (strncmp(c, ".", 1) == 0 || strncmp(c,"..",2) == 0))
        printf("\033[%dm\033[1m%s\033[0m\n",color(path),c);
    else if(strcmp(c,"..") != 0 && strncmp(c, ".",1) != 0)
    {
        if(color(path) == 37)
        printf("\033[%dm%s\n",color(path),c);
        else
        printf("\033[%dm\033[1m%s\033[0m\n",color(path),c);
    }
}


int main(int argc, char *argv[])
{
    int a = 0,l = 0,R = 0,ii = 0,r = 0,s = 0,t = 0;
    const char *fd = ".";
    char arr[10];
    if(argc < 2)
    list(".",a,l,ii,s,r,t,R);
    else
    {
        for(int i = 1; i < argc; i++)
        {
            if(strncmp(argv[i],"-",1) == 0)
            {
                for(int j = 1; j < strlen(argv[i]); j++)
                {
                    if(argv[i][j] == 'a')
                    a = 1;
                    else if(argv[i][j] == 'l')
                    l = 1;
                    else if(argv[i][j] == 'i')
                    ii = 1;
                    else if(argv[i][j] == 's')
                    s = 1;
                    else if(argv[i][j] == 'r')
                    r = 1;
                    else if(argv[i][j] == 't')
                    t = 1;
                    else if(argv[i][j] == 'R')
                    R = 1;
                }
                continue;
            }
            else
            {
                //printf("%s\n",argv[i]);
                fd = argv[i];
            }
        }
        
    // if(R == 1)
    // list_R(fd);
    // else if(r == 1 || t == 1)
    // list_r(fd,a,l,ii,r,s,t,R);
    // else
    list(fd,a,l,ii,s,r,t,R);
    }
    
}