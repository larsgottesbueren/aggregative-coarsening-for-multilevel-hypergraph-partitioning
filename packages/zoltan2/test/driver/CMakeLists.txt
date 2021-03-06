#TRIBITS_ADD_EXECUTABLE_AND_TEST(driver
#  SOURCES ${HEADERS} driver.cpp
#  NUM_MPI_PROCS 4
#  COMM mpi serial
#  ARGS "basic.xml"
#  PASS_REGULAR_EXPRESSION "PASS"
#  FAIL_REGULAR_EXPRESSION "FAIL"
#)
#
#TRIBITS_COPY_FILES_TO_BINARY_DIR(Zoltan2_copy_test_options
#  SOURCE_FILES basic.xml
#  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}
#  DEST_DIR ${CMAKE_CURRENT_BINARY_DIR}
#  NOEXEPREFIX
#)

ADD_SUBDIRECTORY(driverinputs)

TRIBITS_ADD_EXECUTABLE(
   test_driver
   SOURCES ${HEADERS} test_driver.cpp
   COMM serial mpi
)


IF (${PACKAGE_NAME}_ENABLE_ParMETIS)
  TRIBITS_ADD_TEST(
    test_driver
    NAME parmetisSubComm
    NUM_MPI_PROCS 2
    COMM serial mpi
    ARGS
    "./driverinputs/parmetisSubComm.xml"
    PASS_REGULAR_EXPRESSION "PASS"
    FAIL_REGULAR_EXPRESSION "FAIL"
  )
ENDIF()

TRIBITS_ADD_TEST(
    test_driver
    NAME geometricTest
    NUM_MPI_PROCS 4
    COMM serial mpi
    ARGS
    "./driverinputs/geometricTest.xml"
    PASS_REGULAR_EXPRESSION "PASS"
    FAIL_REGULAR_EXPRESSION "FAIL"
)

TRIBITS_ADD_TEST(
    test_driver
    NAME test578
    NUM_MPI_PROCS 4
    COMM serial mpi
    ARGS
    "./driverinputs/test578.xml"
    PASS_REGULAR_EXPRESSION "PASS"
    FAIL_REGULAR_EXPRESSION "FAIL"
)

IF (${PACKAGE_NAME}_ENABLE_PuLP)
  TRIBITS_ADD_TEST(
    test_driver
    NAME pulpTest
    NUM_MPI_PROCS 4
    COMM serial mpi
    ARGS
    "./driverinputs/pulpTest.xml"
    PASS_REGULAR_EXPRESSION "PASS"
    FAIL_REGULAR_EXPRESSION "FAIL"
  )
ENDIF()

TRIBITS_ADD_TEST(
    test_driver
    NAME geometricVwgtTest
    NUM_MPI_PROCS 4
    COMM serial mpi
    ARGS
    "./driverinputs/geometricVwgtTest.xml"
    PASS_REGULAR_EXPRESSION "PASS"
    FAIL_REGULAR_EXPRESSION "FAIL"
)

TRIBITS_ADD_TEST(
    test_driver
    NAME geometricVwgt2Test
    NUM_MPI_PROCS 4
    COMM serial mpi
    ARGS
    "./driverinputs/geometricVwgt2Test.xml"
    PASS_REGULAR_EXPRESSION "PASS"
    FAIL_REGULAR_EXPRESSION "FAIL"
)

# MultiJagged Tests
IF (${PROJECT_NAME}_ENABLE_Galeri)
  TRIBITS_ADD_TEST(
    test_driver
    NAME coordinateDriverTest
    NUM_MPI_PROCS 4
    COMM serial mpi
    ARGS
    "./driverinputs/galeriTest.xml"
    PASS_REGULAR_EXPRESSION "PASS"
    FAIL_REGULAR_EXPRESSION "FAIL"
  )
ENDIF()

TRIBITS_ADD_TEST(
    test_driver
    NAME rcbDriverTest
    NUM_MPI_PROCS 4
    COMM serial mpi
    ARGS
    "./driverinputs/rcbTest.xml"
    PASS_REGULAR_EXPRESSION "PASS"
    FAIL_REGULAR_EXPRESSION "FAIL"
)

TRIBITS_ADD_TEST(
    test_driver
    NAME mjDriverTest
    NUM_MPI_PROCS 3
    COMM serial mpi
    ARGS
    "./driverinputs/multiJaggedTest.xml"
    PASS_REGULAR_EXPRESSION "PASS"
    FAIL_REGULAR_EXPRESSION "FAIL"
)

# Command that copies files to the executable directory.
# KDD: I am using this for Zoltan data files.  When Zoltan tests are not built,
# KDD: we can't point driver to files in build directory (as they won't be 
# KDD: there.  Also, we don't want to use hard-code paths in XML files.
# KDD: Copying the files here seems to be best, unless we can make CMAKE
# KDD: do macro substitution in the XML files.
TRIBITS_COPY_FILES_TO_BINARY_DIR(copy_zoltan_simple_for_driver_tests_
  SOURCE_FILES
    simple.coords
    simple.graph
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../zoltan/test/ch_simple
  DEST_DIR ${CMAKE_CURRENT_BINARY_DIR}
)

TRIBITS_COPY_FILES_TO_BINARY_DIR(copy_zoltan_vwgt_for_driver_tests_
  SOURCE_FILES
    vwgt.coords
    vwgt.graph
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../zoltan/test/ch_vwgt
  DEST_DIR ${CMAKE_CURRENT_BINARY_DIR}
)

TRIBITS_COPY_FILES_TO_BINARY_DIR(copy_zoltan_vwgt2_for_driver_tests_
  SOURCE_FILES
    vwgt2.coords
    vwgt2.graph
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../zoltan/test/ch_vwgt2
  DEST_DIR ${CMAKE_CURRENT_BINARY_DIR}
)

TRIBITS_COPY_FILES_TO_BINARY_DIR(copy_zoltan_ewgt_for_driver_tests_
  SOURCE_FILES
    ewgt.coords
    ewgt.graph
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../zoltan/test/ch_ewgt
  DEST_DIR ${CMAKE_CURRENT_BINARY_DIR}
)

