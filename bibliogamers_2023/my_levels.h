extern uchar level_0[];
extern uchar level_1[];
extern uchar level_2[];
extern uchar level_3[];
extern uchar level_4[];
extern uchar level_5[];

// 32 x 24

#asm

._level_4
defb @00001111, @11111111, @00000000, @00000000
defb @00010000, @00000000, @10000000, @00000000
defb @01110000, @00000000, @01100000, @00000000
defb @10000000, @00000000, @00010000, @00000000
defb @10000000, @00000000, @00010000, @00000000
defb @10000011, @11111100, @00010000, @00000000
defb @10000010, @00000100, @00010000, @00000000
defb @10000010, @00000100, @00010000, @00000000
defb @10000011, @11000100, @00010000, @00000000
defb @10000000, @00100100, @00010000, @00000000
defb @10000000, @00100100, @00010000, @00000000
defb @01111111, @11000011, @11100000, @00000000
defb @00000000, @00000000, @00000000, @00000000
defb @00000000, @00000000, @00000000, @00000000
defb @00000000, @00000000, @00000000, @00000000
defb @00000000, @00000000, @00000000, @00000000
defb @00000000, @00000000, @00000000, @00000000

._level_3
defb @00000001, @10000000, @00000000, @00000000
defb @00000010, @01000000, @00000000, @00000000
defb @00000010, @01000000, @00000000, @00000000
defb @00001100, @00111100, @00111100, @00000000
defb @00010000, @00000010, @01000010, @00000000
defb @00010000, @00000010, @01000010, @00000000
defb @00010000, @00000001, @10000010, @00000000
defb @01100000, @00000000, @00000010, @00000000
defb @10000000, @00000000, @00000010, @00000000
defb @10000000, @00000000, @00000010, @00000000
defb @01110000, @00000000, @00001100, @00000000
defb @00010000, @00000000, @00001000, @00000000
defb @00001111, @11100001, @11110000, @00000000
defb @00000000, @00010010, @00000000, @00000000
defb @00000000, @00010010, @00000000, @00000000
defb @00000000, @00001100, @00000000, @00000000
defb @00000000, @00000000, @00000000, @00000000


._level_2
defb @00000000, @00111100, @00111100, @00000000
defb @00000000, @01000010, @01000010, @00000000
defb @00000000, @01000010, @01000010, @00000000
defb @01111111, @10000001, @10000010, @00000000
defb @10000000, @00000000, @00000010, @00000000
defb @10000000, @00000000, @00000010, @00000000
defb @01100001, @11111111, @10000010, @00000000
defb @00010010, @00000000, @01000010, @00000000
defb @00010010, @00000000, @01000010, @00000000
defb @00010010, @00000000, @00111100, @00000000
defb @00010010, @00000000, @00000000, @00000000
defb @00001100, @00000000, @00000000, @00000000
defb @00000000, @00000000, @00000000, @00000000
defb @00000000, @00000000, @00000000, @00000000
defb @00000000, @00000000, @00000000, @00000000
defb @00000000, @00000000, @00000000, @00000000
defb @00000000, @00000000, @00000000, @00000000

._level_1
defb @00000011, @11110000, @00000000, @00000000
defb @00000100, @00001000, @00000000, @00000000
defb @00000100, @00001000, @00000000, @00000000
defb @00000100, @01110000, @00000000, @00000000
defb @00000100, @10000000, @00000000, @00000000
defb @00000100, @10000000, @00000000, @00000000
defb @00000100, @10000000, @00000000, @00000000
defb @01111000, @01110000, @00000000, @00000000
defb @10000000, @00001000, @00000000, @00000000
defb @10000000, @00001000, @00000000, @00000000
defb @01111000, @00001000, @00000000, @00000000
defb @00000100, @00001000, @00000000, @00000000
defb @00000100, @00001000, @00000000, @00000000
defb @00000100, @00001000, @00000000, @00000000
defb @00000100, @00001000, @00000000, @00000000
defb @00000011, @11110000, @00000000, @00000000
defb @00000000, @00000000, @00000000, @00000000
                           

._level_0
defb @01111110, @00000000, @00000000, @00000000
defb @10000001, @00000000, @00000000, @00000000
defb @10000001, @00000000, @00000000, @00000000
defb @10000001, @00000000, @00000000, @00000000
defb @10000001, @00000000, @00000000, @00000000
defb @10000001, @00000000, @00000000, @00000000
defb @10000001, @00000000, @00000000, @00000000
defb @01111110, @00000000, @00000000, @00000000
defb @00000000, @00000000, @00000000, @00000000


._level_5
defb @01111111, @11111110, @00000000, @00000000
defb @10000000, @00000000, @00000000, @00000000
defb @10000000, @00000000, @00000000, @00000000
defb @10001111, @11111110, @00000000, @00000000
defb @10010000, @00000000, @00000000, @00000000
defb @10010000, @00000000, @00000000, @00000000
defb @10010000, @00000000, @00000000, @00000000
defb @01100000, @00000000, @00000000, @00000000
defb @00000000, @00000000, @00000000, @00000000



#endasm