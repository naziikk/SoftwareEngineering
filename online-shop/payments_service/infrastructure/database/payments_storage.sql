DROP SCHEMA IF EXISTS payments CASCADE;

CREATE SCHEMA IF NOT EXISTS payments;

CREATE TABLE IF NOT EXISTS payments.bill (
    id uuid primary key DEFAULT gen_random_uuid(),
    user_id uuid NOT NULL,
    money_amount DECIMAL(10, 2) NOT NULL
);

CREATE TABLE IF NOT EXISTS files_storage.locations (
    location text primary key NOT NULL
);

CREATE INDEX IF NOT EXISTS files_storage_files_hash_idx ON files_storage.files using HASH (hash);
CREATE INDEX IF NOT EXISTS files_storage_files_location_idx ON files_storage.locations using HASH (location);
