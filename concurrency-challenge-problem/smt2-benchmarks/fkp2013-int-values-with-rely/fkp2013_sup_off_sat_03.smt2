(set-logic ALL_SUPPORTED)
(declare-fun v!8 () Int)
(declare-fun v!12 () Int)
(declare-fun v!16 () Int)
(assert (< v!8 3))
(assert (< v!12 3))
(assert (< v!16 3))
(declare-fun v!19 () Int)
(declare-fun t!15 () Real)
(declare-fun t!14 () Real)
(declare-fun t!16 () Real)
(declare-fun t!17 () Real)
(declare-fun t!11 () Real)
(declare-fun t!10 () Real)
(declare-fun t!12 () Real)
(declare-fun t!13 () Real)
(declare-fun t!7 () Real)
(declare-fun t!6 () Real)
(declare-fun t!8 () Real)
(declare-fun t!9 () Real)
(declare-fun t!3 () Real)
(declare-fun t!2 () Real)
(declare-fun t!4 () Real)
(declare-fun t!5 () Real)
(declare-fun t!1 () Real)
(declare-fun t!0 () Real)
(declare-fun t!18 () Real)
(declare-fun rf!18 () Real)
(declare-fun v!4 () Int)
(declare-fun rf!3 () Real)
(declare-fun rf!7 () Real)
(declare-fun rf!11 () Real)
(declare-fun rf!15 () Real)
(assert (and true (<= 3 v!19)))
(assert (< 0 t!15))
(assert (< 0 t!14))
(assert (< 0 t!16))
(assert (< 0 t!17))
(assert (< 0 t!11))
(assert (< 0 t!10))
(assert (< 0 t!12))
(assert (< 0 t!13))
(assert (< 0 t!7))
(assert (< 0 t!6))
(assert (< 0 t!8))
(assert (< 0 t!9))
(assert (< 0 t!3))
(assert (< 0 t!2))
(assert (< 0 t!4))
(assert (< 0 t!5))
(assert (< 0 t!1))
(assert (< 0 t!0))
(assert (< 0 t!18))
(assert (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and true (< t!14 t!15)) (< t!15 t!16)) (< t!16 t!17)) (< t!10 t!11)) (< t!11 t!12)) (< t!12 t!13)) (< t!6 t!7)) (< t!7 t!8)) (< t!8 t!9)) (< t!2 t!3)) (< t!3 t!4)) (< t!4 t!5)) (< t!0 t!1)) (< t!1 t!2)) (< t!2 t!6)) (< t!6 t!10)) (< t!10 t!14)) (< t!14 t!18)))
(assert (let ((_let_0 (= 1 rf!18))) (let ((_let_1 (and true true))) (let ((_let_2 (= 4 rf!18))) (let ((_let_3 (= 0 rf!3))) (let ((_let_4 (= 8 rf!3))) (let ((_let_5 (+ v!8 1))) (let ((_let_6 (= 12 rf!3))) (let ((_let_7 (+ v!12 1))) (let ((_let_8 (= 16 rf!3))) (let ((_let_9 (+ v!16 1))) (let ((_let_10 (= 0 rf!7))) (let ((_let_11 (= 8 rf!7))) (let ((_let_12 (= 12 rf!7))) (let ((_let_13 (= 16 rf!7))) (let ((_let_14 (= 0 rf!11))) (let ((_let_15 (= 8 rf!11))) (let ((_let_16 (= 12 rf!11))) (let ((_let_17 (= 16 rf!11))) (let ((_let_18 (= 0 rf!15))) (let ((_let_19 (= 8 rf!15))) (let ((_let_20 (= 12 rf!15))) (let ((_let_21 (= 16 rf!15))) (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and true (=> _let_0 (and (and _let_1 (< t!1 t!18)) (= 0 v!19)))) (=> _let_2 (and (and _let_1 (< t!4 t!18)) (= v!4 v!19)))) (=> true (or _let_2 (or _let_0 false)))) (=> _let_3 (and (and _let_1 (< t!0 t!3)) (= 0 v!4)))) (=> _let_4 (and (and _let_1 (< t!8 t!3)) (= _let_5 v!4)))) (=> _let_6 (and (and _let_1 (< t!12 t!3)) (= _let_7 v!4)))) (=> _let_8 (and (and _let_1 (< t!16 t!3)) (= _let_9 v!4)))) (=> true (or _let_8 (or _let_6 (or _let_4 (or _let_3 false)))))) (=> _let_10 (and (and _let_1 (< t!0 t!7)) (= 0 v!8)))) (=> _let_11 (and (and _let_1 (< t!8 t!7)) (= _let_5 v!8)))) (=> _let_12 (and (and _let_1 (< t!12 t!7)) (= _let_7 v!8)))) (=> _let_13 (and (and _let_1 (< t!16 t!7)) (= _let_9 v!8)))) (=> true (or _let_13 (or _let_12 (or _let_11 (or _let_10 false)))))) (=> _let_14 (and (and _let_1 (< t!0 t!11)) (= 0 v!12)))) (=> _let_15 (and (and _let_1 (< t!8 t!11)) (= _let_5 v!12)))) (=> _let_16 (and (and _let_1 (< t!12 t!11)) (= _let_7 v!12)))) (=> _let_17 (and (and _let_1 (< t!16 t!11)) (= _let_9 v!12)))) (=> true (or _let_17 (or _let_16 (or _let_15 (or _let_14 false)))))) (=> _let_18 (and (and _let_1 (< t!0 t!15)) (= 0 v!16)))) (=> _let_19 (and (and _let_1 (< t!8 t!15)) (= _let_5 v!16)))) (=> _let_20 (and (and _let_1 (< t!12 t!15)) (= _let_7 v!16)))) (=> _let_21 (and (and _let_1 (< t!16 t!15)) (= _let_9 v!16)))) (=> true (or _let_21 (or _let_20 (or _let_19 (or _let_18 false)))))))))))))))))))))))))))))
(assert (let ((_let_0 (< t!15 t!16))) (let ((_let_1 (< t!11 t!12))) (let ((_let_2 (< t!7 t!8))) (let ((_let_3 (and (= 0 rf!3) true))) (let ((_let_4 (< t!0 t!8))) (let ((_let_5 (< t!3 t!8))) (let ((_let_6 (< t!0 t!12))) (let ((_let_7 (< t!3 t!12))) (let ((_let_8 (< t!0 t!16))) (let ((_let_9 (< t!3 t!16))) (let ((_let_10 (and (= 8 rf!3) true))) (let ((_let_11 (< t!8 t!0))) (let ((_let_12 (< t!3 t!0))) (let ((_let_13 (< t!8 t!12))) (let ((_let_14 (< t!8 t!16))) (let ((_let_15 (and (= 12 rf!3) true))) (let ((_let_16 (< t!12 t!0))) (let ((_let_17 (< t!12 t!8))) (let ((_let_18 (< t!12 t!16))) (let ((_let_19 (and (= 16 rf!3) true))) (let ((_let_20 (< t!16 t!0))) (let ((_let_21 (< t!16 t!8))) (let ((_let_22 (< t!16 t!12))) (let ((_let_23 (and (= 0 rf!7) true))) (let ((_let_24 (< t!7 t!12))) (let ((_let_25 (< t!7 t!16))) (let ((_let_26 (and (= 8 rf!7) true))) (let ((_let_27 (< t!7 t!0))) (let ((_let_28 (and (= 12 rf!7) true))) (let ((_let_29 (and (= 16 rf!7) true))) (let ((_let_30 (and (= 0 rf!11) true))) (let ((_let_31 (< t!11 t!8))) (let ((_let_32 (< t!11 t!16))) (let ((_let_33 (and (= 8 rf!11) true))) (let ((_let_34 (< t!11 t!0))) (let ((_let_35 (and (= 12 rf!11) true))) (let ((_let_36 (and (= 16 rf!11) true))) (let ((_let_37 (and (= 0 rf!15) true))) (let ((_let_38 (< t!15 t!8))) (let ((_let_39 (< t!15 t!12))) (let ((_let_40 (and (= 8 rf!15) true))) (let ((_let_41 (< t!15 t!0))) (let ((_let_42 (and (= 12 rf!15) true))) (let ((_let_43 (and (= 16 rf!15) true))) (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and true (=> (and (and (= 1 rf!18) true) (< t!1 t!4)) (< t!18 t!4))) (=> (and (and (= 4 rf!18) true) (< t!4 t!1)) (< t!18 t!1))) (=> (and _let_3 _let_4) _let_5)) (=> (and _let_3 _let_6) _let_7)) (=> (and _let_3 _let_8) _let_9)) (=> (and _let_10 _let_11) _let_12)) (=> (and _let_10 _let_13) _let_7)) (=> (and _let_10 _let_14) _let_9)) (=> (and _let_15 _let_16) _let_12)) (=> (and _let_15 _let_17) _let_5)) (=> (and _let_15 _let_18) _let_9)) (=> (and _let_19 _let_20) _let_12)) (=> (and _let_19 _let_21) _let_5)) (=> (and _let_19 _let_22) _let_7)) (=> (and _let_23 _let_4) _let_2)) (=> (and _let_23 _let_6) _let_24)) (=> (and _let_23 _let_8) _let_25)) (=> (and _let_26 _let_11) _let_27)) (=> (and _let_26 _let_13) _let_24)) (=> (and _let_26 _let_14) _let_25)) (=> (and _let_28 _let_16) _let_27)) (=> (and _let_28 _let_17) _let_2)) (=> (and _let_28 _let_18) _let_25)) (=> (and _let_29 _let_20) _let_27)) (=> (and _let_29 _let_21) _let_2)) (=> (and _let_29 _let_22) _let_24)) (=> (and _let_30 _let_4) _let_31)) (=> (and _let_30 _let_6) _let_1)) (=> (and _let_30 _let_8) _let_32)) (=> (and _let_33 _let_11) _let_34)) (=> (and _let_33 _let_13) _let_1)) (=> (and _let_33 _let_14) _let_32)) (=> (and _let_35 _let_16) _let_34)) (=> (and _let_35 _let_17) _let_31)) (=> (and _let_35 _let_18) _let_32)) (=> (and _let_36 _let_20) _let_34)) (=> (and _let_36 _let_21) _let_31)) (=> (and _let_36 _let_22) _let_1)) (=> (and _let_37 _let_4) _let_38)) (=> (and _let_37 _let_6) _let_39)) (=> (and _let_37 _let_8) _let_0)) (=> (and _let_40 _let_11) _let_41)) (=> (and _let_40 _let_13) _let_39)) (=> (and _let_40 _let_14) _let_0)) (=> (and _let_42 _let_16) _let_41)) (=> (and _let_42 _let_17) _let_38)) (=> (and _let_42 _let_18) _let_0)) (=> (and _let_43 _let_20) _let_41)) (=> (and _let_43 _let_21) _let_38)) (=> (and _let_43 _let_22) _let_39)))))))))))))))))))))))))))))))))))))))))))))))
(assert (and (and true (distinct t!1 t!4)) (distinct t!0 t!8 t!12 t!16)))
(check-sat)
