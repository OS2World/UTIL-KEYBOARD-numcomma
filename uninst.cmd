/* Install 'dll' entry into USER INI file */

call RxFuncAdd 'SysLoadFuncs', 'RexxUtil', 'SysLoadFuncs'
call SysLoadFuncs

dll = 'NUMCOMMA'

/* get INI entry, and strip out null terminator */
string = SysIni("USER","SYS_DLLS","LoadOneTime")
string = left(string,length(string)-1)

flag = 0
do wrd = 1 to WORDS(string)
  if word(string,wrd) = dll then
     if SysIni("USER","SYS_DLLS","LoadOneTime",delword(string,wrd,1)||d2c(0)) = '' then
        say dll 'successfully uninstalled.'
end
