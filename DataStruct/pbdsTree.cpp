#include <bits/extc++.h>
namespace pb = __gnu_pbds;

template<class T, class Cmp = std::less<T>>
using RedBlackTree =
    pb::tree<T, pb::null_type, Cmp, pb::rb_tree_tag, pb::tree_order_statistics_node_update>;

/**
 * order_of_key(x) -> 查询有多少元素比x小
 * find_by_order(x) -> 查询有x个元素比它小的元素的迭代器
 */