#define INCL_WIN
#define INCL_DOS

#include <os2.h>
#include <stdio.h>

BOOL EXPENTRY WinHookProc(HAB hab,PQMSG pqmsg,USHORT usRemove );

int _CRT_init(void);
void _CRT_term(void);

HAB mainhab = 0;
HMODULE hmDll = 0;
BOOL loaded = FALSE;

BOOL EXPENTRY WinHookProc(HAB hab,PQMSG pqmsg,USHORT usRemove )
{
   loaded = TRUE;

   if ((pqmsg->msg == WM_CHAR) &&                  /* character message */
      !(SHORT1FROMMP(pqmsg->mp1) & KC_KEYUP) &&    /* key down */
       (SHORT1FROMMP(pqmsg->mp1) & KC_SCANCODE) && /* valid scan code */
       (CHAR4FROMMP(pqmsg->mp1) == 83) &&          /* . and del on numpad */
       (SHORT1FROMMP(pqmsg->mp2) != ',') &&        /* just make sure we
                                                      haven't already
                                                      processed it  */
       (WinGetKeyState(HWND_DESKTOP,VK_NUMLOCK)))  /* numlock on */
   {
      WinPostMsg(pqmsg->hwnd,WM_CHAR,pqmsg->mp1,MPFROM2SHORT(',',SHORT2FROMMP(pqmsg->mp2)));
      return(TRUE);
   }
   return(FALSE);
}

BOOL EXPENTRY HookInit(void)
{
   if (!loaded)
   {
      /* find desktop anchor */
      mainhab = WinQueryAnchorBlock(HWND_DESKTOP);

      /* setting hook */
      if(DosQueryModuleHandle("numcomma", &hmDll))
         return FALSE;
      return WinSetHook(mainhab, NULLHANDLE, HK_INPUT, (PFN)WinHookProc, hmDll);
   }
   return FALSE;
}

BOOL EXPENTRY HookKill(void)
{
   loaded = FALSE;
   return WinReleaseHook(mainhab, NULLHANDLE, HK_INPUT, (PFN)WinHookProc, hmDll);
}

BOOL EXPENTRY WaitLoaded(void)
{
   while(!loaded) DosSleep(10);
   return TRUE;
}
