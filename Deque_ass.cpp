#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
using namespace std;

#define Deque_DEFINE(t)											\
	struct Deque_##t;										\
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
		char *type_name;									\
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
			index = deq->front_pointer+1;							\
		}											\
		else											\
			index = deq->front_pointer;							\
		if(deq->front_pointer < deq->back_pointer) {						\
			for(i=deq->front_pointer; i< deq->length;i++, index++)				\
				deq->data[index] = deq->tmpdata[i];					\
		}else {											\
			for(i=deq->front_pointer; i< deq->length;i++,index++)				\
				deq->data[index] = deq->tmpdata[i];					\
			for(i=0;i<=deq->back_pointer;i++, index++)					\
				deq->data[index] = deq->tmpdata[i];					\
		}											\
		deq->length = 2 * deq->length;								\
		if(leave)										\
			deq->back_pointer++;								\
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
		if(deq->front_pointer == 0 || deq->front_pointer-1 == deq->back_pointer)		\
			deq->extend_array(deq,1);							\
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
	}												\
	void Deque_##t##_pop_front(Deque_##t *deq){							\
		if(!deq->empty(deq)){									\
			deq->front_pointer++;								\
			deq->Size--;									\
		}											\
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
		index = (index + deq->front_pointer)%deq->length;					\
		return deq->data[index];								\
	}												\
	void Deque_##t##_clear(Deque_##t *deq){								\
		free(deq->data);									\
		deq->data = NULL;									\
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
	void Deque_##t##_ctor(Deque_##t *deq, bool (*fp)(const t &, const t &)) {			\
		deq->Size = 0;										\
		deq->length = 1;									\
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
		deq->clear = &Deque_##t##_clear;							\
		deq->compare = fp;									\
	}												

struct MyClass {
	int id;
	char name[10];
};

void MyClass_print(const MyClass *o) {
	printf("%d\n", o->id);
	printf("%s\n", o->name);
}

bool MyClass_less_by_id(const MyClass &o1, const MyClass &o2) {
    return o1.id < o2.id;
}

Deque_DEFINE(MyClass)

bool
int_less(const int &o1, const int &o2) {
    return o1 < o2;
}

Deque_DEFINE(int)
int main() {
	Deque_int deq;
        Deque_int_ctor(&deq, int_less);

        assert(deq.size(&deq) == 0);
        assert(deq.empty(&deq));

        deq.push_back(&deq, 1);
        deq.push_back(&deq, 2);
        deq.push_back(&deq, 3);
        deq.push_front(&deq, 0);
        deq.push_front(&deq, -1);

	printf("%d\n", deq.front(&deq));
        printf("%d\n", deq.back(&deq));
        assert(deq.front(&deq) == -1);
        assert(deq.back(&deq) == 3);

	deq.pop_front(&deq);
        deq.pop_back(&deq);
        assert(deq.front(&deq) == 0);
        assert(deq.back(&deq) == 2);
        assert(deq.size(&deq) == 3);
        for (Deque_int_Iterator it = deq.begin(&deq);
         !Deque_int_Iterator_equal(it, deq.end(&deq)); it.inc(&it)) {
            printf("%d\n", it.deref(&it));
        }

        // Test decrement.
        {
            auto it = deq.end(&deq);
            it.dec(&it);
            assert(it.deref(&it) == 2);
        }

        printf("Using at.\n");

        for (size_t i = 0; i < 3; i++) {
            printf("%d: %d\n", int(i), deq.at(&deq, i));
        }

	    // Test equality.  It is undefined behavior if the two deques were constructed with different
    // comparison functions.
    {
        Deque_int deq1, deq2;
        Deque_int_ctor(&deq1, int_less);
        Deque_int_ctor(&deq2, int_less);

        deq1.push_back(&deq1, 1);
        deq1.push_back(&deq1, 2);
        deq1.push_back(&deq1, 3);
        deq2.push_back(&deq2, 1);
        deq2.push_back(&deq2, 2);
        deq2.push_back(&deq2, 3);

        assert(Deque_int_equal(deq1, deq2));

        deq1.pop_back(&deq1);
        assert(!Deque_int_equal(deq1, deq2));
        deq1.push_back(&deq1, 4);
        assert(!Deque_int_equal(deq1, deq2));

        deq1.clear(&deq1);
        deq2.clear(&deq2);
    }


        deq.clear(&deq);



}

