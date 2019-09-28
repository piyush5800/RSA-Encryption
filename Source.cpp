#include<iostream>
#include<math.h>
using namespace std;

class number
{
public:
  long int no[400];
  int place;

  number()
  {
    place=0;
    for(int i=0; i<400; i++)
    {
      no[i] = 0;
    }
  }
  friend ostream & operator << (ostream &out,  number no);
  friend istream & operator >> (istream &in, number &no);

};

ostream & operator <<(ostream &out, number num)
{
  //cout<<"output called";
  for(int i=num.place-1; i>=0; i--)
  {
    if(num.no[i]/10==0)
    {
      cout<<"000";
      out<<num.no[i];
    }
    else if(num.no[i]/100==0)
    {
      cout<<"00";
      out<<num.no[i];
    }
    else if(num.no[i]/1000==0)
    {
      cout<<"0";
      out<<num.no[i];
    }
    else
    {
      out<<num.no[i];
    }
  }
  return out;
}

istream & operator >>(istream &in, number &num)
{
  //cout<<"Input called";
  char str[500];
  cin>>str;
  for(int i=strlen(str)-1; i>=0;)
  {
    int power=0;
    long int ans=0;
    while(power<=3)
    {
      int digit=0;
      if(i>=0)
        digit = str[i]-'0';
      else
        digit = 0;
      long int temp = digit*pow(10, power);
      ans+=temp;
      power++;
      i--;
    }
    //cout<<ans<<"  ";
    num.no[num.place] = ans;
    //cout<<num.no[num.place]<<"  ";
    num.place++;
    //cout<<num.place<<"  ";
  }
  return in;
}


int main()
{

  return 0;
}
