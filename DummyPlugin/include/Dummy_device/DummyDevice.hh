#ifndef _DUMMY_DEVICE_HH__
#define _DUMMY_DEVICE_HH__

// for tool device base class
#include <BUTool/CommandList.hh>
#include <BUTool/DeviceFactory.hh>

#include <string>
#include <iostream>

#include <Dummy/Dummy.hh>

namespace BUTool {

    class DummyDevice : public CommandList<DummyDevice> {
        public:
            DummyDevice();
            ~DummyDevice();
        private:
            Dummy * myDummy = NULL;

            // update map beteen string and function
            void LoadCommandList();

            // add new commands here
            // instantiates the Dummy obj
            CommandReturn::status Start(std::vector<std::string>, std::vector<uint64_t>);
            // performs a given operation (not working yet)
            CommandReturn::status Operations(std::vector<std::string>, std::vector<uint64_t>);

            // perform the operations individually
            CommandReturn::status Add(std::vector<std::string>, std::vector<uint64_t>);
            CommandReturn::status Subtract(std::vector<std::string>, std::vector<uint64_t>);
            CommandReturn::status Multiply(std::vector<std::string>, std::vector<uint64_t>);

            // add new command (sub command) auto-complete here
            std::string autoComplete_Help(std::vector<std::string> const &, stdLLstring const &, int);
    };

    // register Dummydevice with factory
    RegisterDevice(DummyDevice,    // class Name
                   "Dummy",        // class nickname 
                   "",             // class help
                   "d",            // CLI flag 
                   "dummy",        // CLI full flag 
                   ""              // CLI description
                   );

}   // namespace BUTool

#endif