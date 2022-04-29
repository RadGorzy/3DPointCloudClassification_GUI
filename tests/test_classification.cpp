#include "gtest/gtest.h"
//#include "model/classification.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

// TEST(ClassificationTest,LoadPythonModule){
//   MultiViewClassification classifier;
//   PyObject *pModule;
//   EXPECT_NE(classifier.loadPythonModule(&pModule,"ModelTesting","classify_multiple_projections_and_get_response_vector"),false);
// }