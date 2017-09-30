/*d 
 * Código para diagnostico de conhecimento básico em C.
 * Desenvolvido para o curso CET-088, CET-082
 * Modificado por Leard Fernandes, 2017
 * Developed by R. E. Bryant, 2017
*/

 /*
  * Este programa implementa uma fila que suporta ambas as operações FIFO e LILO.
  *
  * Ele utiliza uma lista unicamente ligada para representar o conjunto de
  * elementos da fila
*/

#include <stdlib.h>
#include <stdio.h>

#include "harness.h"
#include "queue.h"

/*
  Cria uma fila vazia.
  Retorna NULL se o espaço na puder ser alocado.
*/
queue_t *q_new()
{
	 
    queue_t *q =  malloc(sizeof(queue_t));
    /* E se malloc retornar NULL? */
    if(q==NULL){
    	return NULL;	
    } 
    q->head = NULL;
    q->tail = q->head;
    q->size = 0;
    return q;
    
}

/*  Libera todo o espaço utilizado pela fila. */
void q_free(queue_t *q)
{   list_ele_t *aux = q->head;
	if(q!=NULL){
        while(q->head!=NULL){
            q->head = q->head->next;
            free(aux);
            aux = q->head;
        }

        /* Libera a estrutura da fila */
        free(q);
	}
    
}

/*
  Tenta inserir o elemento na cabeça da fila.
  Retorna true se houve sucesso
  Retorna false se q é NULL ou não foi possível alocar espaço
*/
bool q_insert_head(queue_t *q, int v)
{
    list_ele_t *newh;
    /* O que você deverá fazer se q é NULL ? */
    if(q != NULL) {
 
	    newh = malloc(sizeof(list_ele_t));
	    /* E se malloc retornar NULL? */
	    if(newh == NULL) return false;
	    newh->value = v;
	    newh->next = q->head;
	    if(q->head == NULL){
	       q->tail = newh;     
	    }
	    q->head = newh;
	    q->size++;
	   
	    return true;
	}else
		return false;    
}


/*
  Tenta inserir o elemento na calda da fila.
  Retorna true se houve sucesso
  Retorna false se q é NULL ou não foi possível alocar espaço
*/
bool q_insert_tail(queue_t *q, int v)
{	list_ele_t *newh;
    /* O que você deverá fazer se q é NULL ? */
    if(q == NULL) {
    	return false;
    }
    newh = malloc(sizeof(list_ele_t));
    /* E se malloc retornar NULL? */
    if(newh == NULL){ 
    	return false;
    }
    newh->value = v;
    newh->next = NULL;
    if(q->tail != NULL) 
    	q->tail->next = newh;
    else
    	q->head = newh; 
    q->tail = newh;
    q->size++;
    return true;
    /* Você precisa escrever o código completo para esta função */
    /* lembre-se: Você deverá operar no tempo de O(1) */
}

/*
  Tenta remover o elemento na cabeça da fila.
  Retorna true se houve sucesso
  Retorna false se q é NULL ou vazia
  Se vp é não-NULL e o elemento removido, armazena o valor removido em *vp
  Qualquer armazenamento não utilizado deve ser liberado
*/
bool q_remove_head(queue_t *q, int *vp)
{   
	list_ele_t *aux = q->head;
    /* Você precisa consertar este código. */
    if (q == NULL || q->head == NULL) return false;
    else if(vp != NULL){
        q->head = q->head->next;
        *vp = aux->value;
        free(aux);
        q->size--; 
        if(q->size < 1){
        	q->head = NULL;
        	q->tail = NULL;
        }
        return true;
    }else
    	return false;
}

/*
  Retorna o número de elementos na fila.
  Retorna 0 se q é NULL ou vazia
*/
int q_size(queue_t *q)
{  
        if(q == NULL || q->head == NULL){
        	return 0;
        }else
			return q->size;
	
  /* Você precisa escrever o código completo para esta função */
  /* lembre-se: Você deverá operar no tempo de O(1) */
}

/*
  Inverte os elementos na fila.

  Sua implementação não dever alocar ou liberar quaisquer elementos (e.g., pela
  chamada de q_insert_head ou q_remove_head). Ao invés disso, ela deverá
  modificar os ponteiros na estrutura de dados existente.
*/
void q_reverse(queue_t *q)
{
  list_ele_t *aux;	
  if(q!=NULL && q->head !=NULL){
	  while(q->head != q->tail){
	  	   aux=q->head; 
	       q->head = q->head->next;
	       aux->next = q->tail->next;
	       q->tail->next = aux; 	
	    }
	  aux=q->head;
	  while(aux->next!=NULL){
	      aux=aux->next;
	  }	
	  q->tail=aux;
	}  
}