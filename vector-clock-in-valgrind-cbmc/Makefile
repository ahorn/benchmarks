SRC = *.c 
CBMC=/Users/ahorn/Github/cbmc-trunk-4.9/src/cbmc/cbmc
CBMC_OPT=${CBMC} ${SRC} --unwindset c::vgDrd_vc_combine.0:${STATIC_SIZE},c::vgDrd_vc_combine.1:${STATIC_SIZE},c::vgDrd_vc_combine.2:${STATIC_SIZE},c::vgDrd_vc_combine.3:${STATIC_SIZE},c::vgDrd_vc_combine.4:${STATIC_SIZE},c::vgDrd_vc_check.0:${STATIC_SIZE},c::vgDrd_vc_lte.0:${STATIC_SIZE},c::vgDrd_vc_lte.1:${STATIC_SIZE},c::memcpy.0:${STATIC_SIZE_OF_VECTOR_CLOCK}

STATIC_SIZE=9
STATIC_SIZE_OF_VECTOR_CLOCK=80
ALL_TESTS=-D_TEST_1_ \
          -D_TEST_2_

gcc:
	gcc -g ${SRC} -D_CONCRETE_EXECUTION_ ${ALL_TESTS}

cbmc:
	${CBMC_OPT} ${ALL_TESTS}

cbmc-test-1:
	${CBMC_OPT} -D_TEST_1_

cbmc-test-2:
	${CBMC_OPT} -D_TEST_2_

cbmc-vc-1:
	${CBMC_OPT} -D_CBMC_VC_1_

cbmc-vc-2:
	${CBMC_OPT} -D_CBMC_VC_2_

cbmc-vc-3:
	${CBMC_OPT} -D_CBMC_VC_3_

cbmc-vc-4:
	${CBMC_OPT} -D_CBMC_VC_4_

cbmc-vc-5:
	${CBMC_OPT} -D_CBMC_VC_5_
