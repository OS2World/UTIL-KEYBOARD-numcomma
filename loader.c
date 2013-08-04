#define INCL_DOS
#include <os2.h>
#include <stdio.h>

BOOL EXPENTRY HookInit(void);
BOOL EXPENTRY HookKill(void);
BOOL EXPENTRY WaitLoaded(void);

int main(int argc, char *argv[])
{
   if(argc > 1)
      switch(argv[1][0])
      {
      case 'l':
         if (HookInit())
            printf("Hook successfully loaded.");
         else
            printf("Hook NOT successfully loaded.");
         WaitLoaded();
         break;
      case 'u':
         if (HookKill())
            printf("Hook successfully unloaded.");
         else
            printf("Hook NOT successfully unloaded.");
         break;
      default:
         printf("l for loading and u for unloading");
      }
   else
      printf("l for loading and u for unloading");

   return 0;
}
