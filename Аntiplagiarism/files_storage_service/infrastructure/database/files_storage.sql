DROP SCHEMA IF EXISTS files_storage CASCADE;

CREATE SCHEMA IF NOT EXISTS files_storage;

CREATE TABLE IF NOT EXISTS files_storage.files (
    id primary key uuid DEFAULT gen_random_uuid(),
    name text NOT NULL,
    hash integer NOT NULL,
    location text
);

CREATE TABLE IF NOT EXISTS files_storage.locations (
    location text NOT NULL
);

CREATE INDEX IF NOT EXISTS files_storage_files_hash_idx ON files_storage.files (hash);
CREATE INDEX IF NOT EXISTS files_storage_files_location_idx ON files_storage.locations (location);
