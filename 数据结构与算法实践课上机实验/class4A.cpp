#include<iostream>
#include<stdlib.h>
#include<math.h>
using namespace std;
int threshold;

/* 请在这里补充你的代码，即你所实现的sort函数 */

int maxDepth = 0;
int maxN = 10;

void swap(int * R, int i, int j)
{
    int tmp = R[i];
    R[i] = R[j];
    R[j] = tmp;
}

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
    printf("Heap:");
    printR(R, n);
    printf("\n");
    for(int i = n; i > 1; i--)
    {
        int temp = R[1];
        R[1] = R[i];
        R[i] = temp;
        shiftDown(R, i - 1, 1);
    }
}

void quickSortPartition(int *R, int m, int n, int &i, int &k)
{
    int mid = (m + n) / 2;// 三数取中
    swap(R[(m+n)/2], R[m+1]);
    if(R[m + 1] > R[n]) swap(R[m+1], R[n]);
    if(R[m] > R[n]) swap(R[m], R[n]);
    if(R[m+1] > R[m]) swap(R[m + 1], R[m]);

    // 三路分化
    int j, pivot;
    i = m, j = m, k = n, pivot = R[m];
    while(j<=k)
    {
        if(R[j] < pivot)
        {
            swap(R[j], R[i]);
            j++;
            i++;
        }
        else if(R[j] > pivot)
        {
            swap(R[j], R[k]);
            k--;
        }
        else
        {
            j++;
        }
    }
}

void quickSort(int *R, int m, int n, int deep)
{
    //printf("\n");
    //printR(R, maxN);
    //printf("\n");
    /*
    if(n - m + 1<= threshold)// 达到阈值后退出待插入排序处理
    {
        return;
    }
    if(deep == 0 && n - m + 1 > 1)
    {
        int *heap = R;
        if(m - 1 >= 0)
        {
            heap += m - 1;
        }
        heapSort(heap, n - m + 1);
        return;
    }
    */
    
    while(m < n)
    {
        if(n - m + 1<= threshold)// 达到阈值后退出待插入排序处理
        {
            return;
        }
        if(deep == 0 && n - m + 1 > 1)
        {
            int *heap = R;
            if(m - 1 >= 0)
            {
                heap += m - 1;
            }
            heapSort(heap, n - m + 1);
            return;
        }
        int i, k;
        quickSortPartition(R, m, n, i, k);
        
        if(i - m < n - k)// 先处理短区间
        {
            quickSort(R, m, i - 1, deep - 1);
            m = k + 1;
        }
        else
        {
            quickSort(R, k + 1, n, deep - 1);
            n = i - 1;
        }
        deep -= 1;
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
    maxDepth = int(2 * log(n) / log(2));
    printf("depth_limit:%d\n", maxDepth);
    
    quickSort(R, 1, n, maxDepth);
    printf("Intermediate:");
    printR(R, n);
    printf("\n");
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
    
    printf("Final:");
    for (i = 1; i <= n; i++)
        printf("%d ",a[i]);
    printf("\n");
    return 0;
}

/*
A 手撕STL sort（进阶版）
分数 100
作者 朱允刚
单位 吉林大学
事实上，STL的sort函数在上一题（基础版）的基础上，还采用了下列优化手段，以进一步提升快速排序算法的效率。

（3）“三数取中”选基准元素。不是选取第一个元素作为基准元素，而是在当前子数组中选取3个元素，取中间大的那个元素作为基准元素。从而保证选出的基准元素不是子数组的最小元素，也不是最大元素，避免Partition分到子数组最边上，以降低最坏情况发生的概率。
为确保本题答案唯一，本算法的实现请以教材为准，即普林斯顿大学Sedgewick教授给出的方法：若当前子数组是R[m]…R[n]，选取R[m]、R[(m+n)/2]和R[n]的中位数作为基准元素。先将R[(m+n)/2]与R[m+1]交换；若R[m+1]比R[n]大，交换二者；若R[m]比R[n]大，交换二者；若R[m+1]比R[m]大，交换二者。

（4）尾递归转为循环。即将传统快速排序代码

void QuickSort(int R[],int m,int n){
   if(n - m + 1 > threshold){
        int j = Partition(R, m, n); 
        QuickSort(R, m, j-1);  //递归处理左区间
        QuickSort(R, j+1, n);  //递归处理右区间，尾递归
     }
}
转换为

void QuickSort(int R[],int m,int n){
   while(n - m + 1 > threshold){    //注意此处不是if，而是while
        int j = Partition(R, m, n); 
        QuickSort(R, m, j-1);  //递归处理左区间
        m = j+1;  //通过while循环处理右区间，从而消除尾递归
     }
}

即先递归处理左区间，后循环处理右区间，从而消除一个尾递归，以减少递归调用带来的时空消耗。
这里需注意，尾递归转循环后，转入堆排序的时机不仅仅是递归深度达到2logn，而是递归深度和while循环迭代的次数加一起达到2logn时转入堆排序。

（5）优先处理短区间。在上述策略（4）的基础上进一步改进，不是按固定次序处理左右子区间（每次都先处理左区间、后处理右区间），而是先（通过递归）处理左右两个子区间中“较短的那个区间”，然后再（通过循环）处理两个子区间中“较长的那个区间”。从而使每次递归处理的子数组长度至少缩减一半，使最坏情况下递归深度（算法最坏情况空间复杂度）为logn。

（6）三路分划（3-Way Partition）。当重复元素很多时，传统快速排序效率较低。可修改Partition操作，不是把当前数组划分为两部分，而是三部分：小于基准元素K的元素放在左边，等于K的元素放在中间，大于K的元素在右边。接下来仅需对小于K的左半部分子数组和大于K的右半部分子数组进行排序。中间等于K的所有元素都已就位，无需处理。
为确保本题答案唯一，此处请采用如下做法：若当前子数组是R[m]…R[n]，可设置3个指针，前指针i，中指针j，后指针k。初始时i和j指向第一个元素，k指向最后一个元素；指针j从左往右扫描数组：

若R[j]小于基准元素，交换R[j]和R[i], i++, j++；
若R[j]大于基准元素，交换R[j]和R[k], k--；
若R[j]等于基准元素，j++；
通过指针j的遍历，使小于基准元素的元素换到当前子数组左侧，大于基准元素的元素换到右侧。当j扫描完当前子数组后，R[m]…R[i-1]即小于基准元素的元素，R[i]…R[k]即等于基准元素的元素，R[k+1]…R[n]即大于基准元素的元素。


在本题中，请你在之前实现的STL sort()初级版的基础上，进一步实现上述优化策略。

提示：本题只需把原来的Partition改为3-way Partition，并使用“三数取中”法选择基准元素。
在快速排序函数里，改为“尾递归转循环 + 先处理短区间”。你可以在Visual Studio里对sort函数右键点击“转到定义”，查看VS中STL的sort()实现细节
vstudio sort转到定义图片.jpg

函数接口定义：
void sort(int *R, int n);
功能为对整数R[1]…R[n]递增排序。

裁判测试程序样例：
#include<iostream>
#include<stdlib.h>
#include<math.h>
using namespace std;
int threshold;

// 请在这里补充你的代码，即你所实现的sort函数

int main()
{
    int n,i;
    int a[50010];
    scanf("%d %d", &n, &threshold);
    for (i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    
    sort(a,n);
    
    printf("Final:");
    for (i = 1; i <= n; i++)
        printf("%d ",a[i]);
    printf("\n");
    return 0;
}


备注：提交代码时，只需提交sort函数以及你自定义的其他函数，不用提交#include或者main函数等内容。

输入格式:
输入第一行为2个正整数n和threshold，n为待排序的元素个数，不超过50000，threshold为改用插入排序的阈值，不超过20，含义如上所述。第二行为n个空格间隔的整数。本题中读入数据的操作无需你来实现，而由框架程序完成。

输出格式:
输出第一行为以depth_limit:开头的整数，表示转为堆排序的递归深度，即⌊2log 
2n⌋。从第二行开始，输出对某子数组转为堆排序后，该子数组初始建堆的结果，每个元素后一个空格，每个堆占一行，以Heap:开头。注意，可能不止一个堆。接下来下一行，输出n个整数，每个整数后一个空格，为快速排序所有递归退出后，插入排序执行前的数组元素，以Intermediate:开头。最后一行为n整数，每个整数后一个空格，表示排序后的数组，以Final:开头（最后一行由框架程序完成，无需你来输出）。

输入样例1：
10 2
10 9 8 7 6 5 4 3 2 1

输出样例1：
depth_limit:6
Intermediate:1 2 3 5 4 6 7 8 9 10 
Final:1 2 3 4 5 6 7 8 9 10 

输入样例2：
60 2
66 61 92 22 50 80 39 2 25 60 49 17 37 19 24 57 40 82 11 52 45 0 33 78 32 25 19 42 92 50 39 87 74 87 56 79 63 63 80 83 50 3 87 2 91 77 87 10 59 23 25 6 49 85 9 95 60 16 28 1 
输出样例2：
depth_limit:11
Intermediate:1 0 2 2 3 6 9 10 11 16 17 19 19 22 23 24 25 25 25 32 28 33 37 39 39 40 42 45 49 49 50 50 50 52 56 57 59 60 60 61 63 63 66 74 77 78 79 80 80 82 83 85 87 87 87 87 91 92 92 95 
Final:0 1 2 2 3 6 9 10 11 16 17 19 19 22 23 24 25 25 25 28 32 33 37 39 39 40 42 45 49 49 50 50 50 52 56 57 59 60 60 61 63 63 66 74 77 78 79 80 80 82 83 85 87 87 87 87 91 92 92 95 

代码长度限制
16 KB
时间限制
100 ms
内存限制
64 MB
*/