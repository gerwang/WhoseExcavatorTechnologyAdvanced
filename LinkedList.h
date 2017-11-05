//
// Created by Gerwa on 2017/11/5.
//

#ifndef WHOSEEXCAVATORTECHNOLOGYADVANCED_LINKEDLIST_H
#define WHOSEEXCAVATORTECHNOLOGYADVANCED_LINKEDLIST_H

#include <utility>

template<typename T>
struct LinkedNode {
    typedef T value_type;
    typedef LinkedNode<T> instance_type;

    LinkedNode() {}

    explicit LinkedNode(const value_type &data) : data(data) {}

    explicit LinkedNode(value_type &&data) : data(std::move(data)) {}

    value_type data{};
    instance_type *pre{}, *nxt{};
};

template<typename T>
class LinkedList;

template<typename T>
class LinkedListIterator {
public:
    typedef T value_type;
    typedef LinkedNode<T> node_type;
    typedef LinkedListIterator<T> iterator_type;
    friend LinkedList<T>;
private:
    node_type *current;
public:
    LinkedListIterator() : current(nullptr) {}

    explicit LinkedListIterator(node_type *current) : current(current) {}

    LinkedListIterator(iterator_type &&other) noexcept = default;

    LinkedListIterator(const iterator_type &other) = default;

    value_type *operator->() {
        return &current->data;
    }

    value_type &operator*() {
        return current->data;
    }

    iterator_type &operator++() {
        current = current->nxt;
        return *this;
    }

    iterator_type &operator--() {
        current = current->pre;
        return *this;
    }

    bool operator==(const iterator_type &other) {
        return current == other.current;
    }

    bool operator!=(const iterator_type &other) {
        return !(*this == other);
    }

    iterator_type &&operator++(int) {
        iterator_type res(*this);
        current = current->nxt;
        return std::move(res);
    }

    iterator_type &&operator--(int) {
        iterator_type res(*this);
        current = current->pre;
        return std::move(res);
    }
};

template<typename T>
class LinkedList {
public:
    typedef T value_type;
    typedef LinkedNode<T> node_type;
    typedef LinkedListIterator<T> iterator;
    typedef LinkedList<T> instance_type;
    typedef std::size_t size_type;
private:
    node_type *m_root;
    size_type m_size;
public:
    LinkedList() : m_size(0) {
        init_root();
    }

    LinkedList(instance_type &&other) noexcept {
        m_root = other.m_root;
        other.m_root = nullptr;
        m_size = other.m_size;
        other.m_size = 0;
    }

    LinkedList(const instance_type &other) {
        init_root();
        assign(other.begin(), other.end());
    }

    template<typename InputIterator>
    LinkedList(InputIterator first, InputIterator last) {
        init_root();
        assign(first, last);
    }

    iterator begin() {
        return iterator(m_root->nxt);
    }

    iterator end() {
        return iterator(m_root);
    }

    iterator last() {
        return iterator(m_root->pre);
    }

    const iterator begin() const {
        return iterator(m_root->nxt);
    }

    const iterator end() const {
        return iterator(m_root);
    }

    const iterator last() const {
        return iterator(m_root->pre);
    }

    ~LinkedList() {
        clear();
        delete m_root;
        m_root = nullptr;
    }

    void clear() {
        iterator it = begin();
        while (it != end()) {
            erase(it++);
        }
        m_root->pre = m_root->nxt = m_root;
        m_size = 0;
    }

    /*!
     * 在这个链表结点之前插入elem
     * @param it 所指位置的迭代器
     * @param elem 待插入的元素
     */
    void insert(iterator it, const value_type &elem) {
        insert(it.current, new node_type(elem));
    }

    void insert(iterator it, value_type &&elem) {
        insert(it.current, new node_type(std::move(elem)));
    }

    void erase(iterator it) {
        erase(it.current);
    }

    void push_back(const value_type &elem) {
        insert(end(), elem);
    }

    void push_back(value_type &&elem) {
        insert(end(), std::move(elem));
    }

    void pop_back() {
        erase(last());
    }

    template<typename InputIterator>
    void assign(InputIterator first, InputIterator last) {
        clear();
        for (auto it = first; it != last; ++it) {
            push_back(*it);
        }
    }

    int size() const {
        return m_size;
    }

private:
    /*!
     * 将elem插入到node之前
     * @param node 原来在链表中
     * @param elem 原来不在链表中
     */
    void insert(node_type *node, node_type *elem) {
        node_type *temp = node->pre;
        temp->nxt = elem;
        elem->pre = temp;
        node->pre = elem;
        elem->nxt = node;
        m_size++;
    }

    /*!
     * 删除链表中的这个结点
     * @param node
     */
    void erase(node_type *node) {
        auto prev = node->pre, succ = node->nxt;
        prev->nxt = succ;
        succ->pre = prev;
        delete node;
        node = nullptr;
        m_size--;
    }

    void init_root() {
        delete m_root;
        m_root = new node_type();
        m_root->data = value_type();
        m_root->pre = m_root->nxt = m_root;
    }
};

template<typename CharT, typename T>
std::basic_ostream<CharT> &operator<<(std::basic_ostream<CharT> &out, const LinkedList<T> &list) {
    out << CharT('[');
    for (auto x:list) {
        out << x << CharT(',') << CharT(' ');
    }
    out << CharT(']');
};

#endif //WHOSEEXCAVATORTECHNOLOGYADVANCED_LINKEDLIST_H
