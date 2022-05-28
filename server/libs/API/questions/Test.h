//
// Created by vladislav on 06.05.22.
//

#ifndef SERVER_V0_1_TEST_H
#define SERVER_V0_1_TEST_H

template<typename... Args>
class Test {
public:
    Test();
    ~Test();

    void get_page_tests();
    void get_user_tests();
private:
    void auth_user();
};

#endif //SERVER_V0_1_TEST_H
