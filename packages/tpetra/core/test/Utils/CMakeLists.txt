
TRIBITS_ADD_EXECUTABLE_AND_TEST(
  TpetraUtils_UnitTests
  SOURCES
    TpetraUtils_UnitTests
    ${TEUCHOS_STD_UNIT_TEST_MAIN}
  ARGS ${ARGS}
  COMM serial
  STANDARD_PASS_OUTPUT
  )

TRIBITS_ADD_EXECUTABLE_AND_TEST(
  TpetraUtils_merge
  SOURCES
    TpetraUtils_merge
    ${TEUCHOS_STD_UNIT_TEST_MAIN}
  ARGS ${ARGS}
  COMM serial
  STANDARD_PASS_OUTPUT
  )

TRIBITS_ADD_EXECUTABLE_AND_TEST(
  TpetraUtils_congruent
  SOURCES
    TpetraUtils_congruent
    ${TEUCHOS_STD_UNIT_TEST_MAIN}
  ARGS ${ARGS}
  COMM serial mpi
  STANDARD_PASS_OUTPUT
  )

TRIBITS_ADD_EXECUTABLE_AND_TEST(
  TpetraUtils_gathervPrint
  SOURCES
    TpetraUtils_gathervPrint
    ${TEUCHOS_STD_UNIT_TEST_MAIN}
  ARGS ${ARGS}
  COMM serial mpi
  STANDARD_PASS_OUTPUT
  )
