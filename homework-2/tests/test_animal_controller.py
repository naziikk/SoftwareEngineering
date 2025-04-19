import random

import pytest
import requests
from config import BASE_URL


# Ниже будет описан полный сценарий тестирования приложения

# 1. Для начала давайте создадим несколько животных, пусть 3 (травоядное, хищник и птицу)
@pytest.mark.parametrize("data, expected_status_code, expected_animals_count", [
    (
            {
                "name": "Dog",
                "type": "Herbo",
                "sex": 0,
                "favorite_food": "Sausage",
                "health_status": 0,
                "birthday": "2023-01-01"
            },
            200,
            1
    ),
    (
            {
                "name": "Lion",
                "type": "Predator",
                "sex": 1,
                "favorite_food": "Meat",
                "health_status": 0,
                "birthday": "2025-02-01"
            },
            200,
            2
    ),
    (
            {
                "name": "Parrot",
                "type": "Bird",
                "sex": 0,
                "favorite_food": "Seeds",
                "health_status": 0,
                "birthday": "2021-07-21"
            },
            200,
            3
    )
])
def test_add_animal(data, expected_status_code, expected_animals_count):
    response = requests.post(f"{BASE_URL}/animal", json=data)

    assert response.status_code == expected_status_code
    # чтобы убедиться в корректности работы API, проверим, что в ответе есть id нового животного
    result_json = response.json()
    assert "id" in result_json
    # дополнительно проверим, что в базе появилось новое животное
    response = requests.get(f"{BASE_URL}/zoo/statistics")

    assert len(response.json()["animals"]) == expected_animals_count


# 2. Теперь давайте создадим 3 вольера под каждый тип животного
@pytest.mark.parametrize("data, expected_status_code, expected_enclosures_count", [
    (
            {
                "type": "Herbo",
                "capacity": 2
            },
            200,
            1
    ),
    (
            {
                "type": "Birds",
                "capacity": 2
            },
            200,
            2
    ),
    (
            {
                "type": "Predator",
                "capacity": 2
            },
            200,
            3
    )
])
def test_add_enclosure(data, expected_status_code, expected_enclosures_count):
    response = requests.post(f"{BASE_URL}/enclosure", json=data)

    assert response.status_code == expected_status_code
    # чтобы убедиться в корректности работы API, проверим, что в ответе есть id нового вольера
    result_json = response.json()
    assert "id" in result_json
    # дополнительно проверим, что в базе появился новый вольер
    response = requests.get(f"{BASE_URL}/zoo/statistics")

    assert len(response.json()["enclosures"]) == expected_enclosures_count


# 3. Теперь давайте добавим в каждый вольер по одному животному
@pytest.mark.parametrize("animal_id, enclosure_id, expected_status_code", [
    (
            0,  # кладем травоядное в вольер для травоядных
            0,
            200
    ),
    (
            1,  # кладем хищника в вольер для хищников
            2,
            200
    ),
    (
            2,  # кладем птицу в вольер для птиц
            1,
            200
    ),
    (
            1,  # давайте попробуем поселить животное в вольер не для своего типа
            1,
            409
    ),
    (
            10,  # попробуем поселить несуществующее животное
            0,
            409
    ),
    (
            0,  # попробуем поселить животное в несуществующий вольер
            10,
            409
    )
])
def test_move_animal_to_enclosure(animal_id, enclosure_id, expected_status_code):
    response = requests.put(f"{BASE_URL}/animal/{animal_id}/move", json={"enclosure_id": enclosure_id})

    assert response.status_code == expected_status_code
    # чтобы убедиться в корректности работы API, проверим, что в ответе есть id нового животного
    result_json = response.json()

    if expected_status_code == 200:
        assert result_json["animal_id"] == animal_id  # проверим, что животное действительно переехало
        assert result_json["new_enclosure_id"] == enclosure_id


# 4. Теперь давайте попробуем удалить одно из животных
@pytest.mark.parametrize("animal_id, expected_status_code", [
    (
            0,
            200
    )
])
def test_delete_animal(animal_id, expected_status_code):
    # дополнительным шагом для проверки будет проверить, что животное пропало из вольера после удаления
    statistics = requests.get(f"{BASE_URL}/zoo/statistics")

    in_enclosure = False
    for enclosure in statistics.json()["enclosures"]:
        if animal_id in enclosure["animals_in"]:
            in_enclosure = True
            break

    assert in_enclosure == True

    response = requests.delete(f"{BASE_URL}/animal/{animal_id}")

    assert response.status_code == expected_status_code

    statistics = requests.get(f"{BASE_URL}/zoo/statistics")

    in_enclosure = False
    for enclosure in statistics.json()["enclosures"]:
        if animal_id in enclosure["animals_in"]:
            in_enclosure = True
            break

    assert in_enclosure == False


# 5. Теперь давайте попробуем удалить несуществующее животное
def test_delete_unexisting_animal():
    random_id = random.randint(100, 1000)

    response = requests.delete(f"{BASE_URL}/animal/{random_id}")

    assert response.status_code == 409
    result_json = response.json()


# 6. Добавим в расписание кормление животного
@pytest.mark.parametrize("animal_id, data, expected_status_code, expected_schedule_size", [
    (
            1,
            {
                "interval": 15,
            },
            201,
            1
    ),
    (
            2,
            {
                "interval": 18,
            },
            201,
            2
    )
])
def test_add_feeding_schedule(animal_id, data, expected_status_code, expected_schedule_size):
    response = requests.post(f"{BASE_URL}/animal/{animal_id}/feeding_schedule/1", json=data)

    assert response.status_code == expected_status_code

    # проверим, что кормление появилось в расписании
    statistics = requests.get(f"{BASE_URL}/zoo/statistics")

    feeding_schedule = statistics.json()["feeding_schedule"]
    assert len(feeding_schedule) == expected_schedule_size


# 7. Теперь давайте почистим вольер
def test_clean_enclosure():
    response = requests.post(f"{BASE_URL}/enclosure/1/clean")

    assert response.status_code == 200

    # если сразу же попробуем почистить еще раз, получим ошибку т.к. вольер уже чистый
    # между уборками должна пройти хотя бы минута
    response = requests.post(f"{BASE_URL}/enclosure/1/clean")

    assert response.status_code == 400


# 8. Теперь давайте попробуем почистить несуществующий вольер
def test_clean_unexisting_enclosure():
    random_id = random.randint(100, 1000)

    response = requests.post(f"{BASE_URL}/enclosure/{random_id}/clean")

    assert response.status_code == 404
    result_json = response.json()


# 9. Давайте накормим животное в ручную, не учитывая расписания
@pytest.mark.parametrize("animal_id, data, expected_status_code", [
    (
            1,
            {
                "food": "Meat",
            },
            200  # лев любит мясо
    ),
    (
            2,
            {
                "food": "Fish"
            },
            400  # при проверке, что это любимое блюдо животного, получили несовпадение и животное не хочет это есть
    )
])
def test_feed_animal(animal_id, data, expected_status_code):
    response = requests.post(f"{BASE_URL}/animal/{animal_id}/feed", json=data)

    assert response.status_code == expected_status_code

    # проверим, что животное покормилось
    result_json = response.json()
    if expected_status_code == 200:
        assert result_json["message"] == "Animal successfully fed"
    else:
        assert result_json["message"] == "Animal don`t like this food"


# 10. Следующим шагом предлагаю