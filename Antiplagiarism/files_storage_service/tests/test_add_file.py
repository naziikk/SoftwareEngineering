import io

import pytest
import requests
import psycopg2
from config import BASE_URL, DATABASE_CONFIG


@pytest.fixture(scope="module")
def db_connection():
    conn = psycopg2.connect(
        dbname=DATABASE_CONFIG["dbname"],
        host=DATABASE_CONFIG["host"],
        port=DATABASE_CONFIG["port"],
        user=DATABASE_CONFIG["user"],
        password=DATABASE_CONFIG["password"]
    )
    yield conn
    conn.close()


def get_database_size(db_connection):
    cursor = db_connection.cursor()
    cursor.execute("SELECT * FROM files_storage.files")

    size = cursor.fetchone()[0]
    cursor.close()

    return size


@pytest.mark.parametrize('file_content, expected_status, expected_files_in_database',
         [
             ("some data inside the file with only letters", 200, 1),
             ("1some1 2data2 3inside3 4the4 5file5 6with6 93535digits3593", 200, 2),
             ("1some1 2data2 3inside3 4the4 5file5 6with6 93535digits3593", 200, 2),
         ]
)
def test_add_file(db_connection, file_content, expected_status, expected_files_in_database):
    file = io.BytesIO(file_content.encode('utf-8'))
    file.name = "test_file.txt"

    files = {
        'file': (file.name, file, 'text/plain')
    }

    response = requests.post(f"{BASE_URL}/file/upload", files=files)

    assert response.status_code == expected_status
    assert get_database_size(db_connection) == expected_files_in_database
