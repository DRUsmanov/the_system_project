#include "url_decoder.h"

#include <boost/url/url_view.hpp>
#include <boost/url/parse.hpp>

using namespace infrastructure;

std::string DecodeUrl(std::string_view encoded_url) {
    boost::urls::url_view encoded_url_view{encoded_url};

    std::string decoded_url;

    decoded_url.append(encoded_url_view.path());

    if(encoded_url_view.params().size() != 0){
        decoded_url.append("?");

        bool is_first = true;

        for (auto it : encoded_url_view.params()){
            if (!is_first){
                decoded_url.append("&");
            }
            decoded_url.append(std::string(it.key));
            if (it.has_value){
                decoded_url.append("=");
                decoded_url.append(std::string(it.value));
            }
            is_first = false;
        }
    }

    if (!encoded_url_view.fragment().empty()){
        decoded_url.append("#");
        decoded_url.append(std::string(encoded_url_view.fragment()));
    }
    
    return decoded_url;
}
