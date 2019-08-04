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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q != NULL) {
        q->head = NULL;
        q->tail = q->head;
        q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{   
    if (q == NULL) {
        return;
    }
    /* How about freeing the list elements and the strings? */
    list_ele_t *access = q->head;

    while (access != NULL) {
        q->head = access;
        access = access->next;
        free(q->head->value);
        free(q->head);
        q->size--;
    }
    access = NULL;
    /* Free queue structure */
    free(q);
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
    /* What should you do if the q is NULL? */
    if (q == NULL) {
      return false;
    }
    
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL) {
        return false;
    }
    /* Don't forget to allocate space for the string and copy it */
    newh->value = (char *) malloc(strlen(s) + 1);
    if (!newh->value) {
        free(newh);
        return false;
    }
    strcpy(newh->value, s);
    /* What if either call to malloc returns NULL? */
    newh->next = q->head;
    if (q->size == 0) {
        q->tail = newh;
    }
    q->head = newh;
    q->size++;
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
    if (q == NULL) {
        return false;
    }
    
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL) {
        return false;
    }
    newh->value = (char *) malloc(strlen(s) + 1);
    if (newh->value == NULL) {
        free(newh);
        return false;
    }
    strcpy(newh->value, s);
    newh->next = NULL;
    if (q->size != 0) {
        q->tail = newh;
    } else {
        q->head = newh;
    }
    q->tail = newh;
    q->size++;
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
    /* You need to fix up this code. */
    if (q == NULL || q->size == 0) {
        return false;
    }
    int size;
    if (sp != NULL) {
        size = strlen(q->head->value);
        if (size > bufsize - 1) {
            size = bufsize - 1;
        }
        strncpy(sp, q->head->value, size);
        sp[size] = '\0';
    }
    
    list_ele_t *h = q->head;
    q->head = q->head->next;
    sp = h->value;
    free(h->value);
    free(h);
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
    return (q != NULL)? q->size : 0;
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
    /* You need to write the code for this function */
    // if (q == NULL || q->size == 0) {
    //     return;
    // }

    // list_ele_t *reverse = NULL;
    // list_ele_t *p = q->head;

    // while (!p) {
    //     list_ele_t *nex = p->next;
    //     p->next = reverse;
    //     if (!reverse) {
    //         q->tail = p;
    //     }
    //     reverse = p;
    //     p = nex;
    // }

    if (q == NULL)
        return;
    if (q->head == NULL)
        return;

    list_ele_t *p = NULL;
    list_ele_t *t = q->head;
    list_ele_t *r = q->head->next;
    while (t != NULL) {
        t->next = p;
        p = t;
        t = r;
        if (r != NULL)
            r = r->next;
    }
    q->tail = q->head;
    q->head = p;
}

