DROP SCHEMA IF EXISTS finance_tracker CASCADE;

CREATE SCHEMA IF NOT EXISTS finance_tracker;

CREATE TYPE finance_tracker.transaction_type AS ENUM ('INCOME', 'EXPENSE');

CREATE TABLE IF NOT EXISTS finance_tracker.bank_account (
    account_id UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    account_name VARCHAR(50) NOT NULL,
    balance DECIMAL(10, 2) DEFAULT 0
);

CREATE TABLE IF NOT EXISTS finance_tracker.category (
    category_id UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    category_type finance_tracker.transaction_type NOT NULL,
    category_name VARCHAR(50) NOT NULL
);

CREATE TABLE IF NOT EXISTS finance_tracker.operations (
    operation_id UUID PRIMARY KEY DEFAULT gen_random_uuid(),
    operation_type finance_tracker.transaction_type NOT NULL,
    bank_account_id UUID REFERENCES finance_tracker.bank_account(account_id) ON DELETE CASCADE,
    category_id UUID REFERENCES finance_tracker.category(category_id) ON DELETE SET NULL,
    amount DECIMAL(10, 2) NOT NULL CHECK (amount > 0),
    operation_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    description TEXT
);