import pytest
import requests
import uuid
from config import BASE_URL

@pytest.mark.parametrize("amount", [
    "500",
    "1500",
])
def test_payment_flow(amount):
    user_id = str(uuid.uuid4())

    # пока аккаунта не существует, мы должны получать 404 в ответ на запрос
    response = requests.get(f"{BASE_URL}/account/{user_id}/balance")
    assert response.status_code == 404

    # создадим аккаунт
    response = requests.post(f"{BASE_URL}/account/create", json={"user_id": user_id})
    assert response.status_code == 200

    # создадим аккаунт повторно, должно упасть
    response = requests.post(f"{BASE_URL}/account/create", json={"user_id": user_id})
    assert response.status_code == 400

    # пополним сумму на балансе
    response = requests.post(f"{BASE_URL}/account/top_up", json={"user_id": user_id, "amount": amount})
    assert response.status_code == 200

    # проверим баланс
    response = requests.get(f"{BASE_URL}/account/{user_id}/balance")
    assert response.status_code == 200
    balance = int(response.json()["balance"])
    assert balance >= int(amount)