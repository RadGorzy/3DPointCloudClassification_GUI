include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#copy required files (python modules)
file(COPY ../embedded_python/ModelTesting.py DESTINATION .) #source (default CMAKE_CURRENT_SOURCE_DIR) destination (default CMAKE_CURRENT_BINARY_DIR)
file(COPY ../embedded_python/model.py DESTINATION .)

#copy some examples
file(COPY ../configurations/CNN_binary_Map_person_edited_3x3_KITTI.txt DESTINATION .)
file(COPY ../configurations/CNN_range_SemanticKITTI_IGN.txt DESTINATION .)
file(COPY ../configurations/CNN_range_SemanticKITTI_KITTI.txt DESTINATION .)
file(COPY ../example_scenes/IGN_Z0_car_1.pcd DESTINATION .)
file(COPY ../example_scenes/0000000003.pcd DESTINATION .)
file(COPY ../example_scenes/000023.bin DESTINATION .)
file(COPY ../benchmark DESTINATION .) 

add_executable(
  test_classification
  ${PROJECT_SOURCE_DIR}/tests/test_classification.cpp)
target_link_libraries(
  test_classification
  classifier
  gtest_main)

include(GoogleTest)
gtest_discover_tests(test_classification)