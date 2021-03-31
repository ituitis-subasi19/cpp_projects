#include <iostream>
#include <stdio.h>

#include "data_structs.h"

using namespace std;

void read_from_file(Queue& data, const char* file){
    FILE* ptr = fopen(file, "r+");

    while(!feof(ptr)){
        Process* process = new Process;
        process->task_stack.init(); //I initialized the stacks here since i defined new Process*es here
        fscanf(ptr, "%s %d", process->name, &process->priority);
        fscanf(ptr, "%d %d", &process->arrival_time, &process->task_count);
        process->deadline = process->arrival_time;
        
        for(int i = 0; i < process->task_count; i++){
            Subtask* new_task = new Subtask;
            fscanf(ptr, " %c %d", &new_task->name, &new_task->duration);
            process->deadline += new_task->duration;
            process->task_stack.push(new_task);
        }

        data.queue(process);

        if(!feof(ptr))
            fseek(ptr, SEEK_CUR, 1);
    }
    fclose(ptr);
}

bool put_to_line(const int& time, Queue& data, MultiQueue& line){
    bool inserted = false;
    if(!data.isEmpty() && time >= data.front()->arrival_time){
        line.queue(data.dequeue());
        inserted = true;
    }
    return inserted;
}

int decide_priority(int& special_condition, MultiQueue& line){ //Since i checked the condition that all priorities are empty in the process(Queue&, MultiQueueu&) that is where i called this function, i don't need to check this condition here
    int priority;

    if(!line.queues[0].isEmpty()){
        priority = 1;
    } else if(!line.queues[1].isEmpty() && special_condition != 2){
        priority = 2;
        special_condition += 1;
    } else if(!line.queues[2].isEmpty()){
        priority = 3;
        special_condition = 0;
    } else { //special codition is 2 (which means on in my code), priority 1 and priority 3 are empty
        priority = 2;
        special_condition = 1;//Since there is no priority 3, special condition is 0. Since there is no priority 1, priority 2 will be implemented so special condition is 1
    }
    return priority;
}

void do_subtask(int& priority, int& time, int& cumulative_lateness, MultiQueue& line){
    Subtask* token;
    
    token = line.front(priority)->task_stack.pop();
    time += token->duration; //I updated the time instead of increase it 1 by 1 since explanation said run a subtask and change the time and for my code to work faster
    cout << line.front(priority)->name << " " << token->name << endl;
    delete token;
        
    if(--line.front(priority)->task_count == 0){
        cumulative_lateness += (time - line.front(priority)->deadline); //The right-hand side of the equation is the lateness of the process
        line.dequeue(priority); //This is where the Process*es are deleted. Since i deleted all Subtask*s before i delete the Process*, i don't need to check it
    }
}

void process(Queue& data, MultiQueue& line){
    int time = 0;
    int special_condition = 0;
    int cumulative_lateness = 0;
    int priority;

    while(!(data.isEmpty() && line.isEmpty())){
        while(put_to_line(time, data, line));
        if(!line.isEmpty()){
            priority = decide_priority(special_condition, line);
            do_subtask(priority, time, cumulative_lateness, line);
        } else{ //If MultiQueueu is empty but there are Process*es in the Queue, i thougth that the arrival_time of next Process* may be huge like 10000 so i updated the time instead of increase it 1 by 1 for my code to work faster
            if(special_condition == 2)
                special_condition = 0; //since priority 3 is empty when special condition is activated, special condition is deactivated
            time = data.front()->arrival_time;
        }
    }
    cout << "Cumulative Lateness: " << cumulative_lateness << endl;
}

int main(int argc, char* argv[]){
    if(argc != 2)
        return 1;
    
    const char* file = argv[1];

    Queue data;
    data.init();
    read_from_file(data, file);

    MultiQueue line;
    line.init();
    
    process(data, line);

    return 0;
}