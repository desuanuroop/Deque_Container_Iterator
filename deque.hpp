#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
using namespace std;
#define base_name "Deque_"
#define Deque_DEFINE(t)											\
	struct Deque_##t;										\
	void Deque_##t##_ctor(Deque_##t *, bool (*)(const t &, const t &));				\
	struct Deque_##t##_Iterator {									\
		Deque_##t *deq;										\
		int index;										\
		int length;										\
		void (*inc)(Deque_##t##_Iterator *);							\
		void (*dec)(Deque_##t##_Iterator *);							\
		t& (*deref)(Deque_##t##_Iterator *);							\
	};												\
	void Deque_##t##_Iterator_inc(Deque_##t##_Iterator *it){					\
		it->index++;										\
		if(it->index >= it->length)								\
			it->index = 0;									\
	}												\
	void Deque_##t##_Iterator_dec(Deque_##t##_Iterator *it){					\
		it->index--;										\
		if(it->index <0)									\
			it->index = it->length-1;							\
	}												\
	bool Deque_##t##_Iterator_equal(Deque_##t##_Iterator it, Deque_##t##_Iterator end){		\
		return (it.index != end.index)?0:1;							\
	}												\
	struct Deque_##t {										\
		t *data;										\
		t *tmpdata;										\
		char type_name[strlen(base_name#t)+1];							\
		int Size;										\
		int length;										\
		int front_pointer;									\
		int back_pointer;									\
		int (*size)(Deque_##t *deq);								\
		bool (*empty)(Deque_##t *deq);								\
		void (*push_back)(Deque_##t *,t ob);							\
		void (*push_front)(Deque_##t *, t ob);							\
		void (*pop_back)(Deque_##t *);								\
		void (*pop_front)(Deque_##t *);								\
		void (*extend_array)(Deque_##t *, int);							\
		t& (*front)(Deque_##t *);								\
		t& (*back)(Deque_##t *);								\
		Deque_##t##_Iterator (*begin)(Deque_##t *);						\
		Deque_##t##_Iterator (*end)(Deque_##t *);						\
		t& (*at)(Deque_##t *, int);								\
		void (*clear)(Deque_##t *);								\
		bool (*compare)(const t &, const t &);							\
		void (*dtor)(Deque_##t *);								\
	};												\
	int Deque_##t##_size(Deque_##t *deq) {								\
		return deq->Size;									\
	}												\
	bool Deque_##t##_empty(Deque_##t *deq) {							\
		return (deq->front_pointer == deq->back_pointer && deq->front_pointer == 0)? 1:0;	\
	}												\
	void Deque_##t##_extend_array(Deque_##t *deq, int leave){					\
		int i, index;										\
		deq->tmpdata = (t *)malloc(sizeof(t) * deq->length);					\
		memcpy(deq->tmpdata, deq->data, sizeof(t)*deq->length);					\
		free(deq->data);									\
		deq->data = (t *)malloc(sizeof(t) * (2 * deq->length));					\
		if(leave){										\
                        if(deq->front_pointer == deq->length-1)						\
                             index = (2* deq->length)-1;						\
                        else										\
			     index = deq->front_pointer+1;						\
		}											\
		else											\
			index = deq->front_pointer;							\
		if(deq->front_pointer < deq->back_pointer) {						\
			for(i=deq->front_pointer; i< deq->length;i++, index++)				\
				deq->data[index] = deq->tmpdata[i];					\
		}else {											\
			for(i=deq->front_pointer; i< deq->length;i++,index--)				\
				deq->data[index] = deq->tmpdata[i];					\
			for(i=0;i<deq->back_pointer;i++, index++)					\
				deq->data[i] = deq->tmpdata[i];						\
		}											\
		if(leave) {										\
                        if(deq->front_pointer == deq->length-1)						\
                             deq->front_pointer = (2 * deq->length)-2;					\
                        else										\
                             deq->back_pointer++;							\
                }											\
		deq->length = 2 * deq->length;								\
		free(deq->tmpdata);									\
	}												\
	void Deque_##t##_push_back(Deque_##t *deq,t ob){						\
		if(deq->back_pointer == deq->length){							\
			if(deq->front_pointer !=0 )							\
				deq->back_pointer = 0;							\
			else {										\
				deq->extend_array(deq,0);						\
			}										\
		}											\
		memcpy(&deq->data[deq->back_pointer++], &ob, sizeof(t));				\
		deq->Size++;										\
	}												\
	void Deque_##t##_push_front(Deque_##t *deq, t ob){						\
                if(deq->front_pointer ==0 && deq->Size != deq->length)                                  \
                        deq->front_pointer = deq->length -1;                                            \
		else if(deq->front_pointer == 0 || deq->front_pointer-1 == deq->back_pointer || (deq->front_pointer != 0 && deq->front_pointer == deq->back_pointer))		\
			deq->extend_array(deq,1);					         	\
		else											\
			deq->front_pointer--;								\
		memcpy(&deq->data[deq->front_pointer], &ob, sizeof(t));					\
		deq->Size++;										\
	}												\
	void Deque_##t##_pop_back(Deque_##t *deq){							\
		if(!deq->empty(deq)){									\
			deq->back_pointer--;								\
			deq->Size--;									\
		}											\
		if(deq->back_pointer == -1)								\
			deq->back_pointer = deq->front_pointer + deq->Size+1;				\
	}												\
	void Deque_##t##_pop_front(Deque_##t *deq){							\
		if(!deq->empty(deq)){									\
			deq->front_pointer++;								\
			deq->Size--;									\
		}											\
		if(deq->front_pointer >= deq->length)							\
			deq->front_pointer = 0;								\
	}												\
	t& Deque_##t##_front(Deque_##t *deq){								\
		return deq->data[deq->front_pointer];							\
	}												\
	t& Deque_##t##_back(Deque_##t *deq){								\
		return deq->data[deq->back_pointer-1];							\
	}												\
        t& Deque_##t##_Iterator_deref(Deque_##t##_Iterator *it){					\
		return it->deq->data[it->index];							\
	}						                                                \
	Deque_##t##_Iterator Deque_##t##_begin(Deque_##t *deq){						\
		return Deque_##t##_Iterator{deq, deq->front_pointer, deq->length, &Deque_##t##_Iterator_inc, &Deque_##t##_Iterator_dec, &Deque_##t##_Iterator_deref};\
	}												\
	Deque_##t##_Iterator Deque_##t##_end(Deque_##t *deq){						\
		return Deque_##t##_Iterator{deq, deq->back_pointer, deq->length, &Deque_##t##_Iterator_inc, &Deque_##t##_Iterator_dec, &Deque_##t##_Iterator_deref};\
	}												\
	t& Deque_##t##_at(Deque_##t *deq, int index){							\
                if(deq->Size != 0)                                                                      \
		     index = (index + deq->front_pointer)%deq->length;					\
		return deq->data[index];								\
	}												\
	bool Deque_##t##_equal(Deque_##t deq1, Deque_##t deq2){						\
		if(deq1.Size == deq2.Size) {								\
			int i;										\
			for(i=0;i<deq1.Size;i++){							\
				if(memcmp(&deq1.at(&deq1, i), &deq2.at(&deq2, i), sizeof(t)))		\
					return 0;							\
			}										\
			return 1;									\
													\
		}else											\
			return 0;									\
	}												\
	void Deque_##t##_clear(Deque_##t *deq){								\
		free(deq->data);									\
		deq->data = NULL;									\
		Deque_##t##_ctor(deq, deq->compare);							\
	}												\
	void Deque_##t##_dtor(Deque_##t *deq){								\
		free(deq->data);									\
		deq->data = NULL;									\
	}												\
	void Deque_##t##_ctor(Deque_##t *deq, bool (*fp)(const t &, const t &)) {			\
		strcpy(deq->type_name, base_name#t);\
		deq->Size = 0;										\
		deq->length = 10;									\
		deq->data = (t *)calloc(deq->length, sizeof(t));					\
		deq->front_pointer = 0;									\
		deq->back_pointer = 0;									\
		deq->size = &Deque_##t##_size; 								\
		deq->empty = &Deque_##t##_empty;							\
		deq->push_back = &Deque_##t##_push_back;						\
		deq->push_front = &Deque_##t##_push_front;						\
		deq->pop_back = &Deque_##t##_pop_back;							\
		deq->pop_front = &Deque_##t##_pop_front;						\
		deq->extend_array = &Deque_##t##_extend_array;						\
		deq->front = &Deque_##t##_front;							\
		deq->back = &Deque_##t##_back;								\
		deq->begin = &Deque_##t##_begin;							\
		deq->end = &Deque_##t##_end;								\
		deq->at = &Deque_##t##_at;								\
		deq->compare = fp;									\
		deq->clear = &Deque_##t##_clear;							\
		deq->dtor = &Deque_##t##_dtor;								\
	}

