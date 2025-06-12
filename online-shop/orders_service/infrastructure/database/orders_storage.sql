DROP SCHEMA IF EXISTS orders_storage CASCADE;

CREATE SCHEMA IF NOT EXISTS orders_storage;

CREATE TYPE Status AS ENUM ('NEW', 'COMPLETED', 'CANCELLED');

CREATE TABLE IF NOT EXISTS orders_storage.users (
    id uuid primary key DEFAULT gen_random_uuid(),
    name text,
    email text
);

CREATE TABLE IF NOT EXISTS orders_storage.orders (
    id uuid primary key DEFAULT gen_random_uuid(),
    user_id uuid NOT NULL REFERENCES orders_storage.users(id) ON DELETE CASCADE,
    amount DECIMAL(10, 2) NOT NULL,
    status Status NOT NULL DEFAULT 'NEW',
    description text
);

CREATE INDEX IF NOT EXISTS user_id_hash_idx ON orders_storage.users using HASH (id);
CREATE INDEX IF NOT EXISTS orders_hash_idx ON orders_storage.orders using HASH (id);
