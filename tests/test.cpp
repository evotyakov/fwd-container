#include <gtest/gtest.h>
#include <sstream>
#include <algorithm>
#include <cmath>
#include "stack.h"
#include "queue.h"

TEST(StackTest, Stack_Iterator)
{
    stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);

    // Константный итератор
    stack<int>::const_iterator cit = s.cbegin(), ocit;
    EXPECT_EQ(*cit, 30);
    ocit = ++cit;
    EXPECT_EQ(*cit, 20);
    EXPECT_EQ(*ocit, 20);
    ocit = cit++;
    EXPECT_EQ(*cit, 10);
    EXPECT_EQ(*ocit, 20);
    ++cit;
    EXPECT_EQ(cit, s.cend());

    // Константная ссылка
    const stack<int>& r = s;
    cit = r.begin();
    EXPECT_EQ(*cit, 30);
    ++cit;
    EXPECT_EQ(*cit, 20);
    cit++;
    EXPECT_EQ(*cit, 10);
    ++cit;
    EXPECT_EQ(cit, r.end());

    // Неконстантный итератор
    stack<int>::iterator it = s.begin(), oit;
    EXPECT_EQ(*it, 30);
    oit = ++it;
    EXPECT_EQ(*it, 20);
    EXPECT_EQ(*oit, 20);
    oit = it++;
    EXPECT_EQ(*it, 10);
    EXPECT_EQ(*oit, 20);
    *oit = 5;
    EXPECT_EQ(*it, 10);
    EXPECT_EQ(*oit, 5);
    ++it;
    EXPECT_EQ(it, s.end());

    std::stringstream sout;
    sout << s;
    EXPECT_EQ(sout.str(), "30 5 10");
}

TEST(StackTest, Stack_For)
{
    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);  // верх = 3

    const stack<int>& r = s;
    int expected1[] = {3, 2, 1};
    int idx = 0;
    for (auto& v : r) EXPECT_EQ(v, expected1[idx++]);

    int expected2[] = {6, 4, 2};
    idx = 0;
    for (auto& v : s) v *= 2;

    idx = 0;
    for (const auto& v : s) EXPECT_EQ(v, expected2[idx++]);

    int expected3[] = {7, 5, 3};

    for (stack<int>::iterator it = s.begin(); it != s.end(); ++it) {
        *it += 1;
    }
    idx = 0;
    for (stack<int>::const_iterator it = s.begin(); it != s.end(); ++it)
        EXPECT_EQ(*it, expected3[idx++]);
    idx = 0;
    for (stack<int>::const_iterator it = r.begin(); it != r.end(); ++it)
        EXPECT_EQ(*it, expected3[idx++]);
    idx = 0;
    for (stack<int>::const_iterator it = s.cbegin(); it != s.cend(); ++it)
        EXPECT_EQ(*it, expected3[idx++]);
}

TEST(StackTest, Stack_PushPopCopy)
{
    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);

    s.pop();
    s.push(10);
    s.push(20);

    stack<int> copy_s(s);

    int expected_orig[] = {20, 10, 2, 1};
    int idx = 0;
    for (auto v : copy_s) EXPECT_EQ(v, expected_orig[idx++]);

    copy_s.pop();
    copy_s.pop();
    copy_s.push(99);
    copy_s.push(98);
    copy_s.push(97);

    idx = 0;
    for (auto v : s) EXPECT_EQ(v, expected_orig[idx++]);

    int expected_copy[] = {97, 98, 99, 2, 1};
    idx = 0;
    for (auto v : copy_s) EXPECT_EQ(v, expected_copy[idx++]);

    stack<int> moved_s(std::move(copy_s));

    int expected_moved[] = {97, 98, 99, 2, 1};
    idx = 0;
    for (auto v : moved_s) EXPECT_EQ(v, expected_moved[idx++]);

    EXPECT_TRUE(copy_s.is_empty());

    stack<int> s2;
    s2 = s;
    idx = 0;
    for (auto v : s2) EXPECT_EQ(v, expected_orig[idx++]);

    s2.pop();
    s2.push(42);
    s2.push(99);

    idx = 0;
    for (auto v : s) EXPECT_EQ(v, expected_orig[idx++]);

    int expected_copy_asgn[] = {99, 42, 10, 2, 1};
    idx = 0;
    for (auto v : s2) EXPECT_EQ(v, expected_copy_asgn[idx++]);

    stack<int> s3;
    s3 = std::move(s2);
    idx = 0;
    for (auto v : s3) EXPECT_EQ(v, expected_copy_asgn[idx++]);

    EXPECT_TRUE(s2.is_empty());

    s3.pop();
    s3.push(77);
    int expected_final[] = {77, 42, 10, 2, 1};
    idx = 0;
    for (auto v : s3) EXPECT_EQ(v, expected_final[idx++]);
}

TEST(StackTest, Stack_IO)
{
    stack<int> s;
    s.push(0);

    std::stringstream sin("1 2 3 4 5");
    sin >> s;

    // Проверим размер
    EXPECT_EQ(s.size(), 6u);

    int expected[] = {5, 4, 3, 2, 1, 0};
    int idx = 0;
    for (auto v : s) EXPECT_EQ(v, expected[idx++]);

    std::stringstream sout;
    sout << s;

    std::string expected_str = "5 4 3 2 1 0";
    EXPECT_EQ(sout.str(), expected_str);

    for (auto& v : s) v += 10;  // увеличим каждый элемент на 10

    std::stringstream sout2;
    sout2 << s;
    std::string expected_str2 = "15 14 13 12 11 10";
    EXPECT_EQ(sout2.str(), expected_str2);
}

TEST(StackTest, Stack_Algs)
{
    stack<int> s;

    for (int i = 1; i <= 5; ++i) s.push(i);

    auto it = std::find_if(s.begin(), s.end(), [](int v){ return v % 2 == 0; });
    EXPECT_NE(it, s.end());
    EXPECT_EQ(*it, 4);
    *it = 3;

    const stack<int>& r = s;
    auto cit = std::find_if(r.begin(), r.end(), [](int v){ return v % 2 == 0; });
    EXPECT_NE(cit, r.end());
    EXPECT_EQ(*cit, 2);

    it = std::find_if(s.begin(), s.end(), [](int v){ return v == 0; });
    EXPECT_EQ(it, s.end());

    auto count_even = std::count_if(s.begin(), s.end(), [](int v){ return v % 2 == 0; });
    EXPECT_EQ(count_even, 1);

    std::replace_if(s.begin(), s.end(), [](int v){ return v % 2 != 0; }, 99);
    int expected_replace[] = {99, 99, 99, 2, 99};
    int idx = 0;
    for (auto v : s) EXPECT_EQ(v, expected_replace[idx++]);

    std::for_each(s.begin(), s.end(), [](int& v){ v += 1; });
    int expected_for_each[] = {100, 100, 100, 3, 100};
    idx = 0;
    for (auto v : s) EXPECT_EQ(v, expected_for_each[idx++]);
}

TEST(ContainerTest, BaseContainer)
{
    stack<int> s;
    queue<int> q;

    // Наполним контейнеры
    s.push(1);
    s.push(2);
    s.push(3);
    q.push(10);
    q.push(20);
    q.push(30);

    fwd_container<int>& bs = s;
    fwd_container<int>& bq = q;
    const fwd_container<int>& cs = s;

    int expected_s_after[] = {3, 2, 1};
    int idx = 0;
    for (auto v : s) EXPECT_EQ(v, expected_s_after[idx++]);

    int expected_q_after[] = {10, 20, 30};
    idx = 0;
    for (auto v : q) EXPECT_EQ(v, expected_q_after[idx++]);

    idx = 0;
    for (auto& it : bs) EXPECT_EQ(it, expected_s_after[idx++]);

    idx = 0;
    for (const auto& it : bs) EXPECT_EQ(it, expected_s_after[idx++]);

    idx = 0;
    for (auto& it : cs) EXPECT_EQ(it, expected_s_after[idx++]);

    idx = 0;
    for (auto& it : bq) EXPECT_EQ(it, expected_q_after[idx++]);

    idx = 0;
    for (const auto& it : bq) EXPECT_EQ(it, expected_q_after[idx++]);

    idx = 0;
    for (auto& it : bq) EXPECT_EQ(it, expected_q_after[idx++]);
}

TEST(QueueTest, Queue_Iterator)
{
    queue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);

    // Константный итератор
    queue<int>::const_iterator cit = q.cbegin(), ocit;
    EXPECT_EQ(*cit, 10);
    ocit = ++cit;
    EXPECT_EQ(*cit, 20);
    EXPECT_EQ(*ocit, 20);
    ocit = cit++;
    EXPECT_EQ(*cit, 30);
    EXPECT_EQ(*ocit, 20);
    ++cit;
    EXPECT_EQ(cit, q.cend());

    // Константная ссылка
    const queue<int>& r = q;
    cit = r.begin();
    EXPECT_EQ(*cit, 10);
    ++cit;
    EXPECT_EQ(*cit, 20);
    cit++;
    EXPECT_EQ(*cit, 30);
    ++cit;
    EXPECT_EQ(cit, r.end());

    // Неконстантный итератор
    queue<int>::iterator it = q.begin(), oit;
    EXPECT_EQ(*it, 10);
    oit = ++it;
    EXPECT_EQ(*it, 20);
    EXPECT_EQ(*oit, 20);
    oit = it++;
    EXPECT_EQ(*it, 30);
    EXPECT_EQ(*oit, 20);
    *oit = 5;
    EXPECT_EQ(*it, 30);
    EXPECT_EQ(*oit, 5);
    ++it;
    EXPECT_EQ(it, q.end());

    std::stringstream sout;
    sout << q;
    EXPECT_EQ(sout.str(), "10 5 30");
}

TEST(QueueTest, Queue_For)
{
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    const queue<int>& r = q;
    int expected1[] = {1, 2, 3};
    int idx = 0;
    for (auto& v : r) EXPECT_EQ(v, expected1[idx++]);

    int expected2[] = {2, 4, 6};
    idx = 0;
    for (auto& v : q) v *= 2;

    idx = 0;
    for (const auto& v : q) EXPECT_EQ(v, expected2[idx++]);

    int expected3[] = {3, 5, 7};

    for (queue<int>::iterator it = q.begin(); it != q.end(); ++it) {
        *it += 1;
    }
    idx = 0;
    for (queue<int>::const_iterator it = q.begin(); it != q.end(); ++it)
        EXPECT_EQ(*it, expected3[idx++]);
    idx = 0;
    for (queue<int>::const_iterator it = r.begin(); it != r.end(); ++it)
        EXPECT_EQ(*it, expected3[idx++]);
    idx = 0;
    for (queue<int>::const_iterator it = q.cbegin(); it != q.cend(); ++it)
        EXPECT_EQ(*it, expected3[idx++]);
}

TEST(QueueTest, Queue_PushPopCopy)
{
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    q.pop();
    q.push(10);
    q.push(20);

    queue<int> copy_q(q);

    int expected_orig[] = {2, 3, 10, 20};
    int idx = 0;
    for (auto v : copy_q) EXPECT_EQ(v, expected_orig[idx++]);

    copy_q.pop();
    copy_q.pop();
    copy_q.push(99);
    copy_q.push(98);
    copy_q.push(97);

    idx = 0;
    for (auto v : q) EXPECT_EQ(v, expected_orig[idx++]);

    int expected_copy[] = {10, 20, 99, 98, 97};
    idx = 0;
    for (auto v : copy_q) EXPECT_EQ(v, expected_copy[idx++]);

    queue<int> moved_q(std::move(copy_q));

    int expected_moved[] = {10, 20, 99, 98, 97};
    idx = 0;
    for (auto v : moved_q) EXPECT_EQ(v, expected_moved[idx++]);

    EXPECT_TRUE(copy_q.is_empty());

    queue<int> q2;
    q2 = q;
    idx = 0;
    for (auto v : q2) EXPECT_EQ(v, expected_orig[idx++]);

    q2.pop();
    q2.push(42);
    q2.push(99);

    idx = 0;
    for (auto v : q) EXPECT_EQ(v, expected_orig[idx++]);

    int expected_copy_asgn[] = {3, 10, 20, 42, 99};
    idx = 0;
    for (auto v : q2) EXPECT_EQ(v, expected_copy_asgn[idx++]);

    queue<int> q3;
    q3 = std::move(q2);
    idx = 0;
    for (auto v : q3) EXPECT_EQ(v, expected_copy_asgn[idx++]);

    EXPECT_TRUE(q2.is_empty());

    q3.pop();
    q3.push(77);
    int expected_final[] = {10, 20, 42, 99, 77};
    idx = 0;
    for (auto v : q3) EXPECT_EQ(v, expected_final[idx++]);
}

TEST(QueueTest, Queue_IO)
{
    queue<int> q;
    q.push(0);

    std::stringstream sin("1 2 3 4 5");
    sin >> q;

    EXPECT_EQ(q.size(), 6u);

    int expected[] = {0, 1, 2, 3, 4, 5};
    int idx = 0;
    for (auto v : q) EXPECT_EQ(v, expected[idx++]);

    std::stringstream sout;
    sout << q;

    std::string expected_str = "0 1 2 3 4 5";
    EXPECT_EQ(sout.str(), expected_str);

    for (auto& v : q) v += 10;

    std::stringstream sout2;
    sout2 << q;
    std::string expected_str2 = "10 11 12 13 14 15";
    EXPECT_EQ(sout2.str(), expected_str2);
}

TEST(QueueTest, Queue_Algs)
{
    queue<int> q;

    for (int i = 1; i <= 5; ++i) q.push(i);

    auto it = std::find_if(q.begin(), q.end(), [](int v){ return v % 2 == 0; });
    EXPECT_NE(it, q.end());
    EXPECT_EQ(*it, 2);
    *it = 3;

    const queue<int>& r = q;
    auto cit = std::find_if(r.begin(), r.end(), [](int v){ return v % 2 == 0; });
    EXPECT_NE(cit, r.end());
    EXPECT_EQ(*cit, 4);

    it = std::find_if(q.begin(), q.end(), [](int v){ return v == 0; });
    EXPECT_EQ(it, q.end());

    auto count_even = std::count_if(q.begin(), q.end(), [](int v){ return v % 2 == 0; });
    EXPECT_EQ(count_even, 1);

    std::replace_if(q.begin(), q.end(), [](int v){ return v % 2 != 0; }, 99);
    int expected_replace[] = {99, 99, 99, 4, 99};
    int idx = 0;
    for (auto v : q) EXPECT_EQ(v, expected_replace[idx++]);

    std::for_each(q.begin(), q.end(), [](int& v){ v += 1; });
    int expected_for_each[] = {100, 100, 100, 5, 100};
    idx = 0;
    for (auto v : q) EXPECT_EQ(v, expected_for_each[idx++]);
}

TEST(DoubleContainerTest, DoubleStack_Iterator)
{
    stack<double> s;
    s.push(10.5);
    s.push(20.5);
    s.push(30.5);

    stack<double>::const_iterator cit = s.cbegin(), ocit;
    EXPECT_DOUBLE_EQ(*cit, 30.5);
    ocit = ++cit;
    EXPECT_DOUBLE_EQ(*cit, 20.5);
    EXPECT_DOUBLE_EQ(*ocit, 20.5);
    ocit = cit++;
    EXPECT_DOUBLE_EQ(*cit, 10.5);
    EXPECT_DOUBLE_EQ(*ocit, 20.5);
    ++cit;
    EXPECT_EQ(cit, s.cend());

    const stack<double>& r = s;
    cit = r.begin();
    EXPECT_DOUBLE_EQ(*cit, 30.5);
    ++cit;
    EXPECT_DOUBLE_EQ(*cit, 20.5);
    cit++;
    EXPECT_DOUBLE_EQ(*cit, 10.5);
    ++cit;
    EXPECT_EQ(cit, r.end());

    stack<double>::iterator it = s.begin(), oit;
    EXPECT_DOUBLE_EQ(*it, 30.5);
    oit = ++it;
    EXPECT_DOUBLE_EQ(*it, 20.5);
    EXPECT_DOUBLE_EQ(*oit, 20.5);
    oit = it++;
    EXPECT_DOUBLE_EQ(*it, 10.5);
    EXPECT_DOUBLE_EQ(*oit, 20.5);
    *oit = 5.5;
    EXPECT_DOUBLE_EQ(*it, 10.5);
    EXPECT_DOUBLE_EQ(*oit, 5.5);
    ++it;
    EXPECT_EQ(it, s.end());

    std::stringstream sout;
    sout << s;
    EXPECT_EQ(sout.str(), "30.5 5.5 10.5");
}

TEST(DoubleContainerTest, DoubleQueue_For)
{
    queue<double> q;
    q.push(1.1);
    q.push(2.2);
    q.push(3.3);

    const queue<double>& r = q;
    double expected1[] = {1.1, 2.2, 3.3};
    int idx = 0;
    for (auto& v : r) EXPECT_DOUBLE_EQ(v, expected1[idx++]);

    double expected2[] = {2.2, 4.4, 6.6};
    idx = 0;
    for (auto& v : q) v *= 2.0;

    idx = 0;
    for (const auto& v : q) EXPECT_DOUBLE_EQ(v, expected2[idx++]);

    double expected3[] = {3.2, 5.4, 7.6};

    for (queue<double>::iterator it = q.begin(); it != q.end(); ++it) {
        *it += 1.0;
    }
    idx = 0;
    for (queue<double>::const_iterator it = q.begin(); it != q.end(); ++it)
        EXPECT_DOUBLE_EQ(*it, expected3[idx++]);
    idx = 0;
    for (queue<double>::const_iterator it = r.begin(); it != r.end(); ++it)
        EXPECT_DOUBLE_EQ(*it, expected3[idx++]);
    idx = 0;
    for (queue<double>::const_iterator it = q.cbegin(); it != q.cend(); ++it)
        EXPECT_DOUBLE_EQ(*it, expected3[idx++]);
}

TEST(DoubleContainerTest, DoubleStack_PushPopCopy)
{
    stack<double> s;
    s.push(1.1);
    s.push(2.2);
    s.push(3.3);

    s.pop();
    s.push(10.1);
    s.push(20.2);

    stack<double> copy_s(s);

    double expected_orig[] = {20.2, 10.1, 2.2, 1.1};
    int idx = 0;
    for (auto v : copy_s) EXPECT_DOUBLE_EQ(v, expected_orig[idx++]);

    copy_s.pop();
    copy_s.pop();
    copy_s.push(99.9);
    copy_s.push(98.8);
    copy_s.push(97.7);

    idx = 0;
    for (auto v : s) EXPECT_DOUBLE_EQ(v, expected_orig[idx++]);

    double expected_copy[] = {97.7, 98.8, 99.9, 2.2, 1.1};
    idx = 0;
    for (auto v : copy_s) EXPECT_DOUBLE_EQ(v, expected_copy[idx++]);

    stack<double> moved_s(std::move(copy_s));

    double expected_moved[] = {97.7, 98.8, 99.9, 2.2, 1.1};
    idx = 0;
    for (auto v : moved_s) EXPECT_DOUBLE_EQ(v, expected_moved[idx++]);

    EXPECT_TRUE(copy_s.is_empty());

    stack<double> s2;
    s2 = s;
    idx = 0;
    for (auto v : s2) EXPECT_DOUBLE_EQ(v, expected_orig[idx++]);

    s2.pop();
    s2.push(42.42);
    s2.push(99.99);

    idx = 0;
    for (auto v : s) EXPECT_DOUBLE_EQ(v, expected_orig[idx++]);

    double expected_copy_asgn[] = {99.99, 42.42, 10.1, 2.2, 1.1};
    idx = 0;
    for (auto v : s2) EXPECT_DOUBLE_EQ(v, expected_copy_asgn[idx++]);

    stack<double> s3;
    s3 = std::move(s2);
    idx = 0;
    for (auto v : s3) EXPECT_DOUBLE_EQ(v, expected_copy_asgn[idx++]);

    EXPECT_TRUE(s2.is_empty());

    s3.pop();
    s3.push(77.77);
    double expected_final[] = {77.77, 42.42, 10.1, 2.2, 1.1};
    idx = 0;
    for (auto v : s3) EXPECT_DOUBLE_EQ(v, expected_final[idx++]);
}

TEST(DoubleContainerTest, DoubleQueue_IO)
{
    queue<double> q;
    q.push(0.5);

    std::stringstream sin("1.1 2.2 3.3 4.4 5.5");
    sin >> q;

    EXPECT_EQ(q.size(), 6u);

    double expected[] = {0.5, 1.1, 2.2, 3.3, 4.4, 5.5};
    int idx = 0;
    for (auto v : q) EXPECT_DOUBLE_EQ(v, expected[idx++]);

    std::stringstream sout;
    sout << q;

    std::string expected_str = "0.5 1.1 2.2 3.3 4.4 5.5";
    EXPECT_EQ(sout.str(), expected_str);

    for (auto& v : q) v += 10.0;

    std::stringstream sout2;
    sout2 << q;
    std::string expected_str2 = "10.5 11.1 12.2 13.3 14.4 15.5";
    EXPECT_EQ(sout2.str(), expected_str2);
}

TEST(DoubleContainerTest, DoubleStack_Algs)
{
    stack<double> s;

    for (double i = 1.0; i <= 5.0; i += 1.0) s.push(i);

    auto it = std::find_if(s.begin(), s.end(), [](double v){ return std::fmod(v, 2.0) == 0.0; });
    EXPECT_NE(it, s.end());
    EXPECT_DOUBLE_EQ(*it, 4.0);
    *it = 3.0;

    const stack<double>& r = s;
    auto cit = std::find_if(r.begin(), r.end(), [](double v){ return std::fmod(v, 2.0) == 0.0; });
    EXPECT_NE(cit, r.end());
    EXPECT_DOUBLE_EQ(*cit, 2.0);

    it = std::find_if(s.begin(), s.end(), [](double v){ return v == 0.0; });
    EXPECT_EQ(it, s.end());

    auto count_even = std::count_if(s.begin(), s.end(), [](double v){ return std::fmod(v, 2.0) == 0.0; });
    EXPECT_EQ(count_even, 1);

    std::replace_if(s.begin(), s.end(), [](double v){ return std::fmod(v, 2.0) != 0.0; }, 99.0);
    double expected_replace[] = {99.0, 99.0, 99.0, 2.0, 99.0};
    int idx = 0;
    for (auto v : s) EXPECT_DOUBLE_EQ(v, expected_replace[idx++]);

    std::for_each(s.begin(), s.end(), [](double& v){ v += 1.0; });
    double expected_for_each[] = {100.0, 100.0, 100.0, 3.0, 100.0};
    idx = 0;
    for (auto v : s) EXPECT_DOUBLE_EQ(v, expected_for_each[idx++]);
}

TEST(DoubleContainerTest, DoubleContainerBase)
{
    stack<double> s;
    queue<double> q;

    s.push(1.1);
    s.push(2.2);
    s.push(3.3);
    q.push(10.1);
    q.push(20.2);
    q.push(30.3);

    fwd_container<double>& bs = s;
    fwd_container<double>& bq = q;
    const fwd_container<double>& cs = s;

    double expected_s_after[] = {3.3, 2.2, 1.1};
    int idx = 0;
    for (auto v : s) EXPECT_DOUBLE_EQ(v, expected_s_after[idx++]);

    double expected_q_after[] = {10.1, 20.2, 30.3};
    idx = 0;
    for (auto v : q) EXPECT_DOUBLE_EQ(v, expected_q_after[idx++]);

    idx = 0;
    for (auto& it : bs) EXPECT_DOUBLE_EQ(it, expected_s_after[idx++]);

    idx = 0;
    for (const auto& it : bs) EXPECT_DOUBLE_EQ(it, expected_s_after[idx++]);

    idx = 0;
    for (auto& it : cs) EXPECT_DOUBLE_EQ(it, expected_s_after[idx++]);

    idx = 0;
    for (auto& it : bq) EXPECT_DOUBLE_EQ(it, expected_q_after[idx++]);

    idx = 0;
    for (const auto& it : bq) EXPECT_DOUBLE_EQ(it, expected_q_after[idx++]);

    idx = 0;
    for (auto& it : bq) EXPECT_DOUBLE_EQ(it, expected_q_after[idx++]);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}