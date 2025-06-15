DROP SCHEMA IF EXISTS orders_storage CASCADE;

CREATE SCHEMA IF NOT EXISTS orders_storage;

CREATE TYPE Status AS ENUM ('NEW', 'COMPLETED', 'CANCELLED');
CREATE TYPE SendingStatus AS ENUM ('NOT_SENT', 'SENT');

CREATE TABLE IF NOT EXISTS orders_storage.orders (
    id uuid primary key DEFAULT gen_random_uuid(),
    user_id uuid NOT NULL,
    amount DECIMAL(10, 2) NOT NULL,
    status Status NOT NULL DEFAULT 'NEW',
    description text
);

CREATE TABLE IF NOT EXISTS orders_storage.outbox (
    id uuid primary key DEFAULT gen_random_uuid(),
    user_id uuid NOT NULL,
    amount DECIMAL(10, 2) NOT NULL,
    status SendingStatus NOT NULL DEFAULT 'NOT_SENT',
    description text
);

CREATE INDEX IF NOT EXISTS orders_hash_idx ON orders_storage.orders using HASH (id);
