DROP SCHEMA IF EXISTS payments CASCADE;

CREATE SCHEMA IF NOT EXISTS payments;

CREATE TYPE payments.Status AS ENUM ('FAILED', 'SUCCESS');
CREATE TYPE payments.SendingStatus AS ENUM ('NOT_SENT', 'SENT');

CREATE TABLE IF NOT EXISTS payments.bill (
    id uuid primary key DEFAULT gen_random_uuid(),
    user_id uuid NOT NULL,
    money_amount DECIMAL(10, 2) NOT NULL
);

CREATE TABLE IF NOT EXISTS payments.outbox (
    id uuid primary key DEFAULT gen_random_uuid(),
    order_id uuid NOT NULL,
    status payments.Status NOT NULL,
    sending_status payments.SendingStatus NOT NULL DEFAULT 'NOT_SENT'
)
