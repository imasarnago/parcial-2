#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue {
    size_t size;
    struct s_node *pq;
};

struct s_node {
    pqueue_elem elem;
    struct s_node *next;
    unsigned int prioridad;
};

static struct s_node *create_node(pqueue_elem e, unsigned int priority) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);

    new_node->elem = e;
    new_node->next = NULL;
    new_node->prioridad = priority;

    assert(e==e && priority == priority); // BORRAR ESTE ASSERT
    return new_node;
}

static struct s_node *destroy_node(struct s_node *node) {
    assert(node != NULL);
    

    node->next =NULL;
    free (node);
   

    assert(node == NULL);
    return node;
}


static bool invrep(pqueue q) {
    

    bool b;
    while (q->pq->next != NULL) {
        b = (q->pq->prioridad <= q->pq->next->prioridad);
        }
    return b;
}

pqueue pqueue_empty(void) {
    pqueue q=NULL;
    q = malloc (sizeof(struct s_pqueue));

    q->pq =  NULL;
    q->size = 0;

    assert(invrep(q));
    
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, unsigned int priority) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e, priority);


    if (q->pq == NULL) {
        q->pq = new_node;
    }
    else {
        struct s_node *p = q->pq;
        while (p->next != NULL) {
        p = p->next;
        }
        p->next = new_node;
    }
    q->size++;
    assert (invrep(q) && !pqueue_is_empty(q));


    return q;
}

bool pqueue_is_empty(pqueue q) {
    bool b = (q->pq == NULL);
    assert(invrep); 
    return b;
}

pqueue_elem pqueue_peek(pqueue q) {
    unsigned int may_valor = 0;  
    pqueue_elem elementoM;
    elementoM = 0;

    struct s_node *p = q->pq;
    if (p->prioridad >= may_valor) {
            elementoM = p->elem;
    }
    while (p->next != NULL) {
        p = p->next;
        if (p->prioridad > may_valor) {
            elementoM = p->elem;
        }
    }



    assert(invrep); 
    return elementoM;
}

unsigned int pqueue_peek_priority(pqueue q) {
    
    unsigned int may_valor = 0;  

    struct s_node *p = q->pq;
    if (p->prioridad >= may_valor) {
            may_valor = p->prioridad;
    }
    while (p->next != NULL) {
        p = p->next;
        if (p->prioridad > may_valor) {
            may_valor = p->prioridad;
        }
    }



    assert(invrep); 
    return may_valor;
}

unsigned int pqueue_size(pqueue q) {
    assert(invrep(q));
    unsigned int size=0;
    
    size = q->size;
    assert(invrep);
    return size;
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep);

    struct s_node *matame=q->pq;
    q->pq = q->pq->next;
    matame = destroy_node(matame);
    q->size--;

    assert(invrep);
    return q;
}


pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    struct s_node *node=q->pq;
    while (node != NULL) {
        struct s_node *killme=node;
        node = node->next;
        killme = destroy_node(killme);
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}