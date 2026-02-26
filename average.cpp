#include<iostream>
#include<cstdlib>
using namespace std;

int main(int argc,char *argv[]){

    int count=argc-1;
    double sum=0;
    double num=0;

    if(argc==1){
        cout<<"Please input numbers to find average.";
    }else{
        for(int i=0;i<count;i++){
            num=atof(argv[i+1]);
            sum+=num;
        }

        double avg=sum/count;
        cout<<"---------------------------------\n";
        cout<<"Average of "<<count<<" numbers = "<<avg<<"\n";
        cout<<"---------------------------------\n";

    }
    return 0;

}