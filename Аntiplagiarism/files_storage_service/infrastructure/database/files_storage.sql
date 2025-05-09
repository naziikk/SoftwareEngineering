DROP SCHEMA IF EXISTS files_storage CASCADE;

CREATE SCHEMA IF NOT EXISTS files_storage;

CREATE TABLE IF NOT EXISTS files_storage.files (
    id uuid primary key DEFAULT gen_random_uuid(),
    name text NOT NULL,
    hash BIGINT NOT NULL,
    location text
);

CREATE TABLE IF NOT EXISTS files_storage.locations (
    location text primary key NOT NULL
);

CREATE INDEX IF NOT EXISTS files_storage_files_hash_idx ON files_storage.files using HASH (hash);
CREATE INDEX IF NOT EXISTS files_storage_files_location_idx ON files_storage.locations using HASH (location);
