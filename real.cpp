// add header guards at the end
// make a good make file compiling file objects
// include header files in make file
//use type def to make life easy
#include <dlfcn.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <random>
#include <unistd.h>
#include <string.h>
#include <string>
//#include "Deque.hpp"
using namespace std;

#define CAPACITY_SIZE 2;
// int Deque_MyClass_size(Deque_MyClass *deq);
// bool Deque_MyClass_empty(Deque_MyClass *deq);
// void Deque_MyClass_push_back(Deque_MyClass *deq,MyClass obj1);

struct Deque_myClass;
struct MyClass;
void
MyClass_print(const MyClass *o);
// void disp(Deque_MyClass *deq_old);

struct Deque_MyClass_Iterator{
	struct MyClass *value;
	int capacity;
	int position;

	void (*inc)(Deque_MyClass_Iterator *deq);
	void (*dec)(Deque_MyClass_Iterator *deq);
	struct MyClass &(*deref)(Deque_MyClass_Iterator *deq);
};
/*this is the generic object*/
struct MyClass {
	int id;
    char name[10];
};
//#define Deque_Define(t)
struct Deque_MyClass{

	struct MyClass *data;
	//for temporary usage while extending
	struct MyClass *data_temp;
	int front_pointer;
	int rear_pointer;
	int capacity;

	int num_items;
	char * type_name;
	int type_size;

	//fptrs to all the functions.
	int (*size)(Deque_MyClass *deq);
	bool (*empty)(Deque_MyClass *empty);
	void (*push_back)(Deque_MyClass *deq,MyClass obj1);
	void (*push_front)(Deque_MyClass *deq,MyClass obj1);
	void (*pop_front)(Deque_MyClass *deq);
	void (*pop_back)(Deque_MyClass *deq);

	void (*clear)(Deque_MyClass * deq);
	void (*dtor) (Deque_MyClass * deq);

	struct Deque_MyClass_Iterator (*begin)(Deque_MyClass *deq);
	struct Deque_MyClass_Iterator (*end)(Deque_MyClass *deq);


	struct MyClass &(*front)(Deque_MyClass *deq);
	struct MyClass &(*back)(Deque_MyClass *deq);
	struct MyClass &(*at)(Deque_MyClass *deq,int i);
	//for iterator
};

void Deque_Myclass_inc(Deque_MyClass_Iterator *it);
void Deque_Myclass_dec(Deque_MyClass_Iterator *it);
struct MyClass &Deque_MyClass_Iterator_deref(Deque_MyClass_Iterator *it);
//**************Iterator functions***********************

//Is this wrong???????????????????????????????????????????????????????????????????????????????????????????????????
Deque_MyClass_Iterator Deque_MyClass_begin(Deque_MyClass *deq){
	//more like a constructor copies all values form one struct to other

	if(deq->front_pointer != -1 && deq->rear_pointer != -1){
		// a.value = &(deq->data[deq->front_pointer]);
		// a.capacity = deq->capacity;
		// a.position = deq->front_pointer;
		return Deque_MyClass_Iterator{(deq->data),
		deq->capacity,
		deq->front_pointer,
		&Deque_Myclass_inc,
		&Deque_Myclass_dec,
		&Deque_MyClass_Iterator_deref};

	}
	// else{
	// 	a.value=0;
	// 	return a;
	// }
}
Deque_MyClass_Iterator Deque_MyClass_end(Deque_MyClass *deq){

	if(deq->front_pointer != -1 && deq->rear_pointer != -1){
		if(deq->rear_pointer!= deq->capacity-1)
			return Deque_MyClass_Iterator{(deq->data),
			deq->capacity,
			deq->rear_pointer+1,
			&Deque_Myclass_inc,
			&Deque_Myclass_dec,
			&Deque_MyClass_Iterator_deref};
		else{
			return Deque_MyClass_Iterator{(deq->data),
			deq->capacity,
			0,
			&Deque_Myclass_inc,
			&Deque_Myclass_dec,
			&Deque_MyClass_Iterator_deref};}

	}
	// else{
	// 	printf("----");
	// 	a.value=0;
	// 	return a;
	// }
}

void Deque_Myclass_inc(Deque_MyClass_Iterator *it){
	if(it->value!=0){
		if(it->position == it->capacity-1){
			it->position=0;}
			// it->value = &it->value[0];it->position=0;}
		else
			it->position++;
			// it->value = &it->value[it->position++];
	}
}
void Deque_Myclass_dec(Deque_MyClass_Iterator *it){
	if(it->value!=0){
		if(it->position == 0){
			it->position=it->capacity-1;}
			// it->value = &it->value[0];it->position=0;}
		else
			it->position--;
			// it->value = &it->value[it->position++];
	}
}
bool Deque_MyClass_Iterator_equal(Deque_MyClass_Iterator it1,Deque_MyClass_Iterator it2){

	if(it1.position == it2.position)
		return true;
	else
		return false;
}
struct MyClass &Deque_MyClass_Iterator_deref(Deque_MyClass_Iterator *it){
	return it->value[it->position];
}

//**************Iterator functions***********************

int Deque_MyClass_size(Deque_MyClass *deq){
	return deq->num_items;
}
bool Deque_MyClass_empty(Deque_MyClass *deq){
	return (deq->num_items == 0)?true:false;
}

void Deque_MyClass_pop_front(Deque_MyClass *deq){
	if(deq->front_pointer == -1 && deq->rear_pointer == -1){
		fprintf(stderr,"cannot delete in empty buffer");
	}
	else if ( deq->front_pointer == deq->rear_pointer){
		deq->front_pointer=-1;
		deq->rear_pointer=-1;
		deq->num_items-=1;
		//remove this while uploading
		assert(deq->num_items == 0);
	}
	else{
		if(deq->front_pointer== deq->capacity-1) deq->front_pointer = 0;
		else deq->front_pointer+=1;
		deq->num_items-=1;
	}
}
void Deque_MyClass_pop_back(Deque_MyClass *deq){
	if(deq->front_pointer == -1 && deq->rear_pointer == -1){
		fprintf(stderr,"cannot delete in empty buffer");
	}
	else if ( deq->front_pointer == deq->rear_pointer){
		deq->front_pointer=-1;
		deq->rear_pointer=-1;
		deq->num_items-=1;
		//remove this while uploading
		assert(deq->num_items == 0);
	}
	else{
		if(deq->rear_pointer== 0 ) deq->rear_pointer= deq->capacity-1;
		else deq->rear_pointer-=1;
		deq->num_items-=1;
	}
}

bool Deque_MyClass_equal(Deque_MyClass deq1,Deque_MyClass deq2){
	if(deq1.num_items!= deq2.num_items)
		return false;
	else{
		// printf("\n==%d==%d\n",memcmp ( deq1.data, deq2.data, sizeof(deq1.data)),sizeof(deq1.data));
		// return true;
		for(int i=0;i<deq1.num_items;i++){
			MyClass_print(&deq1.at(&deq1,i));
			MyClass_print(&deq2.at(&deq2,i));
			printf(" %d++++ %d\n",  (deq1.data[2].id==deq2.data[2].id), strcmp(deq1.data[2].name,deq2.data[2].name)  );


			if(memcmp( &deq1.at(&deq1,i),&deq2.at(&deq2,i),sizeof(MyClass)) != 0){
				// MyClass_print(&deq1.at(&deq1,i));
				// MyClass_print(&deq2.at(&deq2,i));
				printf("not equal to zero %d\n",memcmp( &deq1.at(&deq1,i),&deq2.at(&deq2,i),sizeof(MyClass)));
				return false;
			}
			else{
				printf("equal to zero\n");
			}
		}
		return true;
	}
}

MyClass &Deque_MyClass_front(Deque_MyClass *deq){
	if(deq->front_pointer != -1 && deq->rear_pointer != -1)
		return deq->data[deq->front_pointer];
	//else would be an exception since there is no data
}

MyClass &Deque_MyClass_back(Deque_MyClass *deq){
	if(deq->front_pointer != -1 && deq->rear_pointer != -1)
		return deq->data[deq->rear_pointer];
	//else would be an exception since there is no data
}


MyClass &Deque_MyClass_at(Deque_MyClass *deq,int i){
	if(deq->front_pointer != -1 && deq->rear_pointer != -1){
		int j = deq->front_pointer;
		while(i>0){//mod capacity.
			if(j == deq->capacity-1)
				j=0;
			else
				j++;
			i--;
		}
		return deq->data[j];
	}
	//else would be an exception since there is no data
}

void Deque_MyClass_clear(Deque_MyClass *deq){

	free(deq->data);
	//they both point to same data so both are free.
	// free(deq->data_temp);
	deq->data =(MyClass *) (malloc( 10*sizeof(MyClass )));
	deq->num_items=NULL;
	//deal with type size and type name.
	//strdup does malloc behind the scenes use this to assign type name
	// char a[]="MyClass";
	// deq->type_name 		= strdup(a);
	deq->front_pointer 	= -1;
	deq->rear_pointer  	= -1;
	deq->capacity 		= CAPACITY_SIZE;
	deq->num_items		= 0;
}
void Deque_MyClass_dtor(Deque_MyClass *deq){
	deq->clear(deq);
	free(deq->data);
	deq->data=NULL;
	// free(deq->data_temp);
	//needn't clear the function pointers.
	// free(size);
	// free(empty);
	// free(push_back);
	// free(push_front);
	// free(pop_front);
	// free(pop_back);
	// free(clear);
	// free(dtor);
	// free(begin);
	// free(end);
	// free(front);
	// free(back);
	// free(at);
}

//helper function
void expand(Deque_MyClass *deq_old){
	deq_old->data_temp =(MyClass *) (malloc((deq_old->capacity)*2*sizeof(MyClass)));

	int i=0;
	while(deq_old->front_pointer != deq_old->rear_pointer){

		deq_old->data_temp[i++] = deq_old->data[deq_old->front_pointer];

		if(deq_old->front_pointer == deq_old->capacity-1) deq_old->front_pointer = 0;
		else deq_old->front_pointer+=1;
	}
	//handle the element that is equal to
	deq_old->data_temp[i] = deq_old->data[deq_old->front_pointer];

	deq_old->capacity *=2;
	free(deq_old->data);
	deq_old->data = 0;
	deq_old->data = deq_old->data_temp;
	//free(deq_old->data_temp);
	deq_old->front_pointer = 0;
	deq_old->rear_pointer = i;
}

void Deque_MyClass_push_front(Deque_MyClass *deq,MyClass obj1){
	if(deq->front_pointer == -1 && deq->rear_pointer == -1){
		deq->front_pointer = 0;
		deq->rear_pointer = 0;
		deq->data[deq->rear_pointer] = obj1;
		deq->num_items+=1;
	}
	else if(deq->front_pointer==0){
		//if inserting at last index of array when front is at starting index
		if( deq-> rear_pointer != (deq->capacity -1) ){
			deq->front_pointer = deq->capacity-1;
			deq->data[deq->front_pointer] = obj1;
			deq->num_items+=1;
		}
		else{
			//not enough memory expand
			expand(deq);
			deq->front_pointer = deq->capacity-1;
			deq->data[deq->front_pointer] = obj1;
			deq->num_items+=1;
			printf("oopsieeeeeeeeeeeee\n");
		}
	}
	else if( (deq->front_pointer - 1)  != deq->rear_pointer){
		deq->front_pointer = (deq->front_pointer - 1 )% deq->capacity;
		deq->data[deq->front_pointer] = obj1;
		deq->num_items+=1;
	}
	else{
		//not enough memory expand size
		expand(deq);
		deq->front_pointer = deq->capacity-1;
		deq->data[deq->front_pointer] = obj1;
		deq->num_items+=1;
		printf("Daddyyyyyyyy\n");
	}
}

void Deque_MyClass_push_back(Deque_MyClass *deq,MyClass obj1){

	if(deq->front_pointer == -1 && deq->rear_pointer == -1){
		deq->front_pointer = 0;
		deq->rear_pointer = 0;
		deq->data[deq->rear_pointer] = obj1;
		deq->num_items+=1;
	}
	else if( (deq->rear_pointer + 1) % deq->capacity != deq->front_pointer){
		deq->rear_pointer = (deq->rear_pointer + 1 )% deq->capacity;
		deq->data[deq->rear_pointer] = obj1;
		deq->num_items+=1;
	}
	else{
		//expand size not enough memory.
		expand(deq);
		deq->rear_pointer = (deq->rear_pointer + 1 )% deq->capacity;
		deq->data[deq->rear_pointer] = obj1;
		deq->num_items+=1;
		printf("mummyyyyyyyy\n");
	}
}

//constructor of the struct no function pointer needs to be called to this.
void Deque_MyClass_ctor(Deque_MyClass *deq, bool (*foo)(const MyClass &o1,const MyClass &o2)){

	deq->data =(MyClass *) (malloc( 10*sizeof(MyClass )));
	deq->num_items=0;

	//strdup does malloc behind the scenes use this to assign type name
	char a[]="MyClass";
	deq->type_name 		= strdup(a);
	deq->front_pointer 	= -1;
	deq->rear_pointer  	= -1;
	deq->capacity 		= CAPACITY_SIZE;
	deq->size 			=&Deque_MyClass_size;
	deq->empty 			=&Deque_MyClass_empty;
	deq->push_back 		=&Deque_MyClass_push_back;
	deq->push_front		=&Deque_MyClass_push_front;
	deq->front 			=&Deque_MyClass_front;
	deq->back  			=&Deque_MyClass_back;
	deq->at  			=&Deque_MyClass_at;
	deq->pop_front 		=&Deque_MyClass_pop_front;
	deq->pop_back 		=&Deque_MyClass_pop_back;

	deq->begin 		=  &Deque_MyClass_begin;
	deq->end 		=  &Deque_MyClass_end;

	deq->clear 		= &Deque_MyClass_clear;
	deq->dtor 		= &Deque_MyClass_dtor;

}

bool
MyClass_less_by_id(const MyClass &o1, const MyClass &o2) {
    return o1.id < o2.id;
}

void
MyClass_print(const MyClass *o) {
    printf("%d\n", o->id);
    printf("%s\n", o->name);
}

/*for testing purposes*/
void disp(Deque_MyClass *deq_old){

	printf("the quee from front to rear capcity is %d\n",deq_old->capacity);
	/*must not be used messing with main dataaaaaaaaaaaa*/
	while(deq_old->front_pointer != deq_old->rear_pointer){

		printf("%d  %s\n",deq_old->data[deq_old->front_pointer].id,deq_old->data[deq_old->front_pointer].name);

		if(deq_old->front_pointer == deq_old->capacity-1) deq_old->front_pointer = 0;
		else deq_old->front_pointer+=1;
	}
	//handle the element that is equal to
	printf("%d  %s\n",deq_old->data[deq_old->front_pointer].id,deq_old->data[deq_old->front_pointer].name);

	for(int i=0;i<deq_old->capacity;i++)
		printf("\n%d %d %s-->\n",i,deq_old->data[i].id,deq_old->data[i].name);
}/*delete till here */


int main()
{
	 FILE *devnull = fopen("/dev/null", "w");
    assert(devnull != 0);
    {
        Deque_MyClass deq;
        Deque_MyClass_ctor(&deq, MyClass_less_by_id);

        assert(deq.size(&deq) == 0);
        assert(deq.empty(&deq));

        // Should print "---- Deque_MyClass, 14".
        printf("---- %s, %d\n", deq.type_name, (int) sizeof(deq.type_name));
        // std::cout << "---- " << deq.type_name << ", " << sizeof(deq.type_name) << std::endl;
        //not yet implemented
        // assert(sizeof deq.type_name == 14);

        deq.push_back (&deq, MyClass{1, "Joe"});
        deq.push_back (&deq, MyClass{2, "Mary"});
        deq.push_back (&deq, MyClass{3, "Tom"});
        deq.push_front(&deq, MyClass{0, "Mike"});
        deq.push_front(&deq, MyClass{-1, "Mary"});


        MyClass_print(&deq.front(&deq));
        MyClass_print(&deq.back(&deq));
        assert(deq.front(&deq).id == -1);
        assert(deq.back(&deq).id == 3);

        deq.pop_front(&deq);
        deq.pop_back(&deq);
        assert(deq.front(&deq).id == 0);
        assert(deq.back(&deq).id == 2);

        assert(deq.size(&deq) == 3);

        // printf("------------------------------------------------------------1");
        for (Deque_MyClass_Iterator it = deq.begin(&deq);
         !Deque_MyClass_Iterator_equal(it, deq.end(&deq)); it.inc(&it)) {
            MyClass_print(&it.deref(&it));
        }

        // Multiple iterators?
        for (Deque_MyClass_Iterator it1 = deq.begin(&deq);
         !Deque_MyClass_Iterator_equal(it1, deq.end(&deq));
         it1.inc(&it1)) {
            MyClass_print(&it1.deref(&it1));
            for (Deque_MyClass_Iterator it2 = deq.begin(&deq);
             !Deque_MyClass_Iterator_equal(it2, deq.end(&deq)); it2.inc(&it2)) {
                MyClass_print(&it2.deref(&it2));
                for (Deque_MyClass_Iterator it3 = deq.begin(&deq);
                 !Deque_MyClass_Iterator_equal(it3, deq.end(&deq)); it3.inc(&it3)) {
                    MyClass_print(&it3.deref(&it3));
                }
            }
        }

        // Test decrement of end.
        {
            auto it = deq.end(&deq);
            it.dec(&it);
            assert(it.deref(&it).id == 2);
        }

        // printf("Using at.\n");

        for (size_t i = 0; i < 3; i++) {
            MyClass_print(&deq.at(&deq, i));
        }

        // Test that front(), back(), at(), and deref() are returning a reference.
        // Change via at().

        assert(deq.at(&deq, 0).id == 0);
        deq.at(&deq, 0).id = 100;
        assert(deq.at(&deq, 0).id == 100);
        // Change via front().
        assert(deq.front(&deq).id == 100);
        deq.front(&deq).id = 0;
        assert(deq.front(&deq).id == 0);
        assert(deq.at(&deq, 0).id == 0); // Verify with at() also.
        {
            auto it = deq.end(&deq);
            it.dec(&it);
            assert(it.deref(&it).id == 2);
            it.deref(&it).id = 200;
            assert(it.deref(&it).id == 200);
            // Change using back().
            assert(deq.back(&deq).id == 200);
            deq.back(&deq).id = 2;
            assert(deq.back(&deq).id == 2);
            assert(it.deref(&it).id == 2); // Verify with iterator also.
        }
        deq.clear(&deq);

        deq.dtor(&deq);

                // Test equality.  Two deques compare equal if they are of the same
        // length and all the elements compare equal.  It is undefined behavior
        // if the two deques were constructed with different comparison
        // functions.
        {
            Deque_MyClass deq1, deq2;

            Deque_MyClass_ctor(&deq1, MyClass_less_by_id);
            Deque_MyClass_ctor(&deq2, MyClass_less_by_id);

            deq1.push_back(&deq1, MyClass{1, "Joe"});
            deq1.push_back(&deq1, MyClass{2, "Jane"});
            deq1.push_back(&deq1, MyClass{3, "Mary"});

            deq2.push_back(&deq2, MyClass{1, "Joe"});
            deq2.push_back(&deq2, MyClass{2, "Jane"});
            deq2.push_back(&deq2, MyClass{3, "Mary"});
            // disp(&deq1);
            // disp(&deq2);
            Deque_MyClass_equal(deq1, deq2);
            assert(Deque_MyClass_equal(deq1, deq2));

            deq1.pop_back(&deq1);
            assert(!Deque_MyClass_equal(deq1, deq2));
            deq1.push_back(&deq1, MyClass{4, "Mary"});
            assert(!Deque_MyClass_equal(deq1, deq2));

            // deq1.dtor(&deq1);
            // deq2.dtor(&deq2);
        }
    }


	return 0;
}
