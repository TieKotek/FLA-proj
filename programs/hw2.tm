#Q = {q0,q1,q2,q3,halt_reject,halt_accept}
#S = {1,#}
#G = {1,#,_}
#q0 = q0
#B = _
#F = {halt_accept}
#N = 1

q0 1 1 r q0
q0 # _ r q1
q0 _ _ r halt_reject
q1 1 _ l q2
q1 # # r halt_reject
q1 _ _ l halt_accept
q2 _ 1 r q3
q3 _ _ r q1