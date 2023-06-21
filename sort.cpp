#pragma region // 归并排序
// 如何理解MergeSort
// 归并排序的精髓在于一个无序数组的拆分和两个有序数组的合并。我们的base就是：只含有一个数字的数组一定是有序的。（废话）
// 我们将一个含n个数字的数组拆分为n个含一个数字的数组。于是我们很高兴地宣布我们得到了n个有序的数组。（bushi
// 接下来的任务其实就变成了：将这n个有序数组（难道不是吗？他们就是有序的捏...）进行合并。任意两个有序数组合并，得到一个新的有序数组。
// 当我们合并到最后只剩下一个数组的时候，我们的排序就已经完成了，毕竟他也是有序的。
// 你说“任意两个有序数组合并，得到一个新的有序数组。”如何合并？每次比较要合并的两个数组各自最前面的一个元素（假设这两个有序数组是从小到大排好了的）。
// 拿出那个较小的元素。好，这时这个元素就是这两个数组中最小的那个。为什么？我们比较的这两个元素在他们各自的数组里面已经小于他们后面所有的的元素了啊！
// 这样子每次拿一个元素出来放到我们的结果数组里，然后将这个元素从原来的数组里面删掉。这样子依次操作下去就行。（当然还有一些细节先别管他）
// 那么，我们总共需要比较的次数无非就是：把每次合并所需要比较的次数加起来。当然，这个次数越少越好。
// 我们先来想一个问题：我们要进行多少次合并的操作？这是一个定值吗？
// 呃呃这不肯定是一个定值嘛，你每操作一个，数组的总个数就少一个，操作一次少一个，你总共不就是要操作n-1次嘛。
// 既然如此，我们就需要尽量地减少每次合并所需要比较的次数。直觉上，我们每次应该将两个最小的数组合并。事实上也确实如此。具体证明不太容易。

#include <iostream>
using namespace std;

void mergearray(int a[], int a1, int end1, int a2, int end2, int b[])
{
    int p1, p2;
    p1 = p2 = a1;
    // 注意，这个函数针对的两个数组是相邻的，也就是end1+1=a2
    while (a1 <= end1 && a2 <= end2)
    {
        if (a[a1] < a[a2])
            b[p1++] = a[a1++];
        else
            b[p1++] = a[a2++];
    }
    // 因为一个数组会先比较完毕，所以还需要补充两个情况
    while (a1 <= end1)
        b[p1++] = a[a1++];
    while (a2 <= end2)
        b[p1++] = a[a2++];
    // 最后把temp里面排好了的数组再放回去替换掉原来无序的
    while (p2 <= end2)
    {
        a[p2] = b[p2];
        p2++;
    }
}

void mergesort(int a[], int op, int ed, int temp[])
{
    if (op < ed)
    {
        int mi = (op + ed) / 2;
        mergesort(a, op, mi, temp);
        mergesort(a, mi + 1, ed, temp);
        mergearray(a, op, mi, mi + 1, ed, temp);
    }
}

bool MergeSort(int a[], int n)
{
    int *temp = new int[n];
    if (temp == nullptr)
        return false;
    mergesort(a, 0, n - 1, temp);
    delete[] temp;
    return true;
}

int main(void)
{
    int n;
    cin >> n;
    int *array = new int[n];
    for (int count = 0; count < n; count++)
        cin >> array[count];
    MergeSort(array, n);
    for (int count = 0; count < n; count++)
        cout << array[count] << ' ';
    return 0;
}
#pragma endregion

#pragma region // 基数排序
// 如何理解RadixSort
// 基数：基数的概念其实和进制差不多，二进制基数就是2，十进制基数就是radix
// 想一想我们平常比较两个数的大小是咋整的：首先看位数，哪个位数大，肯定大。若位数一样大，就从最高位开始依次往下比，若在哪一位谁比另一个大了，那谁就大。
// 这种平常的习惯其实也是以基数来排序的一种。但是如果我们不是只有两个元素需要排序，而是有一个数组需要排序的时候，我们还适合从高位开始比较吗？
// 如果我们还是从高位开始比较，那么在比完最高位以后我们就将整个数组拆散了！接下来我们得在各个部分（每一个部分里面最高位是相同的）里面进行排序。
// 这个方式不是不行，但是如果我们一直都能以一个整体来考虑，而不是划成很多很多的小部分来比较就好了。
// 考虑一个问题：为什么在比完最高位以后，我们不能确定谁大谁小？因为我们不知道在低位他们谁大谁小啊。但是...如果我们知道呢？
// 或者说，我们反过来排序呢？
// 很显然，如果低位被排好了，那么在排最高位的时候，如果最高位相同，原来的大小顺序依然是现在的大小顺序。比如，2<3，那么62<63依然成立。
// 你看，前后顺序没变，但我大小顺序也就刚刚好是我要的。这就是基数排序的原理。
// 当然，如果最高位不同，那么最高位的大小就是数的大小，和低位就没有关系了。这没什么好说的，但是这一点很重要！
// 因为你会说，那我一样操作，如果高位被排好了，那么在排低位的时候，如果低位相同，原来的大小顺序依然是现在的大小顺序！为啥不能这样排？
// 这话没错。我认可“如果低位相同”原来的大小顺序依然是现在的大小顺序，但我不认可在低位不同的情况下，低位的大小就能决定数的大小！2<3，但是29>31吗？
// 理解为什么要从低位排序，才算懂基数排序。
// 那么接下来就是基于每一位去排序了。
// 刚刚说过，如果如果低位被排好了，那么在排高位的时候，哪怕高位相同，原来的大小顺序依然是现在的大小顺序。所以，我们应该这样做：
// 将这一位上为0的数字拿出来，按原来的顺序放到结果数组里；将这一位上为1的数字拿出来，按原来的顺序放到结果数组里，
// 将这一位上为2的数字拿出来，按原来的顺序放到结果数组里；将这一位上为3的数字拿出来，按原来的顺序放到结果数组里...直到基数结束。
// 但是一遍一遍地遍历实在有些浪费。我们只需要遍历一遍就能够知道：有多少个0，有多少个1，有多少个2，有多少个3...
// 而一旦知道了有多少个，我就明白这一位上为0，为1，为2，为3...的数应该被放在结果数组里面的哪一个块（或者说哪个部分）。我们将这些位置记录下来。
// 举个例子。比如我知道为0的有a个，为1的有b个，为2的有c个...
// 当然为0的肯定从头开始排；那么为1的就得从第a+1个位置开始排，为2的就得从第a+b+1个位置开始排....每拿到一个数，我都知道要把他放到哪里。
// 从而，我只需要再遍历一遍，把每一个数放到他需要去的地方就行咯。

#include <iostream>
#include <limits.h>
#include <string.h>
using namespace std;

int GetNumberOnTheNthBit(int object, int N, int radix)
{
    for (int count = 1; count < N; count++)
        object /= radix;
    return object % radix;
}

bool RadixSort(int ar[], int N, int radix)
{
    int *manipulate, max = INT_MIN, bits = 1, record;
    manipulate = ar;
    // 统计最大的数字的位数
    for (int count = 1; count < N; count++, manipulate++)
        max = *manipulate > max ? *manipulate : max;
    while (max > radix)
    {
        bits++;
        max /= radix;
    }
    // 开始排序
    for (int count = 1; count <= bits; count++)
    {
        // 开一个新计数器，统计待排位上各个数字的个数
        int *digit = new int[radix];
        for (int i = 0; i < radix; i++)
            digit[i] = 0;
        manipulate = ar;
        for (int i = 0; i < N; i++, manipulate++)
            digit[GetNumberOnTheNthBit(*manipulate, count, radix)]++;
        // 开一个新定位器，计算该位不同数字所应该被放置的位置
        for (int i = 1; i < radix; i++)
            digit[i] += digit[i - 1];
        int *temp = new int[N];
        if (temp == nullptr)
            return false;
        int **locate = new int *[radix];
        locate[0] = temp;
        for (int i = 1; i < radix; i++)
            locate[i] = temp + digit[i - 1];
        // 按照位置进行放置
        manipulate = ar;
        for (int i = 0; i < N; i++, manipulate++)
        {
            record = GetNumberOnTheNthBit(*manipulate, count, radix);
            *locate[record] = *manipulate;
            locate[record]++;
        }
        // 复制排序结果到原数组
        memcpy(ar, temp, sizeof(int) * N);
        // 释放临时内存
        delete[] temp;
    }
    return true;
}

int main(void)
{
    int N;
    cin >> N;
    int *ar = new int[N];
    for (int count = 0; count < N; count++)
        cin >> ar[count];
    RadixSort(ar, N, 10); // 基数为10的排序
    for (int count = 0; count < N; count++)
        cout << ar[count] << ' ';
    return 0;
}
#pragma endregion

#pragma region // 快速排序
//快速排序应该属于非常好理解的一种排序，每一次Partition所做的就是将范围内最左边的元素放到其最终的位置上。
#include <iostream>
#include <stack>
using namespace std;

int Partition(int *ar, int l, int r)
{
    int temp = ar[l];
    bool initiative = true;
    while (l != r)
    {
        if (initiative)
        {
            if (ar[r] < temp)
            {
                ar[l] = ar[r];
                l++;
                initiative = false;
            }
            else
                r--;
        }
        else
        {
            if (ar[l] > temp)
            {
                ar[r] = ar[l];
                r--;
                initiative = true;
            }
            else
                l++;
        }
    }
    ar[l] = temp;
    return l;
}

void quicksort(int *ar, int l, int r)
{
    stack<pair<int, int>> manualstack;
    manualstack.push(make_pair(l, r));
    while (!manualstack.empty())
    {
        pair<int, int> temp = manualstack.top();
        manualstack.pop();
        if (temp.first >= temp.second)
            continue;
        int pv = Partition(ar, temp.first, temp.second);
        if ((pv - temp.first) <= (temp.second - pv))
        {
            manualstack.push(make_pair(pv + 1, temp.second));
            manualstack.push(make_pair(temp.first, pv - 1));
        }
        else
        {
            manualstack.push(make_pair(temp.first, pv - 1));
            manualstack.push(make_pair(pv + 1, temp.second));
        }
    }
}

int main(void)
{
    int N;
    cin >> N;
    int *ar = new int[N];
    for (int i = 0; i < N; i++)
        cin >> ar[i];
    quicksort(ar, 0, N - 1);
    for (int i = 0; i < N; i++)
        cout << ar[i] << ' ';
    return 0;
}
#pragma endregion