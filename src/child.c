#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>



float solving_func(char * nums) {
    float answer = strtof(nums, NULL);

    float divider = 0;
    int flag = 0;
    for (int i = 0; i < strlen(nums)+1; ++i) {
        if ((flag == 0) && ((nums[i] == ' ') | (nums[i] == '\0'))) {    
            flag = 1;
        }
        else if ((flag == 1) && (nums[i] != ' ') && (nums[i] != '\0')) {   
            divider = divider*10 + ((int)nums[i] - 48); 
        }
        else if ((flag == 1) && ((nums[i] == ' ') | (nums[i] == '\0'))) {
            if (divider == 0) {
                write(STDERR_FILENO, "Division by 0",14);
                exit(1);
            }
            answer = answer / divider;
            divider = 0;
        }
    }

    return answer;
}


int main() {

    char child_numbers[128];
    float answer;
    read(STDIN_FILENO,child_numbers, 128);

    answer = solving_func(child_numbers);

    char answer_char[128] = " ";
    gcvt(answer, 12, answer_char);
    write(STDOUT_FILENO, answer_char, 128);


    return 0;
}