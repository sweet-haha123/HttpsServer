#pragma once
#include "../../../../HttpServer/include/router/RouterHandler.h"
#include "../GomokuServer.h"
#include <filesystem>
#include <vector>
#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;
using json = nlohmann::json;
class ResourceListHandler : public http::router::RouterHandler 
{
public:
    explicit ResourceListHandler(GomokuServer* server) : server_(server) {}

    void handle(const http::HttpRequest& req, http::HttpResponse* resp) override;

    std::string formatFileTime(std::filesystem::file_time_type ftime) ;
    json getUploadHistoryJson(const std::string& rootDir) ;

private:
    GomokuServer* server_;
};