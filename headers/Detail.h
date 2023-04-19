#include <string>
using namespace std;

class Detail {
    
    private:

        int Size;
        string Name;
        string MetalType;

    public:
        Detail();
        Detail(int Size, string Name, string MetalType);

        void setSize(int Size);
        int getSize();

        void setName(string Name);
        string getName();

        void setMetalType(string MetalType);
        string getMetalType();
};