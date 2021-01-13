#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

/*
taken from
https://stackoverflow.com/questions/4753153/redirecting-stdcout
*/

class Redirect {
    public:
    // arguments: original stream, stream to redirect it to 
        Redirect(std::ostream & inOriginal, std::ostream & inRedirect) :
            mOriginal(inOriginal),
            mRedirect(inRedirect)
            {
                mOriginal.rdbuf(mRedirect.rdbuf(mOriginal.rdbuf()));
            }
            ~Redirect()
            {
                mOriginal.rdbuf(mRedirect.rdbuf(mOriginal.rdbuf()));
            }
    private:
        Redirect(const Redirect&);
        Redirect& operator=(const Redirect&);

        std::ostream & mOriginal;
        std::ostream & mRedirect;
};

int main()
{
    std::cout << "Before redirect." << std::endl;
    std::ofstream filestream("redirected.txt");
    {
        Redirect redirect(std::cout, filestream);
        std::cout << "During redirect." << std::endl;

        // oops:
        filestream << "also to the file, right?...nope" << std::endl;
        filestream << "ah, why am i on the screen?!" << std::endl;
    }
    std::cout << "After redirect." << std::endl;

    // in main, return 0 is implicit, if there is no return statement;
    // helpful to keep in mind in snippets and short things
}