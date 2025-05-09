DROP SCHEMA IF EXISTS files_analysis CASCADE;

CREATE SCHEMA IF NOT EXISTS files_analysis;

CREATE TABLE IF NOT EXISTS files_analysis.analyses_performed (
    id uuid primary key not null,
    paragraphs_count BIGINT not null,
    words_count BIGINT not null,
    consonant_letters_count BIGINT not null,
    vowel_letters_count BIGINT not null,
    digits_count BIGINT not null,
    symbols_count BIGINT not null,
    words_cloud_url text
);

CREATE index IF NOT EXISTS files_analysis_analyses_performed_id_hash_idx ON files_analysis.analyses_performed using HASH (id);
