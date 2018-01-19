//
// Created by Gerwa on 2017/12/10.
//

#ifndef WHOSEEXCAVATORTECHNOLOGYADVANCED_AVLMAP_H
#define WHOSEEXCAVATORTECHNOLOGYADVANCED_AVLMAP_H

#include <algorithm>
#include "Stack.h"
#include <functional>

#define Height(x) ((x)?(x)->height:-1)

template<typename Key, typename Value>
struct AvlNode {
    typedef Key key_type;
    typedef Value value_type;
    typedef AvlNode<key_type, value_type> node_type;
    key_type key;
    value_type value;
    int height;
    node_type *ch[2];

    explicit AvlNode(const key_type &key, const value_type &value = value_type()) : key(key), value(value), height(0) {
        ch[0] = ch[1] = nullptr;
    }

    int cmp(const key_type &x) const {
        if (key == x) {
            return -1;
        }
        return x < key ? 0 : 1;
    }

    void maintain() {
        height = std::max(Height(ch[0]), Height(ch[1])) + 1;
    }

    int imbalance() const {
        return Height(ch[0]) - Height(ch[1]);
    }

    int heavySide() const {
        if (Height(ch[0]) == Height(ch[1])) {
            return -1;
        }
        return Height(ch[0]) > Height(ch[1]) ? 0 : 1;
    }
};

template<typename Key, typename Value>
class AvlMap {
    typedef Key key_type;
    typedef Value value_type;
    typedef AvlNode<key_type, value_type> node_type;
    node_type *root;

    void rotate(node_type *&o, int d) {
        node_type *k = o->ch[d ^ 1];
        o->ch[d ^ 1] = k->ch[d];
        k->ch[d] = o;
        o->maintain();
        o = k;
        o->maintain();
    }

    void adjust(node_type *&o) {
        while (true) {
            int imba = o->imbalance();
            if (-1 <= imba && imba <= 1) {
                break;
            }
            int d = o->heavySide();
            int d2 = o->ch[d]->heavySide();
            if (d != d2) {
                rotate(o->ch[d], d2 ^ 1);
            }
            rotate(o, d ^ 1);
        }
    }

    void insert(node_type *&o, const key_type &key, const key_type &value) {
        if (o == nullptr) {
            o = new node_type(key, value);
        } else {
            int d = o->cmp(key);
            if (d == -1) {
                return;//same key, return
            }
            insert(o->ch[d], key, value);
            o->maintain();
            adjust(o);
        }
    }

    void erase(node_type *&o, const key_type &key) {
        if (o == nullptr) {//do not find
            return;
        }
        int d = o->cmp(key);
        if (d == -1) {
            if (o->ch[0] == nullptr || o->ch[1] == nullptr) {
                node_type *pre = o;
                if (o->ch[0] == nullptr) {
                    o = o->ch[1];
                } else {
                    o = o->ch[0];
                }
                delete pre;
            } else {
                node_type *succ = o->ch[1], *fa = o;
                Stack<node_type *> link;
                while (succ->ch[0] != nullptr) {
                    link.push(succ);
                    fa = succ;
                    succ = succ->ch[0];
                }
                o->key = std::move(succ->key);
                o->value = std::move(succ->value);
                if (fa == o) {
                    o->ch[1] = succ->ch[1];
                } else {
                    fa->ch[0] = succ->ch[1];
                }
                while (!link.empty()) {
                    adjust(link.top()->ch[0]);
                    link.top()->maintain();
                    link.pop();
                }
                o->maintain();
                adjust(o->ch[1]);
                adjust(o);
                delete succ;
                succ = nullptr;
            }
        } else {
            erase(o->ch[d], key);
            o->maintain();
            adjust(o);
        }
    }

    node_type *&find(node_type *&o, const key_type &key) {
        if (o == nullptr) {
            return o;
        }
        int d = o->cmp(key);
        if (d == -1) {
            return o;
        }
        return find(o->ch[d], key);
    }

    void removeTree(node_type *&o) {
        if (o == nullptr) {
            return;
        }
        removeTree(o->ch[0]);
        removeTree(o->ch[1]);
        delete o;
        o = nullptr;
    }

    void traverse(node_type *o, const std::function<void(const node_type *)> &callback) {
        if (o == nullptr) {
            return;
        }
        traverse(o->ch[0], callback);
        callback(o);
        traverse(o->ch[1], callback);
    }

public:
    AvlMap() : root(nullptr) {}

    virtual ~AvlMap() {
        clear();
    }

    value_type &operator[](const key_type &key) {
        node_type *&ref = find(root, key);
        if (ref == nullptr) {
            ref = new node_type(key);
        }
        return ref->value;
    }

    void clear() {
        removeTree(root);
    }

	/*!
	 * 将一个键值对插入到树中，如果键已经存在则不会插入
	 * @param key 待插入的键
	 * @param value 待插入的值
	 */
    void insert(const key_type &key, const value_type &value) {
        insert(root, key, value);
    }

	/*!
	 *删除对应的键值对
	* @param key 待删除的键值
	*/
    void erase(const key_type &key) {
        erase(root, key);
    }

	/*!
	 * 判断树中是否存在这个键值
	 * @note 只可能返回0或者1
	 * @param key 待查询的键值
	 */
    int count(const key_type &key) {
        return find(root, key) == nullptr ? 0 : 1;
    }

	/*!
	 *	按照中序遍历整棵树，对每个结点调用回调函数
	 * @param callback 对每个结点指针调用的函数
	 */
    void traverse(const std::function<void(const node_type *)> &callback) {
        traverse(root, callback);
    }
};

#endif //WHOSEEXCAVATORTECHNOLOGYADVANCED_AVLMAP_H
