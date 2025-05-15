#include "../include/handlers/ResourceUploadHandler.h"
#include <fstream>
#include <iostream>


void ResourceUploadHandler::handle(const http::HttpRequest &req, http::HttpResponse *resp)
{
    // JSON 解析使用 try catch 捕获异常
    try
    {
        // 检查用户是否已登录
        auto session = server_->getSessionManager()->getSession(req, resp);
        LOG_INFO << "session->getValue(\"isLoggedIn\") = " << session->getValue("isLoggedIn");
        if (session->getValue("isLoggedIn") != "true")
        {
            // 用户未登录，返回未授权错误
            json errorResp;
            errorResp["status"] = "error";
            errorResp["message"] = "Unauthorized";
            std::string errorBody = errorResp.dump(4);

            server_->packageResp(req.getVersion(), http::HttpResponse::k401Unauthorized,
                                "Unauthorized", true, "application/json", errorBody.size(),
                                 errorBody, resp);
            return;
        }

       if (req.get_parseMultipartData_state())
       {    

            // 获取当前时间字符串
            auto now = std::chrono::system_clock::now();
            std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
            std::stringstream time_ss;
            time_ss << std::put_time(std::localtime(&now_time_t), "%Y-%m-%d %H:%M");

             // 返回成功信息
            json successResp;
            successResp["status"] = "success";
            successResp["message"] = "上传成功";
            successResp["uploadTime"] = time_ss.str();  // 添加时间字段
            

            std::string successBody = successResp.dump();

            resp->setStatusLine(req.getVersion(), http::HttpResponse::k200Ok, "OK");
            resp->setCloseConnection(false);
            resp->setContentType("application/json");
            resp->setContentLength(successBody.size());
            resp->setBody(successBody);

            LOG_INFO<<"进来了嘛？";
            LOG_INFO<<"上传时间"<<muduo::Timestamp::now().toFormattedString(false);
       }
       else
       {
              throw std::runtime_error("Multipart parsing failed");
       }
       
    }
    catch (const std::exception &e)
    {
        // 捕获异常，返回错误信息
        json failureResp;
        failureResp["status"] = "error";
        failureResp["message"] = e.what();
        std::string failureBody = failureResp.dump(4);
        resp->setStatusLine(req.getVersion(), http::HttpResponse::k400BadRequest, "Bad Request");
        resp->setCloseConnection(true);
        resp->setContentType("application/json");
        resp->setContentLength(failureBody.size());
        resp->setBody(failureBody);
    }
}