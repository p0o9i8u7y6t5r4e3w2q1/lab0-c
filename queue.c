#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
void printList(list_ele_t *start)
{
    printf("[ ");
    list_ele_t *ele = start;
    while (ele != NULL) {
        printf(ele->value);
        printf(" ");
        ele = ele->next;
    }
    printf("]\n");
}
*/

/*
new
it dkaec
it dakec
it adkav
it ckaec
it daekaf
it adjqwf
it heiqqd
it kedai
sort
*/
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
    int size = strlen(s) + 1;
    char *new_s = malloc(size);
    /* What if either call to malloc returns NULL? */
    if (new_s == NULL) {
        free(newt);
        return false;
    }
    strncpy(new_s, s, size);
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
    if (q == NULL || q->head == NULL || sp == NULL)
        return false;

    list_ele_t *removed = q->head;
    q->head = q->head->next;
    if (removed == q->tail)
        q->tail = NULL;
    removed->next = NULL;

    if (removed->value != NULL) {
        int copy_len = strlen(removed->value);
        if (bufsize - 1 < copy_len)
            copy_len = bufsize - 1;

        strncpy(sp, removed->value, copy_len);
        sp[copy_len] = '\0';
    }

    free_ele(removed);
    q->size--;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    return (q == NULL) ? 0 : q->size;
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
list_ele_t *pop_next(queue_t *q, list_ele_t *prev)
{
    if (q == NULL)
        return NULL;

    list_ele_t **change_pos = (prev == NULL) ? &(q->head) : &(prev->next);
    list_ele_t *removed = *change_pos;
    *change_pos = removed->next;
    removed->next = NULL;
    if (q->tail == removed)
        q->tail = prev;
    q->size--;
    return removed;
}

void push_next(queue_t *q, list_ele_t *prev, list_ele_t *new_ele)
{
    if (q == NULL || prev == NULL || new_ele == NULL)
        return;

    list_ele_t *next_ele = prev->next;
    prev->next = new_ele;
    new_ele->next = next_ele;
    if (q->tail == prev)
        q->tail = new_ele;
    q->size++;
}

void partition(queue_t *q, list_ele_t *prefix, list_ele_t *suffix)
{
    if (q == NULL)
        return;

    list_ele_t *pivot = (prefix == NULL) ? q->head : prefix->next;
    list_ele_t *separator = pivot;
    list_ele_t *prev_ele = pivot;

    while (prev_ele->next != suffix) {
        if (strcmp(pivot->value, prev_ele->next->value) > 0) {
            // pivot > prev_ele->next
            if (separator != prev_ele) {
                // prev_ele->next move to separator->next
                // separator = separator->next
                // next time check prev_ele->next
                list_ele_t *now_ele = pop_next(q, prev_ele);
                push_next(q, separator, now_ele);
            } else {
                // when separator == prev_ele
                // next time check prev_ele->next
                // separator = separator->next
                prev_ele = prev_ele->next;
            }
            separator = separator->next;
        } else
            prev_ele = prev_ele->next;
    }

    if (separator != pivot) {
        pivot = pop_next(q, prefix);
        push_next(q, separator, pivot);
        partition(q, prefix, pivot);
    }

    if (pivot->next != suffix) {
        partition(q, pivot, suffix);
    }
}

// q has greater than one elements
void quick_sort(queue_t *q)
{
    partition(q, NULL, NULL);
}
*/


void split_list(list_ele_t *source, list_ele_t **list1, list_ele_t **list2)
{
    list_ele_t *fast_ele = source->next;
    list_ele_t *slow_ele = source;
    while (fast_ele != NULL) {
        fast_ele = fast_ele->next;
        if (fast_ele != NULL) {
            fast_ele = fast_ele->next;
            slow_ele = slow_ele->next;
        }
    }

    *list1 = source;
    *list2 = slow_ele->next;
    slow_ele->next = NULL;
}

// input start address, output end element
// head not NULL
list_ele_t *split_and_merge(list_ele_t **head)
{
    if (*head == NULL || (*head)->next == NULL)
        return *head;

    list_ele_t *left = NULL;
    list_ele_t *right = NULL;
    split_list(*head, &left, &right);

    /* get end element */
    list_ele_t *left_tail = split_and_merge(&left);
    list_ele_t *right_tail = split_and_merge(&right);

    list_ele_t *tail_ele = NULL;
    if (strcmp(left->value, right->value) < 0) {
        *head = tail_ele = left;
        left = left->next;
    } else {
        *head = tail_ele = right;
        right = right->next;
    }

    while (true) {
        if (left == NULL) {
            tail_ele->next = right;
            return right_tail;
        } else if (right == NULL) {
            tail_ele->next = left;
            return left_tail;
        } else if (strcmp(left->value, right->value) < 0) {
            tail_ele->next = left;
            left = left->next;
        } else {
            tail_ele->next = right;
            right = right->next;
        }
        tail_ele = tail_ele->next;
    }
    return tail_ele;
}

// q has greater than one elements
void merge_sort(queue_t *q)
{
    list_ele_t *tail_ele = split_and_merge(&(q->head));
    q->tail = tail_ele;
}

// q has greater than one elements
/*
void bubble_sort(queue_t *q)
{
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
*/

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    if (q == NULL || q->head == NULL || q->size == 1)
        return;
    merge_sort(q);
    // bubble_sort(q);
    // quick_sort(q);
}
