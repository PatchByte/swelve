#pragma once

#include <Windows.h>
#include <iostream>
#include <functional>

namespace swelve
{
    class SwelveExtension;
    class SwelveSupport;
    class SwelveInput;
    class SwelveLoader;

    using SwelveHash = uint64_t;

    class SwelveInput
    {
    public:
        virtual void Acquire(std::vector<uint8_t>& output) = 0;
        virtual void Release() = 0;
        virtual SwelveHash GetInputHash() = 0;
    };

    class SwelveSupport
    {
    public:
        virtual SwelveHash GetExtensionHash() = 0;
        virtual void Handle(SwelveInput* input) = 0;
    };

    class SwelveExtension
    {
    public:
        virtual const char* GetName() = 0;
        virtual const char* GetDescription() = 0;
        virtual void Handle() = 0;
    };

    class SwelveLoader
    {
    public:
        virtual void RegisterSupport(SwelveSupport* support) = 0;
        virtual void HandleExtension(SwelveExtension* extension) = 0;
        virtual void HandleInput(SwelveInput* input) = 0;
    };

}