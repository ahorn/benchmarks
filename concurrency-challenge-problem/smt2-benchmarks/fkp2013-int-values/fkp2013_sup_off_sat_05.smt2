(set-logic QF_LIRA)
(declare-fun v!27 () Int)
(declare-fun t!23 () Real)
(declare-fun t!22 () Real)
(declare-fun t!24 () Real)
(declare-fun t!25 () Real)
(declare-fun t!19 () Real)
(declare-fun t!18 () Real)
(declare-fun t!20 () Real)
(declare-fun t!21 () Real)
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
(declare-fun t!26 () Real)
(declare-fun rf!26 () Real)
(declare-fun v!4 () Int)
(declare-fun rf!3 () Real)
(declare-fun v!8 () Int)
(declare-fun v!12 () Int)
(declare-fun v!16 () Int)
(declare-fun v!20 () Int)
(declare-fun v!24 () Int)
(declare-fun rf!7 () Real)
(declare-fun rf!11 () Real)
(declare-fun rf!15 () Real)
(declare-fun rf!19 () Real)
(declare-fun rf!23 () Real)
(assert (and true (<= 5 v!27)))
(assert (< 0 t!23))
(assert (< 0 t!22))
(assert (< 0 t!24))
(assert (< 0 t!25))
(assert (< 0 t!19))
(assert (< 0 t!18))
(assert (< 0 t!20))
(assert (< 0 t!21))
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
(assert (< 0 t!26))
(assert (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and true (< t!22 t!23)) (< t!23 t!24)) (< t!24 t!25)) (< t!18 t!19)) (< t!19 t!20)) (< t!20 t!21)) (< t!14 t!15)) (< t!15 t!16)) (< t!16 t!17)) (< t!10 t!11)) (< t!11 t!12)) (< t!12 t!13)) (< t!6 t!7)) (< t!7 t!8)) (< t!8 t!9)) (< t!2 t!3)) (< t!3 t!4)) (< t!4 t!5)) (< t!0 t!1)) (< t!1 t!2)) (< t!2 t!6)) (< t!6 t!10)) (< t!10 t!14)) (< t!14 t!18)) (< t!18 t!22)) (< t!22 t!26)))
(assert (let ((_let_0 (= 1 rf!26))) (let ((_let_1 (and true true))) (let ((_let_2 (= 4 rf!26))) (let ((_let_3 (= 0 rf!3))) (let ((_let_4 (= 8 rf!3))) (let ((_let_5 (+ v!8 1))) (let ((_let_6 (= 12 rf!3))) (let ((_let_7 (+ v!12 1))) (let ((_let_8 (= 16 rf!3))) (let ((_let_9 (+ v!16 1))) (let ((_let_10 (= 20 rf!3))) (let ((_let_11 (+ v!20 1))) (let ((_let_12 (= 24 rf!3))) (let ((_let_13 (+ v!24 1))) (let ((_let_14 (= 0 rf!7))) (let ((_let_15 (= 8 rf!7))) (let ((_let_16 (= 12 rf!7))) (let ((_let_17 (= 16 rf!7))) (let ((_let_18 (= 20 rf!7))) (let ((_let_19 (= 24 rf!7))) (let ((_let_20 (= 0 rf!11))) (let ((_let_21 (= 8 rf!11))) (let ((_let_22 (= 12 rf!11))) (let ((_let_23 (= 16 rf!11))) (let ((_let_24 (= 20 rf!11))) (let ((_let_25 (= 24 rf!11))) (let ((_let_26 (= 0 rf!15))) (let ((_let_27 (= 8 rf!15))) (let ((_let_28 (= 12 rf!15))) (let ((_let_29 (= 16 rf!15))) (let ((_let_30 (= 20 rf!15))) (let ((_let_31 (= 24 rf!15))) (let ((_let_32 (= 0 rf!19))) (let ((_let_33 (= 8 rf!19))) (let ((_let_34 (= 12 rf!19))) (let ((_let_35 (= 16 rf!19))) (let ((_let_36 (= 20 rf!19))) (let ((_let_37 (= 24 rf!19))) (let ((_let_38 (= 0 rf!23))) (let ((_let_39 (= 8 rf!23))) (let ((_let_40 (= 12 rf!23))) (let ((_let_41 (= 16 rf!23))) (let ((_let_42 (= 20 rf!23))) (let ((_let_43 (= 24 rf!23))) (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and true (=> _let_0 (and (and _let_1 (< t!1 t!26)) (= 0 v!27)))) (=> _let_2 (and (and _let_1 (< t!4 t!26)) (= v!4 v!27)))) (=> true (or _let_2 (or _let_0 false)))) (=> _let_3 (and (and _let_1 (< t!0 t!3)) (= 0 v!4)))) (=> _let_4 (and (and _let_1 (< t!8 t!3)) (= _let_5 v!4)))) (=> _let_6 (and (and _let_1 (< t!12 t!3)) (= _let_7 v!4)))) (=> _let_8 (and (and _let_1 (< t!16 t!3)) (= _let_9 v!4)))) (=> _let_10 (and (and _let_1 (< t!20 t!3)) (= _let_11 v!4)))) (=> _let_12 (and (and _let_1 (< t!24 t!3)) (= _let_13 v!4)))) (=> true (or _let_12 (or _let_10 (or _let_8 (or _let_6 (or _let_4 (or _let_3 false)))))))) (=> _let_14 (and (and _let_1 (< t!0 t!7)) (= 0 v!8)))) (=> _let_15 (and (and _let_1 (< t!8 t!7)) (= _let_5 v!8)))) (=> _let_16 (and (and _let_1 (< t!12 t!7)) (= _let_7 v!8)))) (=> _let_17 (and (and _let_1 (< t!16 t!7)) (= _let_9 v!8)))) (=> _let_18 (and (and _let_1 (< t!20 t!7)) (= _let_11 v!8)))) (=> _let_19 (and (and _let_1 (< t!24 t!7)) (= _let_13 v!8)))) (=> true (or _let_19 (or _let_18 (or _let_17 (or _let_16 (or _let_15 (or _let_14 false)))))))) (=> _let_20 (and (and _let_1 (< t!0 t!11)) (= 0 v!12)))) (=> _let_21 (and (and _let_1 (< t!8 t!11)) (= _let_5 v!12)))) (=> _let_22 (and (and _let_1 (< t!12 t!11)) (= _let_7 v!12)))) (=> _let_23 (and (and _let_1 (< t!16 t!11)) (= _let_9 v!12)))) (=> _let_24 (and (and _let_1 (< t!20 t!11)) (= _let_11 v!12)))) (=> _let_25 (and (and _let_1 (< t!24 t!11)) (= _let_13 v!12)))) (=> true (or _let_25 (or _let_24 (or _let_23 (or _let_22 (or _let_21 (or _let_20 false)))))))) (=> _let_26 (and (and _let_1 (< t!0 t!15)) (= 0 v!16)))) (=> _let_27 (and (and _let_1 (< t!8 t!15)) (= _let_5 v!16)))) (=> _let_28 (and (and _let_1 (< t!12 t!15)) (= _let_7 v!16)))) (=> _let_29 (and (and _let_1 (< t!16 t!15)) (= _let_9 v!16)))) (=> _let_30 (and (and _let_1 (< t!20 t!15)) (= _let_11 v!16)))) (=> _let_31 (and (and _let_1 (< t!24 t!15)) (= _let_13 v!16)))) (=> true (or _let_31 (or _let_30 (or _let_29 (or _let_28 (or _let_27 (or _let_26 false)))))))) (=> _let_32 (and (and _let_1 (< t!0 t!19)) (= 0 v!20)))) (=> _let_33 (and (and _let_1 (< t!8 t!19)) (= _let_5 v!20)))) (=> _let_34 (and (and _let_1 (< t!12 t!19)) (= _let_7 v!20)))) (=> _let_35 (and (and _let_1 (< t!16 t!19)) (= _let_9 v!20)))) (=> _let_36 (and (and _let_1 (< t!20 t!19)) (= _let_11 v!20)))) (=> _let_37 (and (and _let_1 (< t!24 t!19)) (= _let_13 v!20)))) (=> true (or _let_37 (or _let_36 (or _let_35 (or _let_34 (or _let_33 (or _let_32 false)))))))) (=> _let_38 (and (and _let_1 (< t!0 t!23)) (= 0 v!24)))) (=> _let_39 (and (and _let_1 (< t!8 t!23)) (= _let_5 v!24)))) (=> _let_40 (and (and _let_1 (< t!12 t!23)) (= _let_7 v!24)))) (=> _let_41 (and (and _let_1 (< t!16 t!23)) (= _let_9 v!24)))) (=> _let_42 (and (and _let_1 (< t!20 t!23)) (= _let_11 v!24)))) (=> _let_43 (and (and _let_1 (< t!24 t!23)) (= _let_13 v!24)))) (=> true (or _let_43 (or _let_42 (or _let_41 (or _let_40 (or _let_39 (or _let_38 false)))))))))))))))))))))))))))))))))))))))))))))))))))))
(assert (let ((_let_0 (< t!23 t!24))) (let ((_let_1 (< t!19 t!20))) (let ((_let_2 (< t!15 t!16))) (let ((_let_3 (< t!11 t!12))) (let ((_let_4 (< t!7 t!8))) (let ((_let_5 (and (= 0 rf!3) true))) (let ((_let_6 (< t!0 t!8))) (let ((_let_7 (< t!3 t!8))) (let ((_let_8 (< t!0 t!12))) (let ((_let_9 (< t!3 t!12))) (let ((_let_10 (< t!0 t!16))) (let ((_let_11 (< t!3 t!16))) (let ((_let_12 (< t!0 t!20))) (let ((_let_13 (< t!3 t!20))) (let ((_let_14 (< t!0 t!24))) (let ((_let_15 (< t!3 t!24))) (let ((_let_16 (and (= 8 rf!3) true))) (let ((_let_17 (< t!8 t!0))) (let ((_let_18 (< t!3 t!0))) (let ((_let_19 (< t!8 t!12))) (let ((_let_20 (< t!8 t!16))) (let ((_let_21 (< t!8 t!20))) (let ((_let_22 (< t!8 t!24))) (let ((_let_23 (and (= 12 rf!3) true))) (let ((_let_24 (< t!12 t!0))) (let ((_let_25 (< t!12 t!8))) (let ((_let_26 (< t!12 t!16))) (let ((_let_27 (< t!12 t!20))) (let ((_let_28 (< t!12 t!24))) (let ((_let_29 (and (= 16 rf!3) true))) (let ((_let_30 (< t!16 t!0))) (let ((_let_31 (< t!16 t!8))) (let ((_let_32 (< t!16 t!12))) (let ((_let_33 (< t!16 t!20))) (let ((_let_34 (< t!16 t!24))) (let ((_let_35 (and (= 20 rf!3) true))) (let ((_let_36 (< t!20 t!0))) (let ((_let_37 (< t!20 t!8))) (let ((_let_38 (< t!20 t!12))) (let ((_let_39 (< t!20 t!16))) (let ((_let_40 (< t!20 t!24))) (let ((_let_41 (and (= 24 rf!3) true))) (let ((_let_42 (< t!24 t!0))) (let ((_let_43 (< t!24 t!8))) (let ((_let_44 (< t!24 t!12))) (let ((_let_45 (< t!24 t!16))) (let ((_let_46 (< t!24 t!20))) (let ((_let_47 (and (= 0 rf!7) true))) (let ((_let_48 (< t!7 t!12))) (let ((_let_49 (< t!7 t!16))) (let ((_let_50 (< t!7 t!20))) (let ((_let_51 (< t!7 t!24))) (let ((_let_52 (and (= 8 rf!7) true))) (let ((_let_53 (< t!7 t!0))) (let ((_let_54 (and (= 12 rf!7) true))) (let ((_let_55 (and (= 16 rf!7) true))) (let ((_let_56 (and (= 20 rf!7) true))) (let ((_let_57 (and (= 24 rf!7) true))) (let ((_let_58 (and (= 0 rf!11) true))) (let ((_let_59 (< t!11 t!8))) (let ((_let_60 (< t!11 t!16))) (let ((_let_61 (< t!11 t!20))) (let ((_let_62 (< t!11 t!24))) (let ((_let_63 (and (= 8 rf!11) true))) (let ((_let_64 (< t!11 t!0))) (let ((_let_65 (and (= 12 rf!11) true))) (let ((_let_66 (and (= 16 rf!11) true))) (let ((_let_67 (and (= 20 rf!11) true))) (let ((_let_68 (and (= 24 rf!11) true))) (let ((_let_69 (and (= 0 rf!15) true))) (let ((_let_70 (< t!15 t!8))) (let ((_let_71 (< t!15 t!12))) (let ((_let_72 (< t!15 t!20))) (let ((_let_73 (< t!15 t!24))) (let ((_let_74 (and (= 8 rf!15) true))) (let ((_let_75 (< t!15 t!0))) (let ((_let_76 (and (= 12 rf!15) true))) (let ((_let_77 (and (= 16 rf!15) true))) (let ((_let_78 (and (= 20 rf!15) true))) (let ((_let_79 (and (= 24 rf!15) true))) (let ((_let_80 (and (= 0 rf!19) true))) (let ((_let_81 (< t!19 t!8))) (let ((_let_82 (< t!19 t!12))) (let ((_let_83 (< t!19 t!16))) (let ((_let_84 (< t!19 t!24))) (let ((_let_85 (and (= 8 rf!19) true))) (let ((_let_86 (< t!19 t!0))) (let ((_let_87 (and (= 12 rf!19) true))) (let ((_let_88 (and (= 16 rf!19) true))) (let ((_let_89 (and (= 20 rf!19) true))) (let ((_let_90 (and (= 24 rf!19) true))) (let ((_let_91 (and (= 0 rf!23) true))) (let ((_let_92 (< t!23 t!8))) (let ((_let_93 (< t!23 t!12))) (let ((_let_94 (< t!23 t!16))) (let ((_let_95 (< t!23 t!20))) (let ((_let_96 (and (= 8 rf!23) true))) (let ((_let_97 (< t!23 t!0))) (let ((_let_98 (and (= 12 rf!23) true))) (let ((_let_99 (and (= 16 rf!23) true))) (let ((_let_100 (and (= 20 rf!23) true))) (let ((_let_101 (and (= 24 rf!23) true))) (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and (and true (=> (and (and (= 1 rf!26) true) (< t!1 t!4)) (< t!26 t!4))) (=> (and (and (= 4 rf!26) true) (< t!4 t!1)) (< t!26 t!1))) (=> (and _let_5 _let_6) _let_7)) (=> (and _let_5 _let_8) _let_9)) (=> (and _let_5 _let_10) _let_11)) (=> (and _let_5 _let_12) _let_13)) (=> (and _let_5 _let_14) _let_15)) (=> (and _let_16 _let_17) _let_18)) (=> (and _let_16 _let_19) _let_9)) (=> (and _let_16 _let_20) _let_11)) (=> (and _let_16 _let_21) _let_13)) (=> (and _let_16 _let_22) _let_15)) (=> (and _let_23 _let_24) _let_18)) (=> (and _let_23 _let_25) _let_7)) (=> (and _let_23 _let_26) _let_11)) (=> (and _let_23 _let_27) _let_13)) (=> (and _let_23 _let_28) _let_15)) (=> (and _let_29 _let_30) _let_18)) (=> (and _let_29 _let_31) _let_7)) (=> (and _let_29 _let_32) _let_9)) (=> (and _let_29 _let_33) _let_13)) (=> (and _let_29 _let_34) _let_15)) (=> (and _let_35 _let_36) _let_18)) (=> (and _let_35 _let_37) _let_7)) (=> (and _let_35 _let_38) _let_9)) (=> (and _let_35 _let_39) _let_11)) (=> (and _let_35 _let_40) _let_15)) (=> (and _let_41 _let_42) _let_18)) (=> (and _let_41 _let_43) _let_7)) (=> (and _let_41 _let_44) _let_9)) (=> (and _let_41 _let_45) _let_11)) (=> (and _let_41 _let_46) _let_13)) (=> (and _let_47 _let_6) _let_4)) (=> (and _let_47 _let_8) _let_48)) (=> (and _let_47 _let_10) _let_49)) (=> (and _let_47 _let_12) _let_50)) (=> (and _let_47 _let_14) _let_51)) (=> (and _let_52 _let_17) _let_53)) (=> (and _let_52 _let_19) _let_48)) (=> (and _let_52 _let_20) _let_49)) (=> (and _let_52 _let_21) _let_50)) (=> (and _let_52 _let_22) _let_51)) (=> (and _let_54 _let_24) _let_53)) (=> (and _let_54 _let_25) _let_4)) (=> (and _let_54 _let_26) _let_49)) (=> (and _let_54 _let_27) _let_50)) (=> (and _let_54 _let_28) _let_51)) (=> (and _let_55 _let_30) _let_53)) (=> (and _let_55 _let_31) _let_4)) (=> (and _let_55 _let_32) _let_48)) (=> (and _let_55 _let_33) _let_50)) (=> (and _let_55 _let_34) _let_51)) (=> (and _let_56 _let_36) _let_53)) (=> (and _let_56 _let_37) _let_4)) (=> (and _let_56 _let_38) _let_48)) (=> (and _let_56 _let_39) _let_49)) (=> (and _let_56 _let_40) _let_51)) (=> (and _let_57 _let_42) _let_53)) (=> (and _let_57 _let_43) _let_4)) (=> (and _let_57 _let_44) _let_48)) (=> (and _let_57 _let_45) _let_49)) (=> (and _let_57 _let_46) _let_50)) (=> (and _let_58 _let_6) _let_59)) (=> (and _let_58 _let_8) _let_3)) (=> (and _let_58 _let_10) _let_60)) (=> (and _let_58 _let_12) _let_61)) (=> (and _let_58 _let_14) _let_62)) (=> (and _let_63 _let_17) _let_64)) (=> (and _let_63 _let_19) _let_3)) (=> (and _let_63 _let_20) _let_60)) (=> (and _let_63 _let_21) _let_61)) (=> (and _let_63 _let_22) _let_62)) (=> (and _let_65 _let_24) _let_64)) (=> (and _let_65 _let_25) _let_59)) (=> (and _let_65 _let_26) _let_60)) (=> (and _let_65 _let_27) _let_61)) (=> (and _let_65 _let_28) _let_62)) (=> (and _let_66 _let_30) _let_64)) (=> (and _let_66 _let_31) _let_59)) (=> (and _let_66 _let_32) _let_3)) (=> (and _let_66 _let_33) _let_61)) (=> (and _let_66 _let_34) _let_62)) (=> (and _let_67 _let_36) _let_64)) (=> (and _let_67 _let_37) _let_59)) (=> (and _let_67 _let_38) _let_3)) (=> (and _let_67 _let_39) _let_60)) (=> (and _let_67 _let_40) _let_62)) (=> (and _let_68 _let_42) _let_64)) (=> (and _let_68 _let_43) _let_59)) (=> (and _let_68 _let_44) _let_3)) (=> (and _let_68 _let_45) _let_60)) (=> (and _let_68 _let_46) _let_61)) (=> (and _let_69 _let_6) _let_70)) (=> (and _let_69 _let_8) _let_71)) (=> (and _let_69 _let_10) _let_2)) (=> (and _let_69 _let_12) _let_72)) (=> (and _let_69 _let_14) _let_73)) (=> (and _let_74 _let_17) _let_75)) (=> (and _let_74 _let_19) _let_71)) (=> (and _let_74 _let_20) _let_2)) (=> (and _let_74 _let_21) _let_72)) (=> (and _let_74 _let_22) _let_73)) (=> (and _let_76 _let_24) _let_75)) (=> (and _let_76 _let_25) _let_70)) (=> (and _let_76 _let_26) _let_2)) (=> (and _let_76 _let_27) _let_72)) (=> (and _let_76 _let_28) _let_73)) (=> (and _let_77 _let_30) _let_75)) (=> (and _let_77 _let_31) _let_70)) (=> (and _let_77 _let_32) _let_71)) (=> (and _let_77 _let_33) _let_72)) (=> (and _let_77 _let_34) _let_73)) (=> (and _let_78 _let_36) _let_75)) (=> (and _let_78 _let_37) _let_70)) (=> (and _let_78 _let_38) _let_71)) (=> (and _let_78 _let_39) _let_2)) (=> (and _let_78 _let_40) _let_73)) (=> (and _let_79 _let_42) _let_75)) (=> (and _let_79 _let_43) _let_70)) (=> (and _let_79 _let_44) _let_71)) (=> (and _let_79 _let_45) _let_2)) (=> (and _let_79 _let_46) _let_72)) (=> (and _let_80 _let_6) _let_81)) (=> (and _let_80 _let_8) _let_82)) (=> (and _let_80 _let_10) _let_83)) (=> (and _let_80 _let_12) _let_1)) (=> (and _let_80 _let_14) _let_84)) (=> (and _let_85 _let_17) _let_86)) (=> (and _let_85 _let_19) _let_82)) (=> (and _let_85 _let_20) _let_83)) (=> (and _let_85 _let_21) _let_1)) (=> (and _let_85 _let_22) _let_84)) (=> (and _let_87 _let_24) _let_86)) (=> (and _let_87 _let_25) _let_81)) (=> (and _let_87 _let_26) _let_83)) (=> (and _let_87 _let_27) _let_1)) (=> (and _let_87 _let_28) _let_84)) (=> (and _let_88 _let_30) _let_86)) (=> (and _let_88 _let_31) _let_81)) (=> (and _let_88 _let_32) _let_82)) (=> (and _let_88 _let_33) _let_1)) (=> (and _let_88 _let_34) _let_84)) (=> (and _let_89 _let_36) _let_86)) (=> (and _let_89 _let_37) _let_81)) (=> (and _let_89 _let_38) _let_82)) (=> (and _let_89 _let_39) _let_83)) (=> (and _let_89 _let_40) _let_84)) (=> (and _let_90 _let_42) _let_86)) (=> (and _let_90 _let_43) _let_81)) (=> (and _let_90 _let_44) _let_82)) (=> (and _let_90 _let_45) _let_83)) (=> (and _let_90 _let_46) _let_1)) (=> (and _let_91 _let_6) _let_92)) (=> (and _let_91 _let_8) _let_93)) (=> (and _let_91 _let_10) _let_94)) (=> (and _let_91 _let_12) _let_95)) (=> (and _let_91 _let_14) _let_0)) (=> (and _let_96 _let_17) _let_97)) (=> (and _let_96 _let_19) _let_93)) (=> (and _let_96 _let_20) _let_94)) (=> (and _let_96 _let_21) _let_95)) (=> (and _let_96 _let_22) _let_0)) (=> (and _let_98 _let_24) _let_97)) (=> (and _let_98 _let_25) _let_92)) (=> (and _let_98 _let_26) _let_94)) (=> (and _let_98 _let_27) _let_95)) (=> (and _let_98 _let_28) _let_0)) (=> (and _let_99 _let_30) _let_97)) (=> (and _let_99 _let_31) _let_92)) (=> (and _let_99 _let_32) _let_93)) (=> (and _let_99 _let_33) _let_95)) (=> (and _let_99 _let_34) _let_0)) (=> (and _let_100 _let_36) _let_97)) (=> (and _let_100 _let_37) _let_92)) (=> (and _let_100 _let_38) _let_93)) (=> (and _let_100 _let_39) _let_94)) (=> (and _let_100 _let_40) _let_0)) (=> (and _let_101 _let_42) _let_97)) (=> (and _let_101 _let_43) _let_92)) (=> (and _let_101 _let_44) _let_93)) (=> (and _let_101 _let_45) _let_94)) (=> (and _let_101 _let_46) _let_95)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))
(assert (and (and true (distinct t!1 t!4)) (distinct t!0 t!8 t!12 t!16 t!20 t!24)))
(check-sat)
