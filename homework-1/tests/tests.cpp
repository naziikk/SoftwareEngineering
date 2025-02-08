#include "../third_party/googletest/googletest/include/gtest/gtest.h"
#include "../include/Thing/Thing.h"
#include "../include/Zoo/Zoo.h"
#include "../include/DI-container.h"
#include <memory>

TEST(CheckHerboCharacteristics, Monkey) {
    Monkey monkey(10, 3, true, 7);
    EXPECT_EQ(monkey.GetName(), "Monkey");
    EXPECT_EQ(monkey.IsHealthy(), true);
    EXPECT_EQ(monkey.CanInteractWithPeople(), true);
    EXPECT_EQ(monkey.GetType(), "herbo");
    EXPECT_EQ(monkey.GetFoodRate(), 10);
    EXPECT_FALSE(monkey.GetFoodRate() == 6);
}

TEST(CheckPredatorCharacteristics, Tiger) {
    Tiger tiger(30, 4, true);
    EXPECT_EQ(tiger.GetName(), "Tiger");
    EXPECT_EQ(tiger.IsHealthy(), true);
    EXPECT_EQ(tiger.GetFoodRate(), 30);
    EXPECT_FALSE(tiger.GetFoodRate() == 31);
    EXPECT_EQ(tiger.GetType(), "predator");
}

TEST(CheckDIcontainerWorkingAbility, DI_Container) {
    auto container = DIContainer();
    container.RegisterObject<ZooVetClinic>();

    std::shared_ptr zoo_clinic = container.GetObject<ZooVetClinic>();

    Zoo zoo(*zoo_clinic);

    zoo.AddAnimal(std::make_unique<Wolf>(25, 2, true));
    zoo.AddAnimal(std::make_unique<Monkey>(10, 3, true, 7));
    zoo.AddAnimal(std::make_unique<Tiger>(30, 4, true));

    EXPECT_EQ(zoo.GetAnimalsCount(), 3);

    zoo.AddAnimal(std::make_unique<Rabbit>(8, 5, false, 6));

    EXPECT_EQ(zoo.GetAnimalsCount(), 4);
}

TEST(InventoryWorking, Inventory) {
    Table table(1);
    Computer computer(2);

    EXPECT_EQ(table.GetName(), "Table");
    EXPECT_EQ(computer.GetName(), "Computer");
    EXPECT_EQ(table.InventoryNumber(), 1);
    EXPECT_EQ(computer.InventoryNumber(), 2);
}

TEST(CheckAnimalInteraction, InteractionWithPeople) {
    Monkey monkey(10, 3, true, 7);
    Rabbit rabbit(8, 5, false, 5);

    EXPECT_TRUE(monkey.CanInteractWithPeople());
    EXPECT_FALSE(rabbit.CanInteractWithPeople());
}

TEST(CheckZooClinicTreatment, HealthRecovery) {
    ZooVetClinic clinic;
    Tiger tiger(30, 4, false);

    EXPECT_FALSE(tiger.IsHealthy());

    ZooVetClinic::TreatAnimal(tiger);

    EXPECT_TRUE(tiger.IsHealthy());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}