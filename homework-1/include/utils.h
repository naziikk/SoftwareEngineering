#include <iostream>

class Utils {
public:
    static void ShowMenu() {
        std::cout << "1. Добавить животное в зоопарк\n";
        std::cout << "2. Показать количество еды, необходимое, чтобы прокормить всех животных\n";
        std::cout << "3. Показать всех животных в зоопарке\n";
        std::cout << "4. Вылечить животное\n";
        std::cout << "5. Покинуть зоопарк\n";
    }

    static void AddAnimalInfo() {
        std::cout << "Наш зоопарк пока поддерживает 4 животных:\n";
        std::cout << "1. Кролик\n";
        std::cout << "2. Обезьяна\n";
        std::cout << "3. Волк\n";
        std::cout << "4. Тигр\n";
        std::cout << "Кого бы вы хотели добавить?\n";
    }

    static std::pair<int, int> AnimalInfo(int animal) {
        std::pair<int, int> result;
        if (animal == 1 || animal == 2 || animal == 3 || animal == 4) {
            std::cout << "Подскажите пожалуйста, сколько кг еды в день он кушает?\n";
            int food_rate;
            std::cin >> food_rate;
            int is_healthy;
            std::cout << "А здорово ли ваше животное? (да - 1, не совсем - 0) \n";
            std::cin >> is_healthy;
            return {food_rate, is_healthy};
        }
        return {};
    }
};