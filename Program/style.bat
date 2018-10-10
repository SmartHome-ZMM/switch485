

@echo off

set astyle="D:\Program Files\AStyle\bin\astyle.exe"

REM 循环遍历目录


for /r . %%f in (*.cpp;*.c) do %astyle% --style=ansi -s4 -T -S -N -Y -m2 -M40 -f -p --convert-tabs "%%f"
for /r . %%f in (*.hpp;*.h) do %astyle% --style=ansi -s4 -T -S -N -Y -m2 -M40 -f -p --convert-tabs "%%f"

REM 删除所有的astyle生成文件

for /r . %%a in (*.orig) do del "%%a"

pause
asty