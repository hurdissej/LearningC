#include <lcthw/datastructures/list.h>
#include <lcthw/dbg.h>

List *List_create()
{
    return calloc(1, sizeof(List));
}

void List_destroy(List *list)
{
    LIST_FOREACH(list, first, next, cur)
    {
        if(cur->prev)
        {
            free(cur->prev);
        }
    }
    free(list->last);
    free(list);
}

void List_clear(List *list)
{
    LIST_FOREACH(list, first, next, cur)
    {
        free(cur->value);
    }
}

void List_clear_destroy(List *list)
{
    List_clear(list);
    List_destroy(list);
}

void List_push(List *list, void *value)
{
    ListNode * newNode = calloc(1, sizeof(ListNode));
    check_mem(newNode);

    newNode->value = value;
    
    if(list->last == NULL)
    {
        list->first = newNode;
        list->last = newNode;
    } else {
        list->last->next = newNode;
        newNode->prev = list->last;
        list->last = newNode;
    }

    list->count ++;

    error:
        return;
}

void *List_pop(List *list)
{
    ListNode * lastNode = list->last;
    return List_remove(list, lastNode);
}

void List_unshift(List *list, void *value)
{
    ListNode * node = calloc(1, sizeof(ListNode));
    check_mem(node);
    node->value = value;

    if(list->first == NULL)
    {
        list->first= node;
        list->last=node;

    } else {
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
    }
        list->count++;

    error:
    return;
}

void *List_shift(List * list)
{
    ListNode *node= list->first;
    return node != NULL ? List_remove(list, node): NULL;
}

void *List_remove(List * list, ListNode * node)
{
    void * result = NULL;
    check(list->first && list-> last, "List is empty");
    check(node, "node can't be NULL");

    if(node == list->first && node == list->last)
    {
        list->first = NULL;
        list->last = NULL;
    } else if (node == list->first)
    {
        list->first = node->next;
        check(list->first != NULL, "Invalid list, got a first that is null");
        list->first->prev = NULL;
    } else if (node == list->last)
    {
        list->last = node->prev;
        check(list->last != NULL, "Invalid list, got a last that is null");
        list->last->next = NULL;
    } else 
    {
        ListNode * after = node->next;
        ListNode * before = node->prev;
        after->prev = before;
        before->next = after;
    }

    list->count--;
    result = node->value;
    free(node);

    error:
        return result;
}