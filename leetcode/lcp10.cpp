// https://leetcode-cn.com/problems/er-cha-shu-ren-wu-diao-du/

#include <iostream>
#include <cstdio>
#include <stdlib.h>
using namespace std;


// Definition for a binary tree node.
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct Ret
{
    double con; //并行
    double seq; //串行
};
// 考虑每个节点状态，可以认为由并行时长+串行时长构成，则每个节点最短运行时间是con+seq，最长是con*2+seq，可以用于和另一边匹配，让并行的部分尽量长。

class Solution
{
public:
    Ret dp(TreeNode *root)
    {
        if (root == nullptr)
        {
            return Ret{0, 0};
        }
        auto l = dp(root->left);
        auto r = dp(root->right);
        if (l.seq < r.seq)
        { //确保l.seq > r.seq
            swap(l, r);
        }
        //只要匹配l.seq - r.seq看看能和右边多长的尽量并行。r.seq的部分肯定并行了，比较大小看最长能额外转换并行多长。
        auto mins = min(r.con * 2, l.seq - r.seq);
        return Ret{l.con + r.con + r.seq + mins / 2, l.seq - r.seq - mins + root->val};
    }

    double minimalExecTime(TreeNode *root)
    {
        auto r = dp(root);
        return r.con + r.seq;
    }
};