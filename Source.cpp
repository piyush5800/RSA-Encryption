#include<iostream>
#include<math.h>
using namespace std;

//----------------------This is the class Declaration that includes basic operations on big numbers-----------------
class number
{
public:
  long int no[400];
  int place;

  //Constructor function
  number()
  {
    place=0;
    for(int i=0; i<400; i++)
      no[i] = 0;
  }

  //Function prototypes
  number operator + (number num);
  number multiply4 (long int no1);
  bool operator <(number num);
  number operator -(number num);
  number operator /(number num);
  number operator %(number num);
  void addZeros(int n);
  number operator * (number num);
  friend ostream & operator << (ostream &out,  number no);
  friend istream & operator >> (istream &in, number &no);


};

//Number Input operator Declaration
ostream & operator <<(ostream &out, number num)
{
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
      out<<num.no[i];
  }
  return out;
}

//Number Output operator declaration
istream & operator >>(istream &in, number &num)
{
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
    num.no[num.place] = ans;
    num.place++;
  }
  return in;
}

//Operator less than Declaration
bool number::operator <(number num)
{
  if(place<num.place)
  {
    return true;
  }
  if(place>num.place)
  {
    return false;
  }
  //This loop is executed only if the number of places are equal
  for(int i=place-1; i>=0; i--)
  {
    if(no[i]<num.no[i])
      return true;
    else if(no[i]>num.no[i])
      return false;
  }
  return false;
}

//Number add operator declaration
number number::operator + (number num)
{
  number res;
  int place1=0, place2=0;
  long int temp=0;

  while(place>=place1 || num.place>=place2)
  {
    temp = no[place1] + num.no[place2] + res.no[res.place];
    int flag=0;
    res.no[res.place] = temp%10000;
    temp/=10000;
    if(temp!=0)
    {
      flag=1;
      res.place++;
      res.no[res.place] = temp%10000;
    }
    if(flag!=1)
      res.place++;
    place1++;
    place2++;
  }
  ++res.place;

  //Checkpoint to remove all the extra zeroes from the beginning
  for(int i=res.place-1; i>=0; i--)
  {
    if(res.no[i]>0)
      break;
    if(res.no[i]==0)
      res.place--;
  }
  return res;
}

//Number subtract operator Declaration
number number::operator -(number num)
{

}

//Number divide operator Declaration
number number::operator /(number num)
{

}
//Number modulo operator Declaration
number number::operator %(number num)
{

}
//Helper function to multiply a 'number' by 4 digit number
number number::multiply4(long int no1)
{
  number res;
  int temp_place2 = 0;

  while(temp_place2<place)
  {
    //Calculates the product of each box of number by no1 and
    //puts it in two (or one) box of result
    long int ans = no1 * no[temp_place2];
    int current = ans+res.no[res.place];
    int flag=0;

    res.no[res.place] = current%10000;
    current/=10000;
    if(current!=0)
    {
      flag=1;
      res.place++;
      res.no[res.place] = current%10000;
    }
    if(flag!=1)
      res.place++;
    temp_place2++;
  }
  ++res.place;

  //To delete extra zeroes
  for(int i=res.place-1; i>=0; i--)
  {
    if(res.no[i]>0)
      break;
    if(res.no[i]==0)
      res.place--;
  }
  return res;
}

//Helper function to add n boxes of zeros at end of each step
//of Multiplication
void number::addZeros(int n)
{
  for(int i=place-1; i>=0; i--)
    no[i+n] = no[i];
  for(int i=0; i<n; i++)
    no[i] = 0;
  return;
}

//Number multiply operator Declaration
number number::operator * (number num)
{
  number res;
  int placet=0;
  while(placet<place)
  {
    number temp;
    temp = num.multiply4(no[placet]);
    temp.addZeros(placet);
    res = res+temp;
    placet++;
  }
  return res;
}


//-------------------------------Class Declaration Ends Here-------------------------------------------------
int main()
{
  number num1, num2;
  cin>>num1>>num2;
  bool ans = num1<num2;
  cout<<ans;
  return 0;
}
