#include "common.h"
#include "sys/heap.h"
#include "sys/queue.h"

extern void *memset(void *dst, s32 value, u32 size);

/* Takes a node from the free list, else the next unused one of the pool; NULL when full. */
QueueNode *Queue_AllocNode(Queue *queue) {
    QueueNode *node;

    if (queue->freeList != NULL) {
        node = queue->freeList;
        queue->freeList = node->next;
    } else if (queue->used < queue->capacity - 1) {
        node = &queue->nodes[queue->used++];
    } else {
        return NULL;
    }
    return node;
}

/* Last queued node, or NULL when empty. */
QueueNode *Queue_GetTail(Queue *queue) {
    QueueNode *tail = NULL;
    QueueNode *node = queue->head;

    while (node != NULL) {
        tail = node;
        node = node->next;
    }
    return tail;
}

/* Clears the queue and allocates its node pool. */
void Queue_Init(Queue *queue, s32 capacity);

/* Frees the node pool. */
void Queue_Destroy(Queue *queue);

/* Drops every queued value. */
void Queue_Clear(Queue *queue);

/* Appends a value; returns it, or NULL when the queue is full. */
void *Queue_Push(Queue *queue, void *value);

/* Oldest value without removing it, or NULL when empty. */
void *Queue_Peek(Queue *queue);

/* Removes and returns the oldest value, or NULL when empty. The node goes back on the free list. */
void *Queue_Pop(Queue *queue);

/* Number of queued values. */
s32 Queue_Count(Queue *queue);
