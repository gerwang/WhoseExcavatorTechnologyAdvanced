# WhoseExcavatorTechnologyAdvanced
a search engine which crawls, extract information from http://bbs.cehome.com/
## 实验目标

- 从输入的网址中爬取相应的网页
- 将网页中的HTML解析成DOM树
- 使用类似jQuery的方式提取需要的网页信息
- 对文本进行分词

## 实验环境

本项目使用`CLion`开发，使用`cmake`和`g++`进行编译，在CLion2017.2.1上编译通过。

**注意**：由于使用了一些Visual Studio 2012不支持的C++11特性，**项目不能在Visual Studio 2012上编译通过**，但是通过`cmake`生成了对应的`.sln`文件，方便在VS2012上查看源代码。

## 抽象数据结构说明

> 具体接口说明参见代码中的`doxygen`注释

###### `ArrayList`

可变长的数组，采用模板实现。

接口模仿`std::vector`，并实现了迭代器。

###### `BasicString`

采用`ArrayList`实现的字符串模板。

接口模仿`std::basic_string`。

| 接口功能对照    | 要求的函数       |
| --------- | ----------- |
| indexOf   | find        |
| substring | substr      |
| concat    | operator += |
| assign    | operator =  |

###### `cQuery`

HTML过滤器，可以提取DOM树中满足要求的结点。

###### `Craweler`

爬取网页功能的管理类。

###### `CSVHandler`

负责CSV文件的读取和保存。

###### `DomNode`

DOM树中的多叉树结点。

###### `HashSet`

自己实现的可变长的哈希表，用于分词。

###### `HTMLParser`

负责解析HTML成DOM树。

###### `HttpRequest`

使用Winsock2实现的Http Get请求。

###### `LinkedList`

双向链表模板，**实现了和`std::list`中接口相同的迭代器**。

###### `Logger`

调试日志的输出类。

###### `Stack`

**可以更换容器**（默认使用`ArrayList`）的栈模板。

######`StringConvert`

实现的字符串`char`和`wchar_t`之间的转换类，可以更换code page。

###### `Test`

单元测试类。

## 算法说明

- 通过Winsock2手写HTTP协议实现的Get请求。
- 使用KMP算法实现的字符串匹配（`BasicString<T>::find`）
- 使用栈构建出**HTML对应的完整DOM树**。
- 使用树遍历查找HTML中满足要求的标签。
- 使用C++11的右值引用优化数据结构的性能。
- 使用开散列的哈希实现的哈希表。

## 流程概述

1. 从`url.csv`中加载网址。
2. 发送Get请求获得网页。
3. 解析网页获得DOM树。
4. 使用`cQuery`定位需要的信息。
5. 使用反向分词法用哈希表进行分词。
6. 输出到`result.csv`中。

## 输入输出及操作相关说明

以./input/url.csv作为输入。

输出的result.csv为ANSI编码，字符集为GB2312，在./input目录中。

## 实验结果

在100个测试网页中有3个网页因没有权限访问无法解析。

输出的分词结果中正确的去除了停用词。

## 功能亮点说明

- 采用`doxygen`风格的注释。
- 实现了类似STL的接口和迭代器。
- 不仅实现了提取对应的信息，而且可以对整个HTML文档建立出DOM树，具备良好的日志和HTML错误处理机制，使用了检查机制防止内存泄漏。
- 自己实现了哈希表。

## 实验体会

感觉大作业主要是在考代码能力和工程的稳定性啊，对算法的要求不足。。。希望之后的大作业能够体现更多的数据结构和算法设计成分。

（今年是2017年了，不要再用VS2012作为标准啦，用VS2017或者不限制开发环境就太好了）

