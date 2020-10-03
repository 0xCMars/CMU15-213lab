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
    if (q == NULL)
        return NULL;
    q->head = NULL;
    q->back = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
  /* How about freeing the list elements and the strings? */
  if (q != NULL)
  {
    list_ele_t *oldh = q->head;
    while(oldh != NULL)
    {
      free(oldh->value);
      q->head = q->head->next;
      free(oldh);
      oldh = q->head;
    }
    q->back = NULL;
    /* Free queue structure */
    free(q);
  }
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
    if (q == NULL)
      return false;
    
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL)
      return false;
    
    /* Don't forget to allocate space for the string and copy it */
    /* Don't forger the last '\0' is not count in strlen, so you have to plus 1 */
    newh->value = malloc(sizeof(char) * strlen(s)+1);
    /* What if either call to malloc returns NULL? */
    if (newh->value == NULL)
    {
      free(newh);
      return false;
    }

    strcpy(newh->value,s);
    newh->next = q->head;
    q->head = newh;
    q->size += 1;

    /* if the size of list is 0, which mean q->back is not point to the last one, so point it */
    /* otherwise q->back is not need to be change. */
    if (q->back == NULL)
    {
      q->back = newh;
    }
    
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
    if (q == NULL)
      return false;
    
    list_ele_t *newt = malloc(sizeof(list_ele_t));
    if (newt == NULL)
      return false;
    newt->value = malloc(sizeof(char) * strlen(s)+1);
    if (newt->value == NULL)
    {
      free(newt);
      return false;
    }

    strcpy(newt->value,s);
    newt->next=NULL;

    if (q->head == NULL)
    {
      q->head = newt;
      q->back = newt;
    }
    else
    {
      q->back->next = newt;
      q->back = newt;
    }
    q->size += 1;
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
    if (q == NULL || q->head == NULL)
      return false;
    if (sp != NULL)
    {
      strncpy(sp,q->head->value,bufsize-1);
      sp[bufsize-1] = '\0';
    }
    
    list_ele_t *oldh = q->head;
    q->head = q->head->next;

    free(oldh->value);
    free(oldh);
    
    q->size -= 1;
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
    if (q == NULL || q->head == q->back)
      return 0;
    else
      return q->size;
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
    if (q != NULL) 
    {
      if (q->head != NULL)
      {
        /* not use stack(array) because stack need a lot space */
        /* one time we only focus on three connected node */
        list_ele_t *q_tail = q->head;
        list_ele_t *cur_q_node = q->head->next; 
        list_ele_t *q_head = q->head->next->next;
        while (q_head != NULL)
        {
          cur_q_node->next = q_tail;
          q_tail = cur_q_node;
          cur_q_node = q_head;
          q_head = q_head->next;
        }
        cur_q_node->next = q_tail;
        q->back = q->head;
        q->back->next = NULL;
        q->head = cur_q_node;
      }
    }

}

