/*
 * LinkedList.h
 *
 *  Created on: 31 Mar, 2015
 *      Author: Travis
 */

#ifndef INC_LINKEDLIST_H_
#define INC_LINKEDLIST_H_
template<typename T>
class LinkedList {
public:
	LinkedList(T obj[])
{
		size=sizeof(obj)/sizeof(T);
		head=new Container(obj[0]);
		Container* ptr=head;
		for(int i=1;i<size-1;i++)
		{
			*ptr>>new Container(obj[i]);
			ptr=ptr->next;
		}
		end=ptr;
		push(obj[size-1]);
}
	LinkedList()
	{
		head=end=0;
		size=0;
	}
	~LinkedList()
	{
		Container* ptr=head->next;
		while(ptr!=0)
		{
			delete head;
			head=ptr;
			ptr=ptr->next;
		}
	}
	struct Container
	{
		Container(T obj)
		{
			entry=obj;
			next=previous=0;
		}
		T entry;
		Container* next;
		Container* previous;
		Container& operator>>(Container& nextCon)
		{
			next=&nextCon;
			return nextCon;
		}
		Container& operator>>(Container* pnext)
		{
			next=pnext;
			return *pnext;
		}
		Container& operator<<(Container* pprev)
		{
			previous=pprev;
			return *pprev;
		}
		Container& operator<<(Container& prevCon)
		{
			previous=&prevCon;
			return prevCon;
		}
	};
	int find(T obj)
	{
		Container* ptr=head;
		int pos=0;
		while(ptr!=0)
		{
			if(ptr->entry==obj)return pos;
			pos++;
		}
		return -1;
	}
	void push(T obj)
	{
		*end>>new Container(obj);
		end=end->next;
	}
	template<typename... Args>
	void push(T t,Args... args)
	{
		push(t);
		size++;
		push(args...);
	}
	void append(int pos,T obj)
	{
		if(size<pos)return;
		Container* ptr=head,after=head;
		for(int i=0;i<pos;i++)
		{
			ptr=head->next;
		}
		after=ptr->next;
		ptr->next=new Container(obj);
		ptr->next>>after;
		size++;
	}

private:
	int size;
	Container* head;
	Container* end;
};

#endif /* INC_LINKEDLIST_H_ */
