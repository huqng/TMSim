#Q = {0,reject,accept,ra,rb,ca,cb,reject0,reject1,reject2,reject3,reject4,accept0,accept1,accept2,accept3,accept4,accept5,accept6,halt_accept}
#S = {a,b}
#G = {a,b,_,t,r,u,e,f,l,s}
#q0 = 0
#B = _
#F = {halt_accept}
#N = 3
; oldState oldSymbols newSymbols direction[lr*] newState

; 第一个字符，如果是b或_则reject；如果是a则进入状态ra，并复制到第二条纸带
0 a__ aa_ rr* ra
0 b__ b__ *** reject 
0 ___ ___ *** reject

; 第一个字符是a的情况
;  如果读到a，复制到第二条纸带
ra a__ aa_ rr* ra
;  如果读到b，进入状态rb，复制到第三条纸带
ra b__ b_b r*r rb
;  读到_则reject
ra ___ ___ l** reject

; 已经读到b的情况
;  如果遇到a，进入ca，计数
rb a__ a__ *l* ca
;  读到b则继续向第三条纸带复制
rb b__ b_b r*r rb
;  读到_则reject
rb ___ ___ l** reject

; 状态ca，计数
;  读到a、第二条纸带非空，则删去第二条纸带的a
ca aa_ a__ rl* ca
;  读到a且第二条纸带空、输入读完、或读到b且第二条纸带非空，reject
ca a__ a__ *** reject
ca _a_ ___ *** reject
ca ___ ___ l** reject
ca ba_ b__ *** reject
;  读到b且第二条纸带空，进入cb，计数b（第二段a和第一段a数量相同）
ca b__ b__ **l cb

; 状态cb
;  读到b且第三条纸带上非空，删去一个
cb b_b b__ r*l cb
;  输入空且第三条纸带空，接受
cb ___ ___ l** accept
;  其他情况都reject
;  if read ab, _b, a_ or b_, reject
cb a_b a__ *** reject
cb a__ a__ *** reject
cb __b ___ l** reject
cb b__ b__ *** reject

; 向右直到_
reject a__ a__ r** reject
reject b__ b__ r** reject
; 到达_后左移一格
reject ___ ___ l** reject0
; 向左删除
reject0 a__ ___ l** reject0
reject0 b__ ___ l** reject0
reject0 ___ ___ l** reject1
; 删完后写false
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