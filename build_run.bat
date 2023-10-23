::https://www.oocities.org/aralbrec/spritepack/programmer-intro.htm 

rmdir out /S /Q

mkdir out

:: Criar a TAP com script de basic que carrega o loading screen e a aplicação
..\utils\bas2tap.exe -a10 -sFINAL loader\loader.bas out\loader.tap

:: Cria o binário com screenshot na zona de memoria reservada do basic??
..\utils\png2scr.exe gfx\loading.png out\loading.bin
..\utils\bin2tap -a 16384 out\loading.bin -o out\loading.tap

..\utils\png2scr.exe gfx\title.png out\title.scr

..\utils\apack.exe gfx\farol_prisao_teste_3_v2.scr out\title_a.bin

:: Compilar aplicação a partir do offset 24200??
zcc +zx -vn -m main.c -o out\out.bin -lsplib2_mk2 -zorg=24200

:: App tap, join taps, run fuse
..\utils\bin2tap.exe -a 24200 out\out.bin -o out\out.tap

copy /b out\loader.tap + out\loading.tap + out\out.tap out\demo.tap

"C:\Program Files (x86)\Fuse\fuse.exe" out\demo.tap