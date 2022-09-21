#pragma once

#include "SwelveDeclarations.hpp"
#include "SwelveUtils.hpp"

#include <Windows.h>
#include <iostream>
#include <functional>
#include <vector>

namespace swelve
{

    class SwelveInstance
    {
    public:
        SwelveInstance();
        virtual ~SwelveInstance();

        virtual SwelveReader* CreateReader();
        virtual SwelveWriter* CreateWriter();

        virtual bool ParseExtension(SwelveStream& extensionStream);
        virtual bool AppendExtension(SwelveExtension* extension);

    public:
        std::vector<SwelveExtension*> *swelveExtensionList;
    };

}