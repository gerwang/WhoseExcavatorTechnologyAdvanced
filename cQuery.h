//
// Created by Gerwa on 2017/11/7.
//

#ifndef WHOSEEXCAVATORTECHNOLOGYADVANCED_QUERYSELECTOR_H
#define WHOSEEXCAVATORTECHNOLOGYADVANCED_QUERYSELECTOR_H

#include "LinkedList.h"
#include "DomNode.h"

class cQuery {
    LinkedList<String> m_classNames;
    LinkedList<Pair<String, String> > m_attributes;
    LinkedList<String> m_tagNames;
    ArrayList<DomNode *> m_results;
public:
    explicit cQuery(DomNode *nav);

    cQuery() = default;

    /*!
     * 应用当前的筛选条件，将m_results中的结点的子树中满足要求的结点放在m_results中
     * * @return 当前对象
     */
    cQuery &get();

    /*!
     * 保留当前的第index+1个结果，舍弃其余的结果
     * @param index 保留的位置
     * @return 当前对象
     */
    cQuery &pick(int index);

    /*!
     * 添加一个类名的筛选条件
     * @param name 类的名称
     * @return 当前对象
     */
    cQuery &clas(const String &name);

    /*!
     * 添加一个属性筛选条件
     * @param key 属性的名称
     * @param value 属性的值，如果为空，表示只要存在属性名就算匹配
     * @return 当前对象
     */
    cQuery &attr(const String &key, const String &value);

    /*!
     * 添加一个标签名的筛选对象
     * @param name 标签名
     * @return 当前对象
     */
    cQuery &tag(const String &name);

    /*!
     * 应用当前筛选条件从root出发对子树进行筛选，将结果添加到results中
     * @param root 所搜索的子树的根
     * @param results 放置结果的引用
     */
    void select(DomNode *root, ArrayList<DomNode *> &results);

    /*!
     * 判断一个结点是否满足了所有的条件
     * @param node 待判断的结点
     * @return 该结点是否满足了所有的条件
     */
    bool checkNode(const DomNode *node);
};


#endif //WHOSEEXCAVATORTECHNOLOGYADVANCED_QUERYSELECTOR_H
