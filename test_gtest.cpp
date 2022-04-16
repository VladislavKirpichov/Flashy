#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../src/ServiceInterface.h"
#include "../src/Service.h"
#include "../src/Model.h"
#include "../src/Preprocessor.h"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

////////////////
TEST(ServiceInterfaceFunctionsTest, getAnswer) {
    ServiceInterface* t = new Service;
    EXPECT_EQ(t->getAnswer(), std::vector<int>());
}

TEST(ServiceInterfaceFunctionsTest, sendData) {
    ServiceInterface* t = new Service;
    const std::vector<double*> v{};
    EXPECT_EQ(t->sendData(v), 1);
}


//////////
TEST(ServiceFunctionsTest, getAnswer) {
    Service f;
    EXPECT_EQ(f.getAnswer(), std::vector<int>());
}

TEST(ServiceFunctionTest, sendData) {
    Service f;
    const std::vector<double*> v{};
    EXPECT_EQ(f.sendData(v), 0);
}

///////////////
TEST(ModelFunctionsTest, showNearNeighbor) {
    Model f;
    EXPECT_EQ(f.showNearNeighbor(), std::vector<int>());
}

//////////
TEST(DatasetFunctionsTest, getData) {
    Dataset f;
    EXPECT_EQ(f.getData(), std::vector<double*>());
}

//////////
class MockPreprocessor: public Preprocessor {
public:
    MOCK_METHOD0(calculateAll, int());
    MOCK_METHOD0(calculateTextFeatures, int());
    MOCK_METHOD0(stemming, int());
    MOCK_METHOD0(calculateDifficulty, int());
};

TEST(PreprocessorFunctionsTest, calculateAll) {
    MockPreprocessor f;
    EXPECT_CALL(f, calculateTextFeatures()).Times(AtLeast(1));
    EXPECT_CALL(f, stemming()).Times(AtLeast(1));
    EXPECT_CALL(f, calculateDifficulty()).Times(AtLeast(1));

    EXPECT_EQ(f.calculateAll(), 0);
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
