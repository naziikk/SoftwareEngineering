#include "analyzer.h"

void Analyzer::analyse_file(const httplib::MultipartFormData& file, const std::string& file_id) {
    std::cout << "Received file for analysis" << std::endl;
    Analysis analysis = get_analysis(file, file_id);
    generate_words_cloud(file.content, analysis);

    save_analysis(analysis);
    std::cout << "Analysis completed" << std::endl;
}

void Analyzer::generate_words_cloud(const std::string& file_content, Analysis& analysis) {
    std::string chart_url = "https://quickchart.io/wordcloud?text=" + httplib::detail::encode_url(file_content);
    analysis.words_cloud_url = chart_url;
}

// Общая логика анализа файла:
// 1) За параграф считается текст между двумя пустыми строками
// 2) За предложение считается текст между двумя точками
// 3) За слово считается текст между двумя пробелами
// 4) За символ считается любой символ, кроме пробела
// 5) За букву считается любой символ, кроме пробела, пунктуации и цифр
// А далее уже определяем гласная она или согласная в соответствии с методами
// из utils.h
Analyzer::Analysis Analyzer::get_analysis(const httplib::MultipartFormData& file, const std::string& file_id) {
    std::stringstream file_stream(file.content);
    std::string line;

    Analysis analysis;
    analysis.id = file_id;

    bool in_paragraph = false;

    while (std::getline(file_stream, line)) {
        std::cout << line << '\n';
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
                if (is_vowel(symbol)) {
                    analysis.vowel_letters_count++;
                } else {
                    analysis.consonant_letters_count++;
                }
            } else if (is_digit(symbol)) {
                analysis.digits_count++;
            }

            analysis.symbols_count++;
            prev_symbol = symbol;
        }
    }

    return analysis;
}

void Analyzer::save_analysis(const Analysis& analysis) {
    std::vector<std::string> params = {
        analysis.id,
        std::to_string(analysis.paragraphs_count),
        std::to_string(analysis.words_count),
        std::to_string(analysis.consonant_letters_count),
        std::to_string(analysis.vowel_letters_count),
        std::to_string(analysis.digits_count),
        std::to_string(analysis.symbols_count),
        analysis.words_cloud_url
    };

    std::string query = "INSERT INTO files_analysis.analyses_performed (id, paragraphs_count, words_count, consonant_letters_count, "
                        "vowel_letters_count, digits_count, symbols_count, words_cloud_url) VALUES ($1, $2, $3, $4, $5, $6, $7, $8)";

    db_.execute_query(query, params);
}
