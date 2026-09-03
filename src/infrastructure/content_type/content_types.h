#pragma once

#include <optional>
#include <string_view>
#include <unordered_map>
#include <vector>

using namespace std::literals;

namespace content_type {
constexpr static std::string_view TEXT_HTML = "text/html"sv;
constexpr static std::string_view TEXT_CSS = "text/css"sv;
constexpr static std::string_view TEXT_PLAIN = "text/plain"sv;
constexpr static std::string_view TEXT_JS = "text/javascript"sv;

constexpr static std::string_view IMG_PNG = "image/png"sv;
constexpr static std::string_view IMG_JPEG = "image/jpeg"sv;
constexpr static std::string_view IMG_GIF = "image/gif"sv;
constexpr static std::string_view IMG_BMP = "image/bmp"sv;
constexpr static std::string_view IMG_VMI = "image/vnd.microsoft.icon"sv;
constexpr static std::string_view IMG_TIFF = "image/tiff"sv;
constexpr static std::string_view IMG_SVGXML = "image/svg+xml"sv;

constexpr static std::string_view AUDIO_MPEG = "audio/mpeg"sv;

constexpr static std::string_view APP_JSON = "application/json"sv;
constexpr static std::string_view APP_XML = "application/xml"sv;
constexpr static std::string_view APP_OCTETSTR = "application/octet-stream"sv;
};  // namespace content_type

inline const std::unordered_map<std::string_view, std::string_view> RESOURCE_CONTENT_TYPE{
    {"htm", content_type::TEXT_HTML},
    {"html", content_type::TEXT_HTML},
    {"css", content_type::TEXT_CSS},
    {"txt", content_type::TEXT_PLAIN},
    {"js", content_type::TEXT_JS},
    {"json", content_type::APP_JSON},
    {"xml", content_type::APP_XML},
    {"png", content_type::IMG_PNG},
    {"jpg", content_type::IMG_JPEG},
    {"jpe", content_type::IMG_JPEG},
    {"jpeg", content_type::IMG_JPEG},
    {"gif", content_type::IMG_GIF},
    {"bmp", content_type::IMG_BMP},
    {"ico", content_type::IMG_VMI},
    {"tiff", content_type::IMG_TIFF},
    {"tif", content_type::IMG_TIFF},
    {"svg", content_type::IMG_SVGXML},
    {"svgz", content_type::IMG_SVGXML},
    {"mp3", content_type::AUDIO_MPEG}};
