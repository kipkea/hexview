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

void Usage_Text(){
    cout<<"Usage hexview filename [-o Offset] [-l Length]"<<endl;
}
int main(int argc, char** argv) {   
    long File_Offset = 0;
    char *Filename;
    long Data_Length = 0;
    long End_Pos = 0;
    char *buf;
    
    //check parameter
    //for(int i=0;i<argc;i++)
      //  cout<<argv[i]<<endl;
    
    if(argc>1){
        //check filename
        Filename = argv[1];
        //open file
        ifstream f (Filename, ifstream::binary);
               
        if(f){ 
            //cout<<"Open file already"<<endl;
            f.seekg(0,f.end);
            Data_Length = f.tellg();
            f.seekg(0,f.beg);
            buf = new char[Data_Length];
            End_Pos = Data_Length - 1;
            f.read(buf,Data_Length);

            //cout<<"reading "<<Data_Length<<" Characters... Size of Buffer "<<sizeof(buf[0])*Data_Length<<endl;            
        }else{
            Usage_Text();
            return 0;
        };
        
        if(argc>2){
            //cout<<"check Argument"<<endl;
            if(strncmp(argv[2],"-o",2)==0){
                //check offset
                File_Offset = atoi(argv[3]);
                //End_Pos = Data_Length - File_Offset - 1;
                
                if(argc>4){
                    if(strncmp(argv[4],"-l",2)==0){
                        //check length
                        End_Pos = File_Offset + atoi(argv[5]);            
                    }
                }               
            }
        }
        
        //cout<<"Print Hex now ... Offset = "<<File_Offset<<" Data Length = "<<Data_Length<<" End Pos = "<<End_Pos<<endl;
        //print hex
        for(int i = File_Offset; i<=End_Pos; i+=16){
            cout<<setw(6)<<setfill('0')<<hex<<uppercase<<i<<" ";

            for(int j = i; j<i+16; j++){
                if(j>=End_Pos){
                    cout<<"-- ";
                }else{
                    unsigned out = static_cast<unsigned char>(buf[j]);
                    cout<<setfill('0')<<setw(2)<<hex<<uppercase<<out<<" ";
                }
            }

            for(int j = i; j<i+16; j++){
                if(j>=End_Pos){
                    cout<<" ";
                }else{                
                    unsigned out2 = (buf[j]<=0x7e && buf[j]>=0x20)? buf[j]:32;
                    cout<<static_cast<char>(out2);
                }
            } 
                       
            cout<<endl;
        };

        //clear buffer and close file
        delete []buf;
        f.close();
        
    }else{
        Usage_Text();
    }
    
      
    return 0;
}

