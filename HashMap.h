//
// Created by Gerwa on 2017/11/6.
//

#ifndef WHOSEEXCAVATORTECHNOLOGYADVANCED_HASHMAP_H
#define WHOSEEXCAVATORTECHNOLOGYADVANCED_HASHMAP_H

#include "HashSet.h"

template<typename KeyT, typename ValueT, typename Hash>
class PairHash {
private:
    Hash m_hasher;
public:
    explicit PairHash(const Hash &hasher) : m_hasher(hasher) {}

    size_t operator()(const Pair<KeyT, ValueT> &pair) const {
        return m_hasher(pair.first);
    }
};

template<typename KeyT, typename ValueT, typename KeyEqual>
class PairEqual {
private:
    KeyEqual m_equal;
public:
    explicit PairEqual(const KeyEqual &key_equal) : m_equal(key_equal) {}

    bool operator()(const Pair<KeyT, ValueT> &a, const Pair<KeyT, ValueT> &b) const {
        return m_equal(a.first, b.first);
    }
};

template<typename KeyT, typename ValueT,
        typename KeyHash=Hasher<KeyT>, typename KeyEqual=EqualTo<KeyT>>
class HashMap : public HashSet<Pair<KeyT, ValueT>, PairHash<KeyT, ValueT, KeyHash>,
        PairEqual<KeyT, ValueT, KeyEqual>> {

};

#endif //WHOSEEXCAVATORTECHNOLOGYADVANCED_HASHMAP_H
