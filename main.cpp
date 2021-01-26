
#include <stdio.h>
#include<string>
#include<iostream>
#include "Base32.h"
#include<vector>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
using namespace std;
using namespace cv;

bool base32ToMat(const vector<unsigned char> &x, cv::Mat &decode_img);
char *read_image(const char * path, long &lSize);

int main(int argc, char* argv[])
{
    Base32 * coder=new Base32();

    char * path = "./boat.jpg";

    if(argc > 1)
        path = argv[1];
    cout << "decode image : " << path << endl;

    long lSize;
    unsigned char *img = (unsigned char*)read_image(path, lSize);
    long encodeSize = coder->GetEncode32Length(lSize);
	cout << "original image : " << img << endl;
	cout << "original size : " << lSize << ", encode base32 size : " << encodeSize << endl;
	
    unsigned char *out = (unsigned char *)malloc(encodeSize);
    bool res = coder->Encode32(img, lSize, out);
	cout << "out : " << out << endl;
    if(!res){
        std::cout<<"encode error";
        return 0;
    }
    string ss = (char *)out;
	cout << ss << endl;
    cout << "ss : " << ss.length() << endl;
	long decodeSize =  coder->GetDecode32Length(encodeSize);
    unsigned char *Decode_out = (unsigned char *)malloc(decodeSize);
	
	//cout << "encode base32 size : " << encodeSize << ", decode base32 size : " << decodeSize << endl;
    
	bool decodeFlag = coder->Decode32(out,encodeSize,Decode_out);
    if(!decodeFlag){
        std::cout<<"decode error";
        return 0;
    }

    vector<unsigned char> x;
    x.insert(x.end(), Decode_out, Decode_out+decodeSize);
	cout << "x.size() : " << x.size() << endl;
    cv::Mat resMat;
    if(base32ToMat(x, resMat)) {
        cv::imwrite("./res.jpg", res);
        cout << "write image success\n";
    }


    printf("original length: %d\n", lSize);
    printf("encoded length: %d\n", encodeSize);
    printf("dencoded length: %d\n", coder->GetDecode32Length(encodeSize));

    //free memory
    delete coder;
    return 0;
}

bool base32ToMat(const vector<unsigned char> &x, cv::Mat &decode_img) {

    if(x.empty())
        return false;
    try {
        //
        decode_img = cv::imdecode(x, CV_LOAD_IMAGE_COLOR);
    } catch (cv::Exception &e) {
        cerr << "Caught exception in Base64Converter" << e.msg << endl;
    }

    return !decode_img.empty();
}
char *read_image(const char * path, long &lSize) {
    FILE *pFile;
    char *buffer;
    size_t read_size;

    pFile = fopen(path, "rb");
    if (pFile == NULL) {
        fputs("Open File error", stderr);
        return NULL;
    }

    fseek(pFile, 0, SEEK_END);
    lSize = ftell(pFile);
    rewind(pFile);
    buffer = new char[lSize];
    read_size = fread(buffer, 1, lSize, pFile);
    if (read_size != lSize)
        fputs("Reading error", stderr);
    return buffer;
}

