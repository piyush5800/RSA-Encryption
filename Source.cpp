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
  friend ostream & operator << (ostream &out,  number no);
  friend istream & operator >> (istream &in, number &no);
  bool operator <(number num);
  bool operator ==(number num);
  bool operator !=(number num);
  number operator + (number num);
  number multiply4 (long int no1);
  friend number operator -(number num1, number num2);
  friend number operator /(number num1, number num2);
  friend number operator %(number num1, number num2);
  void addZeros(int n);
  number operator * (number num);

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

//Operator equal to Declaration
bool number::operator ==(number num)
{
  if(place<num.place)
  {
    return false;
  }
  if(place>num.place)
  {
    return false;
  }
  //This loop is executed only if the number of places are equal
  for(int i=place-1; i>=0; i--)
  {
    if(no[i]<num.no[i])
      return false;
    else if(no[i]>num.no[i])
      return false;
  }
  return true;
}

//Operator not equal to Declaration
bool number::operator !=(number num)
{
  if(place<num.place)
  {
    return true;
  }
  if(place>num.place)
  {
    return true;
  }
  //This loop is executed only if the number of places are equal
  for(int i=place-1; i>=0; i--)
  {
    if(no[i]<num.no[i])
      return true;
    else if(no[i]>num.no[i])
      return true;
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
number operator -(number num1, number num2)
{
  number ans;
  if(num1<num2)
  {
    ans = num2-num1;
    return ans;
  }
  int carry=0;
  for(int i=0; i<num1.place; i++)
  {
    ans.no[i] = num1.no[i] - num2.no[i] - carry;
    if(ans.no[i] < 0)
    {
      ans.no[i]+=10000;
      carry=1;
    }
    else
    {
      carry=0;
    }
    ans.place++;
  }
  return ans;
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

//Number divide operator Declaration
number operator /(number num1, number num2)
{
  number ans;
  if(num1<num2)
  {
    ans.place++;
    return ans;
  }

  number one, k;
  one.no[0] = 1;
  one.place++;
  while(num2*k<num1)
  {
    k = k+one;
  }
  if((num2*k) == num1)
  {
    return k;
  }
  else
  {
    return k-one;
  }
}

//Number modulo operator Declaration
number operator %(number num1, number num2)
{
  number ans;
  if(num1<num2)
  {
    ans = num1;
    return ans;
  }

  number one, k;
  one.no[0] = 1;
  one.place++;
  while(num2*k<num1)
  {
    k = k+one;
  }
  if((num2*k) == num1)
  {
  }
  else
  {
    k = k-one;
  }
  return num1-(num2*k);
}

number gcd(number num1, number num2)
{
  number zero;
  zero.place++;
  if(num1==zero)
  {
    return num2;
  }
  if(num2==zero)
  {
    return num1;
  }

  if(num1==num2)
  {
    return num1;
  }

  if(num2<num1)
  {
    return gcd(num1-num2, num2);
  }
  else
  {
    return gcd(num1, num2-num1);
  }
}

number modular_expo(number x, number y, number p)
{
  number res;
  res.no[0] = 1;
  res.place++;
  x = x%p;
  number zero;
  zero.place++;
  number two;
  two.no[0] = 2;
  two.place++;
  while(zero<y)
  {
    if((y%two)!=zero)
    {
      res = (res*x)%p;
      //cout<<y%two;
    }

    y = y/two;
    x = (x*x)%p;
    //cout<<res<<"  "<<x<<"  "<<y<<"  "<<p<<endl;
  }
  //cout<<endl;
  return res;
}
//-------------------------------Class Declaration Ends Here-------------------------------------------------
int main()
{
  number p, q;
  cin>>p>>q;
  number n;
  n = p*q;
  number totient;
  number count;
  number one;
  one.no[0] = 1;
  one.place++;
  totient = (p-one) * (q-one);
  number e;
  e.no[0] = 2;
  e.place++;
  while(e<totient)
  {
    count = gcd(e, totient);
    if(count == one)
    {
      break;
    }
    else
    {
      e = e+one;
    }
  }

  number d;
  number k, two;
  two.no[0] = 2;
  two.place++;
  k = two;

  d = (one+(k*totient))/e;
  number msg;
  cin>>msg;
  number c = modular_expo(msg, e, n);
  number m = modular_expo(c, d, n);

  cout<<"Message data = "<<msg;
  cout<<"\n"<<"p = "<<p;
  cout<<"\n"<<"q = "<<q;
  cout<<"\n"<<"n = pq = "<<n;
  cout<<"\n"<<"totient = "<<totient;
  cout<<"\n"<<"e = "<<e;
  cout<<"\n"<<"d = "<<d;
  cout<<"\n"<<"Encrypted data = "<<c;
  cout<<"\n"<<"Original Message sent = "<<m;
  return 0;
}
