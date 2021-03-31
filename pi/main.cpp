/*
PLEASE DO NOT CHANGE THIS FILE, OTHERWISE YOUR CODE WILL NOT BE EVALUATED AND WILL BE GRADED AS 0 
*/

#include <iostream> 
#include <stdlib.h>
#include <iomanip>
#include <string.h>

#include "counter.h"


using namespace std;

Counter counter;

void print_menu();
bool perform_operation(char);
void display();
void display_most_common_three();

int main(){
	system("cls");
	counter.read_and_count();
	bool end = false; 
	char choice; 	
	while (!end) { 
		print_menu(); 
		cin >> choice;
		end = perform_operation(choice); 
		}

	return EXIT_SUCCESS;
}

void display(){
	char target[TOKEN_LENGTH];
	cout << "Please enter the token that you want to see how many times it is encountered in decimal part in pi number (press'*'for full list)" << endl;
	cout << "Token : ";
	cin >> setw(TOKEN_LENGTH+1) >> target;	
	if(strcmp(target,"*")==0){
		for(int i=0;i<counter.token_count;i++)
			cout<<counter.token_array[i].token<<" "<<counter.token_array[i].count<<endl;
	}
	else{
		int index=counter.findindex(counter.token_array,target);
		if(index==-1)
			cout<<"There is no '"<<target<<"' token in decimal part of PI"<<endl;
		else
			cout<<counter.token_array[index].token<<" "<< counter.token_array[index].count<<endl;
	}
	getchar();
}

void display_most_common_three(){
	Token *common_three=counter.get_most_common_three();
	cout<<"The most common three tokens;"<<endl;
	for(int i=0;i<3;i++)
		cout<<common_three[i].token<<" "<< common_three[i].count<<endl;
	getchar(); 
}

void print_menu(){
	cout << endl << endl;
	cout << "COUNTER APPLICATION OF PI'S DECIMAL" << endl;
	cout << "Choose an operation" << endl;
	cout << "D: Display" << endl;
	cout << "M: Print Most Common Three" << endl;
	cout << "E: Exit" << endl;	
	cout << endl;
	cout << "Enter a choice {D,M,E}: ";
}
bool perform_operation(char choice){
	bool terminate=false;
	switch (choice) {
		case 'D': case 'd': 
			display();
			break;		 
		case 'M': case 'm': 
			display_most_common_three();
			break;		

		case 'E': case 'e': 
			cout << "Are you sure you want to exit the program? (Y/N):";
			cin >> choice;
			if(choice=='Y' || choice=='y')
				terminate=true; 
			break; 
		default: 
			cout << "Error: You have entered an invalid choice" << endl; 
			cout << "Please try again {D,M,E}  :" ;
			cin >> choice;
			terminate = perform_operation(choice);
			break; 
	}
	return terminate;
}