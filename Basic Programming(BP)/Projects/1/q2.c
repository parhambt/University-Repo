#include <stdio.h>
double power(float base , float exponant)
{   
    if (exponant==0) return 1 ; 
    if (exponant==1) return base ;
    double answer = base ; 
    for (exponant ; exponant>1; exponant-=1)
    {
        answer = answer * base ; 
    }
    return answer ; 
}
int main(void)
{
    double mass_1 , mass_2 ; 
    scanf("%lf %lf",&mass_1,&mass_2);
    double const_1 , const_2 ; 
    scanf("%lf %lf",&const_1,&const_2);
    if(mass_1<= mass_2 && const_1<=const_2) 
    {
        printf("-1\n");
        return -1 ;
    }
    
    float exponant = 1 ,output_1,output_2;
    while (exponant)
    {
        output_1 =mass_1*(power(const_1,exponant)) ;
        output_2 =mass_2*(power(const_2,exponant)) ;
        if( output_1>output_2)
        {
            
            printf("%d\n",(int)exponant);
            break;
        }
        exponant+=1;
    }
    
}