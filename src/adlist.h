/* adlist.h - A generic doubly linked list implementation
 *
 * Copyright (c) 2006-2012, Salvatore Sanfilippo <antirez at gmail dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Redis nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __ADLIST_H__
#define __ADLIST_H__

/* Node, List, and Iterator are the only data structures used currently. */

/**
 * 链表节点结构体
 */
typedef struct listNode {
    // 前置节点
    struct listNode *prev;
    // 后置节点
    struct listNode *next;
    // 节点的值 void * 表示可以存储任意类型
    void *value;
} listNode;

typedef struct listIter {
    listNode *next;
    int direction;
} listIter;

/**
 * 链表
 */
typedef struct list {
    // 头节点
    listNode *head;
    // 尾节点
    listNode *tail;
    // 节点复制函数
    void *(*dup)(void *ptr);
    // 节点释放函数
    void (*free)(void *ptr);
    // 节点对比函数
    int (*match)(void *ptr, void *key);
    // 节点数量
    unsigned long len;
} list;

/* Functions implemented as macros */

/**
 * 返回链表的长度
 */
#define listLength(l) ((l)->len)

/**
 * 返回链表的头节点
 */
#define listFirst(l) ((l)->head)

/**
 * 返回链表的尾节点
 */
#define listLast(l) ((l)->tail)

/**
 * 返回给定节点的前一个节点
 */
#define listPrevNode(n) ((n)->prev)

/**
 * 返回给定节点的下一个节点
 */
#define listNextNode(n) ((n)->next)

/**
 * 返回给定节点的值
 */
#define listNodeValue(n) ((n)->value)

/**
 * 将给定的函数设置为链表的节点复制函数
 */
#define listSetDupMethod(l,m) ((l)->dup = (m))

/**
 * 将给定的函数设置为链表的节点释放函数
 */
#define listSetFreeMethod(l,m) ((l)->free = (m))

/**
 * 将给定的函数设置为链表的节点对比函数
 */
#define listSetMatchMethod(l,m) ((l)->match = (m))

/**
 * 返回链表当前正在使用的节点复制函数
 */
#define listGetDupMethod(l) ((l)->dup)
#define listGetFree(l) ((l)->free)
#define listGetMatchMethod(l) ((l)->match)

/* Prototypes */
/**
 * 创建一个不包含任何节点的新链表
 * @return
 */
list *listCreate(void);

/**
 * 释放给定的链表，回收分配内存
 */
void listRelease(list *list);

/**
 * 清空链表
 * @param list
 */
void listEmpty(list *list);

/**
 * 将一个包含给定值的新节点添加到列表表头
 * @param list
 * @param value
 * @return
 */
list *listAddNodeHead(list *list, void *value);

/**
 * 将一个包含给定值的新节点添加到列表表尾
 * @param list
 * @param value
 * @return
 */
list *listAddNodeTail(list *list, void *value);

/**
 * 将一个包含给定值的新节点添加到指定链表节点的前或者后
 */
list *listInsertNode(list *list, listNode *old_node, void *value, int after);

/**
 * 删除链表节点
 * @param list
 * @param node
 */
void listDelNode(list *list, listNode *node);
listIter *listGetIterator(list *list, int direction);
listNode *listNext(listIter *iter);
void listReleaseIterator(listIter *iter);

/**
 * 复制链表的副本
 * @param orig
 * @return
 */
list *listDup(list *orig);
listNode *listSearchKey(list *list, void *key);
listNode *listIndex(list *list, long index);
void listRewind(list *list, listIter *li);
void listRewindTail(list *list, listIter *li);
void listRotate(list *list);
void listJoin(list *l, list *o);

/* Directions for iterators */
#define AL_START_HEAD 0
#define AL_START_TAIL 1

#endif /* __ADLIST_H__ */
