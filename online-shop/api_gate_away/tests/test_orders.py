import pytest
import requests
import uuid
from config import BASE_URL

def create_account(user_id):
    response = requests.post(f"{BASE_URL}/account/create", json={"user_id": user_id})
    assert response.status_code == 200

@pytest.mark.parametrize("description, amount", [
    ("Test order 1", "500"),
    ("Big test order", "1500"),
])
def test_full_order_flow(description, amount):
    user_id = str(uuid.uuid4())
    # заранее создадим аккаунт
    create_account(user_id)

    # пополним баланс
    response = requests.post(f"{BASE_URL}/account/top_up", json={"user_id": user_id, "amount": "2000"})
    assert response.status_code == 200

    order_data = {
        "description": description,
        "amount": amount,
        "user_id": user_id
    }
    # создадим заказ
    response = requests.post(f"{BASE_URL}/order/create", json=order_data)
    assert response.status_code == 200

    # проверим что существует хотя бы 1 заказ у пользователя
    response = requests.get(f"{BASE_URL}/orders/{user_id}/list")
    assert response.status_code == 200
    assert isinstance(response.json(), list)
    assert len(response.json()) >= 1

    order_list = response.json()
    order_id = order_list[-1]["id"]

    # рассмотрим какой-нибудь специфический пример
    response = requests.post(f"{BASE_URL}/orders/{order_id}", json={"user_id": user_id})
    assert response.status_code == 200
    order = response.json()
    assert order["description"] == description
    assert order["amount"] == amount
