#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "simStringList.h"
#include "convertStr2Digi.h"
#include "simMatChar.h"
#include "listChar.h"
#include "simReadXML.h"

/* XML DEFINED */

#define         DEF_CHEAP_STOCK                                         "CHEAP_STOCK"
#define         DEF_EXPENSIVE_STOCK                                   "EXPENSIVE_STOCK"
#define         DEF_LIMIT_DAY_TO_GET_THE_INCOME             "LIMIT_DAY_TO_GET_THE_INCOME"
#define         DEF_THE__MIN_NUMBER_OF_STOCK_TO_BUY    "THE__MIN_NUMBER_OF_STOCK_TO_BUY"
#define         DEF_THE__MAX_NUMBER_OF_STOCK_TO_BUY    "THE__MAX_NUMBER_OF_STOCK_TO_BUY"
#define         DEF_START_MONEY                                        "START_MONEY"
#define         DEF_INCOME_EXPECT_PER_DAY                        "INCOME_EXPECT_PER_DAY"
#define         DEF_MAX_TO_LOSS                                         "MAX_TO_LOSS"
#define         DEF_MAX_TO_GET                                          "MAX_TO_GET"
#define         DEF_EXPECT_PERCENT_TO_SELL                       "EXPECT_PERCENT_TO_SELL"
#define         DEF_REMAIN_STOCK_MIN                                "REMAIN_STOCK_MIN"
#define         DEF_REMAIN_STOCK_MAX                                "REMAIN_STOCK_MAX"
#define         DEF_KEEP_IN_PORT                                         "KEEP_IN_PORT"
#define         FILE_NAME_XML "StockCalForMe.xml"
struct expectVal
{
    int limitDayToCome;
    int MyMoney;
    int incomeExpect;
    double percentToKeepInport;
    double profitToSellPerDay;
};
struct stockConst
{
    double stockPriceMin;
    double stockPriceMax;
    int minStocktoBuy;
    int maxStocktoBuy;
    double MaxpercentLoss;
    double MaxpercentGet;
    double percentStockToKeepMin;
    double percentStockToKeepMax;
};
typedef struct expectVal expectVal;
typedef struct stockConst stockConst;
double randomValue(double min,double max);
int getDataFromXML(char* filename,expectVal* exVal,stockConst* stcConst,int isPrintResult);
void printStockConst(stockConst* stockConstObj);
void printExpectVal(expectVal* expectValObj);
int calWork(stockConst* stockConstObj,expectVal* expectValObj,double* remainStock,double* moneyPort,double* moneyInAccount);
int calStockWantToBut(double currentPriceStock,double currnetMoney,int minNumberToBuy,int maxNumberToBuy);
int main(int argc,char** argv)
{
    int res =0;
    expectVal expVal;
    stockConst stcConst;
    double remainStock=0;
    double moneyPort=0;
    double moneyInAccount=0;
    
    /* initialize random seed: */
    srand (time(NULL));
    
    res =getDataFromXML(FILE_NAME_XML,&expVal,&stcConst,0);
    res = res&&calWork(&stcConst,&expVal,&remainStock,&moneyPort,&moneyInAccount);
    printf("remain stock : %f \n",remainStock);
    printf("remain money in port  : %f \n",moneyPort);
    printf("remain money in account  : %f \n",moneyInAccount); 
    printf("res : %d \n",res);
    return 0;
}
 
double randomValue(double min,double max)
{
    return max + (rand() / ( RAND_MAX / (min-max)));
}
int getDataFromXML(char* filename,expectVal* exVal,stockConst* stcConst,int isPrintResult)
{
    int res = 0;
    treeXML tXML;
    char fact1 = (filename!=NULL)&&(exVal!=NULL)&&(stcConst!=NULL);
    fact1 = fact1&&getSourceToTreeXML(&tXML,filename);//,const char *defaultStr,void *var,unsigned int typeVar);
    if(fact1 ==1)
    {
        res =1;
        res = res&&getValueOfFirstChildEle2Var(tXML.root,DEF_CHEAP_STOCK,"0.5",&(stcConst->stockPriceMin),0x050); /* double */
        res = res&&getValueOfFirstChildEle2Var(tXML.root,DEF_EXPENSIVE_STOCK,"10",&(stcConst->stockPriceMax),0x050); /* double */
        res = res&&getValueOfFirstChildEle2Var(tXML.root,DEF_LIMIT_DAY_TO_GET_THE_INCOME,"400",&(exVal->limitDayToCome),0x010); /* int */
        res = res&&getValueOfFirstChildEle2Var(tXML.root,DEF_THE__MIN_NUMBER_OF_STOCK_TO_BUY,"500",&(stcConst->minStocktoBuy),0x010); /* int */
        res = res&&getValueOfFirstChildEle2Var(tXML.root,DEF_THE__MAX_NUMBER_OF_STOCK_TO_BUY,"10000",&(stcConst->maxStocktoBuy),0x010); /* int */
        res = res&&getValueOfFirstChildEle2Var(tXML.root,DEF_START_MONEY,"5000",&(exVal->MyMoney),0x010); /* int */
        res = res&&getValueOfFirstChildEle2Var(tXML.root,DEF_INCOME_EXPECT_PER_DAY,"1000",&(exVal->incomeExpect),0x010); /* int */
        res = res&&getValueOfFirstChildEle2Var(tXML.root,DEF_MAX_TO_LOSS,"50",&(stcConst->MaxpercentLoss),0x050); /* double */
        res = res&&getValueOfFirstChildEle2Var(tXML.root,DEF_MAX_TO_GET,"50",&(stcConst->MaxpercentGet),0x050); /* double */
        res = res&&getValueOfFirstChildEle2Var(tXML.root,DEF_EXPECT_PERCENT_TO_SELL,"15",&(exVal->profitToSellPerDay),0x050); /* double */
        res = res&&getValueOfFirstChildEle2Var(tXML.root,DEF_REMAIN_STOCK_MIN,"20",&(stcConst->percentStockToKeepMin),0x050); /* double */
        res = res&&getValueOfFirstChildEle2Var(tXML.root,DEF_REMAIN_STOCK_MAX,"30",&(stcConst->percentStockToKeepMax),0x050); /* double */
        res = res&&getValueOfFirstChildEle2Var(tXML.root,DEF_KEEP_IN_PORT,"45",&(exVal->percentToKeepInport),0x050); /* double */
    }
    else
    {
        /* do nothing */
    }
    if((res ==1)&&(isPrintResult==1))
    {
        printStockConst(stcConst);
        printExpectVal(exVal);
    }
    else
    {
        /* do nothing */
    }
    return res;
}
void printStockConst(stockConst* stockConstObj)
{
    if(stockConstObj != NULL)
    {
        printf("stock min-max         :%f - %f \n",stockConstObj->stockPriceMin,stockConstObj->stockPriceMax);
        printf("buy stock min-max   :%d - %d \n",stockConstObj->minStocktoBuy,stockConstObj->maxStocktoBuy);
        printf("stock profit - loss      :%f - %f \n",stockConstObj->MaxpercentGet,stockConstObj->MaxpercentLoss);
        printf("keep stock min - max:%f - %f \n",stockConstObj->percentStockToKeepMin,stockConstObj->percentStockToKeepMax);
    }
    else
    {
        /* do nothing */
    }
}
void printExpectVal(expectVal* expectValObj)
{
    if(expectValObj != NULL)
    {
        printf("limit Dat to Come       : %d \n",expectValObj->limitDayToCome);
        printf("Money                     : %d \n",expectValObj->MyMoney);
        printf("income Expect           : %d \n",expectValObj->incomeExpect);
        printf("Keep stock in percent  : %f \n",expectValObj->percentToKeepInport);
        printf("Profit to sell in percent : %f \n",expectValObj->profitToSellPerDay);
    }
    else
    {
        /* do nothing */
    }
}

int calWork(stockConst* stockConstObj,expectVal* expectValObj,double* remainStock,double* moneyPort,double* moneyInAccount)
{
    double currentStockPrince =0;
    double currentMoney = 0;
    int numStockToBuy = 0;
    int res =(stockConstObj!=NULL)&&(expectValObj!=NULL)&&(remainStock!=NULL)&&(moneyPort!=NULL)&&(moneyInAccount!=NULL);
    if(res ==1)
    {
        currentMoney = expectValObj->MyMoney;
        currentStockPrince =randomValue(stockConstObj->stockPriceMin,stockConstObj->stockPriceMax);
        numStockToBuy = calStockWantToBut(currentStockPrince,currentMoney,stockConstObj->minStocktoBuy,stockConstObj->maxStocktoBuy);
        
        
        currentMoney =currentMoney- numStockToBuy*currentStockPrince;
        printf("cM:%f | StPr:%f | numStc:%d\n",currentMoney,currentStockPrince,numStockToBuy);
    }
    else
    {
        /* do nothing */
    }
    return 0;
}
int calStockWantToBut(double currentPriceStock,double currnetMoney,int minNumberToBuy,int maxNumberToBuy)
{
    int maxNumberCanBuy = 0;
    int res = (maxNumberToBuy>=minNumberToBuy)&&(minNumberToBuy>-1)&&(currnetMoney>0)&&(currentPriceStock>0);
    double dummyDouble = 0;
    double dummyDouble2 = 0;
    if(res ==1)
    {
        maxNumberCanBuy = (int)(currnetMoney/currentPriceStock);
        if(maxNumberCanBuy > maxNumberToBuy)
        {
            dummyDouble = maxNumberToBuy;
        }
        else
        {
            dummyDouble = maxNumberCanBuy;
        }
        if(maxNumberCanBuy > minNumberToBuy)
        {
            dummyDouble2 = minNumberToBuy;
        }
        else
        {
            dummyDouble2 = maxNumberCanBuy;
        }
        dummyDouble = randomValue(dummyDouble2,dummyDouble);
        if(dummyDouble < minNumberToBuy)
        {
            dummyDouble =0;
        }
        else
        {
            /* do nothing */
        }
        res = (int)dummyDouble;
        res = 100*(res/100);
    }
    else
    {
        /* do nothing */
    }
    return res;
}