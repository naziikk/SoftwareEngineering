import os

BASE_URL = "http://storage:8007"

DATABASE_CONFIG = {
    "dbname": os.getenv("DATABASE_NAME", "files_storage"),
    "host": os.getenv("DATABASE_HOST", "localhost"),
    "port": os.getenv("DATABASE_PORT", "5432"),
    "user": os.getenv("DATABASE_USER", "postgres"),
    "password": os.getenv("DATABASE_PASSWORD", "postgres")
}
