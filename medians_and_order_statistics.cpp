/************************************
** Edition:	Demo
** Author:	Kingsley Chen	
** Date:	2013/08/08
** Purpose:	chapter 9 implementation
************************************/

#include <algorithm>
#include <xutility>
#include <random>
#include <cassert>

using std::swap;
using std::random_device;
using std::uniform_int_distribution;
using std::default_random_engine;

typedef std::pair<int,int> MaxMinPair;
int RandomPartition(int ary[], int l, int r);

// less than 3n/2 times of comparisons
MaxMinPair FindLargestSmallestPair(const int* ary, size_t len)
{
    int tmpMax, tmpMin;
    unsigned int begPos = 0U;
    if (len & 1)
    {
        tmpMin = tmpMax = ary[0];
        begPos = 1U;
    } 
    else
    {
        tmpMax = std::max(ary[0], ary[1]);
        tmpMin = std::min(ary[0], ary[1]);
        begPos = 2U;
    }

    for (unsigned int i = begPos; i < len; i += 2)
    {
        if (ary[i] < ary[i+1])
        {
            tmpMin = std::min(tmpMin, ary[i]);
            tmpMax = std::max(tmpMax, ary[i+1]);
        } 
        else
        {
            tmpMin = std::min(tmpMin, ary[i+1]);
            tmpMax = std::max(tmpMax, ary[i]);
        }
    }

    return std::make_pair<int, int>(tmpMax, tmpMin);
}

// k-th smallest
int RandomizedSelect(int ary[], int l, int r, int k)
{
    if (l == r)
    {
        return ary[l];
    }

    int pi = RandomPartition(ary, l, r);
    int lessEqlCnt = pi - l + 1;

    if (lessEqlCnt == k)
    {
        return ary[pi];
    }
    else if (lessEqlCnt < k)
    {
        return RandomizedSelect(ary, pi + 1, r, k - lessEqlCnt);
    } 
    else
    {
        return RandomizedSelect(ary, l, pi - 1, k);
    }
}

// iterative version
int RandomizedSelectIter(int ary[], size_t len, int k)
{
    assert(k >= 1 && k <= static_cast<int>(len));
    int l = 0, r = len - 1;
    int index = -1;
    while (l <= r)
    {
        int s = RandomPartition(ary, l, r);
        if (s + 1 == k)
        {
            index = s;
            break;
        }
        else if (s + 1 < k)
        {
            l = s + 1;
        } 
        else
        {
            r = s - 1;
        }
    }

    assert(index != -1);
    return ary[index];
}