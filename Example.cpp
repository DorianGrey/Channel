/*
 * Example.cpp
 *
 *  Created on: 23.08.2012
 *      Author: doriangrey
 */

#include "Channel/Channel.hpp"
#include <chrono>
#include <cstdint>
#include <iostream>
#include <thread>

/**
    Example 1: Create a channel-object from scratch, handle it over to two threads, and go ahead.
*/
void Example1(std::uint32_t numRuns)
{
    Channel<float> chan;
    std::mutex coutmutex;
    std::thread t1([&chan, numRuns, &coutmutex]() -> void
    {
        std::uint32_t runs = numRuns;
        float msgBase = 5.0f;
        while (runs-- > 0)
        {
            chan << msgBase;
            msgBase += 1.0f;
            std::lock_guard<std::mutex> guard(coutmutex);
            std::cout << "Task 1 put a msg." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

    });
    std::thread t2([&chan, numRuns, &coutmutex]() -> void
    {
        float res = 0;
        std::uint32_t runs = numRuns;
        while (runs-- > 0)
        {
            chan >> res;
            std::lock_guard<std::mutex> guard(coutmutex);
            std::cout << "Task 2 took a msg: " << res << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

    });
    t1.join();
    t2.join();
}

/**
    Example 2: Create a shared-ptr-channel, handle it over to two threads, and go ahead.
    Note that it appears rather similar to the version above, since the channel is handled
    over as reference from enclosing scope.
*/
void Example2(std::uint32_t numRuns)
{
    auto chan = make_chan<int>();
    std::mutex coutmutex;
    std::thread t1([&chan, numRuns, &coutmutex]() -> void
    {
        std::uint32_t runs = numRuns;
        int msgBase = 5;
        while (runs-- > 0)
        {
            chan << msgBase;
            msgBase++;
            std::lock_guard<std::mutex> guard(coutmutex);
            std::cout << "Task 1 put a msg." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

    });
    std::thread t2([&chan, numRuns, &coutmutex]() -> void
    {
        int res = 0;
        std::uint32_t runs = numRuns;
        while (runs-- > 0)
        {
            chan >> res;
            std::lock_guard<std::mutex> guard(coutmutex);
            std::cout << "Task 2 took a msg: " << res << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

    });
    t1.join();
    t2.join();
}

int main()
{
    std::cout << "[Test 1] Directly instantiating channel... " << std::endl;
    Example1(10);
    std::cout << "[Test 1] Completed. " << std::endl;
    std::cout << "[Test 2] Instantiating channel using make_channel and wrapper-struct... " << std::endl;
    Example2(10);
    std::cout << "[Test 2] Completed. " << std::endl;
    return 0;
}
