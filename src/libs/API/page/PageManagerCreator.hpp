//
// Created by vladislav on 14.05.22.
//

#ifndef SERVER_V0_1_PAGEMANAGERCREATOR_H
#define SERVER_V0_1_PAGEMANAGERCREATOR_H

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <iostream>
#include <memory>
#include <string>

#include "PageManager.hpp"

namespace http = beast::http;           // from <boost/beast/http.hpp>


template<typename Body, typename Allocator, typename Send>
class PageManagerCreator {
public:
    static std::shared_ptr<GetPageManager<Body, Allocator, Send>>
    create_GetPageManager(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send);
    static std::shared_ptr<PutPageManager<Body, Allocator, Send>>
    create_PutPageManager(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send);
    static std::shared_ptr<PostPageManager<Body, Allocator, Send>>
    create_PostPageManager(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send);
    static std::shared_ptr<DeletePageManager<Body, Allocator, Send>>
    create_DeletePageManager(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send);
};

template<typename Body, typename Allocator, typename Send>
std::shared_ptr<GetPageManager<Body, Allocator, Send>>
PageManagerCreator<Body, Allocator, Send>::create_GetPageManager(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send) {
    return std::make_shared<GetPageManager<Body, Allocator, Send>>(std::move(req), std::move(send));
}

template<typename Body, typename Allocator, typename Send>
std::shared_ptr<PutPageManager<Body, Allocator, Send>>
PageManagerCreator<Body, Allocator, Send>::create_PutPageManager(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send) {
    return std::make_shared<PutPageManager<Body, Allocator, Send>>(std::move(req), std::move(send));
}

template<typename Body, typename Allocator, typename Send>
std::shared_ptr<PostPageManager<Body, Allocator, Send>>
PageManagerCreator<Body, Allocator, Send>::create_PostPageManager(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send) {
    return std::make_shared<PostPageManager<Body, Allocator, Send>>(std::move(req), std::move(send));
}

template<typename Body, typename Allocator, typename Send>
std::shared_ptr<DeletePageManager<Body, Allocator, Send>>
PageManagerCreator<Body, Allocator, Send>::create_DeletePageManager(http::request<Body, http::basic_fields<Allocator>> &&req, Send &&send) {
    return std::make_shared<DeletePageManager<Body, Allocator, Send>>(std::move(req), std::move(send));
}

#endif //SERVER_V0_1_PAGEMANAGERCREATOR_H
