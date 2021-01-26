//////////////////////////////////////////////////////////////////////
// Base32.h
//////////////////////////////////////////////////////////////////////

#if !defined(_BASE32_H_)
#define _BASE32_H_

#include <string.h>
#include<string>
#include<vector>
using namespace std;
/*
	Base32 encoding / decoding.
	Encode32 outputs at out bytes with values from 0 to 32 that can be mapped to 32 signs.
	Decode32 input is the output of Encode32. The out parameters should be unsigned char[] of
	length GetDecode32Length(inLen) and GetEncode32Length(inLen) respectively.
    To map the output of Encode32 to an alphabet of 32 characters use Map32.
	To unmap back the output of Map32 to an array understood by Decode32 use Unmap32.
	Both Map32 and Unmap32 do inplace modification of the inout32 array.
	The alpha32 array must be exactly 32 chars long.
*/

struct Base32
{
	static int  GetDecode32Length(int bytes);
	static int  GetEncode32Length(int bytes);

    string Base32Encode(const char *bytes_to_encode, unsigned int in_len);
    vector<unsigned char> Base32Decode(const string &str);
};

#endif
