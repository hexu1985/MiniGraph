#ifndef MINI_GRAPH_REF_PRIORITY_QUEUE_INC
#define MINI_GRAPH_REF_PRIORITY_QUEUE_INC

#include <vector>
#include <unordered_map>

namespace MiniGraph {

template <class T>
class RefPriorityQueue { 
private:
    std::vector<int> pqList_;    // 优先级队列, 存放的是refList_中元素的索引
    std::unordered_map<int, int> ref2pqMap_;
    const std::vector<T> &refList_;   

    void exch(int i, int j)
    { 
        std::swap(pqList_[i], pqList_[j]);
        ref2pqMap_[pqList_[i]] = i;
        ref2pqMap_[pqList_[j]] = j;
    }

    void fixUp(int currentPos)
    { 
        int parentPos = (currentPos-1)/2;
        while (currentPos > 0) {
            if (refList_[pqList_[currentPos]] < refList_[pqList_[parentPos]]) {
                exch(currentPos, parentPos);
                currentPos = parentPos;
                parentPos = (currentPos-1)/2;
            } else {
				break;
			}
        }
    }

    void fixDown(int currentPos, int lastPos)
    { 
        int childPos = 2*currentPos+1;
        while (childPos < lastPos) {
            if ((childPos+1 < lastPos) && refList_[pqList_[childPos+1]] < refList_[pqList_[childPos]])
                childPos = childPos + 1;

            if (refList_[pqList_[childPos]] < refList_[pqList_[currentPos]]) {
                exch(currentPos, childPos);
                currentPos = childPos;
                childPos = 2*currentPos+1;
            } else {
				break;
			}
        }
    }

public:
    RefPriorityQueue(const std::vector<T> &arr): refList_(arr) {}

    int isEmpty() const { return pqList_.empty(); }

    void insert(int v)
    { 
        assert(v >= 0 && v < refList_.size());
        pqList_.push_back(v);
        int i = pqList_.size()-1;
        ref2pqMap_[v] = i;
        fixUp(i);
    }

    int deleteMin() 
    { 
        assert(!pqList_.empty());

        // adjust_heap
        int v = pqList_[0];
        int lastPos = pqList_.size()-1;
        exch(0, lastPos); 
        fixDown(0, lastPos);

        // pop
        pqList_.pop_back();
        ref2pqMap_.erase(v);
        return v;
    }

    void lower(int v)
    { 
        assert(ref2pqMap_.count(v));
        fixUp(ref2pqMap_[v]);
    }
};

}	// namespace MiniGraph

#endif
