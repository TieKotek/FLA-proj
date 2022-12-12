#Q = {q0,q1,q2,q3,q4}
#S = {a,b}
#G = {a,b,_}
#q0 = q0
#B = _
#F = {q4}
#N = 1

q0 a _ l q1
q0 b _ l q2
q0 _ _ l q4
q1 _ a r q3
q2 _ b r q3
q3 _ _ r q0