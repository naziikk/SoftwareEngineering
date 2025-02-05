#include "../third_party/googletest/googletest/include/gtest/gtest.h"
#include "../include/Zoo/Zoo.h"
#include "../include/DI-container.h"
#include <memory>

TEST(CheckHerboCharacteristics, Monkey) {
    Monkey monkey(10, 3, true, 7);
    EXPECT_EQ(monkey.GetName() == "Monkey", true);
    EXPECT_EQ(monkey.IsHealthy() == true, true);
    EXPECT_EQ(monkey.CanInteractWithPeople() == true, true);
    EXPECT_EQ(monkey.GetType() == "herbo", true);
    EXPECT_EQ(monkey.GetFoodRate() == 10, true);
    EXPECT_FALSE(monkey.GetFoodRate() == 6);
}

TEST(CheckPredatorCharacteristics, Tiger) {
    Tiger tiger(30, 4, true);
    EXPECT_EQ(tiger.GetName() == "Tiger", true);
    EXPECT_EQ(tiger.IsHealthy() == true, true);
    EXPECT_EQ(tiger.GetFoodRate() == 30, true);
    EXPECT_FALSE(tiger.GetFoodRate() == 31);
    EXPECT_EQ(tiger.GetType() == "predator", true);
}

TEST(CheckDIcontainerWorkingAbility, DI_Container) {
    auto container = DIContainer();
    container.RegisterObject<ZooVetClinic>();

    std::shared_ptr zoo_clinic = container.GetObject<ZooVetClinic>();

    Zoo zoo(*zoo_clinic);

    zoo.AddAnimal(std::make_unique<Wolf>(25, 2, true));
    zoo.AddAnimal(std::make_unique<Monkey>(10, 3, true, 7));
    zoo.AddAnimal(std::make_unique<Tiger>(30, 4, true));

    EXPECT_EQ(zoo.GetAnimalsCount() == 3, true);

    zoo.AddAnimal(std::make_unique<Rabbit>(8, 5, false, 6));

    EXPECT_EQ(zoo.GetAnimalsCount() == 3, true);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}