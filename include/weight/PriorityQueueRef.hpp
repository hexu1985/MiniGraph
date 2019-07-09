#ifndef MINI_GRAPH_PRIORITY_QUEUE_REF_INC
#define MINI_GRAPH_PRIORITY_QUEUE_REF_INC

#include <vector>
#include <unordered_map>

namespace MiniGraph {

template <class T>
class PriorityQueueRef { 
private:
    std::vector<int> pqList_;                   // 优先级队列, 基于最小堆实现: 存放的元素是keyList_中元素的索引
    std::unordered_map<int, int> key2pqMap_;    // 从keyList_中元素索引, 转换成pqList_中元素索引
    const std::vector<T> &keyList_;             // 存放用于实际计算优先级的key列表(这里是引用, 实际队列有构造函数传入)

    void exch(int i, int j)
    { 
        // 交换pqList_[i]和pqList_[j]
        auto tmp = pqList_[i];
        pqList_[i] = pqList_[j];
        pqList_[j] = tmp;

        // 更新keyList索引到pqList索引的映射
        key2pqMap_[pqList_[i]] = i;
        key2pqMap_[pqList_[j]] = j;
    }

    void bubbleUp(int currentPos)
    { 
        int parentPos = (currentPos-1)/2;
        while (currentPos > 0) {
            if (keyList_[pqList_[currentPos]] < keyList_[pqList_[parentPos]]) {
                exch(currentPos, parentPos);
                currentPos = parentPos;
                parentPos = (currentPos-1)/2;
            } else {
				break;
			}
        }
    }

    void siftDown(int currentPos, int lastPos)
    { 
        int childPos = 2*currentPos+1;
        while (childPos < lastPos) {
            if ((childPos+1 < lastPos) && keyList_[pqList_[childPos+1]] < keyList_[pqList_[childPos]])
                childPos = childPos + 1;

            if (keyList_[pqList_[childPos]] < keyList_[pqList_[currentPos]]) {
                exch(currentPos, childPos);
                currentPos = childPos;
                childPos = 2*currentPos+1;
            } else {
				break;
			}
        }
    }

public:
    PriorityQueueRef(const std::vector<T> &keyList): keyList_(keyList) {}

    int isEmpty() const { return pqList_.empty(); }

    void insert(int idxOfKeyList)
    { 
        assert(idxOfKeyList >= 0 && idxOfKeyList < keyList_.size());
        pqList_.push_back(idxOfKeyList);
        int i = pqList_.size()-1;
        key2pqMap_[idxOfKeyList] = i;
        bubbleUp(i);
    }

    int deleteMin() 
    { 
        assert(!pqList_.empty());

        // 交换pqList的0和size-1下标元素,
        // 从pqList的0下标开始heapify pqList
        int idxOfKeyList = pqList_[0];
        int lastPos = pqList_.size()-1;
        exch(0, lastPos); 
        siftDown(0, lastPos);

        // pop minimum key index
        pqList_.pop_back();
        key2pqMap_.erase(idxOfKeyList);
        return idxOfKeyList;
    }

    void decreaseKey(int idxOfKeyList)
    { 
        assert(key2pqMap_.count(idxOfKeyList));
        bubbleUp(key2pqMap_[idxOfKeyList]);
    }
};

}	// namespace MiniGraph

#endif
