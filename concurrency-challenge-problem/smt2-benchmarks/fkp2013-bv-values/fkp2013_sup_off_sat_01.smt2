(set-logic ALL_SUPPORTED)

; values in memory
(declare-fun v!4 () (_ BitVec 32))
(declare-fun v!8 () (_ BitVec 32))
(declare-fun v!11 () (_ BitVec 32))

; read-from functions
(declare-fun rf!3 () Real)
(declare-fun rf!7 () Real)
(declare-fun rf!10 () Real)

; clocks
(declare-fun t!0 () Real)
(declare-fun t!1 () Real)
(declare-fun t!2 () Real)
(declare-fun t!3 () Real)
(declare-fun t!4 () Real)
(declare-fun t!5 () Real)
(declare-fun t!6 () Real)
(declare-fun t!7 () Real)
(declare-fun t!8 () Real)
(declare-fun t!9 () Real)
(declare-fun t!10 () Real)

; safety property to be checked
(assert (bvsle (_ bv1 32) v!11))

; positive clock values
(assert (< 0 t!0))
(assert (< 0 t!1))
(assert (< 0 t!2))
(assert (< 0 t!3))
(assert (< 0 t!4))
(assert (< 0 t!5))
(assert (< 0 t!6))
(assert (< 0 t!7))
(assert (< 0 t!8))
(assert (< 0 t!9))
(assert (< 0 t!10))

; program order of two threads
(assert (and
  (< t!6 t!7)
  (< t!7 t!8)
  (< t!8 t!9)
  (< t!2 t!3)
  (< t!3 t!4)
  (< t!4 t!5)
  (< t!0 t!1)
  (< t!1 t!2)
  (< t!2 t!6)
  (< t!6 t!10)))

; from-read axiom
(assert (and
  (=> (= 1 rf!10) (and (< t!1 t!10) (= (_ bv0 32) v!11)))
  (=> (= 4 rf!10) (and (< t!4 t!10) (= v!4 v!11)))
  (or (= 4 rf!10) (= 1 rf!10))
  (=> (= 0 rf!3) (and (< t!0 t!3) (= (_ bv0 32) v!4)))
  (=> (= 8 rf!3) (and (< t!8 t!3) (= (bvadd v!8 (_ bv1 32)) v!4)))
  (or (= 8 rf!3) (= 0 rf!3))
  (=> (= 0 rf!7) (and (< t!0 t!7) (= (_ bv0 32) v!8)))
  (=> (= 8 rf!7) (and (< t!8 t!7) (= (bvadd v!8 (_ bv1 32)) v!8)))
  (or (= 8 rf!7) (= 0 rf!7))))

; from-read axiom
(assert (and 
  (=> (and (= 1 rf!10) (< t!1 t!4)) (< t!10 t!4))
  (=> (and (= 4 rf!10) (< t!4 t!1)) (< t!10 t!1))
  (=> (and (= 0 rf!3) (< t!0 t!8)) (< t!3 t!8))
  (=> (and (= 8 rf!3) (< t!8 t!0)) (< t!3 t!0))
  (=> (and (= 0 rf!7) (< t!0 t!8)) (< t!7 t!8))
  (=> (and (= 8 rf!7) (< t!8 t!0)) (< t!7 t!0))))

; strict total order of write events
(assert (and (distinct t!1 t!4) (distinct t!0 t!8)))

(check-sat)
