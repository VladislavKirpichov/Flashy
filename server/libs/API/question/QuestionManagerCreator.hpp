//
// Created by vladislav on 28.05.22.
//

#ifndef SERVER_V0_1_QUESTIONMANAGERCREATOR_HPP
#define SERVER_V0_1_QUESTIONMANAGERCREATOR_HPP

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <iostream>
#include <memory>
#include <string>

#include "QuestionManager.hpp"

namespace http = beast::http;           // from <boost/beast/http.hpp>


template<typename Body, typename Allocator, typename Send>
class QuestionManagerCreator {
public:
    static std::shared_ptr<GetQuestionManager<Body, Allocator, Send>>
    create_GetQuestionManager(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send);
    static std::shared_ptr<PutQuestionManager<Body, Allocator, Send>>
    create_PutQuestionManager(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send);
    static std::shared_ptr<PostQuestionManager<Body, Allocator, Send>>
    create_PostQuestionManager(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send);
    static std::shared_ptr<GetQuestionManager<Body, Allocator, Send>>
    create_DeleteQuestionManager(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send);
};

template<typename Body, typename Allocator, typename Send>
std::shared_ptr<GetQuestionManager<Body, Allocator, Send>>
QuestionManagerCreator<Body, Allocator, Send>::create_GetQuestionManager(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send) {
return std::make_shared<GetQuestionManager<Body, Allocator, Send>>(std::move(req), std::move(send));
}

template<typename Body, typename Allocator, typename Send>
std::shared_ptr<PutQuestionManager<Body, Allocator, Send>>
QuestionManagerCreator<Body, Allocator, Send>::create_PutQuestionManager(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send) {
return std::make_shared<PutQuestionManager<Body, Allocator, Send>>(std::move(req), std::move(send));
}

template<typename Body, typename Allocator, typename Send>
std::shared_ptr<PostQuestionManager<Body, Allocator, Send>>
QuestionManagerCreator<Body, Allocator, Send>::create_PostQuestionManager(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send) {
return std::make_shared<PostQuestionManager<Body, Allocator, Send>>(std::move(req), std::move(send));
}

template<typename Body, typename Allocator, typename Send>
std::shared_ptr<GetQuestionManager<Body, Allocator, Send>>
QuestionManagerCreator<Body, Allocator, Send>::create_DeleteQuestionManager(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send) {
return std::make_shared<GetQuestionManager<Body, Allocator, Send>>(std::move(req), std::move(send));
}

#endif //SERVER_V0_1_QUESTIONMANAGERCREATOR_HPP