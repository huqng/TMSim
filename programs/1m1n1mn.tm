#Q = {0,r1,rx,r2,re,r3,accept,accept1,accept2,accept3,accept4,halt_accept,reject,reject0,reject1,reject2,reject3,reject4,reject5,halt_reject}
#S = {x,=,1}
#G = {x,=,1,t,r,u,e,f,a,l,s}
#q0 = 0
#B = _
#F = {halt_accept}
#N = 2

; 第一步需要读到1，往第二条纸带复制
0 1_ 11 rr r1
0 x_ x_ ** reject 
0 =_ =_ ** reject
0 __ __ ** reject

; 读到1之后，可以读1或x，其他reject
; 读到1则继续复制
r1 1_ 11 rr r1
; 读到x则进入rx
r1 x_ x_ r* rx
r1 =_ =_ ** reject
r1 __ __ l* reject

; rx：需要读第二段1，将读到的1复制到第二条纸带，进入r2，其他情况都reject
rx 1_ 11 rr r2
rx x_ x_ ** reject
rx =_ =_ ** reject
rx __ __ l* reject

; r2：读到1则继续，读到=则进入re，其他情况reject
r2 1_ 11 rr r2
r2 x_ x_ ** reject
r2 =_ =_ r* re
r2 __ __ l* reject

; re：读到了一个=，需要再读1，进入r3，其他情况都reject
re 1_ 1_ *l r3
re x_ x_ ** reject
re =_ =_ ** reject
re __ __ l* reject

; r3：每读一个1就删去第二条纸带中的一个1
r3 11 1_ rl r3
; 读到1而第二条纸带空、输入空而第二条纸带非空，reject
r3 1_ 1_ ** reject
r3 _1 __ l* reject
; 读到x或=，reject
r3 x1 x_ ** reject
r3 x_ x_ ** reject
r3 =1 =_ ** reject
r3 =_ =_ ** reject
; 只有读到输入和第二条纸带同时空才accept，表示第三段1的长度是前两段之和
r3 __ __ l* accept

; 逻辑同另一个
accept 1_ 1_ r* accept
accept x_ x_ r* accept
accept =_ =_ r* accept
accept __ __ l* accept0

accept0 1_ __ l* accept0
accept0 x_ __ l* accept0
accept0 =_ __ l* accept0
accept0 __ __ ** accept1

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

