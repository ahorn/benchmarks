(set-logic QF_BV)
(declare-fun v!19 () (_ BitVec 32))
(declare-fun t!15 () (_ BitVec 8))
(declare-fun t!14 () (_ BitVec 8))
(declare-fun t!16 () (_ BitVec 8))
(declare-fun t!17 () (_ BitVec 8))
(declare-fun t!11 () (_ BitVec 8))
(declare-fun t!10 () (_ BitVec 8))
(declare-fun t!12 () (_ BitVec 8))
(declare-fun t!13 () (_ BitVec 8))
(declare-fun t!7 () (_ BitVec 8))
(declare-fun t!6 () (_ BitVec 8))
(declare-fun t!8 () (_ BitVec 8))
(declare-fun t!9 () (_ BitVec 8))
(declare-fun t!3 () (_ BitVec 8))
(declare-fun t!2 () (_ BitVec 8))
(declare-fun t!4 () (_ BitVec 8))
(declare-fun t!5 () (_ BitVec 8))
(declare-fun t!1 () (_ BitVec 8))
(declare-fun t!0 () (_ BitVec 8))
(declare-fun t!18 () (_ BitVec 8))
(declare-fun rf!18 () (_ BitVec 8))
(declare-fun v!4 () (_ BitVec 32))
(declare-fun rf!3 () (_ BitVec 8))
(declare-fun v!8 () (_ BitVec 32))
(declare-fun v!12 () (_ BitVec 32))
(declare-fun v!16 () (_ BitVec 32))
(declare-fun rf!7 () (_ BitVec 8))
(declare-fun rf!11 () (_ BitVec 8))
(declare-fun rf!15 () (_ BitVec 8))
(assert (and true (bvsle (_ bv3 32) v!19)))
(assert (bvult (_ bv0 8) t!15))
(assert (bvult (_ bv0 8) t!14))
(assert (bvult (_ bv0 8) t!16))
(assert (bvult (_ bv0 8) t!17))
(assert (bvult (_ bv0 8) t!11))
(assert (bvult (_ bv0 8) t!10))
(assert (bvult (_ bv0 8) t!12))
(assert (bvult (_ bv0 8) t!13))
(assert (bvult (_ bv0 8) t!7))
(assert (bvult (_ bv0 8) t!6))
(assert (bvult (_ bv0 8) t!8))
(assert (bvult (_ bv0 8) t!9))
(assert (bvult (_ bv0 8) t!3))
(assert (bvult (_ bv0 8) t!2))
(assert (bvult (_ bv0 8) t!4))
(assert (bvult (_ bv0 8) t!5))
(assert (bvult (_ bv0 8) t!1))
(assert (bvult (_ bv0 8) t!0))
(assert (bvult (_ bv0 8) t!18))
(assert (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and true (bvult t!14 t!15)) (bvult t!15 t!16)) (bvult t!16 t!17)) (bvult t!10 t!11)) (bvult t!11 t!12)) (bvult t!12 t!13)) (bvult t!6 t!7)) (bvult t!7 t!8)) (bvult t!8 t!9)) (bvult t!2 t!3)) (bvult t!3 t!4)) (bvult t!4 t!5)) (bvult t!0 t!1)) (bvult t!1 t!2)) (bvult t!2 t!6)) (bvult t!6 t!10)) (bvult t!10 t!14)) (bvult t!14 t!18)))
(assert (let ((_let_0 (= (_ bv1 8) rf!18))) (let ((_let_1 (and true true))) (let ((_let_2 (= (_ bv4 8) rf!18))) (let ((_let_3 (= (_ bv0 8) rf!3))) (let ((_let_4 (= (_ bv8 8) rf!3))) (let ((_let_5 (bvadd v!8 (_ bv1 32)))) (let ((_let_6 (= (_ bv12 8) rf!3))) (let ((_let_7 (bvadd v!12 (_ bv1 32)))) (let ((_let_8 (= (_ bv16 8) rf!3))) (let ((_let_9 (bvadd v!16 (_ bv1 32)))) (let ((_let_10 (= (_ bv0 8) rf!7))) (let ((_let_11 (= (_ bv8 8) rf!7))) (let ((_let_12 (= (_ bv12 8) rf!7))) (let ((_let_13 (= (_ bv16 8) rf!7))) (let ((_let_14 (= (_ bv0 8) rf!11))) (let ((_let_15 (= (_ bv8 8) rf!11))) (let ((_let_16 (= (_ bv12 8) rf!11))) (let ((_let_17 (= (_ bv16 8) rf!11))) (let ((_let_18 (= (_ bv0 8) rf!15))) (let ((_let_19 (= (_ bv8 8) rf!15))) (let ((_let_20 (= (_ bv12 8) rf!15))) (let ((_let_21 (= (_ bv16 8) rf!15))) (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and true (=> _let_0 (and (and _let_1 (bvult t!1 t!18)) (= (_ bv0 32) v!19)))) (=> _let_2 (and (and _let_1 (bvult t!4 t!18)) (= v!4 v!19)))) (=> true (or _let_2 (or _let_0 false)))) (=> _let_3 (and (and _let_1 (bvult t!0 t!3)) (= (_ bv0 32) v!4)))) (=> _let_4 (and (and _let_1 (bvult t!8 t!3)) (= _let_5 v!4)))) (=> _let_6 (and (and _let_1 (bvult t!12 t!3)) (= _let_7 v!4)))) (=> _let_8 (and (and _let_1 (bvult t!16 t!3)) (= _let_9 v!4)))) (=> true (or _let_8 (or _let_6 (or _let_4 (or _let_3 false)))))) (=> _let_10 (and (and _let_1 (bvult t!0 t!7)) (= (_ bv0 32) v!8)))) (=> _let_11 (and (and _let_1 (bvult t!8 t!7)) (= _let_5 v!8)))) (=> _let_12 (and (and _let_1 (bvult t!12 t!7)) (= _let_7 v!8)))) (=> _let_13 (and (and _let_1 (bvult t!16 t!7)) (= _let_9 v!8)))) (=> true (or _let_13 (or _let_12 (or _let_11 (or _let_10 false)))))) (=> _let_14 (and (and _let_1 (bvult t!0 t!11)) (= (_ bv0 32) v!12)))) (=> _let_15 (and (and _let_1 (bvult t!8 t!11)) (= _let_5 v!12)))) (=> _let_16 (and (and _let_1 (bvult t!12 t!11)) (= _let_7 v!12)))) (=> _let_17 (and (and _let_1 (bvult t!16 t!11)) (= _let_9 v!12)))) (=> true (or _let_17 (or _let_16 (or _let_15 (or _let_14 false)))))) (=> _let_18 (and (and _let_1 (bvult t!0 t!15)) (= (_ bv0 32) v!16)))) (=> _let_19 (and (and _let_1 (bvult t!8 t!15)) (= _let_5 v!16)))) (=> _let_20 (and (and _let_1 (bvult t!12 t!15)) (= _let_7 v!16)))) (=> _let_21 (and (and _let_1 (bvult t!16 t!15)) (= _let_9 v!16)))) (=> true (or _let_21 (or _let_20 (or _let_19 (or _let_18 false)))))))))))))))))))))))))))))
(assert (let ((_let_0 (bvult t!15 t!16))) (let ((_let_1 (bvult t!11 t!12))) (let ((_let_2 (bvult t!7 t!8))) (let ((_let_3 (and (= (_ bv0 8) rf!3) true))) (let ((_let_4 (bvult t!0 t!8))) (let ((_let_5 (bvult t!3 t!8))) (let ((_let_6 (bvult t!0 t!12))) (let ((_let_7 (bvult t!3 t!12))) (let ((_let_8 (bvult t!0 t!16))) (let ((_let_9 (bvult t!3 t!16))) (let ((_let_10 (and (= (_ bv8 8) rf!3) true))) (let ((_let_11 (bvult t!8 t!0))) (let ((_let_12 (bvult t!3 t!0))) (let ((_let_13 (bvult t!8 t!12))) (let ((_let_14 (bvult t!8 t!16))) (let ((_let_15 (and (= (_ bv12 8) rf!3) true))) (let ((_let_16 (bvult t!12 t!0))) (let ((_let_17 (bvult t!12 t!8))) (let ((_let_18 (bvult t!12 t!16))) (let ((_let_19 (and (= (_ bv16 8) rf!3) true))) (let ((_let_20 (bvult t!16 t!0))) (let ((_let_21 (bvult t!16 t!8))) (let ((_let_22 (bvult t!16 t!12))) (let ((_let_23 (and (= (_ bv0 8) rf!7) true))) (let ((_let_24 (bvult t!7 t!12))) (let ((_let_25 (bvult t!7 t!16))) (let ((_let_26 (and (= (_ bv8 8) rf!7) true))) (let ((_let_27 (bvult t!7 t!0))) (let ((_let_28 (and (= (_ bv12 8) rf!7) true))) (let ((_let_29 (and (= (_ bv16 8) rf!7) true))) (let ((_let_30 (and (= (_ bv0 8) rf!11) true))) (let ((_let_31 (bvult t!11 t!8))) (let ((_let_32 (bvult t!11 t!16))) (let ((_let_33 (and (= (_ bv8 8) rf!11) true))) (let ((_let_34 (bvult t!11 t!0))) (let ((_let_35 (and (= (_ bv12 8) rf!11) true))) (let ((_let_36 (and (= (_ bv16 8) rf!11) true))) (let ((_let_37 (and (= (_ bv0 8) rf!15) true))) (let ((_let_38 (bvult t!15 t!8))) (let ((_let_39 (bvult t!15 t!12))) (let ((_let_40 (and (= (_ bv8 8) rf!15) true))) (let ((_let_41 (bvult t!15 t!0))) (let ((_let_42 (and (= (_ bv12 8) rf!15) true))) (let ((_let_43 (and (= (_ bv16 8) rf!15) true))) (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and true (=> (and (and (= (_ bv1 8) rf!18) true) (bvult t!1 t!4)) (bvult t!18 t!4))) (=> (and (and (= (_ bv4 8) rf!18) true) (bvult t!4 t!1)) (bvult t!18 t!1))) (=> (and _let_3 _let_4) _let_5)) (=> (and _let_3 _let_6) _let_7)) (=> (and _let_3 _let_8) _let_9)) (=> (and _let_10 _let_11) _let_12)) (=> (and _let_10 _let_13) _let_7)) (=> (and _let_10 _let_14) _let_9)) (=> (and _let_15 _let_16) _let_12)) (=> (and _let_15 _let_17) _let_5)) (=> (and _let_15 _let_18) _let_9)) (=> (and _let_19 _let_20) _let_12)) (=> (and _let_19 _let_21) _let_5)) (=> (and _let_19 _let_22) _let_7)) (=> (and _let_23 _let_4) _let_2)) (=> (and _let_23 _let_6) _let_24)) (=> (and _let_23 _let_8) _let_25)) (=> (and _let_26 _let_11) _let_27)) (=> (and _let_26 _let_13) _let_24)) (=> (and _let_26 _let_14) _let_25)) (=> (and _let_28 _let_16) _let_27)) (=> (and _let_28 _let_17) _let_2)) (=> (and _let_28 _let_18) _let_25)) (=> (and _let_29 _let_20) _let_27)) (=> (and _let_29 _let_21) _let_2)) (=> (and _let_29 _let_22) _let_24)) (=> (and _let_30 _let_4) _let_31)) (=> (and _let_30 _let_6) _let_1)) (=> (and _let_30 _let_8) _let_32)) (=> (and _let_33 _let_11) _let_34)) (=> (and _let_33 _let_13) _let_1)) (=> (and _let_33 _let_14) _let_32)) (=> (and _let_35 _let_16) _let_34)) (=> (and _let_35 _let_17) _let_31)) (=> (and _let_35 _let_18) _let_32)) (=> (and _let_36 _let_20) _let_34)) (=> (and _let_36 _let_21) _let_31)) (=> (and _let_36 _let_22) _let_1)) (=> (and _let_37 _let_4) _let_38)) (=> (and _let_37 _let_6) _let_39)) (=> (and _let_37 _let_8) _let_0)) (=> (and _let_40 _let_11) _let_41)) (=> (and _let_40 _let_13) _let_39)) (=> (and _let_40 _let_14) _let_0)) (=> (and _let_42 _let_16) _let_41)) (=> (and _let_42 _let_17) _let_38)) (=> (and _let_42 _let_18) _let_0)) (=> (and _let_43 _let_20) _let_41)) (=> (and _let_43 _let_21) _let_38)) (=> (and _let_43 _let_22) _let_39)))))))))))))))))))))))))))))))))))))))))))))))
(assert (and (and true (distinct t!1 t!4)) (distinct t!0 t!8 t!12 t!16)))
(check-sat)
