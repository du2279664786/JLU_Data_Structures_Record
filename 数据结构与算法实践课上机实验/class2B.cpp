#include<iostream>
#include<stdlib.h>
#include<math.h>
using namespace std;
int threshold;

/* 请在这里补充你的代码，即你所实现的sort函数 */

int maxDepth = 0;
int maxN = 10;

void printR(int *R, int n)
{
    for(int i = 1; i <= n; i++)
    {
        printf("%d ", R[i]);
    }
}

void shiftDown(int *R, int n, int i)
{
    int maxchd;
    while(i <= n / 2)
    {
        if((2 * i + 1 <= n) && (R[2 * i + 1] > R[2 * i]))
        {
            maxchd = 2 * i + 1;
        }
        else
            maxchd = 2 * i;
        if(R[maxchd] <= R[i])
            return;
        int temp = R[i];
        R[i] = R[maxchd];
        R[maxchd] = temp;
        i = maxchd;
    }
}

void bulidHeap(int *R, int n)
{
    for(int i = n / 2; i >= 1; i--)
    {
        shiftDown(R, n, i);
    }
}

void heapSort(int * R, int n)
{
    bulidHeap(R, n);
    for(int i = n; i > 1; i--)
    {
        int temp = R[1];
        R[1] = R[i];
        R[i] = temp;
        shiftDown(R, i - 1, 1);
    }
}

int quickSortPartition(int *R, int m, int n)
{
    int k = R[m], left = m, right = n + 1;
    while(left < right)
    {
        left++;
        while(left <= n && R[left] <= k)
        {
            left++;
        }
        right--;
        while(R[right] > k)
        {
            right--;
        }
        if(left < right)
        {
            int temp = R[right];
            R[right] = R[left];
            R[left] = temp;
        }
        //printR(R, 10);
    }
    int temp = R[right];
    R[right] = R[m];
    R[m] = temp;
    return right;
}

void quickSort(int *R, int m, int n, int deep)
{
    //printf("\n");
    //printR(R, maxN);
    //printf("\n");

    if(n - m + 1 <= threshold)// 达到阈值后退出待插入排序处理
    {
        return;
    }
    else if(deep > maxDepth && m < n)
    {
        int *heap = R + m - 1;
        heapSort(heap, n - m + 1);
    }
    else if(m < n)
    {
        int j = quickSortPartition(R, m, n);
        
        quickSort(R, m, j-1, deep + 1);
        quickSort(R, j+1, n, deep + 1);
    }
}



void insertionSort(int *R, int n)
{
    for(int i = 2; i <= n; i++)
    {
        int k = R[i], j = i - 1;
        while(j >= 1 && R[j] > k)
        {
            R[j + 1] = R[j];
            j--;
        }
        R[j + 1] = k;
    }
}



void sort(int * R, int n)
{
    maxDepth = int(2 * log2(n));
    quickSort(R, 1, n, 1);

    insertionSort(R, n);
}

int main()
{
    int n,i;
    int a[50010];
    scanf("%d %d", &n, &threshold);
    for (i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    
    sort(a,n);
    
    for (i = 1; i <= n; i++)
        printf("%d ",a[i]);
    printf("\n");
    return 0;
}


/*
B 排序
分数 10
作者 朱允刚
单位 吉林大学
请编写程序对不超过50000个整数递增排序。
备注：本题不允许使用STL sort()或qsort()等现成的排序库函数。

输入格式:
输入第一行一个正整数n，表示待排序的元素个数。第二行为n个整数，表示待排序的元素。n不超过50000。

输出格式:
输出为一行，表示排序结果，每个整数后一个空格。

输入样例:
5
5 4 3 2 1

输出样例:
1 2 3 4 5 

代码长度限制
16 KB
时间限制
5000 ms
内存限制
64 MB
栈限制
8192 KB
*/