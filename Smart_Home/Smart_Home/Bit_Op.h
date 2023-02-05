
#ifndef BIT_OP_H_
#define BIT_OP_H_

#define read_bit(x,n) (x&(1<<n))>>n
#define set_bit(x,n) x|=(1<<n)
#define clear_bit(x,n) x&=(~(1<<n))
#define toggle_bit(x,n) x^=(1<<n)


#endif /* BIT_OP_H_ */