#Q = {start,cp,ready,move_0,move_1,accept}
#S = {0,1}
#G = {0,1,_}
#q0 = start
#B = _
#F = {accept}
#N = 2

start *_ *_ ** cp
start __ __ ** accept

cp 0_ 00 rr cp
cp 1_ 11 rr cp
cp __ __ ll ready

ready 0* 0* *l move_0
ready 1* 1* *l move_1

move_0 *0 00 ll move_0
move_0 *1 11 ll move_0
move_0 *_ 0_ *r accept

move_1 *0 00 ll move_1
move_1 *1 11 ll move_1
move_1 *_ 1_ *r accept