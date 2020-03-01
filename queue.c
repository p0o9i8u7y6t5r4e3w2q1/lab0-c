#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

void free_ele(list_ele_t *ele)
{
    if (ele == NULL)
        return;
    free(ele->value);
    free(ele);
}

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* TODO: What if malloc returned NULL? */
    if (q == NULL)
        return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q == NULL)
        return;
    /* TODO: How about freeing the list elements and the strings? */
    /* Free queue structure */
    list_ele_t *ele = q->head;
    list_ele_t *tmp_ele = NULL;
    while (ele != NULL) {
        tmp_ele = ele->next;
        free_ele(ele);
        ele = tmp_ele;
    }
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (q == NULL)
        return false;

    list_ele_t *newh;
    /* TODO: What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL)
        return false;
    /* Don't forget to allocate space for the string and copy it */
    char *new_s = malloc(strlen(s) + 1);
    /* What if either call to malloc returns NULL? */
    if (new_s == NULL) {
        free(newh);
        return false;
    }
    strncpy(new_s, s, strlen(s) + 1);
    newh->value = new_s;
    newh->next = q->head;

    if (q->tail == NULL)
        q->tail = newh;
    q->head = newh;
    q->size += 1;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */

    if (q == NULL || s == NULL)
        return false;

    list_ele_t *newt;
    /* TODO: What should you do if the q is NULL? */
    newt = malloc(sizeof(list_ele_t));
    if (newt == NULL)
        return false;
    /* Don't forget to allocate space for the string and copy it */
    char *new_s = malloc(strlen(s) + 1);
    /* What if either call to malloc returns NULL? */
    if (new_s == NULL) {
        free(newt);
        return false;
    }
    strncpy(new_s, s, strlen(s) + 1);
    newt->value = new_s;
    newt->next = NULL;

    if (q->head == NULL)
        q->head = newt;
    else
        q->tail->next = newt;

    q->tail = newt;
    q->size += 1;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (q == NULL)
        return false;
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    list_ele_t *removed = q->head;
    q->head = q->head->next;
    if (removed == q->tail)
        q->tail = NULL;
    if (sp != NULL)
        strncpy(removed->value, sp, bufsize - 1);

    free_ele(removed);
    q->size -= 1;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (q == NULL)
        return 0;
    else
        return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (q == NULL || q->head == NULL || q->size == 1)
        return;
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    list_ele_t *ele = q->head;
    list_ele_t *prev_ele = NULL;
    list_ele_t *tmp_ele;
    q->tail = ele;
    while (ele != NULL) {
        tmp_ele = ele->next;
        ele->next = prev_ele;
        prev_ele = ele;
        ele = tmp_ele;
    }
    q->head = prev_ele;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    if (q == NULL || q->head == NULL || q->size == 1)
        return;
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    list_ele_t *cmp_tail = NULL;
    while (cmp_tail != q->head) {
        list_ele_t **now_pos = &(q->head);
        while ((*now_pos)->next != cmp_tail) {
            if (strcmp((*now_pos)->value, (*now_pos)->next->value) > 0) {
                // swap
                list_ele_t *now_ele = (*now_pos);
                (*now_pos) = now_ele->next;  // now *now_dptr is next ele

                now_ele->next = (*now_pos)->next;
                (*now_pos)->next = now_ele;
            }
            now_pos = &((*now_pos)->next);
        }
        if (cmp_tail == NULL)
            q->tail = *now_pos;  // only first time
        cmp_tail = (*now_pos);
    }
}
