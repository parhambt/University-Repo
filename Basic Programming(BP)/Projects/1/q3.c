#include <stdio.h>

int main(void)
{
    char sign_operator ; 
    int get_number_count ; 
    scanf("%c %d",&sign_operator,&get_number_count);
    int flag = -1 ;
    int answer ; 
    if (sign_operator=='+')
    {
        flag =1 ; // flag 1 means it is plus sign
        answer =0 ;
    } 
    else if (sign_operator=='*')
    {
        flag =2 ; // flag 2 means it is multiply sign
        answer =1 ;
    }
    else  
    {
        printf("Wrong Symbol");
        return flag ; 
    } 
    
    int input_each_line ;  
    for (int starter=1 ; starter<=get_number_count ; starter+=1)
    {
        scanf("%d",&input_each_line);
        if(flag==1)
        {
            answer = answer + input_each_line ; 
        }
        else if (flag==2)
        {
            answer = answer * input_each_line ; 
        }

        
    }
    printf("%d\n",answer);
}