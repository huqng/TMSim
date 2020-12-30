#Q = {0,r1,rx,r2,re,r3,accept,accept1,accept2,accept3,accept4,halt_accept,reject,reject0,reject1,reject2,reject3,reject4,reject5,halt_reject}
#S = {x,=,1}
#G = {x,=,1,t,r,u,e,f,a,l,s}
#q0 = 0
#B = _
#F = {halt_accept}
#N = 2

0 1_ 11 rr r1
0 x_ x_ ** reject 
0 =_ =_ ** reject
0 __ __ ** reject

r1 1_ 11 rr r1
r1 x_ x_ r* rx
r1 =_ =_ ** reject
r1 __ __ l* reject

rx 1_ 11 rr r2
rx x_ x_ ** reject
rx =_ =_ ** reject
rx __ __ l* reject

r2 1_ 11 rr r2
r2 x_ x_ ** reject
r2 =_ =_ r* re
r2 __ __ l* reject

re 1_ 1_ *l r3
re x_ x_ ** reject
re =_ =_ ** reject
re __ __ l* reject

r3 11 1_ rl r3
r3 1_ 1_ ** reject
r3 _1 __ l* reject
r3 x1 x_ ** reject
r3 x_ x_ ** reject
r3 =1 =_ ** reject
r3 =_ =_ ** reject
r3 __ __ l* accept

accept 1_ __ l* accept
accept x_ __ l* accept
accept =_ __ l* accept
accept __ __ ** accept1

accept1 __ t_ r* accept2
accept2 __ r_ r* accept3
accept3 __ u_ r* accept4
accept4 __ e_ ** halt_accept

reject 1_ 1_ r* reject
reject x_ x_ r* reject
reject =_ =_ r* reject
reject __ __ l* reject0

reject0 1_ __ l* reject0
reject0 x_ __ l* reject0
reject0 =_ __ l* reject0
reject0 __ __ ** reject1

reject1 __ f_ r* reject2
reject2 __ a_ r* reject3
reject3 __ l_ r* reject4
reject4 __ s_ r* reject5
reject5 __ e_ ** halt_reject

