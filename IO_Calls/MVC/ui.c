#include <stdio.h>
#include <viml.h>


void displaymenu()
{
   int choice;
   char path[100];
 
	while(1){


		printf("\nEnter Choice");
		printf("\n1.Show Image \n2.Convert Image \n3.Save File");
                scanf("%d",&choice);

             scanf("%s",path);
               switch(choice){

                 case 1:
                         printf("\nImage : %s",path);
                         vdrawImage(path);
                     break;
		 case 2:
                         vconvertImage(path);
		    break;
                 case 3:
                        vsaveImage(path); 
                     break;
               }

	}
    
}


int _init()
{
   printf("\nHello World");
}

main()
{

   displaymenu();
}
