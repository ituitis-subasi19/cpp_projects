#include "data_structs.h"

void Stack::init(){
    head = NULL;
}

void Stack::close(){
    Subtask* to_delete;
    while(!isEmpty()){
        to_delete = head;
        head = head->next;
        delete to_delete;
    }
}

void Stack::push(Subtask* in){
    in->next = head;
    head = in;
}

Subtask* Stack::pop(){
    Subtask* popped = head;
    head = head->next;
    return popped;
}

bool Stack::isEmpty(){
    return head == NULL;
}

void Queue::init(){
    head = NULL;
    tail = NULL;
}

void Queue::close(){
    Process* to_delete;
    while(!isEmpty()){
        to_delete = head;
        head = head->next;
        delete to_delete;
    }
}

void Queue::queue(Process* in){
    in->next = NULL;
    if(isEmpty()){
        head = in;
        tail = in;
        return;
    }
    tail->next = in;
    tail = in;
}

Process* Queue::dequeue(){
    Process* token;
    token = head;
    head = head->next;
    if(isEmpty()){
        tail = NULL;
    }
    return token;
}

bool Queue::isEmpty(){
    return head == NULL;
}

Process* Queue::front(){
    return head;
}

void MultiQueue::init(){
    queues[0].init();
    queues[1].init();
    queues[2].init();
}

void MultiQueue::close(){
    queues[0].close();
    queues[1].close();
    queues[2].close();
}

void MultiQueue::queue(Process* in){
    queues[in->priority - 1].queue(in);
}

void MultiQueue::dequeue(const int& priority){
    delete queues[priority - 1].dequeue(); //Since i didn't put the Process* i dequed to somewhere else, i deleted it and this is the function the procsses are deleted
}

bool MultiQueue::isEmpty(){
    return (queues[0].isEmpty() && queues[1].isEmpty() && queues[2].isEmpty());
}

Process* MultiQueue::front(const int& priority){
    return queues[priority - 1].front();
}