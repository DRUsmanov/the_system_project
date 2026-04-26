#pragma once

#include <boost/beast.hpp>
#include <optional>
#include <filesystem>
#include <unordered_map>

namespace infrastructure{

namespace beast = boost::beast;
namespace http = beast::http;
namespace sys = boost::system;
namespace fs = std::filesystem;
using namespace std::literals;

using FileResponse = http::response<http::file_body>;

/**
 * @brief Направляет пользователю выбранную страницу
 */
class FileSender{
public:
    FileSender(std::string files_directory)
    :files_directory_{files_directory}{ }

    enum class File{
        LOGIN_HTML,
        INDEX_HTML
    };
    
    template <typename TextResponseMaker, typename FileResponseMaker, typename Send>
    void operator()(File file_name, TextResponseMaker&& text_response_maker, FileResponseMaker&& file_response_maker, Send&& send) {
        http::file_body::value_type file;
        std::string file_path = files_directory_ + "/" + std::string(files[file_name]);

        if (sys::error_code ec; file.open(file_path.c_str(), beast::file_mode::read, ec), ec) {
            auto file_not_found_response = text_response_maker(http::status::not_found, FILE_NOT_FOUND, TEXT_PLAIN);
            send(std::move(file_not_found_response));
            return;
        }
        
        FileResponse file_response = file_response_maker(http::status::ok, std::move(file), TEXT_HTML);

        send(std::move(file_response));
    }
private:
    std::string files_directory_;

    inline static std::unordered_map<File, std::string_view> files{
        {File::INDEX_HTML, "index.html"sv},
        {File::LOGIN_HTML, "login.html"sv}    
    };
    
    constexpr static std::string_view FILE_NOT_FOUND = "File not found"sv;
    constexpr static std::string_view TEXT_HTML = "text/html"sv;
    constexpr static std::string_view TEXT_PLAIN = "text/plain"sv;
};
} // namespace infrastructure