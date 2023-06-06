#include <iostream>
using namespace std;
bool nand(bool a, bool b)
  {
   if (a == 1 && b==1)
    return false;
  else
     return true;}
// decoder

bool OR(bool a, bool b) {
  return nand(nand(a, a), nand(b, b)); // visada true isskyrus kai abu false
}

bool AND(bool a, bool b) {
  return nand(nand(a, b), nand(a, b));// jeigu a ir b true viskas kita false 
}

bool NOT(bool a) {
  return nand(a, a);//inversija 
}

bool XOR(bool a, bool b) {
  return nand(nand(a, nand(a, b)), nand(b, nand(a, b))); // jeigu skirtingi true jeigu vienodi false
}

bool NOR(bool a, bool b) {  
  return nand(nand(nand(a, a), nand(b, b)),nand(nand(a, a), nand(b, b))); //jeigu a==b==0 kitaip false
}
void half_adder(bool a, bool b, bool& sum, bool& carry) {
  sum = XOR(a,b);
  carry = AND(a,b);
  }
void full_adder(bool a, bool b, bool carryin, bool& sum, bool& carryout) {
    bool sum1, sum2, carry1, carry2;
    half_adder(a, b, sum1, carry1);
    half_adder(sum1, carryin, sum2, carry2);
    sum = sum2;
    carryout = OR(carry1, carry2);
}

void suma2(bool a[], bool b[], bool result[]) {  //adder 
    bool carry = 0;
    for (int i = 7; i >= 0; i--) {
        bool sum, carryout;
        full_adder(a[i], b[i], carry, sum, carryout);
        result[i] = sum;
        carry = carryout;
    }
  if (a[0] == b[0] && result[0] != a[0]) {
        cout<<"Ivyko overflow";
    } 
  else
    for (int i = 0; i < 8; i++)
        cout << result[i] << " ";
}
void suma1(bool a[], bool b[], bool result[]) {
    // padaryt invertuota sudeti su praeitu skaicium ir overflow 
     for (int i=0; i<8; i++)
      b[i]=NOT(b[i]); 
    bool carry = false;
    bool g[8]={0,0,0,0,0,0,0,1};
  
    for (int i = 7; i >= 0; i--) {
        bool sum, carryout;
        full_adder(b[i], g[i], carry, sum, carryout);
        result[i] = sum;
        carry = carryout;
    }
    carry = 0;
    for (int i = 7; i >= 0; i--) {
        bool sum, carryout;
        full_adder(a[i], result[i], carry, sum, carryout);
        b[i] = sum;
        carry = carryout;
    }
    for (int i = 0; i < 8; i++)
        cout << b[i] << " ";}

void suma4(bool a[], bool result[]){
bool c = 1;
result[0]=AND(NOT(c),a[6]);
result[1]=OR(AND(a[7],c), AND(NOT(c),a[5]));
result[2]=OR(AND(NOT(c),a[4]), AND(a[6],c));
result[3]=OR(AND(a[5],c),AND(a[3],NOT(c)));
result[4]=OR(AND(a[4],c),AND(a[2],NOT(c)));
result[5]=OR(AND(a[3],c),AND(a[1],NOT(c)));
result[6]=OR(AND(a[2],c),AND(a[0],NOT(c)));
result[7]=AND(a[1],c);
   if (a[0] == 1) {
        cout<<"Ivyko overflow";
    } 
  else
  for (int i=7; i>=0; i--)
    cout<<result[i]<<" ";
}
void suma5(bool a[],bool result[]){
   bool g[8]={1,1,1,1,1,1,1,1};
  bool carry=false;
  for (int i = 7; i >= 0; i--) {
        bool sum, carryout;
        full_adder(a[i], g[i], carry, sum, carryout);
        result[i] = sum;
        carry = carryout;
    }
  for (int i=0; i<8; i++)
    cout<<result[i]<<" ";
}
void suma6(bool b[])
{
  short a=0;
  for (int i=0; i<8; i++)
  if (b[i]!=0)
  a++;
  if (a==0)
  cout<<"NO";
  if (a>0)
  cout<<"YES";
}

int main() {
 bool result[8];
 bool s[3];
 bool a[8]={1,1,0,0,1,0,1,1};
 bool b[8]={0,0,0,0,0,0,0,0};
  cin>>s[0]>>s[1]>>s[2];
if (AND(NOR(s[0],s[1]),NOT(s[2]))) // 0 0 0
  {
    suma1(a,b,result);
  }
 if (AND(NOR(s[0],s[1]),s[2])) // 0 0 1
  {
    suma2(a,b,result);
  }
 if (AND(NOR(s[0], NOT(s[1])), NOT(s[2]))) // 010 
 {

 }
if (AND(NOR(s[0], NOT(s[1])), (s[2]))) // 011
  {
  suma4(a,result);
  }
if (AND(NOR(NOT(s[0]), s[1]), NOT(s[2])))// 100
  {
    suma5(a,result);
  }
if (AND(NOR(NOT(s[0]), (s[1])), (s[2]))) // 101
  {
    suma6(b);
  }
    return 0;
}