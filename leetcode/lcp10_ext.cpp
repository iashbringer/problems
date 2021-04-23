// https://leetcode-cn.com/problems/er-cha-shu-ren-wu-diao-du/
// 增加扩展条件。
// 1. 不止一个孩子，可以有多个孩子
// 2. 不止2个核，可以有任意多个核
// 3. 不止一棵树，可以有多个树
//
// 1. 可以简化为兄弟节点间用0消耗节点连接
// 3. 可以简化为用0消耗节点连接所有根节点
// 所以只要处理2的情况，考虑有n个处理器。

#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <memory.h>
#include <algorithm>
#include <numeric>
using namespace std;


// Definition for a binary tree node.
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

const int n = 2;

struct Ret
{
    double c[n]; //其中c[i]表示同时并行i+1个任务所用的时间
    Ret()
    {
        memset(c, 0, sizeof(c));
    }
    double sum()
    {
        return accumulate(c, c + n, 0);
    }
};

// 父节点本身直接最后添加到`c[1]`即可。
// 只有并行到`c[n]`是没有优化空间的。
// 考虑到匹配的目的，一定是尽量往较长的并行匹配。
// 对于所有左孩子的从`c[1]...c[n]`，匹配右孩子的`c[n]...c[1]`因为只有这样，才能让总时间缩短的最短。

class Solution
{
public:
    Ret dp(TreeNode *root)
    {
        if (root == nullptr)
        {
            return Ret{};
        }
        auto l = dp(root->left);
        auto r = dp(root->right);
        Ret ret;
        ret.c[0] += root->val;
        for (int i = 1; i <= n; i++)
        {
            auto &lc = l.c[i - 1];
            if (lc == 0)
            {
                continue;
            }
            for (int j = n; j > 0; j--) //l.c[i-1]与r.c[j-1]匹配
            {
                auto &rc = r.c[j - 1];
                if (rc == 0)
                {
                    continue;
                }
                int maxCn = min(i + j, n); //最大并行任务数
                auto maxT = min(lc, rc); //实际能并行的长度
                ret.c[maxCn - 1] += maxT * (i + j) / maxCn;
                lc -= maxT;
                rc -= maxT;
            }
            ret.c[i - 1] += lc;//无法匹配了
        }
        transform(ret.c, ret.c+n, r.c, ret.c, plus<int>());//r[c]需要加到ret.c中
        return ret;
    }

    double minimalExecTime(TreeNode *root)
    {
        auto r = dp(root);
        return r.sum();
    }
};