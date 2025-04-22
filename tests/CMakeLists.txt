
add_executable(Dynamic_Array_Test dynamic_array_test/main.cpp)
target_link_libraries(Dynamic_Array_Test PUBLIC cs_util)

add_test(NAME Dynamic_Array_Test_1e1 COMMAND Dynamic_Array_Test 1)
add_test(NAME Dynamic_Array_Test_1e8 COMMAND Dynamic_Array_Test 8)
add_test(NAME Dynamic_Array_Test_1e16 COMMAND Dynamic_Array_Test 16)

add_executable(Hash_Map_Test hash_map_test/main.cpp)
target_link_libraries(Hash_Map_Test PUBLIC cs_util)
add_test(NAME Hash_Map_Test_1e1 COMMAND Hash_Map_Test 1)
add_test(NAME Hash_Map_Test_1e3 COMMAND Hash_Map_Test 3)
add_test(NAME Hash_Map_Test_1e8 COMMAND Hash_Map_Test 8)
add_test(NAME Hash_Map_Test_1e16 COMMAND Hash_Map_Test 16)

add_executable(Class_Test class_test/main.cpp)
target_link_libraries(Class_Test PUBLIC cs_util)
add_test(NAME Class_Test COMMAND Class_Test)