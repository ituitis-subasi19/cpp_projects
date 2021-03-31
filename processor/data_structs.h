#include <iostream>
#include <stdio.h>

#pragma once

using namespace std;

struct Subtask{
    char name;
    int duration;
    Subtask* next;
};

struct Stack{
    Subtask* head;
    void init();
    void close();
    void push(Subtask* in);
    Subtask* pop();
    bool isEmpty();
};

struct Process{
    char name[9];
    int arrival_time;
    int deadline;
    int task_count;
    int priority;
    Stack task_stack;
    Process* next;
};

struct Queue{
    Process* head;
    Process* tail;
    void init();
    void close();
    void queue(Process* in);
    Process* dequeue();
    bool isEmpty();
    Process* front();
};

struct MultiQueue{
    Queue queues[3];
    void init();
    void close();
    void queue(Process* in);
    void dequeue(const int& priority);
    bool isEmpty();
    Process* front(const int& priority);
};