#define SetBit(Reg,Bit)         Reg     |=  (1<<Bit)
#define Clear_Bit(Reg,Bit)      Reg     &= ~(1<<Bit)
#define GET_BIT(Reg,Bit)        ( Reg & (1<<Bit) )
#define Toggle_Bit(Reg,Bit)     Reg     ^=  (1<<Bit)