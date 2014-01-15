/* 
 * File:   main.cpp
 * Author: kipkea
 *
 * Created on 14 มกราคม 2557, 19:56 น.
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include  <iomanip>

using namespace std;

/*
 * 
 */
string convBase(unsigned long v, long base)
{
	string digits = "0123456789abcdef";
	string result;
	if((base < 2) || (base > 16)) {
		result = "Error: base out of range.";
	}
	else {
		do {
			result = digits[v % base] + result;
			v /= base;
		}
		while(v);
	}
	return result;
}

int main(int argc, char** argv) {
    cout<<"Hello World"<<endl;
    //cout << "0x" << setfill('0') << setw(2) << hex << 10 << endl;
    
    //ifstream f ("/Users/kipkea/nesdev/hexview/test.txt", ifstream::binary);
    ifstream f ("/Users/kipkea/nesdev/hexview/TANK.NES", ifstream::binary);
    
    if(f){ 
        cout<<"Open file already"<<endl;
        f.seekg(0,f.end);
        long length = f.tellg();
        f.seekg(0,f.beg);
        
        char *buf = new char[length];
        
        f.read(buf,length);
        
        cout<<"reading "<<length<<" Characters... Size of Buf "<<sizeof(buf[0])*length<<endl;
                
        
        
        if(f) cout<<"OK"<<endl;
        else cout<<"error"<<endl;
        
        long File_Offset=0;
        
        //print hex
        for(int i = 0; i<=length; i+=16){
            
            unsigned out2 = (buf[i]<=0x7e && buf[i]>=0x20)? buf[i]:20;
            //cout<<convBase(buf[i],16);
            //cout<<setw(6)<<setfill('0')<<i<<endl;
            cout<<setw(6)<<setfill('0')<<hex<<uppercase<<i;
            //cout<<setfill('0')<<setw(2)<<hex<<uppercase<<out<<":"<<dec<<out2<<"]";    
 
            for(int j = i; j<=i+16; j++){
                unsigned out = static_cast<unsigned char>(buf[j]);
                cout<<setfill('0')<<setw(2)<<hex<<uppercase<<out<<" ";
            }
            
            for(int j = i; j<=i+16; j++){
                unsigned out2 = (buf[j]<=0x7e && buf[j]>=0x20)? buf[j]:32;
                cout<<static_cast<char>(out2);
            }            
            //printf("%02x ",static_cast<unsigned char>(buf[i]));
            cout<<endl;
        };
        
        delete[] buf;
        
    } else cout<<"Can't Open file"<<endl;
    
    f.close();
            
    return 0;
}

