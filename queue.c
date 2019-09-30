/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q != (queue_t *) NULL) {
        q->head = NULL;
        q->tail = NULL;
        q->length = 0UL;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */

    if (q == NULL) {
        return;
    }

    if (q->length > 0) {
        list_ele_t *e = q->head;
        list_ele_t *tmp = q->head->next;

        while (e != NULL) {
            if (e->value != NULL) {
                free(e->value);  // free string
            }
            free(e);  // free list element
            e = tmp;
            if (tmp != NULL) {
                tmp = tmp->next;
            }
        }
    }

    free(q);  // free queue object
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    char *str;
    size_t len;

    /* q checked */
    if (q == (queue_t *) NULL || s == (char *) NULL) {
        return false;
    }

    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL) {
        return false;
    }

    len = strlen(s) + 1;
    str = malloc(sizeof(len) << 3);  // len * 8
    if (str == NULL) {
        free(newh);
        return false;
    }
    len--;
    memcpy(str, s, len);
    str[len] = '\0';

    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    newh->value = str;
    newh->next = q->head;
    q->head = newh;
    if (q->tail == NULL) {
        q->tail = newh;
    }
    q->length++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */

    list_ele_t *newt;
    char *str;
    size_t len;

    /* q checked */
    if (q == (queue_t *) NULL || s == (char *) NULL) {
        return false;
    }

    /* alloc the element space */
    newt = malloc(sizeof(list_ele_t));
    if (newt == NULL) {
        return false;
    }

    /* alloc the string copy space */
    len = strlen(s);
    str = malloc(sizeof(len + 1) << 3);  // len * 8
    if (str == NULL) {
        free(newt);
        return false;
    }

    /* copy string to element */
    memcpy(str, s, len);
    str[len] = '\0';
    newt->value = str;

    /* insert to queue */
    newt->next = NULL;
    if (q->length > 0) {
        q->tail->next = newt;
    } else {
        q->head = newt;
    }
    q->tail = newt;
    q->length++;

    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* args checked */
    if (q == NULL || q->head == NULL) {
        return false;
    }

    list_ele_t *e = q->head;

    if (sp != NULL) {
        /* get the string length */
        size_t len = strlen(e->value);
        if (--bufsize < len) {
            len = bufsize;
        }

        /* copy string to sp */
        memcpy(sp, e->value, len);
        *(sp + len) = '\0';
    }

    /* shift head to next */
    if (e->next == NULL) {
        q->tail = NULL;
    }
    q->head = q->head->next;
    q->length--;

    /* release space (list element / string) */
    free(e->value);
    free(e);

    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    return (q != NULL) ? q->length : 0;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* queue length is 0 or 1, not reversed. */
    if (q == NULL || q->length < 2) {
        return;
    }

    list_ele_t *eleh = q->head;  // list head
    list_ele_t *elet = NULL;     // list tail
    list_ele_t *tmp = NULL;      // reversr temp

    /* reverse */
    while (eleh != NULL) {
        tmp = eleh->next;
        eleh->next = elet;
        elet = eleh;
        eleh = tmp;
    }

    /* change head / tail pointer */
    tmp = q->tail;
    q->tail = q->head;
    q->head = tmp;
}
