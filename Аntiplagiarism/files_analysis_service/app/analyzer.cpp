#include "analyzer.h"

void Analyzer::analyse_file(const httplib::MultipartFormData& file, const std::string& file_id) {
    Analysis analysis = get_analysis(file, file_id);
    get_words_cloud(file.content, analysis);

    save_analysis(analysis);
}

void Analyzer::generate_words_cloud(const std::string& file_content, Analysis& analysis) {
    std::string url = "https://quickchart.io/wordcloud";
    httplib::Client client(url);

    json request_body = {
        {"text", file_content},
        {"width", 800},
        {"height", 600},
        {"fontFamily", "Arial"},
        {"scale", "log"},
        {"padding", 2},
        {"rotation", 0}
    };

    auto res = client.Post("/generate", request_body.dump(), "application/json");

    if (res && res->status == 200) {
        analysis.words_cloud_url = res->body;
    } else {
        throw std::runtime_error("Shit happens while generating word cloud");
    }
}

// Общая логика анализа файла:
// 1) За параграф считается текст между двумя пустыми строками
// 2) За предложение считается текст между двумя точками
// 3) За слово считается текст между двумя пробелами
// 4) За символ считается любой символ, кроме пробела
// 5) За букву считается любой символ, кроме пробела, пунктуации и цифр
// А далее уже определяем гласная она или согласная в соответствии с методами
// из utils.h
Analysis Analyzer::get_analysis(const httplib::MultipartFormData& file, const std::string& file_id) {
    std::stringstream file_stream(file.content);
    std::string line;

    Analysis analysis;
    analysis.id = file_id;

    bool in_paragraph = false;

    while (std::getline(file_stream, line)) {
        if (line.empty()) {
            in_paragraph = false;
            continue;
        }

        if (!in_paragraph) {
            analysis.paragraphs_count++; // новый непустой блок == новый параграф
            in_paragraph = true;
        }

        char prev_symbol;

        for (const auto& symbol : line) {
            if (is_space(symbol) || is_punctuation(symbol)) {
                if (is_letter(prev_symbol)) {
                    analysis.words_count++;
                }

                prev_symbol = symbol;
                continue;
            }

            if (is_letter(symbol)) {
                analysis.letters_count++;
                if (is_vowel(symbol)) {
                    analysis.vowels_count++;
                } else {
                    analysis.consonants_count++;
                }
            } else if (is_digit(symbol)) {
                analysis.digits_count++;
            } else {
                analysis.symbols_count++;
            }
        }
    }

    return analysis;
}

void Analyzer::save_analysis(const Analysis& analysis) {
    std::vector<std::string> params = {
        analysis.id,
        std::to_string(analysis.paragraphs_count),
        std::to_string(analysis.words_count),
        std::to_string(analysis.consonants_count),
        std::to_string(analysis.vowels_count),
        std::to_string(analysis.digits_count),
        std::to_string(analysis.symbols_count),
        analysis.words_cloud_url
    };

    std::string query = "INSERT INTO files_storage.analysis (id, paragraphs_count, words_count, consonants_count, "
                        "vowels_count, digits_count, symbols_count, words_cloud_url) VALUES ($1, $2, $3, $4, $5, $6, $7, $8)";

    db_.execute_query(query, params);
}
