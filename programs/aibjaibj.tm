#Q = {0,reject,accept,ra,rb,ca,cb,reject0,reject1,reject2,reject3,reject4,accept0,accept1,accept2,accept3,accept4,accept5,accept6,halt_accept}
#S = {a,b}
#G = {a,b,_,t,r,u,e,f,l,s}
#q0 = 0
#B = _
#F = {halt_accept}
#N = 3
; oldState oldSymbols newSymbols direction[lr*] newState

; 1st character
0 a__ aa_ rr* ra
0 b__ b__ *** reject 
0 ___ ___ *** reject

; reading a's
;  if read a, continue
ra a__ aa_ rr* ra
;  if read b, read b
ra b__ b_b r*r rb
;  if read _, reject
ra ___ ___ l** reject

; reading b's
;  if read a, count
rb a__ a__ *l* ca
;  if read b, continue
rb b__ b_b r*r rb
;  if read _, reject
rb ___ ___ l** reject

; Count A
;  if aa, continue
ca aa_ a__ rl* ca
;  if a_ _a or __, reject
ca a__ a__ r** reject
ca _a_ ___ *l* reject
ca ___ ___ l** reject
;  if b_, count b
ca b__ b__ **l cb
;  if ba, reject
ca ba_ b__ *** reject

; cb
;  if read bb, continue
cb b_b b__ r*l cb
;  if read ab, _b, a_ or b_, reject
cb a_b a__ *** reject
cb __b ___ *** reject
cb a__ a__ *** reject
cb b__ b__ *** reject
cb ___ ___ l** accept


reject a__ a__ r** reject
reject b__ b__ r** reject
reject ___ ___ l** reject0
reject0 a__ ___ l** reject0
reject0 b__ ___ l** reject0
reject0 ___ ___ l** reject1
reject1 ___ f__ r** reject2
reject2 ___ a__ r** reject3
reject3 ___ l__ r** reject4
reject4 ___ s__ r** reject5
reject5 ___ e__ *** halt_reject

accept a__ a__ r** accept
accept b__ b__ r** accept
accept ___ ___ l** accept0
accept0 a__ ___ l** accept0
accept0 b__ ___ l** accept0
accept0 ___ ___ l** accept1
accept1 ___ t__ r** accept2
accept2 ___ r__ r** accept3
accept3 ___ u__ r** accept4
accept4 ___ e__ r** halt_accept