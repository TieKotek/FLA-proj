#Q = {start,restart,final,verify_end,goLeftEnd,verify_empty,goRightA,goRightB,cAndgoRightA,cAndgoRightB,goLeft,cAndGoLeft,halt_reject,halt_accept}
#S = {a,b,c}
#G = {a,b,c,x,_}
#q0 = start
#B = _
#F = {halt_accept}
#N = 1

start _ _ r halt_reject
start c c r verify_empty
start a x r goRightA
start b x r goRightB

verify_empty _ _ r halt_accept
verify_empty * * r halt_reject

goRightA a a r goRightA
goRightA b b r goRightA
goRightA c c r cAndgoRightA

goRightB a a r goRightB
goRightB b b r goRightB
goRightB c c r cAndgoRightB

cAndgoRightA x x r cAndgoRightA
cAndgoRightA a x r verify_end
cAndgoRightA b b r halt_reject
cAndgoRightA c c r halt_reject

cAndgoRightB x x r cAndgoRightB
cAndgoRightB a a r halt_reject
cAndgoRightB b x r verify_end
cAndgoRightB c c r halt_reject

verify_end _ _ l goLeftEnd
verify_end * * l goLeft

goLeft a a l goLeft
goLeft b b l goLeft
goLeft x x l goLeft
goLeft c c l cAndGoLeft

goLeftEnd a a l goLeftEnd
goLeftEnd b b l goLeftEnd
goLeftEnd x x l goLeftEnd
goLeftEnd c c l final

final x x r halt_accept
final a a r halt_reject
final b b r halt_reject
final c c r halt_reject
final _ _ r halt_reject

cAndGoLeft a a l cAndGoLeft
cAndGoLeft b b l cAndGoLeft
cAndGoLeft x x r restart

restart c c r halt_reject
restart a x r goRightA
restart b x r goRightB