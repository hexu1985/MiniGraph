/**
 * @file Edge.hpp
 * @brief 带权重的边
 * @author hexu_1985@sina.com
 * @version 1.0
 * @date 2019-06-25
 */
#ifndef MINI_GRAPH_WEIGHT_EDGE_INC
#define MINI_GRAPH_WEIGHT_EDGE_INC

#include <cassert>

namespace MiniGraph {

namespace weight {

/**
 * @brief 带权重的边
 */
class Edge {
private:
	int u_ = -1;
    int v_ = -1;
    double wt_ = 1;

public:
    /**
     * @brief 构造一个边对象
     *
     * @param u from顶点
     * @param v to顶点
     */
	Edge(int u = -1, int v = -1): u_(u), v_(v) { }

    /**
     * @brief 构造一个边对象
     *
     * @param u from顶点
     * @param v to顶点
     * @param wt 边的权重
     */
	Edge(int u, int v, double wt): u_(u), v_(v), wt_(wt) { }

    /**
     * @brief 获取from顶点
     *
     * @return from顶点索引
     */
    int u() const { return u_; }

    /**
     * @brief 获取to顶点
     *
     * @return to顶点索引
     */
    int v() const { return v_; }

    /**
     * @brief 获取边权重
     *
     * @return 权重大小
     */
    double weight() const { return wt_; }

    /**
     * @brief 测试顶点是否为from顶点
     *
     * @param w 顶点索引
     *
     * @return 如果w为from顶点, 则返回true, 否则返回false
     */
    bool from(int w)
    {
        return w == u_;
    }

    /**
     * @brief 给定边的一个顶点, 返回另外一端顶点的索引
     *
     * @param w 给定的顶点
     *
     * @return 另外一端顶点的索引
     */
    int other(int w)
    {
        return from(w) ? v_ : u_;
    }
};

}   // namespace weight

}	// namespace MiniGraph

#endif
