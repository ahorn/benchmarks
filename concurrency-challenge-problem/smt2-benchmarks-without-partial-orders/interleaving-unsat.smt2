(set-logic QF_LIA)

;
; The variable "x!C", where C is a clock value of a write event,
; denotes the value of memory at that time.
;
(declare-fun x!1 () Int)
(declare-fun x!2 () Int)
(declare-fun x!3 () Int)
(declare-fun x!4 () Int)
(declare-fun x!5 () Int)
(declare-fun x!6 () Int)
(declare-fun x!7 () Int)
(declare-fun x!8 () Int)
(declare-fun x!9 () Int)

;
; Values read by read event
;
(declare-fun v!1 () Int)
(declare-fun v!2 () Int)
(declare-fun v!3 () Int)
(declare-fun v!4 () Int)
(declare-fun v!5 () Int)
(declare-fun v!6 () Int)
(declare-fun v!7 () Int)
(declare-fun v!8 () Int)
(declare-fun v!9 () Int)

;
; Clock for read and write event in a thread
;

(declare-fun c_r!1 () Int)
(declare-fun c_w!1 () Int)

(declare-fun c_r!2 () Int)
(declare-fun c_w!2 () Int)

(declare-fun c_r!3 () Int)
(declare-fun c_w!3 () Int)

(declare-fun c_r!4 () Int)
(declare-fun c_w!4 () Int)

(declare-fun c_r!5 () Int)
(declare-fun c_w!5 () Int)

(declare-fun c_r!6 () Int)
(declare-fun c_w!6 () Int)

(declare-fun c_r!7 () Int)
(declare-fun c_w!7 () Int)

(declare-fun c_r!8 () Int)
(declare-fun c_w!8 () Int)

(declare-fun c_r!9 () Int)
(declare-fun c_w!9 () Int)

;
; Strict total order on all writes on the same memory location
;
(assert (distinct c_w!1 c_w!2 c_w!3 c_w!4 c_w!5 c_w!6 c_w!7 c_w!8 c_w!9))

(assert (and (<= 1 c_w!1) (<= c_w!1 9)))
(assert (and (<= 0 c_r!1) (<= c_r!1 9)))

(assert (and (<= 1 c_w!2) (<= c_w!2 9)))
(assert (and (<= 0 c_r!2) (<= c_r!2 9)))

(assert (and (<= 1 c_w!3) (<= c_w!3 9)))
(assert (and (<= 0 c_r!3) (<= c_r!3 9)))

(assert (and (<= 1 c_w!4) (<= c_w!4 9)))
(assert (and (<= 0 c_r!4) (<= c_r!4 9)))

(assert (and (<= 1 c_w!5) (<= c_w!5 9)))
(assert (and (<= 0 c_r!5) (<= c_r!5 9)))

(assert (and (<= 1 c_w!6) (<= c_w!6 9)))
(assert (and (<= 0 c_r!6) (<= c_r!6 9)))

(assert (and (<= 1 c_w!7) (<= c_w!7 9)))
(assert (and (<= 0 c_r!7) (<= c_r!7 9)))

(assert (and (<= 1 c_w!8) (<= c_w!8 9)))
(assert (and (<= 0 c_r!8) (<= c_r!8 9)))

(assert (and (<= 1 c_w!9) (<= c_w!9 9)))
(assert (and (<= 0 c_r!9) (<= c_r!9 9)))

;;;;;;

(assert (=> (= c_r!1 0) (= v!1 0)))
(assert (=> (= c_r!1 1) (= v!1 x!1)))
(assert (=> (= c_r!1 2) (= v!1 x!2)))
(assert (=> (= c_r!1 3) (= v!1 x!3)))
(assert (=> (= c_r!1 4) (= v!1 x!4)))
(assert (=> (= c_r!1 5) (= v!1 x!5)))
(assert (=> (= c_r!1 6) (= v!1 x!6)))
(assert (=> (= c_r!1 7) (= v!1 x!7)))
(assert (=> (= c_r!1 8) (= v!1 x!8)))
(assert (=> (= c_r!1 9) (= v!1 x!9)))

(assert (<= c_r!1 c_w!1))

(assert (=> (= c_w!1 1) (= x!1 (+ v!1 1))))
(assert (=> (= c_w!1 2) (= x!2 (+ v!1 1))))
(assert (=> (= c_w!1 3) (= x!3 (+ v!1 1))))
(assert (=> (= c_w!1 4) (= x!4 (+ v!1 1))))
(assert (=> (= c_w!1 5) (= x!5 (+ v!1 1))))
(assert (=> (= c_w!1 6) (= x!6 (+ v!1 1))))
(assert (=> (= c_w!1 7) (= x!7 (+ v!1 1))))
(assert (=> (= c_w!1 8) (= x!8 (+ v!1 1))))
(assert (=> (= c_w!1 9) (= x!9 (+ v!1 1))))

;;

(assert (=> (= c_r!2 0) (= v!2 0)))
(assert (=> (= c_r!2 1) (= v!2 x!1)))
(assert (=> (= c_r!2 2) (= v!2 x!2)))
(assert (=> (= c_r!2 3) (= v!2 x!3)))
(assert (=> (= c_r!2 4) (= v!2 x!4)))
(assert (=> (= c_r!2 5) (= v!2 x!5)))
(assert (=> (= c_r!2 6) (= v!2 x!6)))
(assert (=> (= c_r!2 7) (= v!2 x!7)))
(assert (=> (= c_r!2 8) (= v!2 x!8)))
(assert (=> (= c_r!2 9) (= v!2 x!9)))

(assert (<= c_r!2 c_w!2))

(assert (=> (= c_w!2 1) (= x!1 (+ v!2 1))))
(assert (=> (= c_w!2 2) (= x!2 (+ v!2 1))))
(assert (=> (= c_w!2 3) (= x!3 (+ v!2 1))))
(assert (=> (= c_w!2 4) (= x!4 (+ v!2 1))))
(assert (=> (= c_w!2 5) (= x!5 (+ v!2 1))))
(assert (=> (= c_w!2 6) (= x!6 (+ v!2 1))))
(assert (=> (= c_w!2 7) (= x!7 (+ v!2 1))))
(assert (=> (= c_w!2 8) (= x!8 (+ v!2 1))))
(assert (=> (= c_w!2 9) (= x!9 (+ v!2 1))))

;;

(assert (=> (= c_r!3 0) (= v!3 0)))
(assert (=> (= c_r!3 1) (= v!3 x!1)))
(assert (=> (= c_r!3 2) (= v!3 x!2)))
(assert (=> (= c_r!3 3) (= v!3 x!3)))
(assert (=> (= c_r!3 4) (= v!3 x!4)))
(assert (=> (= c_r!3 5) (= v!3 x!5)))
(assert (=> (= c_r!3 6) (= v!3 x!6)))
(assert (=> (= c_r!3 7) (= v!3 x!7)))
(assert (=> (= c_r!3 8) (= v!3 x!8)))
(assert (=> (= c_r!3 9) (= v!3 x!9)))

(assert (<= c_r!3 c_w!3))

(assert (=> (= c_w!3 1) (= x!1 (+ v!3 1))))
(assert (=> (= c_w!3 2) (= x!2 (+ v!3 1))))
(assert (=> (= c_w!3 3) (= x!3 (+ v!3 1))))
(assert (=> (= c_w!3 4) (= x!4 (+ v!3 1))))
(assert (=> (= c_w!3 5) (= x!5 (+ v!3 1))))
(assert (=> (= c_w!3 6) (= x!6 (+ v!3 1))))
(assert (=> (= c_w!3 7) (= x!7 (+ v!3 1))))
(assert (=> (= c_w!3 8) (= x!8 (+ v!3 1))))
(assert (=> (= c_w!3 9) (= x!9 (+ v!3 1))))

;;

(assert (=> (= c_r!4 0) (= v!4 0)))
(assert (=> (= c_r!4 1) (= v!4 x!1)))
(assert (=> (= c_r!4 2) (= v!4 x!2)))
(assert (=> (= c_r!4 3) (= v!4 x!3)))
(assert (=> (= c_r!4 4) (= v!4 x!4)))
(assert (=> (= c_r!4 5) (= v!4 x!5)))
(assert (=> (= c_r!4 6) (= v!4 x!6)))
(assert (=> (= c_r!4 7) (= v!4 x!7)))
(assert (=> (= c_r!4 8) (= v!4 x!8)))
(assert (=> (= c_r!4 9) (= v!4 x!9)))

(assert (<= c_r!4 c_w!4))

(assert (=> (= c_w!4 1) (= x!1 (+ v!4 1))))
(assert (=> (= c_w!4 2) (= x!2 (+ v!4 1))))
(assert (=> (= c_w!4 3) (= x!3 (+ v!4 1))))
(assert (=> (= c_w!4 4) (= x!4 (+ v!4 1))))
(assert (=> (= c_w!4 5) (= x!5 (+ v!4 1))))
(assert (=> (= c_w!4 6) (= x!6 (+ v!4 1))))
(assert (=> (= c_w!4 7) (= x!7 (+ v!4 1))))
(assert (=> (= c_w!4 8) (= x!8 (+ v!4 1))))
(assert (=> (= c_w!4 9) (= x!9 (+ v!4 1))))

;;

(assert (=> (= c_r!5 0) (= v!5 0)))
(assert (=> (= c_r!5 1) (= v!5 x!1)))
(assert (=> (= c_r!5 2) (= v!5 x!2)))
(assert (=> (= c_r!5 3) (= v!5 x!3)))
(assert (=> (= c_r!5 4) (= v!5 x!4)))
(assert (=> (= c_r!5 5) (= v!5 x!5)))
(assert (=> (= c_r!5 6) (= v!5 x!6)))
(assert (=> (= c_r!5 7) (= v!5 x!7)))
(assert (=> (= c_r!5 8) (= v!5 x!8)))
(assert (=> (= c_r!5 9) (= v!5 x!9)))

(assert (<= c_r!5 c_w!5))

(assert (=> (= c_w!5 1) (= x!1 (+ v!5 1))))
(assert (=> (= c_w!5 2) (= x!2 (+ v!5 1))))
(assert (=> (= c_w!5 3) (= x!3 (+ v!5 1))))
(assert (=> (= c_w!5 4) (= x!4 (+ v!5 1))))
(assert (=> (= c_w!5 5) (= x!5 (+ v!5 1))))
(assert (=> (= c_w!5 6) (= x!6 (+ v!5 1))))
(assert (=> (= c_w!5 7) (= x!7 (+ v!5 1))))
(assert (=> (= c_w!5 8) (= x!8 (+ v!5 1))))
(assert (=> (= c_w!5 9) (= x!9 (+ v!5 1))))

;;

(assert (=> (= c_r!6 0) (= v!6 0)))
(assert (=> (= c_r!6 1) (= v!6 x!1)))
(assert (=> (= c_r!6 2) (= v!6 x!2)))
(assert (=> (= c_r!6 3) (= v!6 x!3)))
(assert (=> (= c_r!6 4) (= v!6 x!4)))
(assert (=> (= c_r!6 5) (= v!6 x!5)))
(assert (=> (= c_r!6 6) (= v!6 x!6)))
(assert (=> (= c_r!6 7) (= v!6 x!7)))
(assert (=> (= c_r!6 8) (= v!6 x!8)))
(assert (=> (= c_r!6 9) (= v!6 x!9)))

(assert (<= c_r!6 c_w!6))

(assert (=> (= c_w!6 1) (= x!1 (+ v!6 1))))
(assert (=> (= c_w!6 2) (= x!2 (+ v!6 1))))
(assert (=> (= c_w!6 3) (= x!3 (+ v!6 1))))
(assert (=> (= c_w!6 4) (= x!4 (+ v!6 1))))
(assert (=> (= c_w!6 5) (= x!5 (+ v!6 1))))
(assert (=> (= c_w!6 6) (= x!6 (+ v!6 1))))
(assert (=> (= c_w!6 7) (= x!7 (+ v!6 1))))
(assert (=> (= c_w!6 8) (= x!8 (+ v!6 1))))
(assert (=> (= c_w!6 9) (= x!9 (+ v!6 1))))

;;

(assert (=> (= c_r!7 0) (= v!7 0)))
(assert (=> (= c_r!7 1) (= v!7 x!1)))
(assert (=> (= c_r!7 2) (= v!7 x!2)))
(assert (=> (= c_r!7 3) (= v!7 x!3)))
(assert (=> (= c_r!7 4) (= v!7 x!4)))
(assert (=> (= c_r!7 5) (= v!7 x!5)))
(assert (=> (= c_r!7 6) (= v!7 x!6)))
(assert (=> (= c_r!7 7) (= v!7 x!7)))
(assert (=> (= c_r!7 8) (= v!7 x!8)))
(assert (=> (= c_r!7 9) (= v!7 x!9)))

(assert (<= c_r!7 c_w!7))

(assert (=> (= c_w!7 1) (= x!1 (+ v!7 1))))
(assert (=> (= c_w!7 2) (= x!2 (+ v!7 1))))
(assert (=> (= c_w!7 3) (= x!3 (+ v!7 1))))
(assert (=> (= c_w!7 4) (= x!4 (+ v!7 1))))
(assert (=> (= c_w!7 5) (= x!5 (+ v!7 1))))
(assert (=> (= c_w!7 6) (= x!6 (+ v!7 1))))
(assert (=> (= c_w!7 7) (= x!7 (+ v!7 1))))
(assert (=> (= c_w!7 8) (= x!8 (+ v!7 1))))
(assert (=> (= c_w!7 9) (= x!9 (+ v!7 1))))

;;

(assert (=> (= c_r!8 0) (= v!8 0)))
(assert (=> (= c_r!8 1) (= v!8 x!1)))
(assert (=> (= c_r!8 2) (= v!8 x!2)))
(assert (=> (= c_r!8 3) (= v!8 x!3)))
(assert (=> (= c_r!8 4) (= v!8 x!4)))
(assert (=> (= c_r!8 5) (= v!8 x!5)))
(assert (=> (= c_r!8 6) (= v!8 x!6)))
(assert (=> (= c_r!8 7) (= v!8 x!7)))
(assert (=> (= c_r!8 8) (= v!8 x!8)))
(assert (=> (= c_r!8 9) (= v!8 x!9)))

(assert (<= c_r!8 c_w!8))

(assert (=> (= c_w!8 1) (= x!1 (+ v!8 1))))
(assert (=> (= c_w!8 2) (= x!2 (+ v!8 1))))
(assert (=> (= c_w!8 3) (= x!3 (+ v!8 1))))
(assert (=> (= c_w!8 4) (= x!4 (+ v!8 1))))
(assert (=> (= c_w!8 5) (= x!5 (+ v!8 1))))
(assert (=> (= c_w!8 6) (= x!6 (+ v!8 1))))
(assert (=> (= c_w!8 7) (= x!7 (+ v!8 1))))
(assert (=> (= c_w!8 8) (= x!8 (+ v!8 1))))
(assert (=> (= c_w!8 9) (= x!9 (+ v!8 1))))

;;

(assert (=> (= c_r!9 0) (= v!9 0)))
(assert (=> (= c_r!9 1) (= v!9 x!1)))
(assert (=> (= c_r!9 2) (= v!9 x!2)))
(assert (=> (= c_r!9 3) (= v!9 x!3)))
(assert (=> (= c_r!9 4) (= v!9 x!4)))
(assert (=> (= c_r!9 5) (= v!9 x!5)))
(assert (=> (= c_r!9 6) (= v!9 x!6)))
(assert (=> (= c_r!9 7) (= v!9 x!7)))
(assert (=> (= c_r!9 8) (= v!9 x!8)))
(assert (=> (= c_r!9 9) (= v!9 x!9)))

(assert (<= c_r!9 c_w!9))

(assert (=> (= c_w!9 1) (= x!1 (+ v!9 1))))
(assert (=> (= c_w!9 2) (= x!2 (+ v!9 1))))
(assert (=> (= c_w!9 3) (= x!3 (+ v!9 1))))
(assert (=> (= c_w!9 4) (= x!4 (+ v!9 1))))
(assert (=> (= c_w!9 5) (= x!5 (+ v!9 1))))
(assert (=> (= c_w!9 6) (= x!6 (+ v!9 1))))
(assert (=> (= c_w!9 7) (= x!7 (+ v!9 1))))
(assert (=> (= c_w!9 8) (= x!8 (+ v!9 1))))
(assert (=> (= c_w!9 9) (= x!9 (+ v!9 1))))

;;;;;;

(assert (> x!9 9))

(check-sat)
