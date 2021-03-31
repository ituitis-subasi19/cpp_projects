#include <stdlib.h>
#include <iostream>
#include <stdio.h>

#include "circuit.h"
using namespace std;

int main(int argc, char* argv[])
{
    circuit circ;
    circ.create();

    FILE* file = fopen("input.txt", "r+");
    char g_name;
    double v;    
    fseek(file, 0, SEEK_SET);
    while(!feof(file)){
        fscanf(file, "%c %lf ", &g_name ,&v);
        //cout << g_name << " " << v << endl;
        if(v > 0){
            circ.add_resistor(g_name, v);
        } else if(v < 0){
            double abs = 0 - v;
            circ.remove_resistor(g_name, abs);
        } else{
            if(g_name == 'A')
                circ.circuit_info();
        }
    }
    fclose(file);
    circ.clear();
    return EXIT_SUCCESS;
}

//circuit operations

void circuit::create(){
    head = NULL;
}

void circuit::add_resistor(const char& g_name, const double& v){
    resistor* new_resistor = new resistor;
    resistor* predecessor = NULL;
    resistor* traverse = head;
    new_resistor->build_resistor(g_name, v);
    
    if(head == NULL){
        head = new_resistor;
        return;
    }
    if(new_resistor->group < head->group){
        new_resistor->next = head;
        head = new_resistor;
        return;
    }
    while(traverse && new_resistor->group > traverse->group){
        predecessor = traverse;
        traverse = traverse->next;
    }
    if(traverse != NULL) {
        if(new_resistor->group == traverse->group){
            traverse->quantity++;
            delete new_resistor;
        } else{
            predecessor->next = new_resistor;
            new_resistor->next = traverse;
        }
    } else{
        predecessor->next = new_resistor;
    }
}

void circuit::remove_resistor(const char& g_name, const double& v){
    resistor* traverse = head;
    resistor* predecessor = NULL;

    while(traverse && g_name != traverse->group){ //if g_name=head->group then traverse=head situation won't change
        predecessor = traverse;
        traverse = traverse->next;
    }
    if(traverse == NULL){ //this will work if traverse is at the end of the linked list or (traverse=head and head=NULL) so if list is empty there won't be any problem
        cout << "NO_RESISTOR" << endl;
    } else{
        if(traverse->value == v){
            if(traverse->quantity == 1){
                delete_resistor(traverse, predecessor); //traverse=head situation will be dealed in this function
            } else{ //there won't be any problem even if traverse=head because we are not deleting any node so head wont change
                traverse->quantity--;
            }
        } else{
            cout << "NO_RESISTOR" << endl;
        }
    }
}

void circuit::delete_resistor(resistor* todelete, resistor* predecessor){ //since i call this function in remove_resistor function i don't have to check the situations which are checked in there
    
    if(todelete == head){
        head = head->next;
        delete todelete;
        return;
    }
    predecessor->next = todelete->next;
    delete todelete;
    
}

void circuit::circuit_info(){
    circuit toprint;
    toprint.create();
    resistor* read = head;
    resistor* traverse = NULL;
    resistor* predecessor = NULL;
    double total_resistance = 0;
    resistor* write = NULL;

    while(read){
        write = new resistor;
        write->copy_resistor(read->group, read->value, read->quantity);
        traverse = toprint.head;

        if(toprint.head == NULL){
            toprint.head = write;
        } else if(write->value < toprint.head->value){
            write->next = toprint.head;
            toprint.head = write;
        } else{
            while(traverse && write->value > traverse->value){
                predecessor = traverse;
                traverse = traverse->next;
            }
            if(traverse != NULL) {
                if(write->value == traverse->value){
                    traverse->quantity += write->quantity;
                    delete write;
                } else{
                    predecessor->next = write;
                    write->next = traverse;
                }
            } else{
                predecessor->next = write;
            }
        }
        //untill there in while, i created a linked list to print
        total_resistance += (read->value / read->quantity);//i calculated total resistance here not to read circuit again
        read = read->next;
    }
    
    traverse = toprint.head;
    while(traverse){
        cout << traverse->value << ":" << traverse->quantity << endl;
        traverse = traverse->next;
    }
    cout << "Total resistance=" << total_resistance << " ohm" << endl;;
    toprint.clear();
}

void circuit::clear(){
    resistor* todelete = NULL;
    while(head){
        todelete = head;
        head = head->next;
        delete todelete;
    }
}

//resistor operations

void resistor::build_resistor(const char& g_name, const double& v){
    group = g_name;
    value = v;
    quantity = 1;
    next = NULL;
}

void resistor::copy_resistor(const char& g_name, const double& v, const int& q){
    group = g_name;
    value = v;
    quantity = q;
    next = NULL;
}