set(AlgTests
    bubble_test
    insertion_test
    selection_test
    merge_test
    quick_test
)

foreach(TEST_NAME ${AlgTests})
    add_executable(${TEST_NAME} ${TEST_NAME}.cpp)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    set_tests_properties(${TEST_NAME} PROPERTIES LABELS "alg_tests")
endforeach()