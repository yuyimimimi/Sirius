#include "display_private_def.h"
#include <stdlib.h>

static void free_display_object_t(display_object_t_list_t *node)
{
    free(node->display_object_node);
    free(node);
}


static void reset_num()
{
    display_object_t_list_t *probe_node = display_object_list_head;
    int i = 0;
    while(probe_node != NULL)
    {
        probe_node->object_id = i;
        probe_node = probe_node->next;
        i++;
    }
}

static int Iterators_num = 0;

int insert_node_into_list(display_object_t *node)
{
    display_object_t_list_t *new_node;
    new_node = (display_object_t_list_t*) malloc(sizeof(display_object_t_list_t));
    if(new_node == NULL)
    {
        printf("Memory allocation failed in insert_node_into_list\n");
        return -No_memory_error;
    }
    new_node->display_object_node = node;
    new_node->next = NULL;

    display_object_t_list_t *probe_node = display_object_list_head;
    int i = 0;
    while(probe_node != NULL)
    {
        probe_node = probe_node->next;
        i++;
    }
    probe_node = new_node;
    probe_node->object_id = i;
    return i;
}


int display_object_list_release_nide_by_num(int num)
{
    display_object_t_list_t *probe_node = display_object_list_head;
    display_object_t_list_t *node;
    if(probe_node == NULL) return -not_usefull_error;
    while (probe_node != NULL)
    {
        if(probe_node->object_id == num -1 && probe_node->next != NULL)
        {
            node = probe_node->next;
            probe_node->next = node->next;
            free_display_object_t(&node);
            reset_num();
            return 0;
        }
    }
    return -not_usefull_error;
}


display_object_t *get_object_by_id(int id)
{
    display_object_t_list_t *probe_node = display_object_list_head;
    if(probe_node == NULL) return NULL;
    while(probe_node != NULL)
    {
        if(probe_node->object_id == id)
        {
            return probe_node->display_object_node;
        }
    }
    return NULL;
}

display_object_t *display_Iterators(void)
{
    if(display_object_list_head == NULL) return NULL;
    display_object_t *probe_node;
    probe_node = get_object_by_id(Iterators_num);
    if(probe_node == NULL)
    {
        return NULL;
    }
    Iterators_num++;
    return probe_node;
}

void reset_Iterators(void)
{
    Iterators_num = 0;
}


