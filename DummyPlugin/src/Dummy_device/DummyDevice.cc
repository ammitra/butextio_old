#include <DummyDevice/DummyDevice.hh>

#include<string>
#include <iostream>

using namespace BUTool;

DummyDevice::DummyDevice()
    : CommandList<DummyDevice>("Dummy"),
    myDummy(NULL) {
        //constructor takes NO arguments
        //setup commands
        LoadCommandList();
    }

    DummyDevice::~DummyDevice() {
        if (myDummy) {
            delete myDummy;
        }
    }

    void DummyDevice::LoadCommandList() {
        // general commands (launcher commands)
        AddCommand("start",&DummyDevice::Start,
                   "instantiates the dummy\n" \
                   "Usage: \n"                \
                   " start\n");
        AddCommandAlias("s","start");

        AddCommand("operations",&DummyDevice::Operations,
                   "performs addition, subtraction, multiplication \n" \
                   "Usage: \n"                                         \
                   " operations\n");
        AddCommandAlias("o","operations");
    }

    CommandReturn::status DummyDevice::Start(std::vector<std::string>,std::vector<uint64_t>) {
        if (myDummy) {
            printf("dummy already created");
            return CommandReturn::OK;
        }
        /*
        try {
            myDummy = new Dummy();
        }
        */
    }

    CommandReturn::status DummyDevice::Operations(std::vector<std::string> strArg,std::vector<uint64_t> intArg) {
        // strArg = "add", "subtract", or "multiply"
        // intArg = two integers (floats)

        if (!myDummy) {
            printf("dummy not yet created");
            return CommandReturn::OK;
        }


        if (strArg.size() != 1) {
            // need 1 string argument (which command to use)
            return CommandReturn::BAD_ARGS;
        }

        if (intArg.size() != 2) {
            // need exactly 2 numbers
            return CommandReturn::BAD_ARGS;
        }

        // work out different cases
        if (strArg[0] == "add") {
            myDummy->add();
        }
        else if (strArg[0] == "subtract") {
            myDummy->subtract();
        }
        else if (strArg[0] == "multiply") {
            myDummy->multiply();
        }

        return CommandReturn::OK;
    }

