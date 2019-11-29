#include <regex>
#include <boost/filesystem.hpp>

#include "util.h"

void ReadFileNames(const std::string& directory, std::vector<std::string>& fileNames, int nDocs) {
    boost::filesystem::path dirPath(directory);
    boost::filesystem::recursive_directory_iterator start(dirPath);
    boost::filesystem::recursive_directory_iterator end;
    for (auto it = start; it != end; it++) {
        if (boost::filesystem::is_directory(it->path())) {
            continue;
        }
        std::string path = it->path().string();
        if (path.substr(path.length() - 5) == ".html") {
            fileNames.push_back(path);
        }
        if (nDocs != -1 && fileNames.size() == static_cast<size_t>(nDocs)) {
            break;
        }
    }
}

std::string GetHost(const std::string& url) {
    // if u know better way to do it - it would be nice if u rewrite it
    std::string output = "";
    // https://stackoverflow.com/questions/2616011/easy-way-to-parse-a-url-in-c-cross-platform
    std::regex ex("(http|https)://(?:www\.)?([^/ :]+):?([^/ ]*)(/?[^ #?]*)\\x3f?([^ #]*)#?([^ ]*)");
    std::smatch what;
    if (std::regex_match(url, what, ex) && what.size() >= 3) {
        output = std::string(what[2].first, what[2].second);
    }
    return output;
}

