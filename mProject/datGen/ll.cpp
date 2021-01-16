#include <iostream>
using namespace std;

#define NUM_DATA 3001
#define DIVEDPART 8
#define DIVEDPARTARR DIVEDPART+2

void dividedArr(int st,int numSam,int numDiv,int *arr);

int main(int argc,char **argv)
{
    int st1=0;
    int index=0;
    int l1=0;
    int st2=0;
    int l2=NUM_DATA;
    char isOddNum =(NUM_DATA%2==1);
    int halfPart =DIVEDPART/2;
    int halfPart2 = DIVEDPART-halfPart;
    int arrDivied[DIVEDPARTARR];
    int numSamHalf=0;
    if(isOddNum==1)
    {
        l1 = NUM_DATA/2;
        st2 = l1+1;
        numSamHalf = (NUM_DATA-1)/2;
    }
    else 
    {
        l1 = (NUM_DATA/2)-1;
        l1 = (l1>0)*l1;
        st2 = l1+2;
        numSamHalf = (NUM_DATA-2)/2;
    }
    arrDivied[0]=0;
    arrDivied[DIVEDPARTARR-1]=NUM_DATA;
    arrDivied[halfPart2+1]=st2;
    cout<<"str1 :"<<st1<<" l1:"<<l1;
    cout<<" str2:"<<st2<<" l2:"<<l2<<endl;
    cout<<"h1:"<<halfPart<<endl;
    cout<<"h2:"<<halfPart2<<endl;

    dividedArr(1,numSamHalf,halfPart2,arrDivied);
    dividedArr(halfPart2+2,numSamHalf,halfPart,arrDivied);
    for(index =0;index<DIVEDPARTARR;index++)
    {
        cout<<"i :"<<index<<" :"<<arrDivied[index]<<endl;
    }
    return 0;
}

void dividedArr(int st,int numSam,int numDiv,int *arr)
{
    int partSize = numSam/numDiv;
    int fraction = numSam%numDiv;
    int index=0; 
    int endP = st+numDiv;
    cout<<"st :"<<st<<" numSam:"<<numSam<<" numD:"<<numDiv<<" fc:"<<fraction<<endl;
    for(index=st;index<endP;index++)
    {
        arr[index] = arr[index-1]+partSize+(fraction>0);
        fraction--;
    } 
}