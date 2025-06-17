DROP SCHEMA IF EXISTS orders_storage CASCADE;
CREATE SCHEMA orders_storage;

CREATE TYPE orders_storage.status AS ENUM ('NEW', 'COMPLETED', 'CANCELLED', 'SUCCESS', 'FAILED');
CREATE TYPE orders_storage.sendingstatus AS ENUM ('NOT_SENT', 'SENT');

CREATE TABLE IF NOT EXISTS orders_storage.orders (
    id uuid primary key DEFAULT gen_random_uuid(),
    user_id uuid NOT NULL,
    amount DECIMAL(10, 2) NOT NULL,
    status orders_storage.status NOT NULL DEFAULT 'NEW',
    description text
);

CREATE TABLE IF NOT EXISTS orders_storage.outbox (
    id uuid primary key DEFAULT gen_random_uuid(),
    user_id uuid NOT NULL,
    amount DECIMAL(10, 2) NOT NULL,
    status orders_storage.sendingstatus NOT NULL DEFAULT 'NOT_SENT',
    description text
);

CREATE INDEX IF NOT EXISTS orders_hash_idx ON orders_storage.orders using HASH (id);
