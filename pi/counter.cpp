#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "counter.h"

using namespace std;

	
int Counter::findindex(Token *arr,char elem[]){
	int index = -1;
	bool found = false;
	for(int i = 0; i < token_count && !found; i++) {
		if(strcmp(elem, arr[i].token) == 0){
			index = i;
			found = true;
		}
	}
	return index;
} 

bool Counter::contains(char *token, char target){
	bool found = false;
	int index = 0;
	while(token[index] != '\0' && !found) {
		if(token[index] == target) {
			found = true;
		}
		index++;
	}
	return found;
}

void Counter::read_and_count(){
	char control[TOKEN_LENGTH];
	FILE *pi = fopen("pi_approximate", "r+");
	
	while(!feof(pi)) {
		fread(control, sizeof(char), 2, pi);
		control[2] = '\0';
		bool found = false;
		for(int j = 0; j < token_count && !found; j++) {
			if(strcmp(control, token_array[j].token) == 0) {
				token_array[j].count++;
				found = true;
			}
		}
		if((found == false) && (contains(control, '.') == false) && (contains(control, '\n') == false)) {
			strcpy(token_array[token_count].token, control);
			token_array[token_count].count = 1;
			token_count++;
		}
		fseek(pi, -1 * sizeof(char), SEEK_CUR);
		if(contains(control, '\n') == true) {
			break;
		}
	}
	fclose(pi);
}


Token *Counter::get_most_common_three(){
	static Token common_three[3];;
	common_three[0].count = 0;
	common_three[1].count = 0;
	common_three[2].count = 0;
	int index1, index2, index3;
	for(int i = 0; i < token_count; i++) {
		if(token_array[i].count > common_three[0].count) {
			common_three[2].count = common_three[1].count;
			common_three[1].count = common_three[0].count;
			common_three[0].count = token_array[i].count;
			index3 = index2;
			index2 = index1;
			index1 = i;
		} else if(token_array[i].count > common_three[1].count) {
			common_three[2].count = common_three[1].count;
			common_three[1].count = token_array[i].count;
			index3 = index2;
			index2 = i;
		} else if(token_array[i].count > common_three[2].count) {
			common_three[2].count = token_array[i].count;
			index3 = i;
		}
	}
	strcpy(common_three[0].token, token_array[index1].token);
	strcpy(common_three[1].token, token_array[index2].token);
	strcpy(common_three[2].token, token_array[index3].token);
	return common_three;
}