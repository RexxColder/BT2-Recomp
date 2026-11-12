#include "common.h"
#include "sys/list.h"

/* Copies the head, tail and count of a doubly linked list. */
void List_Copy(List *dst, List *src);

/* Copies the head, tail and count of a singly linked list. */
void SList_Copy(SList *dst, SList *src);

/* Empties a list. */
void List_Init(List *list);

/* First node, or NULL. */
ListNode *List_GetHead(List *list) {
    ListNode *node = NULL;

    if (list != NULL) {
        node = list->head;
    }
    return node;
}

/* Last node, or NULL. */
ListNode *List_GetTail(List *list) {
    ListNode *node = NULL;

    if (list != NULL) {
        node = list->tail;
    }
    return node;
}

/* Number of nodes. */
s32 List_GetCount(List *list) {
    s32 count = 0;

    if (list != NULL) {
        count = list->count;
    }
    return count;
}

/* Links a node in front of the head. */
void List_PushFront(List *list, ListNode *node) {
    if (list->head != NULL) {
        list->head->prev = node;
        node->prev = NULL;
        node->next = list->head;
        list->head = node;
    } else {
        list->head = node;
        list->tail = node;
        node->prev = NULL;
        node->next = NULL;
    }
    list->count++;
}

/* Links a node after the tail. */
void List_PushBack(List *list, ListNode *node) {
    if (list->head != NULL) {
        list->tail->next = node;
        node->prev = list->tail;
        node->next = NULL;
        list->tail = node;
    } else {
        list->head = node;
        list->tail = node;
        node->prev = NULL;
        node->next = NULL;
    }
    list->count++;
}

/* Moves every node of other to the front of list, leaving other empty. */
void List_PrependList(List *list, List *other);

/* Moves every node of other to the back of list, leaving other empty. */
void List_AppendList(List *list, List *other);

/* Links node in front of pos. Declared non-void but returns nothing (the calls below are not tail calls). */
s32 List_InsertBefore(List *list, ListNode *pos, ListNode *node) {
    if (pos != NULL) {
        if (list->head == pos) {
            List_PushFront(list, node);
        } else {
            node->prev = pos->prev;
            node->next = pos;
            if (pos->prev != NULL) {
                pos->prev->next = node;
            }
            pos->prev = node;
            list->count++;
        }
    }
}

/* Links node behind pos. Declared non-void but returns nothing, like List_InsertBefore. */
s32 List_InsertAfter(List *list, ListNode *pos, ListNode *node) {
    if (pos != NULL) {
        if (list->tail == pos) {
            List_PushBack(list, node);
        } else {
            node->prev = pos;
            node->next = pos->next;
            if (pos->next != NULL) {
                pos->next->prev = node;
            }
            pos->next = node;
            list->count++;
        }
    }
}

/* Unlinks a node and returns it. */
ListNode *List_Remove(List *list, ListNode *node) {
    if (node != NULL) {
        ListNode *prev = node->prev;
        ListNode *next = node->next;

        if (prev == NULL) {
            list->head = next;
        } else {
            prev->next = next;
        }
        if (next == NULL) {
            list->tail = prev;
        } else {
            next->prev = prev;
        }
        node->next = NULL;
        node->prev = NULL;
        list->count--;
    }
    return node;
}

/* Unlinks and returns the head. */
ListNode *List_PopFront(List *list) {
    return List_Remove(list, list->head);
}

/* Unlinks and returns the tail. */
ListNode *List_PopBack(List *list) {
    return List_Remove(list, list->tail);
}

/* Node before this one, or NULL. */
ListNode *List_GetPrev(ListNode *node);

/* Node after this one, or NULL. */
ListNode *List_GetNext(ListNode *node);

/* 1 when the node is linked in the list. */
s32 List_Contains(List *list, ListNode *node);

/* Empties a singly linked list. */
void SList_Init(SList *list);

/* First node, or NULL. */
SListNode *SList_GetHead(SList *list);

/* Last node, or NULL. */
SListNode *SList_GetTail(SList *list);

/* Number of nodes. */
s32 SList_GetCount(SList *list);

/* Links a node in front of the head. */
void SList_PushFront(SList *list, SListNode *node);

/* Links a node after the tail. */
void SList_PushBack(SList *list, SListNode *node);

/* Moves every node of other to the front of list, leaving other empty. */
void SList_PrependList(SList *list, SList *other);

/* Moves every node of other to the back of list, leaving other empty. */
void SList_AppendList(SList *list, SList *other);

/* Unlinks and returns the head, or NULL when empty. */
SListNode *SList_PopFront(SList *list);

/* Node after this one, or NULL. */
SListNode *SList_GetNext(SListNode *node);

/* 1 when the node is linked in the list. */
s32 SList_Contains(SList *list, SListNode *node);
