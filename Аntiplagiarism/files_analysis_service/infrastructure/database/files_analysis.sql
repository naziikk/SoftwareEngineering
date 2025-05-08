DROP SCHEMA IF EXISTS files_analyzer CASCADE;

CREATE TABLE IF NOT EXISTS files_analysis.analyses_performed (
    id primary key not null,
    paragraphs_count integer not null,
    words_count integer not null,
    consonant_letters_count integer not null,
    vowel_letters_count integer not null,
    digits_count integer not null,
    symbols_count integer not null,
    words_cloud_url varchar(255)
)