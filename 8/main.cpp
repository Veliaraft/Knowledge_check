#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

class Byte{             //main class for byte, parent for u-byte;
    protected:
        typedef vector <bool> base;
        base bit;

    public:
        Byte (base vect = {1, 0, 0, 0, 0, 0, 0, 0} ){//constructor
            bit.reserve(8);
            if (vect.size()>8) vect.erase(vect.begin(),vect.begin()+vect.size()-8);
            bit = vect;
        }
        Byte (const Byte &byte){//copy constructor
            bit.reserve(8);
            bit = byte.bit;
        }
        void SetBit(int BitPos, bool BitState){
            try {
                if(BitPos >=0 && BitPos <8){
                    bit[7-BitPos] = BitState;
                }
                else throw 1;
            }
            catch (int a){
                cout << "error: index out of bounds" << "\n";
            }
        }
        bool GetBit(int BitPos){
            try {
                if(BitPos >=0 && BitPos <8){return bit[7-BitPos];}
                else throw 1;
            }
            catch (int a){
                cout << "error: index out of bounds" << "\n";
                return 0;
            }
        }
        bool No(){ // bitwise not
            for(int i = 0; i < 8; i++) {
                if (bit[i]) {return false;}
            }
            return true;
        }
        Byte And(Byte byte){ //bitwise and
            Byte result;
            for(int i = 0; i < 8; i++) {
                result.bit[i] = bit[i]&&byte.bit[i];
            }
            return result;
        }
        Byte Or (Byte byte){ //bitwise or
            Byte result;
            for(int i = 0; i < 8; i++) {
                result.bit[i] = bit[i]||byte.bit[i];
            }
            return result;
        }
        Byte FullAdder (Byte byte1, bool &overflow, bool &u_overflow){ // full adder
            Byte result;
            bool s, p = 0, p0;
            overflow = 0;
            for(int i = 0; i < 8; i++) {
                p0 = p;
                p = (this->GetBit(i)&& byte1.GetBit(i))||(this->GetBit(i)&&p)|| (byte1.GetBit(i)&&p);
                s = (this->GetBit(i)|| byte1.GetBit(i)||p0)&&!p||(this->GetBit(i)&& byte1.GetBit(i)&&p0);
            result.SetBit(i,s);
            }
            if (p != p0) overflow = 1;
            u_overflow = p;
            return result;
        }
        Byte BitNot(int n) { //bitwise not
            Byte result;
            for(int i = 0; i < n; i++) result.bit[7-i]=!bit[7-i];
            return result;
        }
        Byte ToTwosComplement() {//twos complement
            Byte one ({0,0,0,0,0,0,0,1});
            bool p, p0 = 0;
            if (bit[0]==1) return BitNot(7).FullAdder(one, p, p0);
            else return *this;
        }
        Byte Add(Byte byte, bool &overflow) {//addition of numbers
            Byte result;
            Byte m_one ({1,1,1,1,1,1,1,1});
            bool of, p;
            result = ToTwosComplement().FullAdder(byte.ToTwosComplement(), of, p);
            overflow = of;
            if (result.bit[0] == 1) return result.FullAdder(m_one, of, p).BitNot(7);
            else return result;
        }
        Byte Sub(Byte byte, bool &overflow) {//subtraction of numbers
            Byte byte1;
            byte1 = byte;
            byte1.bit[0] = !byte.bit[0];
            return Add(byte1, overflow);
        }
        void operator = (bool bul){//Overload the "=" operator for Byte and bool;
            for (int i = 0; i < 8; i++){
                bit[i] = 0;
            }
            bit[7] = bul;
        }
        void operator = (base vect){//Overload the "=" operator for Byte and vector;
            if (vect.size()>8) vect.erase(vect.begin(),vect.begin()+vect.size()-8);
            bit = vect;
        }
        friend ostream& operator<< (ostream &out, const Byte &byte);
        friend bool operator ! (Byte byte1);
        friend Byte operator ~ (Byte byte1);
        friend Byte operator & (Byte byte1, Byte byte2);
        friend Byte operator | (Byte byte1, Byte byte2);
        friend Byte operator + (Byte byte1, Byte byte2);
        friend Byte operator - (Byte byte1, Byte byte2);
};
class u_Byte: public Byte{ //unsigned byte
    private:

    public:
        u_Byte (base vect ={0, 0, 0, 0, 0, 0, 0, 0}){
          bit.reserve(8);
          if (vect.size()>8) vect.erase(vect.begin(),vect.begin()+vect.size()-8);
          bit = vect;
        }
        void operator = (Byte byte){//Overload the "=" operator for u_Byte and Byte;
            for (int i = 0; i < 8; i++){
                SetBit(i,byte.GetBit(i));
            }
        }
        friend ostream& operator<< (ostream &out, const u_Byte &byte);
        friend u_Byte operator ~ (u_Byte byte1);
        friend u_Byte operator & (u_Byte byte1, u_Byte byte2);
        friend u_Byte operator | (u_Byte byte1, u_Byte byte2);
        friend u_Byte operator + (u_Byte byte1, u_Byte byte2);
        friend u_Byte operator - (u_Byte byte1, u_Byte byte2);
};

int main(){
    cout << "demo for signed byte:" << "\n";
    Byte b1({0,0,1,0,1,0,1,0,1,0,1,1}), b2({0,0,1,0,0,1,1,0});
    cout << "\n" << "b1: " << b1 << "\n" << "b2: " << b2 << "\n";
    cout << "\n" << "result for b1.SetBit(3,0): " << "\n";
    b1.SetBit(3,0);
    cout << "b1: " << b1 << "\n";
    cout << "\n" << "result for b1.SetBit(12,0): " << "\n";
    b1.SetBit(12,0);
    cout << "\n" << "result for b1.GetBit(8,0): " << "\n";
    cout << b1.GetBit(8)<< "\n";
    cout << "\n" << "result for b1.GetBit(4): " << "\n";
    cout << b1.GetBit(4) << "\n";
    cout << "\n" << "result for b1.GetBit(5): " << "\n";
    cout << b1.GetBit(5) << "\n";
    cout << "\n" << "result for !b1 (logical not): " << "\n";
    cout << !b1 << "\n";
    Byte b({0});
    cout << "\n" << "b: " << b << "\n";
    cout << "result for !b (logical not): " << "\n";
    cout << !b << "\n";
    cout << "\n" << "result for ~b1 (bitwise not): " << "\n";
    cout << "~b1: " << ~b1 << "\n";
    cout << " b1: " << b1 << "\n";
    cout << "\n" << "result for b1&b2: " << "\n";
    cout << "   b1: " << b1 << "\n" << "   b2: " << b2 << "\n";
    cout << "b1&b2: " << (b1&b2) << "\n";
    cout << "\n" << "result for b1|b2: " << "\n";
    cout << "   b1: " << b1 << "\n" << "   b2: " << b2 << "\n";
    cout << "b1|b2: " << (b1|b2) << "\n";
    cout << "\n" << "result for b1+b2: " << "\n";
    cout << "   b1: " << b1 << "\n" << "   b2: " << b2 << "\n";
    cout << "b1+b2: " << b1+b2 << "\n";
    cout << "\n" << "result for b1-b2: " << "\n";
    cout << "   b1: " << b1 << "\n" << "   b2: " << b2 << "\n";
    cout << "b1-b2: " << (b1-b2) << "\n";
    Byte b3({0,1,0,0,1,1,0,1}), b4({0,1,1,0,1,1,1,0});
    cout << "\n" << "result for b3+b4: " << "\n";
    cout << "   b3: " << b3 << "\n" << "   b4: " << b4 << "\n";
    cout << "b3+b4: " << b3+b4 << "\n";
    Byte b5({1,1,0,0,1,1,0,1}), b6({1,1,1,0,1,1,1,0});
    cout << "\n" << "result for b5+b6: " << "\n";
    cout << "   b5: " << b5 << "\n" << "   b6: " << b6 << "\n";
    cout << "b5+b6: " << b5+b6 << "\n";
    cout << "\n" << "result for b3-b6: " << "\n";
    cout << "   b3: " << b3 << "\n" << "   b6: " << b6 << "\n";
    cout << "b3-b6: " << b3-b6 << "\n";
    cout << "\n" << "result for b5-b4: " << "\n";
    cout << "   b5: " << b5 << "\n" << "   b4: " << b4 << "\n";
    cout << "b5-b4: " << b5-b4 << "\n";

    cout << "\n" << "demo for unsigned byte:" << "\n";
    u_Byte u_b1({0,0,0,0,1,1,0,1}), u_b2({1,0,1,0,1,1,1,0});
    cout << "\n" << "b1: " << u_b1 << "\n" << "b2: " << u_b2 << "\n";
    cout << "\n" << "result for b1+b2: " << "\n";
    cout << "   b1: " << u_b1 << "\n" << "   b2: " << u_b2 << "\n";
    cout << "b1+b2: " << u_b1+u_b2 << "\n";
    cout << "\n" << "result for b1-b2: " << "\n";
    cout << "   b1: " << u_b1 << "\n" << "   b2: " << u_b2 << "\n";
    cout << "b1-b2: " << (u_b1-u_b2) << "\n";
    cout << "\n" << "result for b2-b1: " << "\n";
    cout << "   b2: " << u_b2 << "\n" << "   b1: " << u_b1 << "\n";
    cout << "b2-b1: " << (u_b2-u_b1) << "\n";
    u_Byte u_b3({1,1,0,0,1,1,0,1}), u_b4({1,1,1,0,1,1,1,0});
    cout << "\n" << "result for b3+b4: " << "\n";
    cout << "   b3: " << u_b3 << "\n" << "   b4: " << u_b4 << "\n";
    cout << "b3+b4: " << u_b3+u_b4 << "\n";
    system("Pause");
    return 0;
}

bool operator !(Byte byte){ //Overload the '!'(not) operator;
    return byte.No();
}
ostream& operator<< (ostream &out, const Byte &byte){ //Overload the "<<" operator for Byte;
    out << "0b"; int num = 0; out << byte.bit[0];
    int a1 = 1;
    for(int i = 1; i < 8; i++){
        num += a1*byte.bit[8-i];
        a1+= a1;
        out << byte.bit[i];
    } if(byte.bit[0] == 1){ num*=-1; }
    out << " This num is: " << num;
    return out;
}
ostream& operator<< (ostream &out, const u_Byte &byte){ //Overload the "<<" operator for unsigned Byte;
    out << "0b"; int num = 0;
    int a1 = 1;
    for(int i = 0; i < 8; i++){
        num += a1*byte.bit[7-i];
        a1 += a1;
        out << byte.bit[i];
    } out << " This num is: " << num;
    return out;
}
Byte operator ~ (Byte byte1){ //Overload the "~" operator for Byte;
    return byte1.BitNot(8);
}
Byte operator & (Byte byte1, Byte byte2){ //Overload the "&" operator for Byte;
    return byte1.And(byte2);
}
Byte operator | (Byte byte1, Byte byte2){ //Overload the "|" operator for Byte;
    return byte1.Or(byte2);
}
u_Byte operator ~ (u_Byte byte1){ //Overload the "&" operator for u_Byte;
    u_Byte result;
    result = byte1.BitNot(8);
    return result;
}
u_Byte operator & (u_Byte byte1, u_Byte byte2){ //Overload the "&" operator for u_Byte;
    u_Byte result;
    result = byte1.And(byte2);
    return result;
}
u_Byte operator | (u_Byte byte1, u_Byte byte2){ //Overload the "|" operator for u_Byte;
    u_Byte result;
    result = byte1.Or(byte2);
    return result;
}
Byte operator + (Byte byte1, Byte byte2){ //Overload the "+" operator for Byte;
    Byte result;
    bool p;
    result = byte1.Add(byte2, p);
    try {
        if (p>0) throw 100;
        return result;
    }
    catch (int j){
        cout << "error: overflow" << "\n";
        return result;
    }
}
Byte operator - (Byte byte1, Byte byte2){ //Overload the "-" operator for Byte;
    Byte result;
    bool p;
    result = byte1.Sub(byte2, p);
   try {
    if (p>0) throw 100;
    return result;
   }
   catch (int){
    cout << "error: overflow" << "\n";
    return result;
   }
}
u_Byte operator + (u_Byte byte1, u_Byte byte2){ //Overload the "+" operator for u_Byte;
    u_Byte result;
    bool s, p=0, p0;
    result = byte1.FullAdder(byte2, p0, p);
  try {
    if (p>0) throw 100;
    return result;
  }
  catch (int){
    cout << "error: overflow" << "\n";
    return result;
  }
}
u_Byte operator - (u_Byte byte1, u_Byte byte2){ //Overload the "-" operator for u_Byte;
    u_Byte result;
    Byte one ({0,0,0,0,0,0,0,1});
    bool s, p=0, p0;
    result = byte1.FullAdder(byte2.BitNot(8).FullAdder(one,p0,p), p0, p);
  try {
    if (p==0) throw 100;
    return result;
  }
  catch (int){
    cout << "error: overflow" << "\n";
    return result;
  }
}
