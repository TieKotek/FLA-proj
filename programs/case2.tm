#Q = {start,count1,count2,move,go_back,accept,accept1,accept2,accept3,accept4,halt_accept,reject,reject2,reject3,reject4,reject5,halt_reject}
#S = {1}
#G = {1,t,r,u,e,f,a,l,s,_}
#q0 = start
#B = _
#F = {halt_accept}
#N = 2

start 1_ 11 ** move
start __ __ ** accept
count1 1_ 11 *r count2
count2 1_ 11 ** move
move 11 11 rl move
move _1 _1 l* reject
move 1_ 1_ *r go_back
move __ __ l* accept
go_back 11 11 *r go_back
go_back 1_ 1_ ** count1

accept 1_ __ l* accept
accept __ __ ** accept1
accept1 __ t_ r* accept2
accept2 __ r_ r* accept3
accept3 __ u_ r* accept4
accept4 __ e_ ** halt_accept

reject 11 _1 l* reject
reject _1 f1 r* reject2
reject2 _1 a1 r* reject3
reject3 _1 l1 r* reject4
reject4 _1 s1 r* reject5
reject5 _1 e1 ** halt_reject