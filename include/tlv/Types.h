#include <vector>
typedef unsigned short WORD;
typedef unsigned char byte;
typedef byte BYTE;
typedef unsigned long DWORD;
typedef DWORD ULONG;
#define DWORD_PTR DWORD
typedef std::vector<BYTE> ByteArray;

#define LOBYTE(w) ((BYTE)(((DWORD_PTR)(w)) & 0xff))
#define HIBYTE(w) ((BYTE)((((DWORD_PTR)(w)) >> 8) & 0xff))
