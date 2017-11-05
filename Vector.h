//
// Created by Gerwa on 2017/11/5.
//

#ifndef WHOSEEXCAVATORTECHNOLOGYADVANCED_VECTOR_H
#define WHOSEEXCAVATORTECHNOLOGYADVANCED_VECTOR_H

#include <memory>
#include <iostream>

/*!
 * 仿照stl实现的vector，采用了std::move()进行优化
 * @tparam T 元素的类型
 */
template<typename T>
class Vector {
public:
    typedef T value_type;
    typedef T *iterator;
    typedef const T *const_iterator;
    typedef std::size_t size_type;
    typedef Vector<T> instance_type;
    static const size_type MIN_SIZE;
private:
    /*!
     * @param m_begin the address where vector begins
     * @param m_size the current size of vector
     * @param m_cap the caoacity of the vector
     */
    iterator m_begin;
    size_type m_size, m_cap;

    void reallocate(size_type next_cap) {
        iterator next_begin = new value_type[next_cap];
        for (size_type i = 0; i < m_size; i++) {
            next_begin[i] = std::move(m_begin[i]);
        }
        m_cap = next_cap;
        delete[] m_begin;
        m_begin = next_begin;
    }

public:
    Vector() : m_begin(nullptr), m_size(0), m_cap(0) {}

    ~Vector() {
        clear();
    }

    template<typename InputIterator>
    Vector(InputIterator first, InputIterator last): m_begin(nullptr), m_size(0), m_cap(0) {
        assign(first, last);
    }

    Vector(const instance_type &other) : m_begin(nullptr), m_size(0), m_cap(0) {
        assign(other.begin(), other.end());
    }

    Vector(instance_type &&other) noexcept {
        m_begin = other.m_begin;
        other.m_begin = nullptr;

        m_size = other.m_size;
        other.m_size = 0;

        m_cap = other.m_cap;
        other.m_cap = 0;
    }

    Vector &operator=(const instance_type &other) {
        assign(other.begin(), other.end());
        return *this;
    }

    Vector &operator=(instance_type &&other) noexcept {
        m_begin = other.m_begin;
        other.m_begin = nullptr;

        m_size = other.m_size;
        other.m_size = 0;

        m_cap = other.m_cap;
        other.m_cap = 0;

        return *this;
    }

    iterator begin() {
        return m_begin;
    }

    iterator end() {
        return m_begin + m_size;
    }

    const_iterator begin() const {
        return cbegin();
    }

    const_iterator end() const {
        return cend();
    }

    const_iterator cbegin() const {
        return m_begin;
    }

    const_iterator cend() const {
        return m_begin + m_size;
    }

    void clear() {
        delete[] m_begin;
        m_begin = nullptr;
        m_size = m_cap = 0;
    }

    size_type size() const {
        return m_size;
    }

    bool empty() const {
        return m_size == 0;
    }

    int capacity() const {
        return m_cap;
    }

    template<typename InputIterator>
    void assign(InputIterator first, InputIterator last) {
        clear();
        InputIterator temp = first;
        m_cap = 0;
        while (temp != last) {
            temp++;
            m_cap++;
        }
        m_begin = new value_type[m_cap];
        for (size_type i = 0; i < m_cap; i++) {
            m_begin[i] = first[i];
        }
        m_size = m_cap;
    }

    value_type &front() {
        return m_begin[0];
    }

    value_type &back() {
        return m_begin[m_size - 1];
    }

    const value_type &front() const {
        return m_begin[0];
    }

    const value_type &back() const {
        return m_begin[m_size - 1];
    }

    value_type &operator[](size_type index) {
        return m_begin[index];
    }

    const value_type &operator[](size_type index) const {
        return m_begin[index];
    }

    void reserve(size_type next_cap) {
        if (m_cap < next_cap) {
            reallocate(next_cap);
        }
    }

    iterator insert(const_iterator pos, const value_type &elem) {
        size_type index = pos - m_begin;//must convert to index first before reallocate()
        size_type target_cap = m_cap;
        if (target_cap < MIN_SIZE) {
            target_cap = MIN_SIZE;
        }
        if (target_cap < m_size + 1) {
            target_cap *= 2;
        }
        if (m_cap < target_cap) {
            reserve(target_cap);
        }

        for (size_type i = m_size - 1; i >= index; i--) {
            m_begin[i + 1] = std::move(m_begin[i]);
        }
        m_size++;
        m_begin[index] = elem;
        return m_begin + index;
    }

    iterator insert(const_iterator pos, value_type &&elem) {
        size_type index = pos - m_begin;
        size_type target_cap = m_cap;
        if (target_cap < MIN_SIZE) {
            target_cap = MIN_SIZE;
        }
        if (target_cap < m_size + 1) {
            target_cap *= 2;
        }
        if (m_cap < target_cap) {
            reserve(target_cap);
        }

        for (int i = (int) m_size - 1; i >= (int) index; i--) {
            m_begin[i + 1] = std::move(m_begin[i]);
        }
        m_size++;
        m_begin[index] = std::move(elem);
        return m_begin + index;
    }

    void erase(const_iterator pos) {
        size_type index = pos - m_begin;
        for (size_type i = index; i + 1 < m_size; i++) {
            m_begin[i] = std::move(m_begin[i + 1]);
        }
        m_size--;
        if (m_size * 2 < m_cap && MIN_SIZE * 2 <= m_cap) {
            reallocate(m_cap / 2);
        }
    }


    void push_back(const value_type &elem) {
        insert(end(), elem);
    }

    void push_back(value_type &&elem) {
        insert(end(), std::move(elem));
    }

    void pop_back() {
        erase(end() - 1);
    }

    instance_type &&operator+(const instance_type &other) {
        instance_type res(*this);
        for (auto x:other) {
            res.push_back(x);
        }
        return std::move(res);
    }

    instance_type &operator+=(const instance_type &other) {
        for (auto x:other) {
            push_back(x);
        }
        return *this;
    }

    bool operator==(const instance_type &other) {
        if (size() != other.size()) {
            return false;
        }
        for (size_type i = 0; i < m_size; i++) {
            if (!(m_begin[i] == other.m_begin[i])) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const instance_type &other) {
        return !(*this == other);
    }

    bool operator<(const instance_type &other) {
        for (size_type i = 0; i < size() && i < other.size(); i++) {
            if (m_begin[i] < other.m_begin[i] || other.m_begin[i] < m_begin[i]) {
                return m_begin[i] < other.m_begin[i];
            }
        }
        return size() < other.size();
    }

    value_type &at(size_type index) {
        return m_begin[index];
    }

    const value_type &at(size_type index) const {
        return m_begin[index];
    }
};

template<typename T>
const typename Vector<T>::size_type Vector<T>::MIN_SIZE = 24;

template<typename CharT, typename T>
std::basic_ostream<CharT> &operator<<(std::basic_ostream<CharT> &out, const Vector<T> &vector) {
    out << CharT('[');
    for (auto it = vector.begin(); it != vector.end(); ++it) {
        if (it != vector.begin()) {
            out << CharT(',') << CharT(' ');
        }
        out << *it;
    }
    out << CharT(']');
    return out;
};

#endif //WHOSEEXCAVATORTECHNOLOGYADVANCED_VECTOR_H
