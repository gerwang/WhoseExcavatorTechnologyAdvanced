//
// Created by Gerwa on 2017/11/6.
//

#ifndef WHOSEEXCAVATORTECHNOLOGYADVANCED_HASHSET_H
#define WHOSEEXCAVATORTECHNOLOGYADVANCED_HASHSET_H

#include "Utility.h"
#include "ArrayList.h"
#include "LinkedList.h"
#include <cmath>

template<typename Key, typename Hash=Hasher<Key>, typename Pred=EqualTo<Key>>
class HashSet {
public:
    typedef Key key_type;
    static const size_t MIN_BUCKET_COUNT;///< 最少的桶个数，只要集合非空，至少有这么多个桶
    typedef ArrayList<LinkedList<key_type>> container_type;

    bool is_prime(size_t x) {
        auto m = static_cast<int>(sqrt(x));
        if (x == 0 || x == 1 || x % 2 == 0) {
            return false;
        }
        for (int i = 3; i <= m; i += 2) {
            if (x % i == 0) {
                return false;
            }
        }
        return true;
    }

    /*!
     *
     * @param x 给出的下界
     * @return 大于等于x的最小质数
     */
    size_t prime_bound(size_t x) {
        while (!is_prime(x)) {
            x++;
        }
        return x;
    }

private:
    container_type m_container;
    float m_maxLoadFactor;
    size_t m_size;
    Hash m_hasher;


    /*!
     * 判断是否需要重新分配桶的个数
     */
    void checkReHash() {
        if (bucket_count() == 0 || float(m_size + 1) / bucket_count() > m_maxLoadFactor) {
            size_t next_bucket_count = MIN_BUCKET_COUNT;
            if (next_bucket_count < bucket_count() * 2) {
                next_bucket_count = prime_bound(bucket_count() * 2);
            }
            rehash(next_bucket_count);
        }
    }

public:
    /*!
     *
     * @return 当前的装载因子
     */
    float load_factor() {
        return static_cast<float>(m_size) / m_container.size();
    }

    float max_load_factor() {
        return m_maxLoadFactor;
    }

    void max_load_factor(float factor) {
        m_maxLoadFactor = factor;
    }

    explicit HashSet(const Hash &hasher = Hash()) : m_hasher(hasher), m_maxLoadFactor(1), m_size(0) {}

    int size() const {
        return m_size;
    }

    bool empty() const {
        return m_size == 0;
    }

    size_t bucket_count() const {
        return m_container.size();
    }

    bool insert(const key_type &val) {
        checkReHash();
        size_t index = m_hasher(val) % bucket_count();
        if (m_container[index].find(val) == m_container[index].end()) {
            m_container[index].push_back(val);
            m_size++;
        }
    }

    bool insert(key_type &&val) {
        checkReHash();
        size_t index = m_hasher(val) % bucket_count();
        if (m_container[index].find(val) == m_container[index].end()) {
            m_container[index].push_back(std::move(val));
            m_size++;
        }
    }

    bool erase(const key_type &val) {
        size_t index = m_hasher(val) % bucket_count();
        auto it = m_container[index].find(val);
        if (it != m_container[index].end()) {
            m_container[index].erase(it);
            m_size--;
        }
    }

    /*!
     * 重新分配内存空间，所有元素都会正确的呗插入到新的位置中
     * @param next_bucket_count 新的桶的个数
     */
    void rehash(size_t next_bucket_count) {
        if (bucket_count() < next_bucket_count) {

            container_type next_container;
            next_container.reserve(next_bucket_count);
            for (size_t i = 0; i < next_bucket_count; i++) {
                next_container.push_back(LinkedList<key_type>());
            }

            for (auto &list:m_container) {
                for (auto &val:list) {
                    size_t index = m_hasher(val) % next_bucket_count;
                    next_container[index].push_back(std::move(val));
                }
            }

            m_container = std::move(next_container);
        }
    }

    /*!
     *
     * @return 当前对象转换成的arraylist
     * @attention 顺序并不一定
     */
    ArrayList<key_type> toArrayList() {
        ArrayList<key_type> result;
        for (auto &list:m_container) {
            for (auto &val:list) {
                result.push_back(val);
            }
        }
        return std::move(result);
    }

    /*!
     * @note 出现次数只可能是0或者1
     * @param x 待查询的值
     * @return x在当前表中的出现次数
     */
    int count(const key_type &x) const {
        size_t index = m_hasher(x) % bucket_count();
        return m_container[index].count(x);
    }
};

template<typename Key, typename Hash, typename Pred>
const size_t HashSet<Key, Hash, Pred>::MIN_BUCKET_COUNT = 11;

#endif //WHOSEEXCAVATORTECHNOLOGYADVANCED_HASHSET_H
