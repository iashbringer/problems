//魔术师发牌问题，牌用1~13表示，从1开始数，数到第1,2,3,4...13张(循环)，将牌翻出并移出，恰是1,2,3,4,5...13。问原牌堆结果
// result:1 8 2 5 10 3 12 11 9 4 7 6 13
#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    int size = 13;
    int r[100];               //储存结果
    memset(r, -1, sizeof(r)); //-1表示未标注，有值表示已移出
    int curIndex = size - 1;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            curIndex = (curIndex + 1) % size;
            if (r[curIndex] != -1) //跳过
                j--;
        }

        r[curIndex] = i;
    }
    for (int i = 0; i < size; i++)
    {
        cout << r[i] + 1 << " ";
    }
    cout << endl;

    system("pause");
}
